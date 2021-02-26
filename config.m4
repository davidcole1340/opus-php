dnl config.m4 for extension opus

PHP_ARG_WITH([opus],
  [for opus support],
  [AS_HELP_STRING([--with-opus],
    [Include opus support])])

if test "$PHP_OPUS" != "no"; then
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/opus.h"

  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists opus; then
    OPUS_VERSION=`$PKG_CONFIG opus --modversion`
    if $PKG_CONFIG opus --atleast-version=1.3.1; then
      OPUS_CFLAGS=`$PKG_CONFIG opus --cflags`
      OPUS_LIBS=`$PKG_CONFIG opus --libs`
      AC_MSG_RESULT(opus $OPUS_VERSION found)
      PHP_EVAL_LIBLINE($OPUS_LIBS, OPUS_SHARED_LIBADD)
      PHP_EVAL_INCLINE($OPUS_CFLAGS)
    else
      AC_MSG_ERROR(opus $OPUS_VERSION too old - version >= 1.3.1 required)
    fi
  else
    AC_MSG_ERROR(unable to find opus - please ensure it is detected by pkg-config)
  fi

  LIBNAME=opus
  LIBSYMBOL=opus_get_version_string

  PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  [
    AC_DEFINE(HAVE_LIBOPUS,1,[ ])
  ],
  [
    AC_MSG_ERROR([unable to locate compatible opus version])
  ],[])

  PHP_SUBST(OPUS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(opus, opus.c, $ext_shared)
fi
