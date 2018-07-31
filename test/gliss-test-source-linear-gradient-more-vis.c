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

static void
generatePath (GLdouble x,
              GLdouble y)
{
    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (x - 100.0, y - 100.0);
    glissLineTo2d (x + 100.0, y - 100.0);
    glissLineTo2d (x + 100.0, y + 100.0);
    glissLineTo2d (x - 100.0, y + 100.0);
    glissLineTo2d (x - 100.0, y - 100.0);
    glissEnd ();

    glissPathFill ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glissBegin (GLISS_LINEAR_GRADIENT);
    glissGradientStart2d (300.0, 200.0);
    glissGradientEnd2d (-300.0, -200.0);
    glissColorStop4d (1.0, 1.0, 1.0, 1.0, 0.0);
    glissColorStop4d (1.0, 0.0, 0.0, 1.0, 0.2);
    glissColorStop4d (0.0, 1.0, 0.0, 1.0, 0.3);
    glissColorStop4d (0.0, 0.0, 1.0, 1.0, 0.4);
    glissColorStop4d (1.0, 1.0, 0.0, 1.0, 0.5);
    glissColorStop4d (0.0, 1.0, 1.0, 1.0, 0.6);
    glissColorStop4d (1.0, 0.0, 1.0, 1.0, 0.7);
    glissColorStop4d (1.0, 0.5, 1.0, 1.0, 0.8);
    glissColorStop4d (1.0, 1.0, 1.0, 1.0, 1.0);
    glissEnd ();

    generatePath (-160, -120);
    generatePath (160, -120);
    generatePath (160, 120);
    generatePath (-160, 120);

    glutSwapBuffers();
}

int
main (int argc,
      char **argv)
{
    glissTestInitWindowAndEverything (&argc, argv, sceneRender);

    return glissTestMainLoop (NULL);
}

