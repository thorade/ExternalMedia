/* *****************************************************************
 * Working around Windows' dynamic linker
 *
 * Federico Terraneo May 2022
 ********************************************************************/

#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <libloaderapi.h>
#include <errhandlingapi.h>

template<typename T>
T importFromExecutable(const char *funcName)
{
    //TODO: if GetModuleHandleA/GetProcAddress are heavy we could do caching
    HMODULE exe = GetModuleHandleA(NULL);
    if(exe == NULL)
    {
        printf("Can't get handle to executable (error %d)\n", GetLastError());
        exit(1);
    }
    T pfn = reinterpret_cast<T>(GetProcAddress(exe, funcName));
    if(pfn == NULL)
    {
        printf("Can't get handle to %s (error %d)\n",funcName, GetLastError());
        exit(1);
    }
    return pfn;
}

#define IMPORT(x,y) auto y = importFromExecutable<x>(#y)

#else //_WIN32

#include "ModelicaUtilities.h"

// Nothing to do on Linux, its linker just works
#define IMPORT(x,y)

#endif //_WIN32