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

#ifndef ___GLISS_LINE_ACCUMULATOR_H___
#define ___GLISS_LINE_ACCUMULATOR_H___

#include <stdlib.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-state.h"
#include "gliss-list.h"
#include "gliss-slice.h"
#include "gliss-elements.h"
#include "gliss-path.h"
#include "gliss-math.h"
#include "gliss.h"

struct _glissInternalLineAccumulator {

    GLdouble startX;
    GLdouble startY;
    GLdouble currentX;
    GLdouble currentY;
    GLint lineCount;
    glissInternalList *list;
    glissInternalSlice listSlice;
    glissInternalSlice lineElementSlice;
};

GLISS_INTERNAL glissInternalLineAccumulator*
glissInternalLineAccumulatorNew (void);

GLISS_INTERNAL void
glissInternalLineAccumulatorDestroy (glissInternalLineAccumulator *accumulator);

GLISS_INTERNAL void
glissInternalLineAccumulatorPushLine (glissInternalLineAccumulator *accumulator,
                                      GLdouble x,
                                      GLdouble y);

GLISS_INTERNAL GLboolean
glissInternalLineAccumulatorSetStart (glissInternalLineAccumulator *accumulator,
                                      GLdouble x,
                                      GLdouble y);

GLISS_INTERNAL void
glissInternalLineAccumulatorFillMaskFunc (glissInternalPath *path);

#endif

