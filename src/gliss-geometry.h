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

#ifndef ___GLISS_GEOMETRY_H___
#define ___GLISS_GEOMETRY_H___

#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-state.h"
#include "gliss-list.h"
#include "gliss-slice.h"
#include "gliss.h"

#define GLISS_INTERNAL_TRIANGULATION_SIDES_1 1

#define GLISS_INTERNAL_TRIANGULATION_SIDES_2 2

#define GLISS_INTERNAL_TRIANGULATION_ALIGNED_1_2 3

#define GLISS_INTERNAL_TRIANGULATION_ALIGNED_2_1 4

#define GLISS_INTERNAL_TRIANGULATION_INSIDE_1 5

#define GLISS_INTERNAL_TRIANGULATION_INSIDE_2 6

GLISS_INTERNAL GLdouble
glissInternalGeometryPointDistanceToLine (GLdouble pX,
                                          GLdouble pY,
                                          GLdouble x0,
                                          GLdouble y0,
                                          GLdouble x1,
                                          GLdouble y1);

GLISS_INTERNAL GLdouble
glissInternalGeometryPointDistanceToPoint (GLdouble x0,
                                           GLdouble y0,
                                           GLdouble x1,
                                           GLdouble y1);

GLISS_INTERNAL GLboolean
glissInternalGeometryTriangleContainsPoints (GLdouble x0,
                                             GLdouble y0,
                                             GLdouble x1,
                                             GLdouble y1,
                                             GLdouble x2,
                                             GLdouble y2,
                                             GLdouble pX,
                                             GLdouble pY);

GLISS_INTERNAL GLenum
glissInternalGeometryTriangulateControlPoints (GLdouble x0,
                                               GLdouble y0,
                                               GLdouble x1,
                                               GLdouble y1,
                                               GLdouble x2,
                                               GLdouble y2,
                                               GLdouble x3,
                                               GLdouble y3);

#endif

