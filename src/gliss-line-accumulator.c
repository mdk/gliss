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

#include "gliss-line-accumulator.h"

extern glissInternalState glissState;

GLISS_INTERNAL glissInternalLineAccumulator*
glissInternalLineAccumulatorNew (void)
{
    glissInternalLineAccumulator *accumulator = malloc (sizeof (glissInternalLineAccumulator));

    glissInternalSliceInit (&accumulator->listSlice, sizeof (glissInternalList), 10);
    glissInternalSliceInit (&accumulator->lineElementSlice, sizeof (glissInternalLineElement), 10);
    accumulator->list = NULL;
    accumulator->lineCount = 0;
    accumulator->startX = 0;
    accumulator->startY = 0;
    accumulator->currentX = 0;
    accumulator->currentY = 0;

    return accumulator;
}

GLISS_INTERNAL void
glissInternalLineAccumulatorDestroy (glissInternalLineAccumulator *accumulator)
{
    glissInternalSliceDestroy (&accumulator->listSlice);
    glissInternalSliceDestroy (&accumulator->lineElementSlice);
    free (accumulator);
}

GLISS_INTERNAL void
glissInternalLineAccumulatorPushLine (glissInternalLineAccumulator *accumulator,
                                      GLdouble x,
                                      GLdouble y)
{
    glissInternalLineElement *element = glissInternalSliceNewElement (&accumulator->lineElementSlice);
    element->x = accumulator->currentX;
    element->y = accumulator->currentY;

    accumulator->currentX = x;
    accumulator->currentY = y;

    accumulator->list = glissInternalListPrepend (accumulator->list, &accumulator->listSlice, element);
    accumulator->lineCount++;
}

GLISS_INTERNAL GLboolean
glissInternalLineAccumulatorSetStart (glissInternalLineAccumulator *accumulator,
                                      GLdouble x,
                                      GLdouble y)
{
    if (accumulator->lineCount > 0)
        return GL_FALSE;
    else {
        accumulator->startX = x;
        accumulator->startY = y;
        accumulator->currentX = x;
        accumulator->currentY = y;
        return GL_TRUE;
    }
}

GLISS_INTERNAL void
glissInternalLineAccumulatorFillMaskFunc (glissInternalPath *path)
{
    /* Get the accumulator */
    glissInternalLineAccumulator *accumulator = path->accumulator;

    /* We're not going to use quadratics and cubics at all */
    path->fillMaskQuadraticVertexArray = NULL;
    path->fillMaskQuadraticTexCoordArray = NULL;
    path->fillMaskCubicVertexArray = NULL;
    path->fillMaskCubicTexCoordArray = NULL;
    path->fillMaskQuadraticSize = 0;
    path->fillMaskCubicSize = 0;

    /* If nothing accumulated, set NULL at once. Rasterizer will skip the
     * contour mask. */
    if (accumulator->lineCount == 0) {
        path->fillMaskContourVertexArray = NULL;
        path->fillMaskContourSize = 0;
        return;
    }

    /* First calculate the amount of memory needed. We are going to draw
     * one triangle per each contour line. Triangles are in a fan.
     * One triangle consists of 2 vertices + plus we need the initial vertex.
     * Each vertex consists of 2 doubles (we skip the Z component) */

    path->fillMaskContourSize = accumulator->lineCount * 2 + 1;
    path->fillMaskContourVertexArray = malloc (path->fillMaskContourSize * 2 * sizeof (GLdouble));

    glissInternalList *lineIterator = accumulator->list;
    GLdouble currentX = accumulator->currentX;
    GLdouble currentY = accumulator->currentY;
    GLdouble *doubleArray = (GLdouble *) path->fillMaskContourVertexArray;
    int i = 0;

    /* Set initial path extents */
    path->maxX = currentX;
    path->minX = currentX;
    path->maxY = currentY;
    path->minY = currentY;

    /* The initial fan vertex */

    doubleArray [i] = accumulator->startX;
    doubleArray [i + 1] = accumulator->startY;
    i += 2;

    /* Now we iterate over all lines and add them to the fan list */

    while (lineIterator) {
        glissInternalLineElement *lineElement = (glissInternalLineElement *) lineIterator->data;

        doubleArray [i] = currentX;
        doubleArray [i + 1] = currentY;
        doubleArray [i + 2] = lineElement->x;
        doubleArray [i + 3] = lineElement->y;
        i += 4;

        /* Move the plotter */
        currentX = lineElement->x;
        currentY = lineElement->y;

        /* Update the extents */
        path->minX = glissInternalMathMinOutOfTwo (path->minX, currentX);
        path->minY = glissInternalMathMinOutOfTwo (path->minY, currentY);
        path->maxX = glissInternalMathMaxOutOfTwo (path->maxX, currentX);
        path->maxY = glissInternalMathMaxOutOfTwo (path->maxY, currentY);

        lineIterator = lineIterator->next;
    }
}
