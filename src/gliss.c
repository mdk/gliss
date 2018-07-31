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

#include "gliss.h"
#include "gliss-line-accumulator.h"
#include "gliss-quadratic-accumulator.h"
#include "gliss-cubic-accumulator.h"
#include "gliss-rasterizer.h"
#include "gliss-state.h"
#include "gliss-path.h"

extern glissInternalState glissState;

void
glissBegin (GLenum mode)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    switch (mode) {

        case GLISS_LINE_PATH:
            glissInternalPathStartAccumulation (glissState.activePath);
            glissState.activePath->accumulator = glissInternalLineAccumulatorNew ();
            glissState.activePath->accumulatorFreeFunc = glissInternalLineAccumulatorDestroy;
            glissState.activePath->fillMaskFunc = glissInternalLineAccumulatorFillMaskFunc;
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_LINES;
            break;

        case GLISS_QUADRATIC_PATH:
            glissInternalPathStartAccumulation (glissState.activePath);
            glissState.activePath->accumulator = glissInternalQuadraticAccumulatorNew ();
            glissState.activePath->accumulatorFreeFunc = glissInternalQuadraticAccumulatorDestroy;
            glissState.activePath->fillMaskFunc = glissInternalQuadraticAccumulatorFillMaskFunc;
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_QUADRATICS;
            break;

        case GLISS_CUBIC_PATH:
            glissInternalPathStartAccumulation (glissState.activePath);
            glissState.activePath->accumulator = glissInternalCubicAccumulatorNew ();
            glissState.activePath->accumulatorFreeFunc = glissInternalCubicAccumulatorDestroy;
            glissState.activePath->fillMaskFunc = glissInternalCubicAccumulatorFillMaskFunc;
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS;
            break;

        case GLISS_LINEAR_GRADIENT:
            glissInternalSourceSetToLinearGradient (glissState.activeSource);
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_LINEAR_GRADIENT;
            break;

        case GLISS_RADIAL_GRADIENT:
            glissInternalSourceSetToRadialGradient (glissState.activeSource);
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_RADIAL_GRADIENT;
            break;

        case GLISS_SUB_PATH_FILL:
            glissState.state = GLISS_INTERNAL_STATE_ACCUMULATING_SUB_PATH_FILL;

            /* Rasterize the currently active path */
            glissInternalPathEnsureFillMask (glissState.activePath);
            glissInternalRasterizeFilledSubPath (glissState.activePath);

            /* Set the initial min/max values */
            glissState.minX = glissState.activePath->minX;
            glissState.minY = glissState.activePath->minY;
            glissState.maxX = glissState.activePath->maxX;
            glissState.maxY = glissState.activePath->maxY;
            break;

        default:
            GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_ENUM);
            return;
    }
}

void
glissEnd (void)
{
    if (! GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    switch (glissState.state) {

        case GLISS_SUB_PATH_FILL:
            glissInternalRasterizeMask (glissState.activeSource,
                                        glissState.minX, glissState.minY, glissState.maxX, glissState.maxY);
            break;

        default:
            break;
    }

    glissState.state = GLISS_INTERNAL_STATE_IDLE;
}

void
glissLineTo2d (GLdouble x,
               GLdouble y)
{
    switch (glissState.state) {

        case GLISS_INTERNAL_STATE_ACCUMULATING_LINES:
            glissInternalLineAccumulatorPushLine (glissState.activePath->accumulator, x, y);
            break;

        case GLISS_INTERNAL_STATE_ACCUMULATING_QUADRATICS:
            glissInternalQuadraticAccumulatorPushLine (glissState.activePath->accumulator, x, y);
            break;

        case GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS:
            glissInternalCubicAccumulatorPushLine (glissState.activePath->accumulator, x, y);
            break;

        default:
            GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
            break;
    }
}

void
glissQuadraticTo4d (GLdouble cX,
                    GLdouble cY,
                    GLdouble tX,
                    GLdouble tY)
{
    switch (glissState.state) {

        case GLISS_INTERNAL_STATE_ACCUMULATING_QUADRATICS:
            glissInternalQuadraticAccumulatorPushQuadratic (glissState.activePath->accumulator, cX, cY, tX, tY);
            break;

        case GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS:
            glissInternalCubicAccumulatorPushQuadratic (glissState.activePath->accumulator, cX, cY, tX, tY);
            break;

        default:
            GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
            break;
    }
}

void
glissCubicTo6d (GLdouble c1X,
                GLdouble c1Y,
                GLdouble c2X,
                GLdouble c2Y,
                GLdouble tX,
                GLdouble tY)
{
    switch (glissState.state) {

        case GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS:
            glissInternalCubicAccumulatorPushCubic (glissState.activePath->accumulator, c1X, c1Y, c2X, c2Y, tX, tY);
            break;

        default:
            GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
            break;
    }
}

void
glissMoveTo2d (GLdouble x,
               GLdouble y)
{
    GLint result;

    switch (glissState.state) {

        case GLISS_INTERNAL_STATE_ACCUMULATING_LINES:
            result = glissInternalLineAccumulatorSetStart (glissState.activePath->accumulator, x, y);
            break;

        case GLISS_INTERNAL_STATE_ACCUMULATING_QUADRATICS:
            result = glissInternalQuadraticAccumulatorSetStart (glissState.activePath->accumulator, x, y);
            break;

        case GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS:
            result = glissInternalCubicAccumulatorSetStart (glissState.activePath->accumulator, x, y);
            break;

        default:
            result = GL_FALSE;
            break;
    }

    if (! result)
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
}

GLenum
glissGetError (void)
{
    /* FIXME According to GLspec, get error should fail when in
     * the beg/end statement */

    if (glissState.error == GLISS_NO_ERROR)
        return GLISS_NO_ERROR;
    else {
        GLenum error = glissState.error;
        glissState.error = GLISS_NO_ERROR;
        return error;
    }
}

void
glissPathFill (void)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalPathEnsureFillMask (glissState.activePath);
    glissInternalRasterizeFilledPath (glissState.activePath, glissState.activeSource);
}

