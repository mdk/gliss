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
    glissMoveTo2d (405.94482, 316.4209);
    glissCubicTo6d (389.72709, 316.42099, 375.72808, 314.04958, 363.94775, 309.30664);
    glissCubicTo6d (352.16691, 304.56391, 342.68124, 297.52616, 335.49072, 288.19336);
    glissCubicTo6d (327.22878, 296.3022, 319.12007, 302.42198, 311.16455, 306.55273);
    glissCubicTo6d (303.36162, 310.68369, 295.71189, 312.74912, 288.21533, 312.74902);
    glissCubicTo6d (271.23275, 312.74912, 255.16831, 305.86436, 240.02197, 292.09473);
    glissCubicTo6d (225.02836, 278.17233, 217.53163, 262.94937, 217.53174, 246.42578);
    glissCubicTo6d (217.53163, 218.12194, 228.62374, 192.26584, 250.80811, 168.85742);
    glissCubicTo6d (273.14518, 145.44948, 298.46579, 133.74539, 326.77002, 133.74512);
    glissCubicTo6d (333.19557, 133.74539, 338.55039, 136.11681, 342.83447, 140.85938);
    glissCubicTo6d (347.11809, 145.60248, 349.26001, 151.33978, 349.26025, 158.07129);
    glissCubicTo6d (349.26001, 167.25122, 341.61028, 174.05948, 326.31104, 178.49609);
    glissCubicTo6d (305.96253, 184.31012, 291.58103, 190.96539, 283.1665, 198.46191);
    glissCubicTo6d (270.77376, 209.32475, 264.57748, 225.31269, 264.57764, 246.42578);
    glissCubicTo6d (264.57748, 250.86279, 266.64291, 255.14664, 270.77393, 259.27734);
    glissCubicTo6d (275.5166, 263.86733, 281.40689, 266.00926, 288.44482, 265.70312);
    glissCubicTo6d (301.75518, 265.09129, 314.07124, 252.69873, 325.39307, 228.52539);
    glissCubicTo6d (335.64349, 207.41231, 344.74667, 196.85568, 352.70264, 196.85547);
    glissCubicTo6d (359.12817, 196.85568, 364.32998, 199.2271, 368.30811, 203.96973);
    glissCubicTo6d (372.2857, 208.71277, 374.27463, 214.52656, 374.2749, 221.41113);
    glissCubicTo6d (374.27463, 224.47122, 373.73915, 229.06105, 372.66846, 235.18066);
    glissCubicTo6d (371.75022, 241.30063, 371.29124, 245.89046, 371.2915, 248.9502);
    glissCubicTo6d (371.29124, 258.89501, 375.57509, 265.16779, 384.14307, 267.76855);
    glissCubicTo6d (387.50867, 268.83966, 394.77592, 269.37514, 405.94482, 269.375);
    glissCubicTo6d (426.90479, 269.37514, 441.59228, 264.24982, 450.00732, 253.99902);
    glissCubicTo6d (457.65671, 244.8195, 461.48158, 229.59654, 461.48193, 208.33008);
    glissCubicTo6d (461.48158, 170.84659, 446.41161, 140.24767, 416.27197, 116.5332);
    glissCubicTo6d (388.73263, 94.808259, 355.83878, 83.94564, 317.59033, 83.945312);
    glissCubicTo6d (273.06868, 83.94564, 238.1859, 100.77505, 212.94189, 134.43359);
    glissCubicTo6d (190.14559, 164.42082, 178.74749, 202.134, 178.74756, 247.57324);
    glissCubicTo6d (178.74749, 289.49394, 192.13452, 324.8357, 218.90869, 353.59863);
    glissCubicTo6d (246.7536, 383.58564, 282.55435, 398.57911, 326.31104, 398.5791);
    glissCubicTo6d (338.70338, 398.57911, 352.70239, 396.2077, 368.30811, 391.46484);
    glissLineTo2d (408.46924, 376.54785);
    glissCubicTo6d (415.2007, 374.09997, 419.56105, 372.87601, 421.55029, 372.87598);
    glissCubicTo6d (427.82276, 372.87601, 433.25407, 375.40043, 437.84424, 380.44922);
    glissCubicTo6d (442.43375, 385.34508, 444.72867, 391.08238, 444.729, 397.66113);
    glissCubicTo6d (444.72867, 412.19564, 428.43474, 423.97622, 395.84717, 433.00293);
    glissCubicTo6d (371.21474, 439.73467, 348.18905, 443.10055, 326.77002, 443.10059);
    glissCubicTo6d (305.19755, 443.10055, 283.08983, 438.8932, 260.44678, 430.47852);
    glissCubicTo6d (237.95641, 422.21679, 218.67909, 411.12467, 202.61475, 397.20215);
    glissCubicTo6d (155.18631, 356.1996, 131.47214, 306.32335, 131.47217, 247.57324);
    glissCubicTo6d (131.47214, 188.82346, 147.68957, 139.71219, 180.12451, 100.23926);
    glissCubicTo6d (214.54823, 58.013048, 260.37013, 36.899788, 317.59033, 36.899414);
    glissCubicTo6d (369.30231, 36.899788, 413.59426, 52.428744, 450.46631, 83.486328);
    glissCubicTo6d (489.17361, 116.3805, 508.52743, 157.99504, 508.52783, 208.33008);
    glissCubicTo6d (508.52743, 242.75407, 500.11272, 269.22215, 483.28369, 287.73438);
    glissCubicTo6d (465.68893, 306.85883, 439.90933, 316.42099, 405.94482, 316.4209);
    glissEnd ();
}

static void
sceneRender (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glPushMatrix ();
    glTranslatef (-320, -240, 0);
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

