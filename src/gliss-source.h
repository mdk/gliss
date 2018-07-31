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

#ifndef ___GLISS_SOURCE_H___
#define ___GLISS_SOURCE_H___

#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-state.h"
#include "gliss-list.h"
#include "gliss-slice.h"
#include "gliss-slice.h"
#include "gliss-elements.h"
#include "gliss.h"

#define GLISS_INTERNAL_SOURCE_TYPE_COLOR 1

#define GLISS_INTERNAL_SOURCE_TYPE_LINEAR_GRADIENT 2

#define GLISS_INTERNAL_SOURCE_TYPE_RADIAL_GRADIENT 3

struct _glissInternalSource {

    GLenum sourceType;
    GLdouble colorR;
    GLdouble colorG;
    GLdouble colorB;
    GLdouble colorA;

    glissInternalList *gradientList;
    glissInternalSlice *listSlice;
    glissInternalSlice *elementSlice;

    GLdouble x0;
    GLdouble y0;
    GLdouble x1;
    GLdouble y1;
    GLdouble r;
};

GLISS_INTERNAL void
glissInternalSourceSetToColorRGBA (glissInternalSource *source,
                                   GLdouble r,
                                   GLdouble g,
                                   GLdouble b,
                                   GLdouble a);

GLISS_INTERNAL void
glissInternalSourceInit (glissInternalSource *source);

GLISS_INTERNAL void
glissInternalSourceSetToLinearGradient (glissInternalSource *source);

GLISS_INTERNAL void
glissInternalSourceSetToRadialGradient (glissInternalSource *source);

GLISS_INTERNAL void
glissInternalSourcePushGradient (glissInternalSource *source,
                                 GLdouble r,
                                 GLdouble g,
                                 GLdouble b,
                                 GLdouble a,
                                 GLdouble position);

GLISS_INTERNAL void
glissInternalSourceSetGradientStart (glissInternalSource *source,
                                     GLdouble x,
                                     GLdouble y);

GLISS_INTERNAL void
glissInternalSourceSetGradientEnd (glissInternalSource *source,
                                   GLdouble x,
                                   GLdouble y);

GLISS_INTERNAL void
glissInternalSourceSetGradientRadius (glissInternalSource *source,
                                      GLdouble r);

#endif


