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

#ifndef ___GLISS_H___
#define ___GLISS_H___

#include <GL/gl.h>

/* Begin operations */

#define GLISS_LINE_PATH 1

#define GLISS_QUADRATIC_PATH 2

#define GLISS_CUBIC_PATH 3

#define GLISS_LINEAR_GRADIENT 4

#define GLISS_RADIAL_GRADIENT 5

#define GLISS_SUB_PATH_FILL 6

/* Error enums */

#define GLISS_NO_ERROR 0

#define GLISS_INVALID_ENUM 1

#define GLISS_INVALID_OPERATION 2

/* API */

void
glissBegin (GLenum mode);

void
glissEnd (void);

void
glissLineTo2d (GLdouble x,
               GLdouble y);

void
glissQuadraticTo4d (GLdouble cX,
                    GLdouble cY,
                    GLdouble tX,
                    GLdouble tY);

void
glissCubicTo6d (GLdouble c1X,
                GLdouble c1Y,
                GLdouble c2X,
                GLdouble c2Y,
                GLdouble tX,
                GLdouble tY);

void
glissMoveTo2d (GLdouble x,
               GLdouble y);

void
glissPathFill (void);

GLenum
glissGetError (void);

void
glissSourceColor4d (GLdouble r,
                    GLdouble g,
                    GLdouble b,
                    GLdouble a);

void
glissGenSources (GLsizei count,
                 GLuint *sources);

void
glissBindSource (GLuint sourceId);

void
glissGenPaths (GLsizei count,
               GLuint *paths);

void
glissBindPath (GLuint pathId);

void
glissColorStop4d (GLdouble r,
                  GLdouble g,
                  GLdouble b,
                  GLdouble a,
                  GLdouble position);

void
glissGradientStart2d (GLdouble x,
                      GLdouble y);

void
glissGradientEnd2d (GLdouble x,
                    GLdouble y);

void
glissGradientRadius1d (GLdouble r);

void
glissSubPath (GLuint id);

#endif

