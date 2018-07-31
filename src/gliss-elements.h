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

#ifndef ___GLISS_ELEMENTS_H___
#define ___GLISS_ELEMENTS_H___

#include <stdlib.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"

struct _glissInternalLineElement {

    GLdouble x;
    GLdouble y;
};

struct _glissInternalQuadraticElement {

    GLdouble cX;
    GLdouble cY;
    GLdouble sX;
    GLdouble sY;
};

struct _glissInternalCubicElement {

    GLenum triangulationType;
    GLdouble c1X;
    GLdouble c1Y;
    GLdouble c2X;
    GLdouble c2Y;
    GLdouble sX;
    GLdouble sY;
};

struct _glissInternalGradientElement {

    GLdouble position;
    GLdouble colorR;
    GLdouble colorG;
    GLdouble colorB;
    GLdouble colorA;
};

#define GLISS_INTERNAL_ELEMENT_LINE 1

#define GLISS_INTERNAL_ELEMENT_QUADRATIC 2

#define GLISS_INTERNAL_ELEMENT_CUBIC 3

#define GLISS_INTERNAL_ELEMENT_GRADIENT 4

#endif

