dnl
dnl Configuring Gauche-al
dnl  process this file with autoconf to generate 'configure'.
dnl

AC_PREREQ([2.54])
AC_INIT(Gauche-al, 1.0, )
dnl If you want to use the system name (OS, architecture, etc) in the
dnl configure, uncomment the following line.  In such a case, you need
dnl to copy config.guess and config.sub from automake distribution.
AC_CANONICAL_SYSTEM

dnl Replace @LOCAL_PATHS@ by --with-local option.
AC_ARG_WITH(local,
  AC_HELP_STRING([--with-local=PATH:PATH...],
                 [For each PATH, add PATH/include to the include search
paths and PATH/lib to the library search paths.  Useful if you have some
libraries installed in non-standard places. ]),
  [
    case $with_local in
      yes|no|"") ;;  #no effect
      *) LOCAL_PATHS=$with_local ;;
    esac
  ])
AC_SUBST(LOCAL_PATHS)

dnl Set up gauche related commands.  The commands are set by scanning
dnl PATH.  You can override them by "GOSH=/my/gosh ./configure" etc.
dnl These variables may contain spaces in the pathnames (especially on
dnl Windows); Makefile.ins and other files that refer to those variables
dnl have to quote them properly.
AC_PATH_PROG([GOSH], gosh)
AC_PATH_PROG([GAUCHE_CONFIG], gauche-config)
AC_PATH_PROG([GAUCHE_PACKAGE], gauche-package)
AC_PATH_PROG([GAUCHE_INSTALL], gauche-install)
AC_PATH_PROG([GAUCHE_CESCONV], gauche-cesconv)

dnl Usually these parameters are set by AC_PROG_CC, but we'd rather use
dnl the same one as Gauche has been compiled with.
SOEXT=`"$GAUCHE_CONFIG" --so-suffix`
OBJEXT=`"$GAUCHE_CONFIG" --object-suffix`
EXEEXT=`"$GAUCHE_CONFIG" --executable-suffix`
AC_SUBST(SOEXT)
AC_SUBST(OBJEXT)
AC_SUBST(EXEEXT)

ac_default_prefix=`"$GAUCHE_CONFIG" --prefix`
dnl On MSYS2/MinGW-w64, we must overwrite prefix because
dnl /mingw64/etc/config.site sets prefix=/mingw64.
case "$target" in
  *-mingw*)
    case "$prefix" in
      /ucrt64 | /mingw64 | /mingw32)
        prefix=`"$GAUCHE_CONFIG" --prefix`;;
    esac;;
esac

GAUCHE_PKGINCDIR=`"$GAUCHE_CONFIG" --pkgincdir`
GAUCHE_PKGLIBDIR=`"$GAUCHE_CONFIG" --pkglibdir`
GAUCHE_PKGARCHDIR=`"$GAUCHE_CONFIG" --pkgarchdir`
AC_SUBST(GAUCHE_PKGINCDIR)
AC_SUBST(GAUCHE_PKGLIBDIR)
AC_SUBST(GAUCHE_PKGARCHDIR)

dnl Check for headers.
dnl Add your macro calls to check required headers, if you have any.

dnl Check for other programs.
dnl Add your macro calls to check existence of programs, if you have any.
AC_CHECK_PROGS(MAKEINFO, makeinfo)
AC_CHECK_PROGS(GZIP_PROGRAM, gzip)


dnl Check for libraries
dnl Add your macro calls to check required libraries, if you have any.

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
	*-apple-darwin*)
		AC_DEFINE(MacOSX, 1)
		AL_LIBS='-framework OpenAL'
		;;
	*)
		;;
	esac
], ,)
AC_CHECK_HEADERS(AL/al.h, [
	case $target in
	*-cygwin*|*-mingw*)
		AL_LIBS='-lalut -lopenal32'
		;;
	*)
		AL_LIBS='-lalut -lopenal'
		;;
	esac
], ,)
AC_SUBST(AL_LIBS)

dnl for MSYS2/MinGW-w64
MINGWDIR=""
case $target in
	*-mingw*)
		case "$MSYSTEM" in
			UCRT64)  MINGWDIR="/ucrt64/bin";;
			MINGW64) MINGWDIR="/mingw64/bin";;
			MINGW32) MINGWDIR="/mingw32/bin";;
			*)       MINGWDIR="/mingw/bin";;
		esac;;
	*)               MINGWDIR="";;
esac
AC_SUBST(MINGWDIR)

dnl Creating gpd (gauche package description) file
GAUCHE_PACKAGE_CONFIGURE_ARGS="`echo ""$ac_configure_args"" | sed 's/[\\""\`\$]/\\\&/g'`"
AC_MSG_NOTICE([creating ${PACKAGE_NAME}.gpd])
"$GAUCHE_PACKAGE" make-gpd "$PACKAGE_NAME" \
  -version "$PACKAGE_VERSION" \
  -configure "./configure $GAUCHE_PACKAGE_CONFIGURE_ARGS"

dnl Output
echo $PACKAGE_VERSION > VERSION
AC_OUTPUT(Makefile src/Makefile lib/Makefile doc/Makefile)

