#-------------------------------------------------
#
# Project created by QtCreator 2014-06-28T21:19:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = 3D_reconstruction
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH +=D:\vtk_qt1\include\vtk-5.10

LIBS    += -LD:\vtk_qt1\bin -llibvtkCommon -llibvtksys -llibQVTK\
-llibvtkQtChart -llibvtkViews -llibvtkWidgets -llibvtkInfovis -llibvtkRendering\
-llibvtkGraphics -llibvtkImaging -llibvtkIO -llibvtkFiltering -llibvtklibxml2\
-llibvtkDICOMParser -llibvtkpng -llibvtkpng -llibvtktiff -llibvtkzlib -llibvtkjpeg\
-llibvtkalglib -llibvtkexpat -llibvtkverdict -llibvtkmetaio -llibvtkNetCDF\
-llibvtkexoIIc -llibvtkftgl -llibvtkfreetype -llibvtkHybrid -llibvtkVolumeRendering
