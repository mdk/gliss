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

#include "gliss-state.h"

glissInternalSource defaultSource = { GLISS_INTERNAL_SOURCE_TYPE_COLOR, 1.0, 1.0, 1.0, 1.0, NULL, NULL, NULL, 0.0, 0.0, 0.0, 0.0, 0.0 };

glissInternalPath defaultPath = { NULL, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, 0, NULL, GL_FALSE, 0.0, 0.0, 0.0, 0.0 };

glissInternalState glissState = { GLISS_INTERNAL_STATE_IDLE, GLISS_NO_ERROR, &defaultPath, &defaultSource, {0, -1, NULL}, {0, -1, NULL}, 0.0, 0.0, 0.0, 0.0 };

