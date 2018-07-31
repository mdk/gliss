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

#include "gliss-rasterizer.h"

static void
setPassFullAlphaBlend (void)
{
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc (GL_GREATER, 0.0);
    glEnable (GL_ALPHA_TEST);
}

static void
setBitFlipStencilMask (void)
{
    glStencilMask (0x01);
    glStencilOp (GL_KEEP, GL_KEEP, GL_INVERT);
    glStencilFunc (GL_ALWAYS, 0, ~0);
    glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
}

static void
setBitPassStencilMask (void)
{
    glStencilFunc (GL_EQUAL, 0x01, 0x01);
    glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP);
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

static void
rasterizeContourStencil (void *array,
                         GLint count)
{
    glVertexPointer (2, GL_DOUBLE, 0, array);

    glEnableClientState (GL_VERTEX_ARRAY);

    glDrawArrays (GL_TRIANGLE_FAN, 0, count);

    glDisableClientState (GL_VERTEX_ARRAY);
}

static void
rasterizeQuadraticStencil (void *vertexArray,
                           void *texCoordArray,
                           GLint count)
{
    glVertexPointer (2, GL_DOUBLE, 0, vertexArray);
    glTexCoordPointer (2, GL_DOUBLE, 0, texCoordArray);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);

    glissInternalShadersActivateQuadratic ();
    setPassFullAlphaBlend ();
    glDrawArrays (GL_TRIANGLES, 0, count);
    // FIXME Helper function to disable shaders?

    glDisable (GL_FRAGMENT_PROGRAM_ARB);
    glDisableClientState (GL_VERTEX_ARRAY);
    glDisableClientState (GL_TEXTURE_COORD_ARRAY);
}

static void
rasterizeCubicStencil (void *vertexArray,
                       void *texCoordArray,
                       GLint count)
{
    glVertexPointer (2, GL_DOUBLE, 0, vertexArray);
    glTexCoordPointer (3, GL_DOUBLE, 0, texCoordArray);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);

    glissInternalShadersActivateCubic ();
    setPassFullAlphaBlend ();
    glDrawArrays (GL_TRIANGLES, 0, count);
    // FIXME Helper function to disable shaders?

    glDisable (GL_FRAGMENT_PROGRAM_ARB);
    glDisableClientState (GL_VERTEX_ARRAY);
    glDisableClientState (GL_TEXTURE_COORD_ARRAY);
}

static void
rasterizeColorFiller (glissInternalSource *source,
                      GLdouble minX,
                      GLdouble minY,
                      GLdouble maxX,
                      GLdouble maxY)
{
    glColor4f (source->colorR, source->colorG, source->colorB, source->colorA);

    /* Clear the stencil as we draw */
    glStencilFunc (GL_EQUAL, 0x01, 0x01);
    glStencilOp (GL_ZERO, GL_ZERO, GL_ZERO);

    glBegin (GL_QUADS);
    glVertex2f (minX, minY);
    glVertex2f (maxX, minY);
    glVertex2f (maxX, maxY);
    glVertex2f (minX, maxY);
    glEnd ();
}

static void
calculateLinearGradientWings (GLdouble x,
                              GLdouble y,
                              GLdouble cx,
                              GLdouble cy,
                              GLdouble *xxl,
                              GLdouble *yyl,
                              GLdouble *xxr,
                              GLdouble *yyr)
{
    GLdouble temp = cx;
    cx = cy * 1000.0;
    cy = temp * 1000.0;

    /* Left wing */
    *xxl = x + cx;
    *yyl = y + (- cy);

    /* Left wing */
    *xxr = x + (- cx);
    *yyr = y + cy;
}

