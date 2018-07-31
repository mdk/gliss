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

#include <stdlib.h>
#include <stdio.h>
#include "gliss-list.h"
#include "gliss-test-common.h"

GLdouble vals [10];

void
createVals (void)
{
    vals [0] = 0.5f;
    vals [1] = 0.8f;
    vals [2] = 0.1f;
    vals [3] = 0.2f;
    vals [4] = 1.0f;
    vals [5] = 0.22f;
    vals [6] = 0.33f;
    vals [7] = 0.11f;
    vals [8] = 0.01f;
    vals [9] = 0.99f;
}

GLint
cmpVals (GLdouble *a,
         GLdouble *b)
{
    if (*a > *b)
        return 1;
    else if (*a < *b)
        return -1;
    else
        return 0;
}

glissInternalList*
createList (glissInternalList *list,
            glissInternalSlice *slice)
{
    int i;

    for (i = 0; i < 10; i++) {
        list = glissInternalListAppendSorted (list, slice, &vals [i], cmpVals);
    }

    return list;
}

int
verifyList (glissInternalList *list)
{
    float min = 0.0;
    glissInternalList *iterator = list;

    while (iterator) {
        if (*((GLdouble *) iterator->data) < min)
            return -1;

        min = *((GLdouble *) iterator->data);
        iterator = iterator->next;
    }

    return 1;
}

int
main (int argc,
      char **argv)
{
    glissInternalSlice slice;
    glissInternalList *list = NULL;

    glissInternalSliceInit (&slice, sizeof (glissInternalList), 10);

    createVals ();
    list = createList (list, &slice);

    if (verifyList (list) != 1) {
        glissTestPrintFailure ("Sorted list verification failed");
        return 128;
    }

    glissInternalSliceDestroy (&slice);

    return 0;
}

