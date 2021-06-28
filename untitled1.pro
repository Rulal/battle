TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        battlecontroller.cpp \
        battleground.cpp \
        buff.cpp \
        buffaction.cpp \
        main.cpp \
        unit.cpp

HEADERS += \
    battlecontroller.h \
    battleground.h \
    buff.h \
    buffaction.h \
    defines.h \
    signaltype.h \
    structures.h \
    unit.h