static void
rasterizeRadialGradientFiller (glissInternalSource *source)
{
    glissInternalList *iterator = source->gradientList;
    glissInternalGradientElement *element = (glissInternalGradientElement *) iterator->data;
    glissInternalGradientElement *nextElement;

    /* Rasterize the master (back) fill */
    glColor4f (element->colorR, element->colorG, element->colorB, element->colorA);

    glBegin (GL_QUADS);
    glVertex2f (source->x0 - source->r, source->y0 - source->r);
    glVertex2f (source->x0 + source->r, source->y0 - source->r);
    glVertex2f (source->x0 + source->r, source->y0 + source->r);
    glVertex2f (source->x0 - source->r, source->y0 + source->r);
    glEnd ();

    GLdouble rr;

    glissInternalShadersActivateRadial ();

    while (iterator->next) {

        element = (glissInternalGradientElement *) iterator->data;
        nextElement = (glissInternalGradientElement *) iterator->next->data;

        glColor4f (element->colorR, element->colorG, element->colorB, element->colorA);
        glSecondaryColor3d (nextElement->colorR, nextElement->colorG, nextElement->colorB);

        rr = source->r * element->position;

        glBegin (GL_QUADS);
        glTexCoord4f (-1.0f, -1.0f, nextElement->position * (1.0 / element->position), nextElement->colorA);
        glVertex2f (source->x0 - rr, source->y0 - rr);

        glTexCoord4f (1.0f, -1.0f, nextElement->position * (1.0 / element->position), nextElement->colorA);
        glVertex2f (source->x0 + rr, source->y0 - rr);

        glTexCoord4f (1.0f, 1.0f, nextElement->position * (1.0 / element->position), nextElement->colorA);
        glVertex2f (source->x0 + rr, source->y0 + rr);

        glTexCoord4f (-1.0f, 1.0f, nextElement->position * (1.0 / element->position), nextElement->colorA);
        glVertex2f (source->x0 - rr, source->y0 + rr);
        glEnd ();

        iterator = iterator->next;
    }

    /* Draw the final one */
    element = (glissInternalGradientElement *) iterator->data;
    glColor4f (element->colorR, element->colorG, element->colorB, element->colorA);
    glSecondaryColor3d (element->colorR, element->colorG, element->colorB);

    rr = source->r * element->position;

    glBegin (GL_QUADS);
    glTexCoord4f (-1.0f, -1.0f, 0.0f, element->colorA);
    glVertex2f (source->x0 - rr, source->y0 - rr);

    glTexCoord4f (1.0f, -1.0f, 0.0f, element->colorA);
    glVertex2f (source->x0 + rr, source->y0 - rr);

    glTexCoord4f (1.0f, 1.0f, 0.0f, element->colorA);
    glVertex2f (source->x0 + rr, source->y0 + rr);

    glTexCoord4f (-1.0f, 1.0f, 0.0f, element->colorA);
    glVertex2f (source->x0 - rr, source->y0 + rr);
    glEnd ();

    glDisable (GL_FRAGMENT_PROGRAM_ARB);
}

static void
rasterizeGradientFiller (glissInternalSource *source)
{
    /* Calculate the slope */
    GLdouble cx = source->x1 - source->x0;
    GLdouble cy = source->y1 - source->y0;

    GLdouble curx = source->x0 + (cx * -1000.0);
    GLdouble cury = source->y0 + (cy * -1000.0);
    GLdouble cur_xxl;
    GLdouble cur_yyl;
    GLdouble cur_xxr;
    GLdouble cur_yyr;

    //printf ("{%.2f %.2f} {%.2f %.2f}\n", prev_xxl, prev_yyl, prev_xxr, prev_yyr);
    calculateLinearGradientWings (curx, cury, cx, cy,
                                  &cur_xxl, &cur_yyl, &cur_xxr, &cur_yyr);

    glissInternalList *iterator = source->gradientList;
    glissInternalGradientElement *element = (glissInternalGradientElement *) iterator->data;

    /* Clear the stencil as we draw */
    glStencilFunc (GL_EQUAL, 0x01, 0x01);
    glStencilOp (GL_ZERO, GL_ZERO, GL_ZERO);

    glBegin (GL_QUADS);
    glColor4f (element->colorR, element->colorG, element->colorB, element->colorA);
    glVertex2f (cur_xxl, cur_yyl);
    glVertex2f (cur_xxr, cur_yyr);

    while (iterator) {
        element = (glissInternalGradientElement *) iterator->data;

        glissInternalGradientElement *element = (glissInternalGradientElement *) iterator->data;

        curx = source->x0 + (cx * element->position);
        cury = source->y0 + (cy * element->position);

        calculateLinearGradientWings (curx, cury, cx, cy,
                                      &cur_xxl, &cur_yyl, &cur_xxr, &cur_yyr);

        glColor4f (element->colorR, element->colorG, element->colorB, element->colorA);
        glVertex2f (cur_xxr, cur_yyr);
        glVertex2f (cur_xxl, cur_yyl);

        /* Finished quad, start new one */

        glVertex2f (cur_xxl, cur_yyl);
        glVertex2f (cur_xxr, cur_yyr);

        iterator = iterator->next;
    }

    /* Final quad finish */
    curx = source->x0 + (cx * 1000.0);
    cury = source->y0 + (cy * 1000.0);

    calculateLinearGradientWings (curx, cury, cx, cy,
                                  &cur_xxl, &cur_yyl, &cur_xxr, &cur_yyr);

    glVertex2f (cur_xxr, cur_yyr);
    glVertex2f (cur_xxl, cur_yyl);
    glEnd ();
}

