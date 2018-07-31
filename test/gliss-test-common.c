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

#include "gliss-test-common.h"

int glutWindow = 0;

void (*onExitFunc) (void) = NULL;

static void
onKeyPress (unsigned char key,
            int x,
            int y)
{
    glutDestroyWindow (glutWindow);
    if (onExitFunc)
        onExitFunc ();

    if (key == 'y')
        exit (0);
    else {
        glissTestPrintFailure ("Rendering not correct!");
        exit (128);
    }
}

static void
onNonInteractiveIdle ()
{
    glutDestroyWindow (glutWindow);
    if (onExitFunc)
        onExitFunc ();

    exit (0);
}

/* Returns the current time in microseconds */
long
glissTestGetTime (void)
{
    static struct timeval tv;
    gettimeofday (&tv, NULL);

    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void
glissTestPrintTabbed (const char *entry,
                      const char *value)
{
    int dots;
    int i;

    dots = 78 - (strlen (entry) + 1) - (strlen (value) + 1);

    printf ("%s ", entry);

    for (i = 0; i < dots; i++)
        printf (".");

    printf (" %s\n", value);
}

void
glissTestPrintMeasuredTime (const char *entry,
                            long startTime)
{
    static char buffer [200];

    sprintf (buffer, "%ld us", glissTestGetTime () - startTime);
    glissTestPrintTabbed (entry, buffer);
}

void
glissTestPrintValue (const char *entry,
                     GLdouble v)
{
    static char buffer [200];

    sprintf (buffer, "%.2f", v);
    glissTestPrintTabbed (entry, buffer);
}

void
glissTestPrintMeasuredPerSec (const char *entry,
                              long startTime,
                              GLdouble multi)
{
    static char buffer [200];

    long elapsed = glissTestGetTime () - startTime;

    sprintf (buffer, "%.0f per sec", (1000000.0 / elapsed) * multi);
    glissTestPrintTabbed (entry, buffer);
}

void
glissTestPrintMeasuredPerSecMillions (const char *entry,
                                      long startTime,
                                      GLdouble multi)
{
    static char buffer [200];

    long elapsed = glissTestGetTime () - startTime;

    sprintf (buffer, "%.3fM per sec", ((1000000.0 / elapsed) * multi) / 1000000);
    glissTestPrintTabbed (entry, buffer);
}

void
glissTestPrintFailure (const char *failureText)
{
    printf ("FAILURE: %s\n", failureText);
}

void
glissTestInitWindowAndEverything (int *argc,
                                  char **argv,
                                  void *renderFunc)
{
    int i;
    int nonInteractiveMode = 0;

    for (i = 0; i < *argc; i++) {
        if (strcmp (argv [i], "--non-interactive") == 0)
            nonInteractiveMode = GL_TRUE;
    }

    glutInit (argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitWindowSize (640, 480);

    glutWindow = glutCreateWindow (argv[0]);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (-320, 320, 240, -240, -1000.0, 1000.0);

    glutDisplayFunc (renderFunc);
    glutKeyboardFunc (onKeyPress);

    if (nonInteractiveMode)
        glutIdleFunc (onNonInteractiveIdle);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

int
glissTestMainLoop (void *exitFunc)
{
    onExitFunc = exitFunc;
    glutMainLoop ();
    return 0;
}


