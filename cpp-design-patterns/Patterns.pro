TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Main.cpp \
    builder/StepBuilder1.cpp \
    builder/StepBuilder2.cpp

HEADERS += \
    builder/StepBuilder1.h \
    builder/StepBuilder2.h