GLISS_INTERNAL void
glissInternalRasterizeFilledSubPath (glissInternalPath *path)
{
    glEnable (GL_STENCIL_TEST);
    setBitFlipStencilMask ();

    /* If we have a contour, fill it */
    if (path->fillMaskContourSize > 0)
        rasterizeContourStencil (path->fillMaskContourVertexArray,
                                 path->fillMaskContourSize);

    /* If we have quadratic triangles, draw them */
    if (path->fillMaskQuadraticSize > 0)
        rasterizeQuadraticStencil (path->fillMaskQuadraticVertexArray,
                                   path->fillMaskQuadraticTexCoordArray,
                                   path->fillMaskQuadraticSize);

    /* If we have cubic triangles, draw them */
    if (path->fillMaskCubicSize > 0)
        rasterizeCubicStencil (path->fillMaskCubicVertexArray,
                               path->fillMaskCubicTexCoordArray,
                               path->fillMaskCubicSize);

    setBitPassStencilMask ();
    glDisable (GL_STENCIL_TEST);
}

GLISS_INTERNAL void
glissInternalRasterizeMask (glissInternalSource *source,
                            GLdouble minX,
                            GLdouble minY,
                            GLdouble maxX,
                            GLdouble maxY)
{
    glEnable (GL_STENCIL_TEST);
    setBitPassStencilMask ();

    switch (source->sourceType) {

        case GLISS_INTERNAL_SOURCE_TYPE_COLOR:
            rasterizeColorFiller (source, minX, minY, maxX, maxY);
            break;

        case GLISS_INTERNAL_SOURCE_TYPE_LINEAR_GRADIENT:
            rasterizeGradientFiller (source);
            break;

        default:
            break;
    }

    glDisable (GL_STENCIL_TEST);
}

GLISS_INTERNAL void
glissInternalRasterizeFilledPath (glissInternalPath *path,
                                  glissInternalSource *source)
{
    glEnable (GL_STENCIL_TEST);
    setBitFlipStencilMask ();

    /* If we have a contour, fill it */
    if (path->fillMaskContourSize > 0)
        rasterizeContourStencil (path->fillMaskContourVertexArray,
                                 path->fillMaskContourSize);

    /* If we have quadratic triangles, draw them */
    if (path->fillMaskQuadraticSize > 0)
        rasterizeQuadraticStencil (path->fillMaskQuadraticVertexArray,
                                   path->fillMaskQuadraticTexCoordArray,
                                   path->fillMaskQuadraticSize);

    /* If we have cubic triangles, draw them */
    if (path->fillMaskCubicSize > 0)
        rasterizeCubicStencil (path->fillMaskCubicVertexArray,
                               path->fillMaskCubicTexCoordArray,
                               path->fillMaskCubicSize);

    setBitPassStencilMask ();

    switch (source->sourceType) {

        case GLISS_INTERNAL_SOURCE_TYPE_COLOR:
            rasterizeColorFiller (source, path->minX, path->minY, path->maxX, path->maxY);
            break;

        case GLISS_INTERNAL_SOURCE_TYPE_LINEAR_GRADIENT:
            rasterizeGradientFiller (source);
            break;

        case GLISS_INTERNAL_SOURCE_TYPE_RADIAL_GRADIENT:
            rasterizeRadialGradientFiller (source);
            break;

        default:
            break;
    }

    glDisable (GL_STENCIL_TEST);
}

