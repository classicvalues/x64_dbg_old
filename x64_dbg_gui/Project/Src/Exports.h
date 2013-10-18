#ifndef EXPORTS_H
#define EXPORTS_H

#include "Imports.h"

/************************************************************************************
                            Exported Function Prototypes
************************************************************************************/

#ifdef BUILD_LIB
    extern "C" __declspec(dllexport) int _gui_guiinit(int argc, char *argv[]);
    extern "C" __declspec(dllexport) void _gui_disassembleat(duint va, duint cip);
    extern "C" __declspec(dllexport) void _gui_setdebugstate(DBGSTATE state);
#endif


#endif // EXPORTS_H
