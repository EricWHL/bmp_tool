QT       += core gui widgets

INCLUDEPATH += inc
INCLUDEPATH += plugin/CodeGen
INCLUDEPATH += plugin/ImageGen

SOURCES += \
    src/EC_iConvLibIF.cpp \
    src/EC_Tool.cpp \
    src/EC_Zipc.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    plugin/CodeGen/EC_CodeGenerationTools.cpp \
    plugin/ImageGen/EC_ImageBinary.cpp \
    plugin/ImageGen/EC_ImageDetail.cpp \
    plugin/ImageGen/EC_ImageGenerateBMP.cpp \
    plugin/CodeGen/EC_CopyRightConfig.cpp \
    plugin/CodeGen/EC_CodeTemplate.cpp

HEADERS += \
    inc/EC_iConvLibIF.h \
    inc/EC_Tool.h \
    inc/mainwindow.h \
    inc/EC_Zipc.h \
    plugin/CodeGen/EC_CodeGenerationTools.h \
    plugin/ImageGen/EC_ImageBinary.h \
    plugin/ImageGen/EC_ImageDetail.h \
    plugin/ImageGen/EC_ImageGenerateBMP.h \
    plugin/CodeGen/EC_CopyRightConfig.h \
    plugin/CodeGen/EC_CodeTemplate.h
