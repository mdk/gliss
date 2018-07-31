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

#include "gliss-cubic-accumulator.h"

extern glissInternalState glissState;

static void
triangulateAligned12 (GLdouble x0,
                      GLdouble y0,
                      GLdouble x1,
                      GLdouble y1,
                      GLdouble x2,
                      GLdouble y2,
                      GLdouble x3,
                      GLdouble y3,
                      GLdouble f [16],
                      GLdouble *vertexArray,
                      GLint *vertexStart,
                      GLdouble *coordsArray,
                      GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x2; vertexArray [*vertexStart + 5] = y2;

    vertexArray [*vertexStart + 6] = x2; vertexArray [*vertexStart + 7] = y2;
    vertexArray [*vertexStart + 8] = x0; vertexArray [*vertexStart + 9] = y0;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    *vertexStart = *vertexStart + 12;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 7] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 9] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 10] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 12] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 13] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 15] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    *coordsStart = *coordsStart + 18;
}

static void
triangulateSides1 (GLdouble x0,
                   GLdouble y0,
                   GLdouble x1,
                   GLdouble y1,
                   GLdouble x2,
                   GLdouble y2,
                   GLdouble x3,
                   GLdouble y3,
                   GLdouble f [16],
                   GLdouble *vertexArray,
                   GLint *vertexStart,
                   GLdouble *coordsArray,
                   GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x3; vertexArray [*vertexStart + 5] = y3;

    vertexArray [*vertexStart + 6] = x2; vertexArray [*vertexStart + 7] = y2;
    vertexArray [*vertexStart + 8] = x0; vertexArray [*vertexStart + 9] = y0;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    *vertexStart = *vertexStart + 12;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 7] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    coordsArray [*coordsStart + 9] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 10] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 12] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 13] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 15] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    *coordsStart = *coordsStart + 18;
}

static void
triangulateSides2 (GLdouble x0,
                   GLdouble y0,
                   GLdouble x1,
                   GLdouble y1,
                   GLdouble x2,
                   GLdouble y2,
                   GLdouble x3,
                   GLdouble y3,
                   GLdouble f [16],
                   GLdouble *vertexArray,
                   GLint *vertexStart,
                   GLdouble *coordsArray,
                   GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x3; vertexArray [*vertexStart + 5] = y3;

    vertexArray [*vertexStart + 6] = x2; vertexArray [*vertexStart + 7] = y2;
    vertexArray [*vertexStart + 8] = x0; vertexArray [*vertexStart + 9] = y0;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    *vertexStart = *vertexStart + 12;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 7] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    coordsArray [*coordsStart + 9] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 10] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 12] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 13] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 15] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = - GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    *coordsStart = *coordsStart + 18;
}

static void
triangulateAligned21 (GLdouble x0,
                      GLdouble y0,
                      GLdouble x1,
                      GLdouble y1,
                      GLdouble x2,
                      GLdouble y2,
                      GLdouble x3,
                      GLdouble y3,
                      GLdouble f [16],
                      GLdouble *vertexArray,
                      GLint *vertexStart,
                      GLdouble *coordsArray,
                      GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x2; vertexArray [*vertexStart + 5] = y2;

    vertexArray [*vertexStart + 6] = x0; vertexArray [*vertexStart + 7] = y0;
    vertexArray [*vertexStart + 8] = x1; vertexArray [*vertexStart + 9] = y1;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    *vertexStart = *vertexStart + 12;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 7] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 9] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 10] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 12] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 13] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 15] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    *coordsStart = *coordsStart + 18;
}

static void
triangulateInside1 (GLdouble x0,
                    GLdouble y0,
                    GLdouble x1,
                    GLdouble y1,
                    GLdouble x2,
                    GLdouble y2,
                    GLdouble x3,
                    GLdouble y3,
                    GLdouble f [16],
                    GLdouble *vertexArray,
                    GLint *vertexStart,
                    GLdouble *coordsArray,
                    GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x2; vertexArray [*vertexStart + 5] = y2;

    vertexArray [*vertexStart + 6] = x1; vertexArray [*vertexStart + 7] = y1;
    vertexArray [*vertexStart + 8] = x2; vertexArray [*vertexStart + 9] = y2;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    vertexArray [*vertexStart + 12] = x3; vertexArray [*vertexStart + 13] = y3;
    vertexArray [*vertexStart + 14] = x1; vertexArray [*vertexStart + 15] = y1;
    vertexArray [*vertexStart + 16] = x0; vertexArray [*vertexStart + 17] = y0;

    *vertexStart = *vertexStart + 18;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 7] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 9] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 10] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 12] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 13] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 15] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    coordsArray [*coordsStart + 18] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 19] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 20] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    coordsArray [*coordsStart + 21] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 22] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 23] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 24] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 25] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 26] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    *coordsStart = *coordsStart + 27;
}

