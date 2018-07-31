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

#ifndef ___GLISS_CUBIC_ACCUMULATOR_H___
#define ___GLISS_CUBIC_ACCUMULATOR_H___

#include <stdlib.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-state.h"
#include "gliss-list.h"
#include "gliss-slice.h"
#include "gliss-elements.h"
#include "gliss-path.h"
#include "gliss-geometry.h"
#include "gliss-math.h"
#include "gliss.h"

#define GLISS_INTERNAL_CUBIC_SERPENTINE 1

#define GLISS_INTERNAL_CUBIC_LOOP 2

#define GLISS_INTERNAL_CUBIC_QUADRATIC 3

#define GLISS_INTERNAL_CUBIC_LINE 4

#define GLISS_INTERNAL_CUBIC_CUSP_INFINITE_INFLECTION 5

#define GLISS_INTERNAL_CUBIC_CUSP_LOCAL_INFLECTION 6

#define GLISS_INTERNAL_CUBIC_UNKNOWN 7

struct _glissInternalCubicAccumulator {

    GLdouble currentX;
    GLdouble currentY;
    GLdouble startX;
    GLdouble startY;
    GLint contourLineCount;
    GLint quadraticCount;
    GLint cubicCount;
    glissInternalList *list;
    glissInternalSlice listSlice;
    glissInternalSlice lineElementSlice;
    glissInternalSlice quadraticElementSlice;
    glissInternalSlice cubicElementSlice;
};

GLISS_INTERNAL glissInternalCubicAccumulator*
glissInternalCubicAccumulatorNew (void);

GLISS_INTERNAL void
glissInternalCubicAccumulatorDestroy (glissInternalCubicAccumulator *accumulator);

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushLine (glissInternalCubicAccumulator *accumulator,
                                       GLdouble x,
                                       GLdouble y);

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushQuadratic (glissInternalCubicAccumulator *accumulator,
                                            GLdouble cX,
                                            GLdouble cY,
                                            GLdouble tX,
                                            GLdouble tY);

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushCubic (glissInternalCubicAccumulator *accumulator,
                                        GLdouble c1X,
                                        GLdouble c1Y,
                                        GLdouble c2X,
                                        GLdouble c2Y,
                                        GLdouble tX,
                                        GLdouble tY);

GLISS_INTERNAL GLboolean
glissInternalCubicAccumulatorSetStart (glissInternalCubicAccumulator *accumulator,
                                       GLdouble x,
                                       GLdouble y);

GLISS_INTERNAL void
glissInternalCubicAccumulatorFillMaskFunc (glissInternalPath *path);

#endif

