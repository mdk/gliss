MAINTAINERCLEANFILES = Makefile.in

if BUILD_WITH_TEST

INCLUDES = -DGLISS_EXPORT_ALL

endif

lib_LTLIBRARIES = libgliss.la

libgliss_includedir = $(includedir)/GL/

libgliss_include_HEADERS = gliss.h

noinst_HEADERS = \
gliss-slice.h \
gliss-basic.h \
gliss-types.h \
gliss-state.h \
gliss-list.h \
gliss-line-accumulator.h \
gliss-quadratic-accumulator.h \
gliss-elements.h \
gliss-path.h \
gliss-rasterizer.h \
gliss-extensions.h \
gliss-shaders.h \
gliss-geometry.h \
gliss-source.h \
gliss-cubic-accumulator.h \
gliss-math.h \
gliss-allocator.h

libgliss_la_SOURCES = \
gliss-slice.c \
gliss-state.c \
gliss-list.c \
gliss-line-accumulator.c \
gliss-quadratic-accumulator.c \
gliss.c \
gliss-path.c \
gliss-rasterizer.c \
gliss-extensions.c \
gliss-shaders.c \
gliss-geometry.c \
gliss-source.c \
gliss-cubic-accumulator.c \
gliss-math.c \
gliss-allocator.c

libgliss_la_CFLAGS = $(GLISS_CFLAGS)