static void
triangulateInside2 (GLdouble x0,
                    GLdouble y0,
                    GLdouble x1,
                    GLdouble y1,
                    GLdouble x2,
                    GLdouble y2,
                    GLdouble x3,
                    GLdouble y3,
                    GLdouble f [16],
                    GLdouble *vertexArray,
                    GLint *vertexStart,
                    GLdouble *coordsArray,
                    GLint *coordsStart)
{
    /* First the triangle coordinates */

    vertexArray [*vertexStart] = x0; vertexArray [*vertexStart + 1] = y0;
    vertexArray [*vertexStart + 2] = x1; vertexArray [*vertexStart + 3] = y1;
    vertexArray [*vertexStart + 4] = x2; vertexArray [*vertexStart + 5] = y2;

    vertexArray [*vertexStart + 6] = x1; vertexArray [*vertexStart + 7] = y1;
    vertexArray [*vertexStart + 8] = x2; vertexArray [*vertexStart + 9] = y2;
    vertexArray [*vertexStart + 10] = x3; vertexArray [*vertexStart + 11] = y3;

    vertexArray [*vertexStart + 12] = x0; vertexArray [*vertexStart + 13] = y0;
    vertexArray [*vertexStart + 14] = x2; vertexArray [*vertexStart + 15] = y2;
    vertexArray [*vertexStart + 16] = x3; vertexArray [*vertexStart + 17] = y3;

    *vertexStart = *vertexStart + 18;

    /* Now the coords */

    coordsArray [*coordsStart] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 1] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 2] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 3] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 4] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 5] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 6] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 7] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 8] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 9] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1);
    coordsArray [*coordsStart + 10] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1);
    coordsArray [*coordsStart + 11] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1);

    coordsArray [*coordsStart + 12] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 13] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 14] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 15] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 16] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 17] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    coordsArray [*coordsStart + 18] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0);
    coordsArray [*coordsStart + 19] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0);
    coordsArray [*coordsStart + 20] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0);

    coordsArray [*coordsStart + 21] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2);
    coordsArray [*coordsStart + 22] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2);
    coordsArray [*coordsStart + 23] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2);

    coordsArray [*coordsStart + 24] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3);
    coordsArray [*coordsStart + 25] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3);
    coordsArray [*coordsStart + 26] = GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3);

    *coordsStart = *coordsStart + 27;
}

static void
loopF (GLdouble d1,
       GLdouble d2,
       GLdouble d3,
       GLdouble f [])
{
    GLdouble sqrtPart = sqrt (4 * d1 * d3 - (3 * (d2 * d2)));
    GLdouble tD = d2 + sqrtPart;
    GLdouble sD = 2 * d1;
    GLdouble tE = d2 - sqrtPart;
    GLdouble sE = 2 * d1;

    /* Assign the matrix */
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0) = tD * tE;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0) = (tD * tD) * tE;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0) = tD * (tE * tE);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 0) = 1;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1) = (- sE * tD) - (sD * tE);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1) = (- sE * (tD * tD)) - (2 * sD * tE * tD);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1) = (- sD * (tE * tE)) - (2 * sE * tD * tE);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 1) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2) = sD * sE;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2) = tE * (sD * sD) + (2 * sE * tD * sD);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2) = tD * (sE * sE) + (2 * sD * tE * sE);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 2) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3) = (- (sD * sD)) * sE;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3) = - sD * (sE * sE);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 3) = 0;
}

