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
generateFlowerPath (GLdouble x,
                    GLdouble y)
{
    glissBegin (GLISS_QUADRATIC_PATH);
    glissMoveTo2d (x, y);
    glissQuadraticTo4d (x - 100, y, x -100, y - 100);
    glissQuadraticTo4d (x, y -100, x, y);
    glissQuadraticTo4d (x + 100, y, x + 100, y - 100);
    glissQuadraticTo4d (x,y - 100, x, y);
    glissQuadraticTo4d (x + 100, y, x + 100, y + 100);
    glissQuadraticTo4d (x, y + 100, x, y);
    glissQuadraticTo4d (x - 100, y, x - 100, y + 100);
    glissQuadraticTo4d (x, y + 100, x, y);
    glissEnd ();

    glissPathFill ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glissBegin (GLISS_RADIAL_GRADIENT);
    glissGradientStart2d (0, 0);
    glissGradientRadius1d (300);
    glissColorStop4d (1.0, 1.0, 1.0, 1.0, 0.0);
    glissColorStop4d (1.0, 0.0, 0.0, 1.0, 0.7);
    glissColorStop4d (1.0, 1.0, 0.0, 1.0, 0.9);
    glissEnd ();

    generateFlowerPath (-160, -120);
    generateFlowerPath (160, -120);
    generateFlowerPath (160, 120);
    generateFlowerPath (-160, 120);

    glutSwapBuffers();
}

int
main (int argc,
      char **argv)
{
    glissTestInitWindowAndEverything (&argc, argv, sceneRender);

    return glissTestMainLoop (NULL);
}

