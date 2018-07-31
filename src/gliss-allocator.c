/*
 * This file is a part of Gliss
 *
 * Copyright (C) 2010:
 *
 *  Michael Dominic K. <mdk@mdk.am>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gliss-allocator.h"

static glissInternalChunk*
newChunk (void)
{
    glissInternalChunk *chunk = malloc (sizeof (glissInternalChunk));
    chunk->iterator = 0;
    chunk->freed = 0;

    memset (chunk->data, 0, sizeof (void *) * GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY);

    return chunk;
}

static GLuint
allocateNewOnChunk (glissInternalChunk *chunk,
                    GLint size,
                    void **object)
{
    *object = malloc (size);
    chunk->data [chunk->iterator] = *object;

    chunk->iterator++;

    return chunk->iterator - 1;
}

static GLint
findFreeChunk (glissInternalAllocator *allocator)
{
    int i;
    for (i = 0; i < allocator->chunksSize; i++) {
        if (allocator->chunks [i] == NULL)
            return i;

        if (allocator->chunks [i]->iterator < GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY)
            return i;
    }

    return -1;
}

static void
resizeChunks (glissInternalAllocator *allocator)
{
    GLsizei oldChunksSize = allocator->chunksSize;
    allocator->chunksSize = allocator->chunksSize + GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE;
    if (allocator->chunks)
        allocator->chunks = realloc (allocator->chunks, sizeof (void *) * (allocator->chunksSize));
    else
        allocator->chunks = malloc (sizeof (void *) * (allocator->chunksSize));

    memset (allocator->chunks + oldChunksSize, 0, GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE * sizeof (void *));
}

GLISS_INTERNAL void
glissInternalAllocatorInit (glissInternalAllocator *allocator)
{
    allocator->chunksSize = GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE;
    allocator->chunks = malloc (sizeof (void *) * GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE);
    memset (allocator->chunks, 0, sizeof (void *) * GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE);

    allocator->allocatorChunk = 0;
}

GLISS_INTERNAL GLuint
glissInternalAllocatorNew (glissInternalAllocator *allocator,
                           GLsizei size,
                           void **object)
{
    /* If we don't have an allocator chunk, find one now */
    if (allocator->allocatorChunk == -1) {
        allocator->allocatorChunk = findFreeChunk (allocator);

        /* If we still don't have the allocator chunk, we need
         * to resize the chunks array */
        if (allocator->allocatorChunk == -1) {
            allocator->allocatorChunk = allocator->chunksSize;
            resizeChunks (allocator);
        }
    }

    /* The chunk might not be yet initialized */
    if (allocator->chunks [allocator->allocatorChunk] == NULL) {
        allocator->chunks [allocator->allocatorChunk] = newChunk ();
    }

    glissInternalChunk *chunk = allocator->chunks [allocator->allocatorChunk];

    GLuint baseId = allocator->allocatorChunk * GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY;
    GLuint chunkId = allocateNewOnChunk (chunk, size, object);

    /* Check if chunk has run out of slots */
    if (chunk->iterator == GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY) {
        /* Try to move to the next chunk */
        if (allocator->allocatorChunk + 1 < allocator->chunksSize) {
            if (allocator->chunks [allocator->allocatorChunk + 1] == NULL ||
                allocator->chunks [allocator->allocatorChunk + 1]->iterator < GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY)
                allocator->allocatorChunk++;
        } else {
            /* Will need to find one next time */
            allocator->allocatorChunk = -1;
        }
    }

    return baseId + chunkId + 1;
}

GLISS_INTERNAL void*
glissInternalAllocatorResolve (glissInternalAllocator *allocator,
                               GLuint id)
{
    if (id == 0)
        return NULL;

    id--;

    GLuint baseId = id / GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY;

    /* Initial check for invalid ID */
    if (baseId > allocator->chunksSize || allocator->chunks [baseId] == NULL)
        return NULL;

    GLuint chunkId = id % GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY;

    return allocator->chunks [baseId]->data [chunkId];
}

GLISS_INTERNAL void*
glissInternalAllocatorResolveAndFree (glissInternalAllocator *allocator,
                                      GLuint id)
{
    if (id == 0)
        return NULL;

    id--;

    GLuint baseId = id / GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY;

    /* Initial check for invalid ID */
    if (baseId > allocator->chunksSize || allocator->chunks [baseId] == NULL)
        return NULL;

    GLuint chunkId = id % GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY;

    void *data = allocator->chunks [baseId]->data [chunkId];

    if (data != NULL) {
        glissInternalChunk *chunk = allocator->chunks [baseId];
        chunk->data [chunkId] = NULL;
        chunk->freed++;

        /* Let's see if we need to free the chunk completely... */
        if (chunk->freed == GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY) {
            free (chunk);
            allocator->chunks [baseId] = NULL;
        }

        return data;
    } else
        return NULL;
}