static void
serpentineF (GLdouble d1,
             GLdouble d2,
             GLdouble d3,
             GLdouble f [])
{
    GLdouble sqrtPart = sqrt ((3 * (d2 * d2)) - (4 * d1 * d3));

    if (sqrtPart < 0.00001)
        sqrtPart = 0.00001;

    GLdouble sqrt3 = sqrt (3);
    GLdouble tL = d2 + (1 / sqrt3) * sqrtPart;
    GLdouble sL = 2 * d1;
    GLdouble tM = d2 - (1 / sqrt3) * sqrtPart;
    GLdouble sM = 2 * d1;

    glissInternalMathNormalizeTwo (&tL, &sL);
    glissInternalMathNormalizeTwo (&tM, &sM);

    /* Assign the matrix */
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0) = tL * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0) = tL * tL * tL;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0) = tM * tM * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 0) = 1;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1) = (- sM * tL) - (sL * tM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1) = - 3 * sL * (tL * tL);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1) = - 3 * sM * (tM * tM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 1) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2) = sL * sM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2) = 3 * (sL * sL) * tL;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2) = 3 * (sM * sM) * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 2) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3) = - (sL * sL * sL);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3) = - (sM * sM * sM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 3) = 0;
}

static void
infiniteInflectionF (GLdouble d1,
                     GLdouble d2,
                     GLdouble d3,
                     GLdouble f [])
{
    GLdouble sqrtPart = 0.00001;
    GLdouble sqrt3 = sqrt (3);
    GLdouble tL = d2 + (1 / sqrt3) * sqrtPart;
    GLdouble sL = 2 * d1;
    GLdouble tM = d2 - (1 / sqrt3) * sqrtPart;
    GLdouble sM = 2 * d1;

    glissInternalMathNormalizeTwo (&tL, &sL);
    glissInternalMathNormalizeTwo (&tM, &sM);

    /* Assign the matrix */
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0) = tL * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0) = tL * tL * tL;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0) = tM * tM * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 0) = 1;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1) = (- sM * tL) - (sL * tM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1) = - 3 * sL * (tL * tL);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1) = - 3 * sM * (tM * tM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 1) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2) = sL * sM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2) = 3 * (sL * sL) * tL;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2) = 3 * (sM * sM) * tM;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 2) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3) = - (sL * sL * sL);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3) = - (sM * sM * sM);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 3) = 0;
}

static void
localInflectionF (GLdouble d2,
                  GLdouble d3,
                  GLdouble f [])
{
    GLdouble tl = d3;
    GLdouble sl = 3 * d2;

    glissInternalMathNormalizeTwo (&tl, &sl);

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0) = tl;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0) = tl * tl * tl;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0) = 1;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 0) = 1;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1) = - sl;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1) = -3 * sl * (tl * tl);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 1) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2) = 3 * (sl * sl) * tl;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 2) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3) = - (sl * sl * sl);
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 3) = 0;
}

static void
quadraticF (GLdouble f [])
{
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 0) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 0) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 0) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 0) = 1;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 1) = -1;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 1) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 1) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 1) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 2) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 2) = 1;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 2) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 2) = 0;

    GLISS_INTERNAL_MATRIX_ELEMENT (f, 0, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 1, 3) = 0;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 2, 3) = 1;
    GLISS_INTERNAL_MATRIX_ELEMENT (f, 3, 3) = 0;
}

static GLint
triangleCountForCubic (GLenum type)
{
    switch (type) {

        case GLISS_INTERNAL_TRIANGULATION_SIDES_1:
        case GLISS_INTERNAL_TRIANGULATION_SIDES_2:
        case GLISS_INTERNAL_TRIANGULATION_ALIGNED_1_2:
        case GLISS_INTERNAL_TRIANGULATION_ALIGNED_2_1:
            return 2;
            break;

        case GLISS_INTERNAL_TRIANGULATION_INSIDE_1:
        case GLISS_INTERNAL_TRIANGULATION_INSIDE_2:
            return 3;
            break;

        default:
            return 0;
            break;
    }
}

