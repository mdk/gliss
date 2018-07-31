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

#include "gliss-source.h"

static void
freeGradientData (glissInternalSource *source)
{
    if (source->elementSlice) {
        glissInternalSliceDestroy (source->elementSlice);
        source->elementSlice = NULL;
    }

    if (source->listSlice) {
        glissInternalSliceDestroy (source->listSlice);
        source->listSlice = NULL;
    }

    source->gradientList = NULL;
}

static void
initGradientData (glissInternalSource *source)
{
    source->elementSlice = malloc (sizeof (glissInternalGradientElement));
    glissInternalSliceInit (source->elementSlice, sizeof (glissInternalGradientElement), 8);

    source->listSlice = malloc (sizeof (glissInternalList));
    glissInternalSliceInit (source->listSlice, sizeof (glissInternalList), 8);
}

static GLint
compareLinearGradientElements (glissInternalGradientElement *a,
                               glissInternalGradientElement *b)
{
    if (a->position > b->position)
        return 1;
    else if (a->position < b->position)
        return -1;
    else
        return 0;
}

static GLint
compareRadialGradientElements (glissInternalGradientElement *a,
                               glissInternalGradientElement *b)
{
    if (a->position > b->position)
        return -1;
    else if (a->position < b->position)
        return 1;
    else
        return 0;
}

GLISS_INTERNAL void
glissInternalSourceSetToColorRGBA (glissInternalSource *source,
                                   GLdouble r,
                                   GLdouble g,
                                   GLdouble b,
                                   GLdouble a)
{
    freeGradientData (source);

    source->sourceType = GLISS_INTERNAL_SOURCE_TYPE_COLOR;
    source->colorR = r;
    source->colorG = g;
    source->colorB = b;
    source->colorA = a;
}

GLISS_INTERNAL void
glissInternalSourceInit (glissInternalSource *source)
{
    /* Intial type is white color */
    source->sourceType = GLISS_INTERNAL_SOURCE_TYPE_COLOR;
    source->colorR = 1.0;
    source->colorG = 1.0;
    source->colorB = 1.0;
    source->colorA = 1.0;
    source->gradientList = NULL;
    source->listSlice = NULL;
    source->elementSlice = NULL;
    source->x0 = 0.0;
    source->y0 = 0.0;
    source->x1 = 0.0;
    source->y1 = 0.0;
}

GLISS_INTERNAL void
glissInternalSourceSetToLinearGradient (glissInternalSource *source)
{
    freeGradientData (source);
    source->sourceType = GLISS_INTERNAL_SOURCE_TYPE_LINEAR_GRADIENT;
    initGradientData (source);

    source->x0 = 0.0;
    source->y0 = 0.0;
    source->x1 = 1.0;
    source->y1 = 1.0;
}

GLISS_INTERNAL void
glissInternalSourceSetToRadialGradient (glissInternalSource *source)
{
    freeGradientData (source);
    source->sourceType = GLISS_INTERNAL_SOURCE_TYPE_RADIAL_GRADIENT;
    initGradientData (source);

    source->r = 1.0;
}

GLISS_INTERNAL void
glissInternalSourcePushGradient (glissInternalSource *source,
                                 GLdouble r,
                                 GLdouble g,
                                 GLdouble b,
                                 GLdouble a,
                                 GLdouble position)
{
    glissInternalGradientElement *element = glissInternalSliceNewElement (source->elementSlice);

    element->position = position;
    element->colorR = r;
    element->colorG = g;
    element->colorB = b;
    element->colorA = a;

    if (source->sourceType == GLISS_INTERNAL_SOURCE_TYPE_LINEAR_GRADIENT)
        source->gradientList = glissInternalListAppendSorted (source->gradientList, source->listSlice,
                                                              element, compareLinearGradientElements);
    else
        source->gradientList = glissInternalListAppendSorted (source->gradientList, source->listSlice,
                                                              element, compareRadialGradientElements);

}

GLISS_INTERNAL void
glissInternalSourceSetGradientStart (glissInternalSource *source,
                                     GLdouble x,
                                     GLdouble y)
{
    source->x0 = x;
    source->y0 = y;
}

GLISS_INTERNAL void
glissInternalSourceSetGradientEnd (glissInternalSource *source,
                                   GLdouble x,
                                   GLdouble y)
{
    source->x1 = x;
    source->y1 = y;
}

GLISS_INTERNAL void
glissInternalSourceSetGradientRadius (glissInternalSource *source,
                                      GLdouble r)
{
    source->r = r;
}
