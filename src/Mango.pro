######################################################################
# Automatically generated by qmake (3.0) Fri Jun 20 00:38:13 2014
######################################################################

TEMPLATE = app
TARGET = Mango
INCLUDEPATH += .
INCLUDEPATH += ../include
LIBS += -L../lib/x64 -lLeap
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += files.h notifier.h
SOURCES += files.cpp mango.cpp notifier.cpp