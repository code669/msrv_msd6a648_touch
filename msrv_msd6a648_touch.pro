TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    msrv_msd6a648_touch.cpp

HEADERS += \
    msrv_msd6a648_touch.h \
    ffprotocol_info.h \
    commands_def.h \
    hid-tp-coords-ops.h

