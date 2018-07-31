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

#include "gliss-geometry.h"

GLISS_INTERNAL GLdouble
glissInternalGeometryPointDistanceToLine (GLdouble pX,
                                          GLdouble pY,
                                          GLdouble x0,
                                          GLdouble y0,
                                          GLdouble x1,
                                          GLdouble y1)
{
    GLdouble xx1 = x1 - x0;
    GLdouble yy1 = y1 - y0;
    GLdouble xx2 = pX - x0;
    GLdouble yy2 = pY - y0;
    GLdouble z  = (xx1 * yy2) - (xx2 * yy1);

    /* FIXME Maybe we can skip sqrt at all here. After all,
     * we're mostly interested in comparing values of same base */
    return z / sqrt ((xx1 * xx1) + (yy1 * yy1));
}

GLISS_INTERNAL GLdouble
glissInternalGeometryPointDistanceToPoint (GLdouble x0,
                                           GLdouble y0,
                                           GLdouble x1,
                                           GLdouble y1)
{
    GLdouble cx = x1 - x0;
    GLdouble cy = y1 - y0;

    /* FIXME Maybe we can skip sqrt at all here. After all,
     * we're mostly interested in comparing values of same base */
    return sqrt ((cx * cx) + (cy * cy));
}

GLISS_INTERNAL GLboolean
glissInternalGeometryTriangleContainsPoints (GLdouble x0,
                                             GLdouble y0,
                                             GLdouble x1,
                                             GLdouble y1,
                                             GLdouble x2,
                                             GLdouble y2,
                                             GLdouble pX,
                                             GLdouble pY)
{
    GLdouble d1 = glissInternalGeometryPointDistanceToLine (pX, pY, x0, y0, x1, y1);
    GLdouble d2 = glissInternalGeometryPointDistanceToLine (pX, pY, x1, y1, x2, y2);
    GLdouble d3 = glissInternalGeometryPointDistanceToLine (pX, pY, x2, y2, x0, y0);

    if (d1 <= 0 && d2 <= 0 && d3 <= 0)
        return 1;

    if (d1 >= 0 && d2 >= 0 && d3 >= 0)
        return 1;

    return 0;
}

GLISS_INTERNAL GLenum
glissInternalGeometryTriangulateControlPoints (GLdouble x0,
                                               GLdouble y0,
                                               GLdouble x1,
                                               GLdouble y1,
                                               GLdouble x2,
                                               GLdouble y2,
                                               GLdouble x3,
                                               GLdouble y3)
{
    GLdouble d1 = glissInternalGeometryPointDistanceToLine (x1, y1, x0, y0, x3, y3);
    GLdouble d2 = glissInternalGeometryPointDistanceToLine (x2, y2, x0, y0, x3, y3);

    if (glissInternalGeometryTriangleContainsPoints (x0, y0, x1, y1, x3, y3, x2, y2))
        return GLISS_INTERNAL_TRIANGULATION_INSIDE_2;

    if (glissInternalGeometryTriangleContainsPoints (x0, y0, x2, y2, x3, y3, x1, y1))
        return GLISS_INTERNAL_TRIANGULATION_INSIDE_1;

    if (d1 > 0 && d2 < 0)
        return GLISS_INTERNAL_TRIANGULATION_SIDES_1;

    if (d2 > 0 && d1 < 0)
        return GLISS_INTERNAL_TRIANGULATION_SIDES_2;

    if (glissInternalGeometryPointDistanceToPoint (x0, y0, x1, y1) <
        glissInternalGeometryPointDistanceToPoint (x0, y0, x2, y2))
        return GLISS_INTERNAL_TRIANGULATION_ALIGNED_1_2;
    else
        return GLISS_INTERNAL_TRIANGULATION_ALIGNED_2_1;
}


