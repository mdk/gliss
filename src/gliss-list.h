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

#ifndef ___GLISS_LIST_H___
#define ___GLISS_LIST_H___

#include <stdlib.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-slice.h"

struct _glissInternalList {

    glissInternalList *next;
    glissInternalList *prev;
    GLint type;
    GLvoid *data;
};

GLISS_INTERNAL glissInternalList*
glissInternalListPrepend (glissInternalList *list,
                          glissInternalSlice *slice,
                          GLvoid *data);

GLISS_INTERNAL glissInternalList*
glissInternalListPrependWithType (glissInternalList *list,
                                  glissInternalSlice *slice,
                                  GLint type,
                                  GLvoid *data);

GLISS_INTERNAL glissInternalList*
glissInternalListPrependUnique (glissInternalList *list,
                                glissInternalSlice *slice,
                                GLvoid *data);

GLISS_INTERNAL glissInternalList*
glissInternalListAppendSorted (glissInternalList *list,
                               glissInternalSlice *slice,
                               GLvoid *data,
                               GLint (*cmpFunction) (void*, void*));

GLISS_INTERNAL glissInternalList*
glissInternalListReverse (glissInternalList *list);

GLISS_INTERNAL glissInternalList*
glissInternalListLast (glissInternalList *list);

GLISS_INTERNAL glissInternalList*
glissInternalListRemoveLink (glissInternalList *list,
                             glissInternalList *link);

GLISS_INTERNAL GLint
glissInternalListCount (glissInternalList *list);

GLISS_INTERNAL glissInternalList*
glissInternalListMerge (glissInternalList *listA,
                        glissInternalList *listB);

GLISS_INTERNAL glissInternalList*
glissInternalListMergeWithoutDestroy (glissInternalList *listA,
                                      glissInternalList *listB,
                                      glissInternalSlice *listSlice);

#endif

