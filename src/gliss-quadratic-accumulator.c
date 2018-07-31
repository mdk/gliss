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

#include "gliss-quadratic-accumulator.h"

extern glissInternalState glissState;

GLISS_INTERNAL glissInternalQuadraticAccumulator*
glissInternalQuadraticAccumulatorNew (void)
{
    glissInternalQuadraticAccumulator *accumulator = malloc (sizeof (glissInternalQuadraticAccumulator));

    glissInternalSliceInit (&accumulator->listSlice, sizeof (glissInternalList), 10);
    glissInternalSliceInit (&accumulator->lineElementSlice, sizeof (glissInternalLineElement), 10);
    glissInternalSliceInit (&accumulator->quadraticElementSlice, sizeof (glissInternalQuadraticElement), 10);
    accumulator->list = NULL;
    accumulator->contourLineCount = 0;
    accumulator->quadraticCount = 0;
    accumulator->startX = 0;
    accumulator->startY = 0;
    accumulator->currentX = 0;
    accumulator->currentY = 0;

    return accumulator;
}

GLISS_INTERNAL void
glissInternalQuadraticAccumulatorDestroy (glissInternalQuadraticAccumulator *accumulator)
{
    glissInternalSliceDestroy (&accumulator->listSlice);
    glissInternalSliceDestroy (&accumulator->lineElementSlice);
    glissInternalSliceDestroy (&accumulator->quadraticElementSlice);
    free (accumulator);
}

GLISS_INTERNAL void
glissInternalQuadraticAccumulatorPushLine (glissInternalQuadraticAccumulator *accumulator,
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
glissInternalQuadraticAccumulatorPushQuadratic (glissInternalQuadraticAccumulator *accumulator,
                                                GLdouble cX,
                                                GLdouble cY,
                                                GLdouble tX,
                                                GLdouble tY)
{
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

GLISS_INTERNAL GLboolean
glissInternalQuadraticAccumulatorSetStart (glissInternalQuadraticAccumulator *accumulator,
                                           GLdouble x,
                                           GLdouble y)
{
    if (accumulator->contourLineCount > 0 || accumulator->quadraticCount > 0)
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
glissInternalQuadraticAccumulatorFillMaskFunc (glissInternalPath *path)
{
    /* Get the accumulator */
    glissInternalQuadraticAccumulator *accumulator = path->accumulator;

    /* We're not going to use cubics at all */
    path->fillMaskCubicVertexArray = NULL;
    path->fillMaskCubicTexCoordArray = NULL;
    path->fillMaskCubicSize = 0;

    /* If nothing accumulated, set NULL at once. Rasterizer will skip the
     * contour mask. */
    if (accumulator->contourLineCount == 0 && accumulator->quadraticCount == 0) {
        path->fillMaskContourVertexArray = NULL;
        path->fillMaskContourSize = 0;
        path->fillMaskQuadraticVertexArray = NULL;
        path->fillMaskQuadraticTexCoordArray = NULL;
        path->fillMaskQuadraticSize = 0;
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

    glissInternalList *iterator = accumulator->list;
    GLdouble currentX = accumulator->currentX;
    GLdouble currentY = accumulator->currentY;
    GLdouble *doubleContourArray = (GLdouble *) path->fillMaskContourVertexArray;
    GLdouble *doubleQuadraticArray = (GLdouble *) path->fillMaskQuadraticVertexArray;
    GLdouble *doubleQuadraticTexArray = (GLdouble *) path->fillMaskQuadraticTexCoordArray;
    int contourI = 0;
    int quadraticI = 0;

    /* Set initial path extents */
    path->maxX = currentX;
    path->minX = currentX;
    path->maxY = currentY;
    path->minY = currentY;

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
            contourI += 4;

            /* Move the plotter */
            currentX = lineElement->x;
            currentY = lineElement->y;

            /* Update the extents */
            path->minX = glissInternalMathMinOutOfTwo (path->minX, currentX);
            path->minY = glissInternalMathMinOutOfTwo (path->minY, currentY);
            path->maxX = glissInternalMathMaxOutOfTwo (path->maxX, currentX);
            path->maxY = glissInternalMathMaxOutOfTwo (path->maxY, currentY);

        } else {
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
        }

        iterator = iterator->next;
    }
}
