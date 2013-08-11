TEMPLATE = lib
TARGET = qmldecorator
CONFIG += static

HEADERS += \
    qmljsscanner.h \
#    decorator.h \
    qmlsyntaxhighlighter.h \
    abstractdecorator.h \
    qmlsyntaxhighlighterpalette.h

SOURCES += \
    qmljsscanner.cpp \
#    decorator.cpp \
    qmlsyntaxhighlighter.cpp \
    abstractdecorator.cpp \
    qmlsyntaxhighlighterpalette.cpp