static GLenum
classifyCubic (GLdouble d1,
               GLdouble d2,
               GLdouble d3,
               GLdouble discr)
{
    if (discr > GLISS_INTERNAL_EPSILON)
        return GLISS_INTERNAL_CUBIC_SERPENTINE;
    else if (discr < - GLISS_INTERNAL_EPSILON)
        return GLISS_INTERNAL_CUBIC_LOOP;
    else if (d1 < GLISS_INTERNAL_EPSILON && d1 > - GLISS_INTERNAL_EPSILON &&
             d2 < GLISS_INTERNAL_EPSILON && d2 > - GLISS_INTERNAL_EPSILON &&
             (d3 > GLISS_INTERNAL_EPSILON || d3 < - GLISS_INTERNAL_EPSILON))
        return GLISS_INTERNAL_CUBIC_QUADRATIC;
    else if (d1 < GLISS_INTERNAL_EPSILON &&
             d1 > - GLISS_INTERNAL_EPSILON &&
             d2 < GLISS_INTERNAL_EPSILON &&
             d2 > - GLISS_INTERNAL_EPSILON &&
             d3 < GLISS_INTERNAL_EPSILON &&
             d3 > - GLISS_INTERNAL_EPSILON)
        return GLISS_INTERNAL_CUBIC_LINE;
    else if (d1 < - GLISS_INTERNAL_EPSILON ||
             d1 > GLISS_INTERNAL_EPSILON)
        return GLISS_INTERNAL_CUBIC_CUSP_INFINITE_INFLECTION;
    else if ((d1 < GLISS_INTERNAL_EPSILON && d1 > - GLISS_INTERNAL_EPSILON) &&
             (d2 < - GLISS_INTERNAL_EPSILON || d2 > GLISS_INTERNAL_EPSILON))
        return GLISS_INTERNAL_CUBIC_CUSP_LOCAL_INFLECTION;
    else
        return GLISS_INTERNAL_CUBIC_UNKNOWN;
}


GLISS_INTERNAL glissInternalCubicAccumulator*
glissInternalCubicAccumulatorNew (void)
{
    glissInternalCubicAccumulator *accumulator = malloc (sizeof (glissInternalCubicAccumulator));

    glissInternalSliceInit (&accumulator->listSlice, sizeof (glissInternalList), 10);
    glissInternalSliceInit (&accumulator->lineElementSlice, sizeof (glissInternalLineElement), 10);
    glissInternalSliceInit (&accumulator->quadraticElementSlice, sizeof (glissInternalQuadraticElement), 10);
    glissInternalSliceInit (&accumulator->cubicElementSlice, sizeof (glissInternalCubicElement), 10);

    accumulator->list = NULL;
    accumulator->contourLineCount = 0;
    accumulator->quadraticCount = 0;
    accumulator->cubicCount = 0;
    accumulator->currentX = 0;
    accumulator->currentY = 0;
    accumulator->startX = 0;
    accumulator->startY = 0;

    return accumulator;
}

GLISS_INTERNAL void
glissInternalCubicAccumulatorDestroy (glissInternalCubicAccumulator *accumulator)
{
    glissInternalSliceDestroy (&accumulator->listSlice);
    glissInternalSliceDestroy (&accumulator->lineElementSlice);
    glissInternalSliceDestroy (&accumulator->quadraticElementSlice);
    glissInternalSliceDestroy (&accumulator->cubicElementSlice);
    free (accumulator);
}

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushLine (glissInternalCubicAccumulator *accumulator,
                                       GLdouble x,
                                       GLdouble y)
{
    glissInternalLineElement *element = glissInternalSliceNewElement (&accumulator->lineElementSlice);
    element->x = accumulator->currentX;
    element->y = accumulator->currentY;

    accumulator->currentX = x;
    accumulator->currentY = y;

    accumulator->list = glissInternalListPrependWithType (accumulator->list, &accumulator->listSlice, GLISS_INTERNAL_ELEMENT_LINE, element);
    accumulator->contourLineCount++;
}

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushQuadratic (glissInternalCubicAccumulator *accumulator,
                                            GLdouble cX,
                                            GLdouble cY,
                                            GLdouble tX,
                                            GLdouble tY)
{
    /* FIXME This is temporary and no-good. In future we'll actually push a cubic here
     * representing the quadratic. Having quadratics separately will make the rasterizer
     * use separate shader programs to render it. That's most likely a performance hit. */

    glissInternalQuadraticElement *element = glissInternalSliceNewElement (&accumulator->quadraticElementSlice);
    element->cX = cX;
    element->cY = cY;
    element->sX = accumulator->currentX;
    element->sY = accumulator->currentY;

    accumulator->currentX = tX;
    accumulator->currentY = tY;

    accumulator->list = glissInternalListPrependWithType (accumulator->list, &accumulator->listSlice, GLISS_INTERNAL_ELEMENT_QUADRATIC, element);
    accumulator->contourLineCount++;
    accumulator->quadraticCount++;
}

