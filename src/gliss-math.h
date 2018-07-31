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

#ifndef ___GLISS_MATH_H___
#define ___GLISS_MATH_H___

#include <stdlib.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-path.h"
#include "gliss-source.h"
#include "gliss.h"

GLISS_INTERNAL GLdouble
glissInternalMathMatrix3x3Determinant (GLdouble a,
                                       GLdouble b,
                                       GLdouble c,
                                       GLdouble d,
                                       GLdouble e,
                                       GLdouble f,
                                       GLdouble g,
                                       GLdouble h,
                                       GLdouble i);

GLISS_INTERNAL void
glissInternalMathUnPowerMatrixMultiply (GLdouble a [16],
                                        GLdouble b [16]);

GLISS_INTERNAL GLdouble
glissInternalMathCalculateDiscriminant (GLdouble d1,
                                        GLdouble d2,
                                        GLdouble d3);

GLISS_INTERNAL void
glissInternalMathCalculateD (GLdouble matrix [16],
                             GLdouble *d1,
                             GLdouble *d2,
                             GLdouble *d3);

GLISS_INTERNAL void
glissInternalMathMatrixMultiply (GLdouble a [16],
                                 GLdouble b [16],
                                 GLdouble c [16]);

GLISS_INTERNAL void
glissInternalMathFillPowerCoordsMatrix (GLdouble x0,
                                        GLdouble y0,
                                        GLdouble x1,
                                        GLdouble y1,
                                        GLdouble x2,
                                        GLdouble y2,
                                        GLdouble x3,
                                        GLdouble y3,
                                        GLdouble m [16]);

GLISS_INTERNAL void
glissInternalMathNormalizeTwo (GLdouble *a,
                               GLdouble *b);

GLISS_INTERNAL void
glissInternalMathNormalizeCoords (GLdouble *x0,
                                  GLdouble *y0,
                                  GLdouble *x1,
                                  GLdouble *y1,
                                  GLdouble *x2,
                                  GLdouble *y2,
                                  GLdouble *x3,
                                  GLdouble *y3);

GLISS_INTERNAL void
glissInternalMathFlipF (GLdouble matrix [16]);

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfTwo (GLdouble a,
                              GLdouble b);

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfThree (GLdouble a,
                                GLdouble b,
                                GLdouble c);

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfFour (GLdouble a,
                               GLdouble b,
                               GLdouble c,
                               GLdouble d);

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfTwo (GLdouble a,
                              GLdouble b);

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfThree (GLdouble a,
                                GLdouble b,
                                GLdouble c);

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfFour (GLdouble a,
                               GLdouble b,
                               GLdouble c,
                               GLdouble d);

#endif

