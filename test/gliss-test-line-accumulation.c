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

int
main (int argc,
      char **argv)
{
    glissBegin (GLISS_LINE_PATH);
    glissMoveTo2d (100.0, 100.0);
    glissLineTo2d (200.0, 100.0);
    glissLineTo2d (200.0, 200.0);
    glissLineTo2d (100.0, 200.0);
    glissLineTo2d (100.0, 100.0);
    glissEnd ();

    if (glissGetError () != GLISS_NO_ERROR) {
        glissTestPrintFailure ("Error during path construction");
        return 128;
    }

    return 0;
}

