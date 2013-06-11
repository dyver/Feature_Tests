# package info
AC_INIT( [autohell],[1.0.0.0],[dyver@hotmail.com] )

OLD_CXXFLAGS=$CXXFLAGS
OLD_CFLAGS=$CFLAGS

# some checks
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

CXXFLAGS=$OLD_CXXFLAGS
CFLAGS=$OLD_CFLAGS

AM_INIT_AUTOMAKE( [1.9] )

AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
    [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])

AM_CXXFLAGS="$AM_CXXFLAGS -std=c++11"

COMMON_COMPILER_FLAGS="-Wall -Wextra -fsigned-char"

if test x"$debugit" = x"yes"; then
    COMMON_COMPILER_FLAGS="$COMMON_COMPILER_FLAGS -g -O0 -DDEBUG"
else
    COMMON_COMPILER_FLAGS="$COMMON_COMPILER_FLAGS -O3 -DNDEBUG"
fi

AM_CXXFLAGS="$AM_CXXFLAGS $COMMON_COMPILER_FLAGS"
AM_CFLAGS="$AM_CFLAGS $COMMON_COMPILER_FLAGS"


# distribute the changes
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# some config
AC_CONFIG_HEADER(config.h)
AC_CONFIG_FILES([Makefile])

# make out
AC_OUTPUT