void
glissSourceColor4d (GLdouble r,
                    GLdouble g,
                    GLdouble b,
                    GLdouble a)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSourceSetToColorRGBA (glissState.activeSource, r, g, b, a);
}

void
glissGenSources (GLsizei count,
                 GLuint *sources)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    GLint i;
    for (i = 0; i < count; i++) {
        glissInternalSource *source;
        sources [i] = glissInternalAllocatorNew (&glissState.sourceAllocator, sizeof (glissInternalSource), &source);
        glissInternalSourceInit (source);
    }
}

void
glissBindSource (GLuint sourceId)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSource *source = glissInternalAllocatorResolve (&glissState.sourceAllocator, sourceId);
    if (source == NULL) {
        /* FIXME: Set correct error here! */
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissState.activeSource = source;
}

void
glissGenPaths (GLsizei count,
               GLuint *paths)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    GLint i;
    for (i = 0; i < count; i++) {
        glissInternalPath *path;
        paths [i] = glissInternalAllocatorNew (&glissState.pathAllocator, sizeof (glissInternalPath), &path);
        glissInternalPathInit (path);
    }
}

void
glissBindPath (GLuint pathId)
{
    if (GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalPath *path = glissInternalAllocatorResolve (&glissState.pathAllocator, pathId);
    if (path == NULL) {
        /* FIXME: Set correct error here! */
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissState.activePath = path;
}

void
glissColorStop4d (GLdouble r,
                  GLdouble g,
                  GLdouble b,
                  GLdouble a,
                  GLdouble position)
{
    if (glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_LINEAR_GRADIENT &&
        glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_RADIAL_GRADIENT) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSourcePushGradient (glissState.activeSource,
                                     r,
                                     g,
                                     b,
                                     a,
                                     position);
}

void
glissGradientStart2d (GLdouble x,
                      GLdouble y)
{
    if (glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_LINEAR_GRADIENT &&
        glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_RADIAL_GRADIENT) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSourceSetGradientStart (glissState.activeSource, x, y);
}

void
glissGradientEnd2d (GLdouble x,
                    GLdouble y)
{
    if (glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_LINEAR_GRADIENT) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSourceSetGradientEnd (glissState.activeSource, x, y);
}

void
glissGradientRadius1d (GLdouble r)
{
    if (glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_RADIAL_GRADIENT) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalSourceSetGradientRadius (glissState.activeSource, r);
}

void
glissSubPath (GLuint id)
{
    if (glissState.state != GLISS_INTERNAL_STATE_ACCUMULATING_SUB_PATH_FILL) {
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalPath *path = glissInternalAllocatorResolve (&glissState.pathAllocator, id);
    if (path == NULL) {
        /* FIXME: Set correct error here! */
        GLISS_INTERNAL_SET_ERROR (GLISS_INVALID_OPERATION);
        return;
    }

    glissInternalPathEnsureFillMask (path);
    glissInternalRasterizeFilledSubPath (path);

    /* Update the min/max path values */
    glissState.minX = glissInternalMathMinOutOfTwo (glissState.minX, path->minX);
    glissState.minY = glissInternalMathMinOutOfTwo (glissState.minY, path->minY);
    glissState.maxX = glissInternalMathMaxOutOfTwo (glissState.maxX, path->maxX);
    glissState.maxY = glissInternalMathMaxOutOfTwo (glissState.maxY, path->maxY);
}


