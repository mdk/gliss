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

#include "gliss-path.h"

static void
freeAccumulator (glissInternalPath *path)
{
    if (path->accumulator != NULL && path->accumulatorFreeFunc != NULL)
        path->accumulatorFreeFunc (path->accumulator);

    path->accumulator = NULL;
}

static void
freeArrays (glissInternalPath *path)
{
    /* Free the contour lines */
    if (path->fillMaskContourVertexArray) {
        free (path->fillMaskContourVertexArray);
        path->fillMaskContourVertexArray = NULL;
    }

    /* Free the quadratic triangles array */
    if (path->fillMaskQuadraticVertexArray) {
        free (path->fillMaskQuadraticVertexArray);
        path->fillMaskQuadraticVertexArray = NULL;
    }

    /* Free the quadratic tex coord array */
    if (path->fillMaskQuadraticTexCoordArray) {
        free (path->fillMaskQuadraticTexCoordArray);
        path->fillMaskQuadraticTexCoordArray = NULL;
    }

    /* Free the cubic triangles array */
    if (path->fillMaskCubicVertexArray) {
        free (path->fillMaskCubicVertexArray);
        path->fillMaskCubicVertexArray = NULL;
    }

    /* Free the cubic tex coord array */
    if (path->fillMaskCubicTexCoordArray) {
        free (path->fillMaskCubicTexCoordArray);
        path->fillMaskCubicTexCoordArray = NULL;
    }

    path->fillMaskContourSize = 0;
    path->fillMaskQuadraticSize = 0;
    path->fillMaskCubicSize = 0;

    path->hasFillMask = GL_FALSE;
}

GLISS_INTERNAL void
glissInternalPathStartAccumulation (glissInternalPath *path)
{
    freeAccumulator (path);
    freeArrays (path);

    /* Reset path extents */
    path->minX = 0;
    path->minY = 0;
    path->maxX = 0;
    path->maxY = 0;
}

GLISS_INTERNAL void
glissInternalPathEnsureFillMask (glissInternalPath *path)
{
    if (path->hasFillMask)
        return;

    if (path->fillMaskFunc)
        path->fillMaskFunc (path);

    path->hasFillMask = GL_TRUE;
}

GLISS_INTERNAL void
glissInternalPathInit (glissInternalPath *path)
{
    path->accumulator = NULL;
    path->accumulatorFreeFunc = NULL;
    path->fillMaskContourVertexArray = NULL;
    path->fillMaskContourSize = 0;
    path->fillMaskQuadraticVertexArray = NULL;
    path->fillMaskQuadraticTexCoordArray = NULL;
    path->fillMaskQuadraticSize = 0;
    path->fillMaskCubicVertexArray = NULL;
    path->fillMaskCubicTexCoordArray = NULL;
    path->fillMaskCubicSize = 0;

    path->fillMaskFunc = NULL;

    path->hasFillMask = GL_FALSE;
    path->minX = 0;
    path->minY = 0;
    path->maxX = 0;
    path->maxY = 0;
}

