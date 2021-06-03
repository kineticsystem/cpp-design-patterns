TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Main.cpp \
    builder/StepBuilder1.cpp \
    builder/StepBuilder2.cpp \
    builder/StepBuilder3.cpp

HEADERS += \
    builder/StepBuilder1.h \
    builder/StepBuilder2.h \
    builder/StepBuilder3.h \
    factory/Factory1.h
