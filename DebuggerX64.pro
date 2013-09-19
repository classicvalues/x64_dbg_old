#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T13:22:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DebuggerX64
TEMPLATE = app


SOURCES += \
    Src/Gui/MainWindow.cpp \
    Src/main.cpp \
    Src/Gui/CPUWidget.cpp \
    Src/Memory/MapViewOfMem.cpp \
    Src/Disassembler/QBeaEngine.cpp \
    Src/DisassemblyView/AbstractTableView.cpp \
    Src/DisassemblyView/Disassembly.cpp \
    Src/DisassemblyView/HexDump.cpp

HEADERS  += \
    Src/Gui/MainWindow.h \
    Src/Gui/CPUWidget.h \
    Src/Memory/MapViewOfMem.h \
    Src/Disassembler/QBeaEngine.h \
    Src/DisassemblyView/AbstractTableView.h \
    Src/DisassemblyView/Disassembly.h \
    Src/Global/NewTypes.h \
    Src/DisassemblyView/HexDump.h

INCLUDEPATH += \
    Src/Gui \
    Src/DisassemblyView \
    Src/Memory \
    Src/BeaEngine/headers \
    Src/Disassembler \
    Src/BeaEngine

FORMS    += \
    Src/Gui/MainWindow.ui \
    Src/Dummy.ui \
    Src/Gui/CPUWidget.ui


LIBS += -L"$$PWD/Src/BeaEngine/" -lBeaEngine_s

INCLUDEPATH += $$PWD/Src/BeaEngine_s
