#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T06:53:07
#
#-------------------------------------------------

QT       -= core gui
#CONFIG   += c++11

QMAKE_CXXFLAGS += -std=c++1y

TARGET = unit
TEMPLATE = lib

DEFINES += LIBUNIT_LIBRARY

SOURCES +=

HEADERS += \
    include/quantity.h \
    include/unitmanip.h \
    include/cmath.h \
    include/units/SI.h \
    include/units/imperial.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    index.md \
    configure.ac \
    Makefile.am \
    libunit.pc.in