GLISS_INTERNAL void
glissInternalCubicAccumulatorPushCubic (glissInternalCubicAccumulator *accumulator,
                                        GLdouble c1X,
                                        GLdouble c1Y,
                                        GLdouble c2X,
                                        GLdouble c2Y,
                                        GLdouble tX,
                                        GLdouble tY)
{
    glissInternalCubicElement *element = glissInternalSliceNewElement (&accumulator->cubicElementSlice);
    element->triangulationType = glissInternalGeometryTriangulateControlPoints (accumulator->currentX,
                                                                                accumulator->currentY,
                                                                                c1X,
                                                                                c1Y,
                                                                                c2X,
                                                                                c2Y,
                                                                                tX,
                                                                                tY);
    element->c1X = c2X;
    element->c1Y = c2Y;
    element->c2X = c1X;
    element->c2Y = c1Y;
    element->sX = accumulator->currentX;
    element->sY = accumulator->currentY;

    accumulator->currentX = tX;
    accumulator->currentY = tY;

    accumulator->list = glissInternalListPrependWithType (accumulator->list, &accumulator->listSlice, GLISS_INTERNAL_ELEMENT_CUBIC, element);
    accumulator->contourLineCount++;
    accumulator->cubicCount += triangleCountForCubic (element->triangulationType);
}

GLISS_INTERNAL GLboolean
glissInternalCubicAccumulatorSetStart (glissInternalCubicAccumulator *accumulator,
                                       GLdouble x,
                                       GLdouble y)
{
    if (accumulator->contourLineCount > 0 ||
        accumulator->quadraticCount > 0   ||
        accumulator->cubicCount > 0)
        return GL_FALSE;
    else {
        accumulator->currentX = x;
        accumulator->currentY = y;
        accumulator->startX = x;
        accumulator->startY = y;
        return GL_TRUE;
    }
}

