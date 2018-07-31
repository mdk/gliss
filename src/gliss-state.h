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

#ifndef ___GLISS_STATE_H___
#define ___GLISS_STATE_H___

#include <stdlib.h>
#include <GL/gl.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-path.h"
#include "gliss-source.h"
#include "gliss-allocator.h"
#include "gliss.h"

struct _glissInternalState {

    GLint state;
    GLenum error;

    glissInternalPath *activePath;
    glissInternalSource *activeSource;

    glissInternalAllocator sourceAllocator;
    glissInternalAllocator pathAllocator;

    GLdouble minX;
    GLdouble minY;
    GLdouble maxX;
    GLdouble maxY;
};

/* Helper macros */

#define GLISS_INTERNAL_SET_ERROR(e) if (glissState.error == 0) glissState.error = e;

#define GLISS_INTERNAL_BEGIN_OP_IN_PROGRESS (glissState.state > GLISS_INTERNAL_STATE_IDLE)

/* State definitions */

#define GLISS_INTERNAL_STATE_IDLE 0

#define GLISS_INTERNAL_STATE_ACCUMULATING_LINES 1

#define GLISS_INTERNAL_STATE_ACCUMULATING_QUADRATICS 2

#define GLISS_INTERNAL_STATE_ACCUMULATING_CUBICS 3

#define GLISS_INTERNAL_STATE_ACCUMULATING_LINEAR_GRADIENT 4

#define GLISS_INTERNAL_STATE_ACCUMULATING_RADIAL_GRADIENT 5

#define GLISS_INTERNAL_STATE_ACCUMULATING_SUB_PATH_FILL 6

#endif

