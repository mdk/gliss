AC_INIT([Gliss light and magic library], [0.1.0], [mdk@mdk.am], [gliss])
AC_CANONICAL_SYSTEM

AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR([src/gliss-basic.h])
AM_MAINTAINER_MODE

AM_INIT_AUTOMAKE

AC_PROG_CC
AM_PROG_LIBTOOL

# build with test support
AC_ARG_WITH(test, 
    AC_HELP_STRING([--with-test], [Build with support for internal API testingi and test programs]),
    [
     case "${withval}" in
         yes) BUILD_WITH_TEST=yes ;;
         no)  BUILD_WITH_TEST=no ;;
         *)   AC_MSG_ERROR(bad value ${withval} for --with-test) ;;
     esac],
     [BUILD_WITH_TEST=no])

if test x$BUILD_WITH_TEST = xyes; then
    AC_MSG_NOTICE(Will build with support for internal API testing + test programs)
else
    AC_MSG_NOTICE(Will build a final test-less build)
fi

AM_CONDITIONAL(BUILD_WITH_TEST, test "x$BUILD_WITH_TEST" = "xyes")

GLISS_CFLAGS="-Wall -Wmissing-prototypes -Wmissing-declarations"
GLISS_OBJ_CFLAGS="\$(CFLAGS) -I\$(top_builddir)/src/ -Wno-missing-prototypes -Wno-missing-prototypes"
GLISS_OBJ_LIBS="\$(top_builddir)/src/libgliss.la -lm -lGL -lGLU -lglut"

AC_SUBST(GLISS_CFLAGS)
AC_SUBST(GLISS_OBJ_CFLAGS)
AC_SUBST(GLISS_OBJ_LIBS)

AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])

AC_OUTPUT

# Display some status information
echo "

- Package:..........................: ${PACKAGE}
- Version...........................: ${VERSION}
- Compiler..........................: ${CC}
- With test support + test programs.: ${BUILD_WITH_TEST}

"

