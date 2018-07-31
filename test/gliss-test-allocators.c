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

struct {

    double x;
    double y;
    double z;

} typedef MyStruct;

void
doSmall (void)
{
    long start = glissTestGetTime ();

    glissInternalAllocator allocator;
    int i;

    glissInternalAllocatorInit (&allocator);

    for (i = 0; i < 100; i++) {
        MyStruct *str;
        glissInternalAllocatorNew (&allocator, sizeof (MyStruct), &str);
        str->x = 1;
        str->y = 2;
        str->z = 3;
    }

    glissTestPrintMeasuredTime ("Small (100) time: ", start);
}

void
doMedium (void)
{
    long start = glissTestGetTime ();

    glissInternalAllocator allocator;
    int i;

    glissInternalAllocatorInit (&allocator);

    for (i = 0; i < 1000; i++) {
        MyStruct *str;
        glissInternalAllocatorNew (&allocator, sizeof (MyStruct), &str);
        str->x = 1;
        str->y = 2;
        str->z = 3;
    }

    glissTestPrintMeasuredTime ("Medium (1000) time: ", start);
}

void
doLarge (void)
{
    long start = glissTestGetTime ();

    glissInternalAllocator allocator;
    int i;

    glissInternalAllocatorInit (&allocator);

    for (i = 0; i < 10000; i++) {
        MyStruct *str;
        glissInternalAllocatorNew (&allocator, sizeof (MyStruct), &str);
        str->x = 1;
        str->y = 2;
        str->z = 3;
    }

    glissTestPrintMeasuredTime ("Large (10000) time: ", start);
}

int
main (int argc,
      char **argv)
{

    doSmall ();
    doMedium ();
    doLarge ();

    return 0;
}

