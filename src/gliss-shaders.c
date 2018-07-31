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

#include "gliss-shaders.h"

extern glissInternalExtensions glissExtensions;

GLuint quadraticShaderId = 0;

GLuint cubicShaderId = 0;

GLuint radialShaderId = 0;

static const char *quadraticShaderSource =
"!!ARBfp1.0\n\
PARAM c[1] = { { 1, 0 } };\n\
TEMP R0;\n\
MUL R0.x, fragment.texcoord[0], fragment.texcoord[0];\n\
SLT R0.x, R0, fragment.texcoord[0].y;\n\
ABS R0.x, R0;\n\
CMP R0.x, -R0, c[0].y, c[0];\n\
CMP result.color, -R0.x, c[0].y, fragment.color.primary;\n\
END";

static const char *cubicShaderSource =
"!!ARBfp1.0\n\
PARAM c[1] = { { 1, 0, 1e-06 } };\n\
TEMP R0;\n\
MUL R0.x, fragment.texcoord[0], fragment.texcoord[0];\n\
MUL R0.x, fragment.texcoord[0], R0;\n\
MAD R0.y, fragment.texcoord[0], fragment.texcoord[0].z, c[0].z;\n\
SLT R0.x, R0.y, R0;\n\
ABS R0.x, R0;\n\
CMP R0.x, -R0, c[0].y, c[0];\n\
CMP result.color, -R0.x, c[0].y, fragment.color.primary;\n\
END";

static const char *radialShaderSource =
"!!ARBfp1.0\n\
PARAM c[1] = { { 1, 0 } };\n\
TEMP R0;\n\
TEMP R1;\n\
MUL R0.x, fragment.texcoord[0].y, fragment.texcoord[0].y;\n\
MAD R0.x, fragment.texcoord[0], fragment.texcoord[0], R0;\n\
RSQ R0.y, R0.x;\n\
RCP R0.w, R0.y;\n\
ADD R0.x, -fragment.texcoord[0].z, c[0];\n\
RCP R0.y, R0.x;\n\
ADD R0.x, R0.w, -fragment.texcoord[0].z;\n\
MUL R1.y, R0.x, R0;\n\
ADD R1.z, -R1.y, c[0].x;\n\
SLT R1.x, c[0], R0.w;\n\
MUL R0.x, R1.z, fragment.color.secondary;\n\
MUL R0.y, R1.z, fragment.color.secondary;\n\
MUL R0.z, R1, fragment.color.secondary;\n\
SLT R0.w, R0, fragment.texcoord[0].z;\n\
ADD_SAT R0.w, R0, R1.x;\n\
MUL R1.x, fragment.texcoord[0].w, R1.z;\n\
ABS R1.z, R0.w;\n\
MAD R0.w, R1.y, fragment.color.primary, R1.x;\n\
MAD R0.x, R1.y, fragment.color.primary, R0;\n\
MAD R0.y, R1, fragment.color.primary, R0;\n\
MAD R0.z, R1.y, fragment.color.primary, R0;\n\
CMP R1.x, -R1.z, c[0].y, c[0];\n\
CMP result.color, -R1.x, R0, c[0].y;\n\
END";

static GLuint
loadShader (GLuint type,
            const char *source)
{
    GLuint shaderNum;

    glEnable (type);
	glissExtensions.glGenProgramsARB (1, &shaderNum);
	glissExtensions.glBindProgramARB (type, shaderNum);
	glissExtensions.glProgramStringARB (type, GL_PROGRAM_FORMAT_ASCII_ARB, strlen (source), (const GLbyte *) source);
	glDisable (type);

	return shaderNum;
}

GLISS_INTERNAL void
glissInternalShadersActivateQuadratic (void)
{
    GLISS_INTERNAL_INITIALIZE_EXTENSIONS;

    if (quadraticShaderId == 0)
        quadraticShaderId = loadShader (GL_FRAGMENT_PROGRAM_ARB, quadraticShaderSource);

    glEnable (GL_FRAGMENT_PROGRAM_ARB);
	glissExtensions.glBindProgramARB (GL_FRAGMENT_PROGRAM_ARB, quadraticShaderId);
}

GLISS_INTERNAL void
glissInternalShadersActivateCubic (void)
{
    GLISS_INTERNAL_INITIALIZE_EXTENSIONS;

    if (cubicShaderId == 0)
        cubicShaderId = loadShader (GL_FRAGMENT_PROGRAM_ARB, cubicShaderSource);

    glEnable (GL_FRAGMENT_PROGRAM_ARB);
	glissExtensions.glBindProgramARB (GL_FRAGMENT_PROGRAM_ARB, cubicShaderId);
}

GLISS_INTERNAL void
glissInternalShadersActivateRadial (void)
{
    GLISS_INTERNAL_INITIALIZE_EXTENSIONS;

    if (radialShaderId == 0)
        radialShaderId = loadShader (GL_FRAGMENT_PROGRAM_ARB, radialShaderSource);

    glEnable (GL_FRAGMENT_PROGRAM_ARB);
	glissExtensions.glBindProgramARB (GL_FRAGMENT_PROGRAM_ARB, radialShaderId);
}

