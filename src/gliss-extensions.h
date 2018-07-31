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

#ifndef ___GLISS_EXTENSIONS_H___
#define ___GLISS_EXTENSIONS_H___

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "gliss-basic.h"
#include "gliss-types.h"
#include "gliss-path.h"
#include "gliss.h"

struct _glissInternalExtensions {

    GLboolean initialized;

    void (*glGenProgramsARB) (GLuint, GLuint*);
    void (*glBindProgramARB) (GLuint, GLuint);
    void (*glProgramStringARB) (GLuint, GLuint, GLint, const GLbyte*);
};

GLISS_INTERNAL void
glissInternalInitializeExtensions (void);

/* Usefull macros */

#define GLISS_INTERNAL_INITIALIZE_EXTENSIONS if (! glissExtensions.initialized) glissInternalInitializeExtensions ()

#endif