GLISS_INTERNAL void
glissInternalCubicAccumulatorFillMaskFunc (glissInternalPath *path)
{
    /* FIXME: This is becoming big. Refactor */

    /* Get the accumulator */
    glissInternalCubicAccumulator *accumulator = path->accumulator;

    /* If nothing accumulated, set NULL at once. Rasterizer will skip the
     * contour mask. */
    if (accumulator->contourLineCount == 0 &&
        accumulator->quadraticCount == 0 &&
        accumulator->cubicCount == 0) {

        path->fillMaskContourVertexArray = NULL;
        path->fillMaskContourSize = 0;
        path->fillMaskQuadraticVertexArray = NULL;
        path->fillMaskQuadraticTexCoordArray = NULL;
        path->fillMaskQuadraticSize = 0;
        path->fillMaskCubicVertexArray = NULL;
        path->fillMaskCubicTexCoordArray = NULL;
        path->fillMaskCubicSize = 0;
        return;
    }

    /* First calculate the amount of memory needed for the contour.
     * We are going to draw one triangle per each contour line. Triangles
     * are in a fan. One triangle consists of 2 vertices + plus we need the
     * initial vertex. Each vertex consists of 2 doubles (we skip the Z component) */

    path->fillMaskContourSize = accumulator->contourLineCount * 2 + 1;
    path->fillMaskContourVertexArray = NULL;
    if (path->fillMaskContourSize > 0)
        path->fillMaskContourVertexArray = malloc (path->fillMaskContourSize * 2 * sizeof (GLdouble));

    /* Now calculate the amount of memory needed for the quadratic.
     * We are going to draw one triangle per each quadratic. Triangles
     * are completely separate. One triangle consists of 3 vertices.
     * Each vertex consists of 2 doubles (we skip the Z component)
     * Aditionally we need 2 tex coords per each quadratic vertex */

    path->fillMaskQuadraticSize = accumulator->quadraticCount * 3;
    path->fillMaskQuadraticVertexArray = NULL;
    path->fillMaskQuadraticTexCoordArray = NULL;
    if (path->fillMaskQuadraticSize > 0) {
        path->fillMaskQuadraticVertexArray = malloc (path->fillMaskQuadraticSize * 2 * sizeof (GLdouble));
        path->fillMaskQuadraticTexCoordArray = malloc (path->fillMaskQuadraticSize * 2 * sizeof (GLdouble));
    }

    /* Now calculate the amount of memory needed for the cubic.
     * We are going to draw one triangle per each cubic. Triangles
     * are completely separate. One triangle consists of 3 vertices.
     * Each vertex consists of 2 doubles (we skip the Z component)
     * Aditionally we need 3 tex coords per each cubic vertex */

    path->fillMaskCubicSize = accumulator->cubicCount * 3;
    path->fillMaskCubicVertexArray = NULL;
    path->fillMaskCubicTexCoordArray = NULL;
    if (path->fillMaskCubicSize > 0) {
        path->fillMaskCubicVertexArray = malloc (path->fillMaskCubicSize * 2 * sizeof (GLdouble));
        path->fillMaskCubicTexCoordArray = malloc (path->fillMaskCubicSize * 3 * sizeof (GLdouble));
    }

    glissInternalList *iterator = accumulator->list;
    GLdouble currentX = accumulator->currentX;
    GLdouble currentY = accumulator->currentY;
    GLdouble *doubleContourArray = (GLdouble *) path->fillMaskContourVertexArray;
    GLdouble *doubleQuadraticArray = (GLdouble *) path->fillMaskQuadraticVertexArray;
    GLdouble *doubleQuadraticTexArray = (GLdouble *) path->fillMaskQuadraticTexCoordArray;
    GLdouble *doubleCubicArray = (GLdouble *) path->fillMaskCubicVertexArray;
    GLdouble *doubleCubicTexArray = (GLdouble *) path->fillMaskCubicTexCoordArray;
    GLdouble coords [16];
    GLdouble result [16];
    GLdouble d1, d2, d3;
    GLdouble discr;
    GLenum cubicType;
    int contourI = 0;
    int quadraticI = 0;
    int cubicI = 0;
    int cubicCoordsI = 0;

    /* The initial fan vertex for contour */

    doubleContourArray [contourI] = accumulator->startX;
    doubleContourArray [contourI + 1] = accumulator->startY;
    contourI += 2;

    /* Now we iterate over all the elements and add them to the fan list */

    while (iterator) {
        if (iterator->type == GLISS_INTERNAL_ELEMENT_LINE) {

            /* This is a simple line. We just add it to the contour */
            glissInternalLineElement *lineElement = (glissInternalLineElement *) iterator->data;

            doubleContourArray [contourI] = currentX;
            doubleContourArray [contourI + 1] = currentY;
            doubleContourArray [contourI + 2] = lineElement->x;
            doubleContourArray [contourI + 3] = lineElement->y;
            printf ("From %.2f %.2f to %.2f %.2f\n", currentX, currentY, lineElement->x, lineElement->y);
            contourI += 4;

            /* Move the plotter */
            currentX = lineElement->x;
            currentY = lineElement->y;

            /* Update the extents */
            path->minX = glissInternalMathMinOutOfTwo (path->minX, currentX);
            path->minY = glissInternalMathMinOutOfTwo (path->minY, currentY);
            path->maxX = glissInternalMathMaxOutOfTwo (path->maxX, currentX);
            path->maxY = glissInternalMathMaxOutOfTwo (path->maxY, currentY);

        } else if (iterator->type == GLISS_INTERNAL_ELEMENT_QUADRATIC) {

            /* This is a quadratic. We need to add the contour line and real triangle */
            glissInternalQuadraticElement *quadraticElement = (glissInternalQuadraticElement *) iterator->data;

            /* Contour */
            doubleContourArray [contourI] = currentX;
            doubleContourArray [contourI + 1] = currentY;
            doubleContourArray [contourI + 2] = quadraticElement->sX;
            doubleContourArray [contourI + 3] = quadraticElement->sY;
            contourI += 4;

            /* Real quadratic triangle */
            doubleQuadraticArray [quadraticI] = currentX;
            doubleQuadraticArray [quadraticI + 1] = currentY;
            doubleQuadraticArray [quadraticI + 2] = quadraticElement->cX;
            doubleQuadraticArray [quadraticI + 3] = quadraticElement->cY;
            doubleQuadraticArray [quadraticI + 4] = quadraticElement->sX;
            doubleQuadraticArray [quadraticI + 5] = quadraticElement->sY;

            /* Tex coords for quadratic */
            doubleQuadraticTexArray [quadraticI] = 0.0;
            doubleQuadraticTexArray [quadraticI + 1] = 0.0;
            doubleQuadraticTexArray [quadraticI + 2] = 0.5;
            doubleQuadraticTexArray [quadraticI + 3] = 0.0;
            doubleQuadraticTexArray [quadraticI + 4] = 1.0;
            doubleQuadraticTexArray [quadraticI + 5] = 1.0;

            quadraticI += 6;

            /* Update the extents */
            path->minX = glissInternalMathMinOutOfThree (path->minX, quadraticElement->sX, quadraticElement->cX);
            path->minY = glissInternalMathMinOutOfThree (path->minY, quadraticElement->sY, quadraticElement->cY);
            path->maxX = glissInternalMathMaxOutOfThree (path->maxX, quadraticElement->sX, quadraticElement->cX);
            path->maxY = glissInternalMathMaxOutOfThree (path->maxY, quadraticElement->sY, quadraticElement->cY);

            /* Move the plotter */
            currentX = quadraticElement->sX;
            currentY = quadraticElement->sY;
        } else {

            /* This is a cubic. */
            glissInternalCubicElement *cubicElement = (glissInternalCubicElement *) iterator->data;

            /* Contour */
            doubleContourArray [contourI] = currentX;
            doubleContourArray [contourI + 1] = currentY;
            doubleContourArray [contourI + 2] = cubicElement->sX;
            doubleContourArray [contourI + 3] = cubicElement->sY;
            contourI += 4;

            /* Fill the powered matrix */
            glissInternalMathFillPowerCoordsMatrix (currentX, currentY,
                                                    cubicElement->c1X, cubicElement->c1Y,
                                                    cubicElement->c2X, cubicElement->c2Y,
                                                    cubicElement->sX, cubicElement->sY,
                                                    coords);

            /* Calculate d's */
            glissInternalMathCalculateD (coords, &d1, &d2, &d3);

            /* Discriminant */
            discr = glissInternalMathCalculateDiscriminant (d1, d2, d3);

            /* Check cubic type */
            cubicType = classifyCubic (d1, d2, d3, discr);

            switch (cubicType) {

                case GLISS_INTERNAL_CUBIC_SERPENTINE:
                    printf ("* SERPENTINE\n");
                    serpentineF (d1, d2, d3, coords);
                    if (d2 > GLISS_INTERNAL_EPSILON || d2 < - GLISS_INTERNAL_EPSILON) {
                    //if (d1 > GLISS_INTERNAL_EPSILON && d2 > GLISS_INTERNAL_EPSILON && d3 > 0) {
                    //    printf ("  Flipping!\n");
                        //glissInternalMathFlipF (coords);
                    }
                    break;

                case GLISS_INTERNAL_CUBIC_LOOP:
                    printf ("* LOOP\n");
                    loopF (d1, d2, d3, coords);
                    break;

                case GLISS_INTERNAL_CUBIC_CUSP_INFINITE_INFLECTION:
                    printf ("* INFINITE INFLECTION\n");
                    infiniteInflectionF (d1, d2, d3, coords);
                    break;

                case GLISS_INTERNAL_CUBIC_CUSP_LOCAL_INFLECTION:
                    printf ("* LOCAL INFLECTION\n");
                    localInflectionF (d2, d3, coords);
                    if (d2 > 0) {
                        printf ("  Flipping!\n");
                        glissInternalMathFlipF (coords);
                    }
                    break;

                case GLISS_INTERNAL_CUBIC_QUADRATIC:
                    printf ("* QUADRATIC\n");
                    quadraticF (coords);
                    GLISS_INTERNAL_MATRIX_ELEMENT (coords, 2, 0) = GLISS_INTERNAL_MATRIX_ELEMENT (coords, 0, 0);
                    GLISS_INTERNAL_MATRIX_ELEMENT (coords, 2, 1) = GLISS_INTERNAL_MATRIX_ELEMENT (coords, 0, 1);
                    GLISS_INTERNAL_MATRIX_ELEMENT (coords, 2, 2) = GLISS_INTERNAL_MATRIX_ELEMENT (coords, 0, 2);
                    GLISS_INTERNAL_MATRIX_ELEMENT (coords, 2, 3) = GLISS_INTERNAL_MATRIX_ELEMENT (coords, 0, 3);
                    break;

                case GLISS_INTERNAL_CUBIC_LINE:
                    printf ("* LINE\n");
                    goto Finished;
                    break;

            }

            /* Unpower the F matrix */
            glissInternalMathUnPowerMatrixMultiply (coords, result);

            switch (cubicElement->triangulationType) {

                case GLISS_INTERNAL_TRIANGULATION_ALIGNED_1_2:
                    printf ("  ALIGNED 1-2\n");
                    triangulateAligned12 (currentX, currentY,
                                          cubicElement->c1X, cubicElement->c1Y,
                                          cubicElement->c2X, cubicElement->c2Y,
                                          cubicElement->sX, cubicElement->sY,
                                          result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;

                case GLISS_INTERNAL_TRIANGULATION_ALIGNED_2_1:
                    printf ("  ALIGNED 2-1\n");
                    triangulateAligned21 (currentX, currentY,
                                          cubicElement->c1X, cubicElement->c1Y,
                                          cubicElement->c2X, cubicElement->c2Y,
                                          cubicElement->sX, cubicElement->sY,
                                          result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;

                case GLISS_INTERNAL_TRIANGULATION_INSIDE_1:
                    printf ("  INSIDE 1\n");
                    triangulateInside1 (currentX, currentY,
                                        cubicElement->c1X, cubicElement->c1Y,
                                        cubicElement->c2X, cubicElement->c2Y,
                                        cubicElement->sX, cubicElement->sY,
                                        result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;

                case GLISS_INTERNAL_TRIANGULATION_INSIDE_2:
                    printf ("  INSIDE 2\n");
                    triangulateInside2 (currentX, currentY,
                                        cubicElement->c1X, cubicElement->c1Y,
                                        cubicElement->c2X, cubicElement->c2Y,
                                        cubicElement->sX, cubicElement->sY,
                                        result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;

                case GLISS_INTERNAL_TRIANGULATION_SIDES_1:
                    printf ("  SIDES 1\n");
                    triangulateSides1 (currentX, currentY,
                                       cubicElement->c1X, cubicElement->c1Y,
                                       cubicElement->c2X, cubicElement->c2Y,
                                       cubicElement->sX, cubicElement->sY,
                                       result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;

                case GLISS_INTERNAL_TRIANGULATION_SIDES_2:
                    printf ("  SIDES 2\n");
                    triangulateSides2 (currentX, currentY,
                                       cubicElement->c1X, cubicElement->c1Y,
                                       cubicElement->c2X, cubicElement->c2Y,
                                       cubicElement->sX, cubicElement->sY,
                                       result, doubleCubicArray, &cubicI, doubleCubicTexArray, &cubicCoordsI);
                    break;
            }
Finished:

            printf ("  DISCR: %.3f\n", discr);
            printf ("  D1: %.5f D2: %.5f D3: %.5f\n\n", d1, d2, d3);

            /* Update the extents */
            path->minX = glissInternalMathMinOutOfFour (path->minX, cubicElement->sX, cubicElement->c1X, cubicElement->c2X);
            path->minY = glissInternalMathMinOutOfFour (path->minY, cubicElement->sY, cubicElement->c1Y, cubicElement->c2Y);
            path->maxX = glissInternalMathMaxOutOfFour (path->maxX, cubicElement->sX, cubicElement->c1X, cubicElement->c2X);
            path->maxY = glissInternalMathMaxOutOfFour (path->maxY, cubicElement->sY, cubicElement->c1Y, cubicElement->c2Y);

            /* Move the plotter */
            currentX = cubicElement->sX;
            currentY = cubicElement->sY;
        }

        iterator = iterator->next;
    }
}
