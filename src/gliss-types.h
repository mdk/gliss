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

#ifndef ___GLISS_TYPES_H___
#define ___GLISS_TYPES_H___

typedef struct _glissInternalSlice glissInternalSlice;

typedef struct _glissInternalState glissInternalState;

typedef struct _glissInternalList glissInternalList;

typedef struct _glissInternalLineElement glissInternalLineElement;

typedef struct _glissInternalLineAccumulator glissInternalLineAccumulator;

typedef struct _glissInternalQuadraticAccumulator glissInternalQuadraticAccumulator;

typedef struct _glissInternalCubicAccumulator glissInternalCubicAccumulator;

typedef struct _glissInternalQuadraticElement glissInternalQuadraticElement;

typedef struct _glissInternalCubicElement glissInternalCubicElement;

typedef struct _glissInternalGradientElement glissInternalGradientElement;

typedef struct _glissInternalPath glissInternalPath;

typedef struct _glissInternalExtensions glissInternalExtensions;

typedef struct _glissInternalSource glissInternalSource;

typedef struct _glissInternalAllocator glissInternalAllocator;

typedef struct _glissInternalChunk glissInternalChunk;

#define GLISS_INTERNAL_MATRIX_ELEMENT(m,x,y) (m [y * 4 + x])

#ifndef GLISS_INTERNAL_EPSILON
#define GLISS_INTERNAL_EPSILON 0.00000001f
#endif

#endif

