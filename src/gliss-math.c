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

#include "gliss-math.h"

GLdouble powerMatrix [16] = { 1, 0, 0, 0, -3, 3, 0, 0, 3, -6, 3, 0, -1, 3, -3, 1 };

GLdouble unPowerMatrix [16] = { 1, 0, 0, 0, 1, 1 / 3.0, 0, 0, 1, 2 / 3.0, 1 / 3.0, 0, 1, 1, 1, 1 };

GLISS_INTERNAL GLdouble
glissInternalMathCalculateDiscriminant (GLdouble d1,
                                        GLdouble d2,
                                        GLdouble d3)
{
    return (d1 * d1) * (3 * (d2 * d2) - 4 * d3 * d1);
}

GLISS_INTERNAL void
glissInternalMathCalculateD (GLdouble matrix [16],
                             GLdouble *d1,
                             GLdouble *d2,
                             GLdouble *d3)
{
    *d1 = - glissInternalMathMatrix3x3Determinant (GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 3),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 3),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 3),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 0),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 0),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 0));

    *d2 = glissInternalMathMatrix3x3Determinant (GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 3),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 3),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 3),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 1),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 1),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 1),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 0),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 0),
                                                 GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 0));

    *d3 = - glissInternalMathMatrix3x3Determinant (GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 2),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 1),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 1),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 1),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 0),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 0),
                                                   GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 2, 0));
}

GLISS_INTERNAL void
glissInternalMathFlipF (GLdouble matrix [16])
{
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 0) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 0);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 1) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 1);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 2) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 2);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 3) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 0, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 0) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 0);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 1) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 1);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 2) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 2);
    GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 3) = - GLISS_INTERNAL_MATRIX_ELEMENT (matrix, 1, 3);
}

GLISS_INTERNAL GLdouble
glissInternalMathMatrix3x3Determinant (GLdouble a,
                                       GLdouble b,
                                       GLdouble c,
                                       GLdouble d,
                                       GLdouble e,
                                       GLdouble f,
                                       GLdouble g,
                                       GLdouble h,
                                       GLdouble i)
{
    return (a * e * i) - (a * f * h) - (b * d * i) +
           (c * d * h) + (b * f * g) - (c * e * g);
}

GLISS_INTERNAL void
glissInternalMathUnPowerMatrixMultiply (GLdouble a [16],
                                        GLdouble b [16])
{
    glissInternalMathMatrixMultiply (unPowerMatrix, a, b);
}

GLISS_INTERNAL void
glissInternalMathFillPowerCoordsMatrix (GLdouble x0,
                                        GLdouble y0,
                                        GLdouble x1,
                                        GLdouble y1,
                                        GLdouble x2,
                                        GLdouble y2,
                                        GLdouble x3,
                                        GLdouble y3,
                                        GLdouble m [16])
{
    GLdouble coords [16];

    glissInternalMathNormalizeCoords (&x0, &y0,
                                      &x1, &y1,
                                      &x2, &y2,
                                      &x3, &y3);

    /* Fill in */
    coords [0] = x0; coords [1] = y0; coords [2] = 1; coords [3] = 0;
    coords [4] = x1; coords [5] = y1; coords [6] = 1; coords [7] = 0;
    coords [8] = x2; coords [9] = y2; coords [10] = 1; coords [11] = 0;
    coords [12] = x3; coords [13] = y3; coords [14] = 1; coords [15] = 0;

    /* Calculate the power-coords matrix by multiplying the original
     * coordinates by the power matrix */

    glissInternalMathMatrixMultiply (powerMatrix, coords, m);
}

