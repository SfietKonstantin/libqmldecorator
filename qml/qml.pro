TARGET = qmldecorator
TARGETPATH=org/SfietKonstantin/qmldecorator

QT = core gui qml
INCLUDEPATH += ../lib
LIBS +=-L../lib -lqmldecorator

SOURCES += plugin.cpp

TEMPLATE = lib
CONFIG += plugin

target.path = $$[QT_INSTALL_QML]/$$TARGETPATH
INSTALLS += target

# Install rules
qmldir.base = $$_PRO_FILE_PWD_
qmldir.files = qmldir
qmldir.path = $$[QT_INSTALL_QML]/$$TARGETPATH
INSTALLS += qmldir
