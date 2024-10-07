// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MemoryMgr.h"
#include <iostream>

#include "ladder.h"

using namespace Memory::VP;

void __declspec(naked) setup_tower_hook()
{
    static int jmpContinue = 0x4A2A5C;
    _asm {
        pushad
    }
    make_custom_tower();
    _asm {
        popad
        mov     dword ptr[ecx * 4 + 96], 0FFFFE000h
        jmp jmpContinue
    }
}

void Init()
{
    srand(time(NULL));
    InjectHook(0x4A2A51, setup_tower_hook, PATCH_JUMP);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

