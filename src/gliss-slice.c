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

#include "gliss-slice.h"

/* Free all data allocated by slice. Iterates over all memory
 * chunks and frees them. */
GLISS_INTERNAL void
glissInternalSliceDestroy (glissInternalSlice *slice)
{
    GLvoid *currentPointer = slice->firstSlice;

    while (currentPointer) {
        GLvoid **v = currentPointer + (slice->elementSize * slice->elementsPerSlice);
        GLvoid *next_pointer = *v;
        free (currentPointer);
        currentPointer = next_pointer;
    }
}

/* Initialize the slice struct for usage. */
GLISS_INTERNAL void
glissInternalSliceInit (glissInternalSlice *slice,
                        GLint elementSize,
                        GLint elementsPerSlice)
{
    slice->firstSlice = malloc ((elementSize * elementsPerSlice) + (sizeof (GLvoid *)));
    slice->elementsLeft = elementsPerSlice;
    slice->elementSize = elementSize;
    slice->elementsPerSlice = elementsPerSlice;
    slice->iterator = slice->firstSlice;

    /* Initially NULL'ify the next pointer */
    GLvoid **v = slice->firstSlice + (slice->elementSize * slice->elementsPerSlice);
    *v = NULL;
}

/* Get a pointer to new element AKA make the slice allocate
 * new struct. Grows automatically. */
GLISS_INTERNAL GLvoid*
glissInternalSliceNewElement (glissInternalSlice *slice)
{
    GLvoid *newPointer;

    /* If we have no elements left, we need to allocate
     * a new data chunk and link the current data chunk to the
     * new one. */

    if (slice->elementsLeft == 0) {
        GLvoid **next_one = slice->iterator;
        *next_one = malloc ((slice->elementSize * slice->elementsPerSlice) + sizeof (GLvoid *));
        slice->iterator = *next_one;
        slice->elementsLeft = slice->elementsPerSlice;

        /* Initially NULL'ify the next pointer */
        GLvoid **v = slice->firstSlice + (slice->elementSize * slice->elementsPerSlice);
        *v = NULL;
    }

    slice->elementsLeft--;
    newPointer = slice->iterator;
    slice->iterator += slice->elementSize;

    return newPointer;
}

