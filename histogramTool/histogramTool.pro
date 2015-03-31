#-------------------------------------------------
#
# Project created by QtCreator 2012-09-03T20:39:27
#
#-------------------------------------------------

QT       += testlib

TARGET = histogramTool
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Histogram.cpp \
    ImageReader.cpp \
    HistogramTest.cpp \
    ThreadCoordTest.cpp \
    HistogramWriterTest.cpp

HEADERS += \
    Histogram.h \
    ImageReader.h \
    FileNotFoundException.h \
    HistogramTest.h \
    BinNotFoundException.h \
    InvalidHistogramException.h \
    UnitTest.h \
    RGBHistogram.h \
    ThreadCoord.h \
    HistogramWriter.h \
    HistogramWriterTest.h \
    ThreadCoordTest.h
