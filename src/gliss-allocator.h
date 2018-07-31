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

#ifndef ___GLISS_ALLOCATOR_H___
#define ___GLISS_ALLOCATOR_H___

#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"

#define GLISS_INTERNAL_ALLOCATOR_INITIAL_CHUNKS_SIZE 10

#define GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY 128

struct _glissInternalChunk {

    GLuint iterator;
    GLuint freed;
    void* data [GLISS_INTERNAL_ALLOCATOR_CHUNK_CAPACITY];
};

struct _glissInternalAllocator {

    GLsizei chunksSize;
    GLint allocatorChunk;
    glissInternalChunk** chunks;
};

GLISS_INTERNAL void
glissInternalAllocatorInit (glissInternalAllocator *allocator);

GLISS_INTERNAL GLuint
glissInternalAllocatorNew (glissInternalAllocator *allocator,
                           GLsizei size,
                           void **object);

GLISS_INTERNAL void*
glissInternalAllocatorResolve (glissInternalAllocator *allocator,
                               GLuint id);

GLISS_INTERNAL void*
glissInternalAllocatorResolveAndFree (glissInternalAllocator *allocator,
                                      GLuint id);

#endif