GLISS_INTERNAL void
glissInternalMathMatrixMultiply (GLdouble a [16],
                                 GLdouble b [16],
                                 GLdouble c [16])
{
    /* Row 0 */
    GLISS_INTERNAL_MATRIX_ELEMENT (c, 0, 0) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 1, 0) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 2, 0) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 3, 0) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 0) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 3);

    /* Row 1 */
    GLISS_INTERNAL_MATRIX_ELEMENT (c, 0, 1) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 1, 1) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 2, 1) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 3, 1) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 1) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 3);

    /* Row 2 */
    GLISS_INTERNAL_MATRIX_ELEMENT (c, 0, 2) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 1, 2) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 2, 2) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 3, 2) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 2) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 3);

    /* Row 3 */
    GLISS_INTERNAL_MATRIX_ELEMENT (c, 0, 3) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 0, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 1, 3) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 1, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 2, 3) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 2, 3);

    GLISS_INTERNAL_MATRIX_ELEMENT (c, 3, 3) = GLISS_INTERNAL_MATRIX_ELEMENT (a, 0, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 0) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 1, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 1) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 2, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 2) +
                                              GLISS_INTERNAL_MATRIX_ELEMENT (a, 3, 3) *
                                              GLISS_INTERNAL_MATRIX_ELEMENT (b, 3, 3);
}

GLISS_INTERNAL void
glissInternalMathNormalizeTwo (GLdouble *a,
                               GLdouble *b)
{
    GLdouble max = 0;
    if (fabs (*a) > max)
        max = fabs (*a);

    if (fabs (*b) > max)
        max = fabs (*b);

    *a = *a / max;
    *b = *b / max;
}

GLISS_INTERNAL void
glissInternalMathNormalizeCoords (GLdouble *x0,
                                  GLdouble *y0,
                                  GLdouble *x1,
                                  GLdouble *y1,
                                  GLdouble *x2,
                                  GLdouble *y2,
                                  GLdouble *x3,
                                  GLdouble *y3)
{
    GLdouble maxx = glissInternalMathMaxOutOfFour (*x0, *x1, *x2, *x3);
    GLdouble minx = glissInternalMathMinOutOfFour (*x0, *x1, *x2, *x3);
    GLdouble maxy = glissInternalMathMaxOutOfFour (*y0, *y1, *y2, *y3);
    GLdouble miny = glissInternalMathMinOutOfFour (*y0, *y1, *y2, *y3);

    /* Spans */
    GLdouble spanx = maxx - minx;
    GLdouble spany = maxy - miny;

    /* Assign back */
    *x0 = (*x0 - minx) / spanx;
    *x1 = (*x1 - minx) / spanx;
    *x2 = (*x2 - minx) / spanx;
    *x3 = (*x3 - minx) / spanx;

    *y0 = (*y0 - minx) / spany;
    *y1 = (*y1 - minx) / spany;
    *y2 = (*y2 - minx) / spany;
    *y3 = (*y3 - minx) / spany;
}

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfTwo (GLdouble a,
                              GLdouble b)
{
    if (a < b)
        return a;
    else
        return b;
}

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfThree (GLdouble a,
                                GLdouble b,
                                GLdouble c)
{
    GLdouble t1;
    GLdouble t2;

    if (a < b)
        t1 = a;
    else
        t1 = b;

    if (b < c)
        t2 = b;
    else
        t2 = c;

    if (t1 < t2)
        return t1;
    else
        return t2;
}

GLISS_INTERNAL GLdouble
glissInternalMathMinOutOfFour (GLdouble a,
                               GLdouble b,
                               GLdouble c,
                               GLdouble d)
{
    GLdouble t1;
    GLdouble t2;

    if (a < b)
        t1 = a;
    else
        t1 = b;

    if (c < d)
        t2 = c;
    else
        t2 = d;

    if (t1 < t2)
        return t1;
    else
        return t2;
}

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfTwo (GLdouble a,
                              GLdouble b)
{
    if (a > b)
        return a;
    else
        return b;

}

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfThree (GLdouble a,
                                GLdouble b,
                                GLdouble c)
{
    GLdouble t1;
    GLdouble t2;

    if (a > b)
        t1 = a;
    else
        t1 = b;

    if (b > c)
        t2 = b;
    else
        t2 = c;

    if (t1 > t2)
        return t1;
    else
        return t2;

}

GLISS_INTERNAL GLdouble
glissInternalMathMaxOutOfFour (GLdouble a,
                               GLdouble b,
                               GLdouble c,
                               GLdouble d)
{
    GLdouble t1;
    GLdouble t2;

    if (a > b)
        t1 = a;
    else
        t1 = b;

    if (c > d)
        t2 = c;
    else
        t2 = d;

    if (t1 > t2)
        return t1;
    else
        return t2;
}


