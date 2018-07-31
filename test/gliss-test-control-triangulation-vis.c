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

#include <stdlib.h>
#include <stdio.h>
#include "gliss-test-common.h"
#include "gliss-geometry.h"

static void
drawControlPointsAsTriangles (GLdouble x0,
                              GLdouble y0,
                              GLdouble x1,
                              GLdouble y1,
                              GLdouble x2,
                              GLdouble y2,
                              GLdouble x3,
                              GLdouble y3)
{
    GLenum type = glissInternalGeometryTriangulateControlPoints (x0, y0, x1, y1, x2, y2, x3, y3);

    glBegin (GL_LINES);

    switch (type) {

        case GLISS_INTERNAL_TRIANGULATION_SIDES_1:
        case GLISS_INTERNAL_TRIANGULATION_SIDES_2:
            glVertex2f (x0, y0); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);

            glVertex2f (x0, y0); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);
            break;

        case GLISS_INTERNAL_TRIANGULATION_ALIGNED_1_2:
            glVertex2f (x0, y0); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x0, y0);

            glVertex2f (x0, y0); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);
            break;

        case GLISS_INTERNAL_TRIANGULATION_ALIGNED_2_1:
            glVertex2f (x0, y0); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x0, y0);

            glVertex2f (x0, y0); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);
            break;

        case GLISS_INTERNAL_TRIANGULATION_INSIDE_1:
            glVertex2f (x0, y0); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x0, y0);

            glVertex2f (x0, y0); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);

            glVertex2f (x2, y2); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x2, y2);
           break;

        case GLISS_INTERNAL_TRIANGULATION_INSIDE_2:
            glVertex2f (x0, y0); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x0, y0);

            glVertex2f (x2, y2); glVertex2f (x1, y1);
            glVertex2f (x1, y1); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x2, y2);

            glVertex2f (x0, y0); glVertex2f (x2, y2);
            glVertex2f (x2, y2); glVertex2f (x3, y3);
            glVertex2f (x3, y3); glVertex2f (x0, y0);
           break;

        default:
           break;
    }

    glEnd ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glPushMatrix ();
    glTranslatef (-180, -120, 0);
    drawControlPointsAsTriangles (-100, 0, -50, -50, 50, -50, 100, 0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (180, -120, 0);
    drawControlPointsAsTriangles (-100, 0, 100, -50, -100, -50, 100, 0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (-180, 0, 0);
    drawControlPointsAsTriangles (-100, 0, 0, -50, 0, 50, 100, 0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (180, 0, 0);
    drawControlPointsAsTriangles (-100, 0, 0, 50, 0, -50, 100, 0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (-180, 120, 0);
    drawControlPointsAsTriangles (-100, 0, 0, -50, 0, -10, 100, 0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (180, 120, 0);
    drawControlPointsAsTriangles (-100, 0, 0, 10, 0, 50, 100, 0);
    glPopMatrix ();

    glutSwapBuffers();
}

int
main (int argc,
      char **argv)
{
    glissTestInitWindowAndEverything (&argc, argv, sceneRender);

    return glissTestMainLoop (NULL);
}

