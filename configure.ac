AC_PREREQ(2.54)
AC_INIT(Gauche-al 0.1)
AC_CONFIG_SRCDIR(src)

AC_CANONICAL_SYSTEM

AC_ARG_WITH(al, [  --with-al=PATH:         Use OpenAL library installed under PATH.
                          By default, Gauche-al assume OpenAL is installed in
                          the system standard location. ], [
	case $with_al in
	yes|no|"")
		;;
	*)
		AL_INCDIR="-I$with_al/include"
		AL_LIBDIR="-L$with_al/lib"
		;;
	esac
])
AC_SUBST(AL_INCDIR)
AC_SUBST(AL_LIBDIR)
INCLUDES="$INCLUDES $AL_INCDIR"
CPPFLAGS="$CPPFLAGS $AL_INCDIR"
LDFLAGS="$LDFLAGS $AL_LIBDIR"

AC_CHECK_HEADERS(OpenAL/al.h, [
	case $target in
	powerpc-apple-darwin*)
		AC_DEFINE(MacOSX, 1)
		AL_LIBS='-framework OpenAL'
		;;
	*)
		;;
	esac
], ,)

AC_CHECK_HEADERS(AL/al.h, [
	AL_LIBS='-lopenal'
], ,)

AC_SUBST(AL_LIBS)

AC_GAUCHE_INIT_EXT
AC_GAUCHE_INSTALL_TYPE(site)
AC_GAUCHE_CC
AC_GAUCHE_FLAGS

AC_PROG_INSTALL

AC_GAUCHE_FIX_LIBS

# Check for other programs.
AC_CHECK_PROGS(MAKEINFO, makeinfo)
AC_CHECK_PROGS(GZIP_PROGRAM, gzip)

AC_OUTPUT(Makefile src/Makefile lib/Makefile doc/Makefile)

