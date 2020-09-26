TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "/home/marek/R/x86_64-pc-linux-gnu-library/4.0/Rcpp/include"

SOURCES += \
    CayenneLPP_Dec.cpp \
    RCppCayenne.cpp

HEADERS += \
    CayenneLPP.hpp \
    CayenneLPP_Dec.h
