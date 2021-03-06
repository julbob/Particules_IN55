######################################################################
# Automatically generated by qmake (2.01a) Sun Mar 6 14:27:38 2011
######################################################################

CONFIG += console release
QT += core gui opengl
TARGET = TP01
TEMPLATE = app

DEPENDPATH += src
INCLUDEPATH = ../Common/ src "../glew-mingw\include"
win32:LIBS += -L"../glew-mingw\lib" -lglew32

DESTDIR = release
OBJECTS_DIR = obj

# Input
HEADERS += \
    ../Common/GlFramework.h \
    ../Common/GlWindow.h \
    ../Common/LF_String.h \
    ../Common/Object3D.h \
    ../Common/Shapes/Basis.h \
    ../Common/Shapes/Shape.h \
    ../Common/Shapes/ParametricShape.h \
    ../Common/Shapes/Cubes.h \
    ../Common/Shapes/Cylinder.h \
    ../Common/Shapes/Pyramid.h \
    ../Common/Shapes/Star.h \
    src/Vector3f.h \
    src/Quaternion.h \
    src/Camera.h \
    particle.h \
    src/scene.h

SOURCES += \
    ../Common/GlFramework.cpp \
    ../Common/GlWindow.cpp \
    ../Common/LF_String.cpp \
    ../Common/Object3D.cpp \
    ../Common/Shapes/Basis.cpp \
    ../Common/Shapes/Shape.cpp \
    ../Common/Shapes/ParametricShape.cpp \
    ../Common/Shapes/Cubes.cpp \
    ../Common/Shapes/Cylinder.cpp \
    ../Common/Shapes/Pyramid.cpp \
    ../Common/Shapes/Star.cpp \
    src/TP01.cpp \
    src/main.cpp \
    src/Vector3f.cpp \
    src/Quaternion.cpp \
    src/Camera.cpp \
    particle.cpp \
    src/scene.cpp
