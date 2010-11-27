dnl configure.ac
dnl Process this file with autoconf to produce a configure script.
dnl

AC_INIT
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE(o2scr-ifd, 0.0.1)

AC_CONFIG_HEADERS([config.h])

PKG_CHECK_MODULES(PCSC, libpcsclite, [], [AC_MSG_ERROR([PCSC/Lite headers are required])])
AC_SUBST(PCSC_CFLAGS)
AC_SUBST(PCSC_LIBS)

LT_INIT([win32-dll disable-static])
AC_SUBST(LIBTOOL_DEPS)

AC_CONFIG_FILES([Makefile src/Makefile etc/Makefile])
AC_OUTPUT
