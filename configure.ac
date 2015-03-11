AC_PREREQ(2.6)
AC_INIT(libunit, 0.1, j_kubik@wp.pl)
AM_INIT_AUTOMAKE(1.11)

AC_PREFIX_DEFAULT(/usr)

AC_PROG_CXX
AC_PROG_INSTALL

AC_LANG([C++])
AX_CHECK_COMPILE_FLAG([-std=c++1y],
                        [ CXXFLAGS="$CXXFLAGS -std=c++1y" ],
                        [ AC_MSG_ERROR([Sorry, your your compiler doesn't support C++1y.]) ])

AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[class Foo{ public: int i; inline auto operator*(){ return i; }  };]],
                 [[Foo f;]])], [], [AC_MSG_ERROR([Sorry, your implementation of C++1y is buggy.])])

libunitincludedir=$includedir/libunit
AC_SUBST(libunitincludedir)
AC_SUBST(CXXFLAGS)

AC_CONFIG_FILES([Makefile libunit.pc])
AC_OUTPUT
