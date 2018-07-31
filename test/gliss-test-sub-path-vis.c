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

GLuint outerPath;
GLuint innerPath;

static void
generatePaths (void)
{
    glissGenPaths (1, &outerPath);
    glissBindPath (outerPath);

    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (- 100.0, - 100.0);
    glissLineTo2d (+ 100.0, - 100.0);
    glissLineTo2d (+ 100.0, + 100.0);
    glissLineTo2d (- 100.0, + 100.0);
    glissLineTo2d (- 100.0, - 100.0);
    glissEnd ();

    glissGenPaths (1, &innerPath);
    glissBindPath (innerPath);

    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (- 50.0, - 50.0);
    glissLineTo2d (+ 50.0, - 50.0);
    glissLineTo2d (+ 50.0, + 50.0);
    glissLineTo2d (- 50.0, + 50.0);
    glissLineTo2d (- 50.0, - 50.0);
    glissEnd ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glissBindPath (outerPath);

    glissBegin (GLISS_SUB_PATH_FILL);
    glissSubPath (innerPath);
    glissEnd ();

    glutSwapBuffers();
}

int
main (int argc,
      char **argv)
{
    glissTestInitWindowAndEverything (&argc, argv, sceneRender);

    generatePaths ();

    return glissTestMainLoop (NULL);
}

