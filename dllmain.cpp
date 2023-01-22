// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#ifdef __cplusplus
extern "C" {
#endif
    struct RegisterofJIT_R128 {
        UINT64 regL;
        UINT64 regH;
    };

    struct RegisterofJIT_R256 {
        RegisterofJIT_R128 reghl[2];
    };

    struct RegisterofJIT {
        UINT64 privstat[16];
        RegisterofJIT_R128 reg[256];
        RegisterofJIT_R256 freg[128];
    };

    __declspec(dllexport) void _GJIT_BEGIN(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x53; *(UINT64*)(pjitinst) += 1;
#endif
    }

    __declspec(dllexport) void _GJIT_ADD(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x00; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x01; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x01; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x11; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x11; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x11; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_SUB(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x28; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x29; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x29; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x19; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x19; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x19; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_AND(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x20; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x21; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x21; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x21; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x21; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x21; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_OR(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x08; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x09; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x09; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x09; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x09; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x09; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_XOR(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x30; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x31; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x31; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x31; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x31; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x31; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_CMP(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1, void* r2) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r1; *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r2; *(UINT64*)(pjitinst)+=4;
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x38; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x39; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        else if (regsize <= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x39; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)r0; *(UINT64*)(pjitinst)+=4;
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 4); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x39; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 8); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x39; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst)+=4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x1d; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r2) + 12); *(UINT64*)(pjitinst)+=4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x39; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xd8; *(UINT64*)(pjitinst)+=1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst)+=4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9c; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_CALL(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, void* pfunc4used) {
#ifdef _M_IX86
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xff; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x15; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(pfunc4used); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_JMP(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, void* pfunc4used) {
#ifdef _M_IX86
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xff; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x25; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(pfunc4used); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_CJMP(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT8 optype, void* pfunc4used) {
#ifdef _M_IX86
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9d; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (0x70 + ((optype & 0xF) ^ 1)); *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x06; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xff; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x25; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(pfunc4used); *(UINT64*)(pjitinst)+=4;
#endif
    }
    __declspec(dllexport) void _GJIT_CCALL(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT8 optype, void* pfunc4used) {
#ifdef _M_IX86
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(&regststat->privstat[0]); *(UINT64*)(pjitinst)+=4;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x9d; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (0x70 + ((optype & 0xF) ^ 1)); *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x06; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xff; *(UINT64*)(pjitinst)+=1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x15; *(UINT64*)(pjitinst)+=1;
        *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(pfunc4used); *(UINT64*)(pjitinst)+=4;
#endif
    }

    __declspec(dllexport) void _GJIT_MOVRGINT(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void *r0, void *r1) {
#ifdef _X86_
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xb0; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa2; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xb8; *(UINT64*)(pjitinst) += 1;
            *(UINT16*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 2;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xb8; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_MOVRGRG(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0, void* r1) {
#ifdef _X86_
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa0; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa2; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r1); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 4); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 8); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r1) + 12); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst) += 4;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_MOVRV(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0) {
#ifdef _X86_
        if (regsize <= 15) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa2; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x89; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x15; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst) += 4;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_PUSH(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0) {
#ifdef _X86_
        if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0)+4); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_PUSHINT(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0) {
#ifdef _X86_
        if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xb8; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xb8; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x50; *(UINT64*)(pjitinst) += 1;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_POP(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0) {
#ifdef _X86_
        if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 96) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 8); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 128) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x58; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa3; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 12); *(UINT64*)(pjitinst) += 4;
        }
#endif
    }

    __declspec(dllexport) void _GJIT_FINISHNR(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x5b; *(UINT64*)(pjitinst) += 1;
#endif
    }

    __declspec(dllexport) void _GJIT_FINISH(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst) {
#ifdef _X86_
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x5b; *(UINT64*)(pjitinst) += 1;
        * (UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xc3; *(UINT64*)(pjitinst)+=1;
#endif
        FlushInstructionCache(GetCurrentProcess(), pointeroffunc, (SIZE_T)(*(UINT64*)(pjitinst)));
    }

    __declspec(dllexport) void _GJIT_FINISHRR(void* pointeroffunc, RegisterofJIT* regststat, void* pjitinst, UINT32 regsize, void* r0) {
#ifdef _X86_
        if (regsize <= 31) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x66; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        else if (regsize <= 63) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xa1; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(r0); *(UINT64*)(pjitinst) += 4;
        }
        if (regsize >= 64) {
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x8b; *(UINT64*)(pjitinst) += 1;
            *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x15; *(UINT64*)(pjitinst) += 1;
            *(UINT32*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = (UINT32)(((UINT64)r0) + 4); *(UINT64*)(pjitinst) += 4;
        }
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0x5b; *(UINT64*)(pjitinst) += 1;
        *(UINT8*)(((UINT64)(pointeroffunc)) + (*(UINT64*)(pjitinst))) = 0xc3; *(UINT64*)(pjitinst) += 1;
#endif
        FlushInstructionCache(GetCurrentProcess(), pointeroffunc, (SIZE_T)(*(UINT64*)(pjitinst)));
    }

#ifdef __cplusplus
}
#endif
