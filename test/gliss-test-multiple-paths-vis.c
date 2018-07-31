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

GLuint path1;
GLuint path2;
GLuint path3;
GLuint path4;

static void
generatePaths (void)
{
    /* Path 1 */
    glissGenPaths (1, &path1);
    glissBindPath (path1);

    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (-100.0, -100.0);
    glissLineTo2d (100.0, -100.0);
    glissLineTo2d (100.0, 100.0);
    glissLineTo2d (-100.0, 100.0);
    glissLineTo2d (-100.0, -100.0);
    glissEnd ();

    /* Path 2 */
    glissGenPaths (1, &path2);
    glissBindPath (path2);

    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (0.0, -100.0);
    glissLineTo2d (100.0, 100.0);
    glissLineTo2d (-100.0, 100.0);
    glissLineTo2d (0.0, -100.0);
    glissEnd ();

    /* Path 3 */
    glissGenPaths (1, &path3);
    glissBindPath (path3);

    glissBegin (GLISS_QUADRATIC_PATH);
    glissMoveTo2d (0.0, -100.0);
    glissQuadraticTo4d (100.0, 0.0, 0, 100);
    glissQuadraticTo4d (-100.0, 0.0, 0, -100);
    glissEnd ();

    /* Path 4 */
    glissGenPaths (1, &path4);
    glissBindPath (path4);
    glissBegin (GLISS_QUADRATIC_PATH);
    glissMoveTo2d (-100.0, -100.0);
    glissQuadraticTo4d (0, -130, 100, -100);
    glissQuadraticTo4d (40, 0, 100, 100);
    glissQuadraticTo4d (0, 130, -100, 100);
    glissQuadraticTo4d (-40, 0, -100, -100);
    glissEnd ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glPushMatrix ();
    glTranslatef (-160, -120, 0);
    glissBindPath (path1);
    glissPathFill ();
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (160, -120, 0);
    glissBindPath (path2);
    glissPathFill ();
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (-160, 120, 0);
    glissBindPath (path3);
    glissPathFill ();
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (160, 120, 0);
    glissBindPath (path4);
    glissPathFill ();
    glPopMatrix ();

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

