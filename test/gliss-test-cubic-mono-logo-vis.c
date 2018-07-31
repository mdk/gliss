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
generatePath (void)
{
    glissBegin (GLISS_CUBIC_PATH);
    glissMoveTo2d (23, 248.35213);
    glissCubicTo6d (23, 246.80511, 74.7466, 184.62003, 75.83756, 184.85603);
    glissCubicTo6d (76.46078, 184.99084, 99.57282, 194.8098, 127.19763, 206.67595);
    glissCubicTo6d (174.37746, 226.94188, 177.50697, 228.14035, 178.7827, 226.43083);
    glissCubicTo6d (180.71204, 223.84549, 187.3572, 209.94547, 190.87217, 201.1427);
    glissLineTo2d (193.85425, 193.67448);
    glissLineTo2d (188.83035, 190.92715);
    glissCubicTo6d (181.71071, 187.03374, 171.26844, 178.36304, 164.72952, 170.91512);
    glissCubicTo6d (158.76255, 164.11865, 148, 147.71975, 148, 145.42435);
    glissCubicTo6d (148, 144.66458, 151.41988, 148.11901, 155.59973, 153.10084);
    glissCubicTo6d (167.34039, 167.09419, 194.39526, 188.99049, 196.09436, 185.87433);
    glissCubicTo6d (198.11061, 182.17652, 199.41392, 171.26008, 199.34932, 158.61091);
    glissCubicTo6d (199.27046, 143.16872, 197.24623, 131.14711, 191.93082, 114.55347);
    glissLineTo2d (188.95233, 105.25525);
    glissLineTo2d (174.22617, 100.62616);
    glissCubicTo6d (166.12677, 98.08016, 158.00735, 95.52784, 156.183, 94.95433);
    glissCubicTo6d (149.8207, 92.95426, 153.80112, 93.06194, 163.11562, 95.14187);
    glissCubicTo6d (174.25265, 97.62878, 185.56527, 99.72929, 192.5702, 100.61097);
    glissCubicTo6d (198.73792, 101.38728, 200.09505, 100.17715, 200.7546, 93.31309);
    glissCubicTo6d (201.59552, 84.56139, 195.94794, 60.39173, 190.25017, 48.357866);
    glissCubicTo6d (187.97612, 43.554997, 186.94956, 42.519359, 182.39671, 40.434994);
    glissCubicTo6d (167.24118, 33.496565, 119.80313, 26.99806, 99.65854, 29.100751);
    glissCubicTo6d (90.95043, 30.009703, 82.00528, 32.125757, 79.21741, 33.936278);
    glissCubicTo6d (78.43163, 34.446588, 84.04815, 35.893447, 93.71741, 37.671593);
    glissCubicTo6d (102.39784, 39.267894, 108.72349, 40.725653, 107.77442, 40.911058);
    glissCubicTo6d (106.82535, 41.096463, 93.18521, 39.597545, 77.463, 37.580129);
    glissCubicTo6d (49.86144, 34.038399, 48.80861, 33.974143, 46.88613, 35.713968);
    glissCubicTo6d (42.87783, 39.341426, 37.11079, 49.256788, 35.92349, 54.562185);
    glissCubicTo6d (34.77399, 59.69873, 34.85485, 60.29395, 37.4123, 65.5212);
    glissCubicTo6d (41.77144, 74.43096, 49.87721, 80.91401, 68.32215, 90.24312);
    glissCubicTo6d (77.04415, 94.65455, 83.96884, 98.47541, 83.71034, 98.73391);
    glissCubicTo6d (83.45184, 98.99241, 76.00857, 96.21333, 67.16973, 92.55819);
    glissLineTo2d (51.09911, 85.91247);
    glissLineTo2d (27.51719, 92.51169);
    glissCubicTo6d (14.54713, 96.14127, 3.49982, 99.11092, 2.96763, 99.11092);
    glissCubicTo6d (2.35941, 99.11092, 2, 83.44205, 2, 56.92664);
    glissCubicTo6d (2, 16.304429, 2.07668, 14.583951, 4.07095, 10.464349);
    glissCubicTo6d (5.28663, 7.9530962, 7.6613004, 5.2415412, 9.82095, 3.8986252);
    glissLineTo2d (13.5, 1.6109162);
    glissLineTo2d (121.5, 1.3103692);
    glissCubicTo6d (180.9, 1.1450692, 231.90259, 1.2949592, 234.83909, 1.6434572);
    glissCubicTo6d (241.45648, 2.4287972, 247.42831, 7.2741032, 249.00763, 13.139249);
    glissCubicTo6d (249.68844, 15.667583, 249.94431, 54.120659, 249.76716, 127.2815);
    glissLineTo2d (249.5, 237.61091);
    glissLineTo2d (247.21229, 241.28996);
    glissCubicTo6d (245.86938, 243.44961, 243.15782, 245.82428, 240.64657, 247.03996);
    glissCubicTo6d (236.40165, 249.09489, 235.54309, 249.11091, 129.684, 249.11091);
    glissCubicTo6d (71.00792, 249.11091, 23, 248.76946, 23, 248.35213);
    glissEnd ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glPushMatrix ();
    glScalef (1.5, 1.5, 1.5);
    glTranslatef (-125, -125, 0);
    glissPathFill ();
    glPopMatrix ();

    glutSwapBuffers();
}

int
main (int argc,
      char **argv)
{
    glissTestInitWindowAndEverything (&argc, argv, sceneRender);

    generatePath ();

    return glissTestMainLoop (NULL);
}

