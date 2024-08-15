#pragma once
#include <windows.h>
#include <iostream>
#include <cstdarg>
#include <psapi.h>
#include "TimeUtil.h"
#include "../Libraries/Libraries.h"
#include "Logger.h"

template<typename Ret, typename Type>
Ret& direct_access(Type* type, size_t offset) {
    union {
        size_t raw;
        Type* source;
        Ret* target;
    } u;
    u.source = type;
    u.raw += offset;
    return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define FAKE_FIELD(type, name)       \
    AS_FIELD(type, name, get##name); \
    type get##name()
#define BUILD_ACCESS(ptr, type, name, offset)                           \
    AS_FIELD(type, name, get##name);                                    \
    type get##name() const { return direct_access<type>(ptr, offset); } \
    void set##name(type v) const { direct_access<type>(ptr, offset) = v; }

#define BUILD_ACCESS_STRING(ptr, name, offset)                          \
    AS_FIELD(std::string, name, get##name);                             \
    std::string get##name() const { if (ptr) return direct_access<std::string>(ptr, offset); else return ""; } \
    void set##name(std::string v) const {if (ptr) direct_access<std::string>(ptr, offset) = v; }

namespace Memory {
    template <typename R, typename... Args>
    R CallFunc(void* func, Args... args)
    {
        return ((R(*)(Args...))func)(args...);
    }

    static uintptr_t ResolveRef(uintptr_t ptr, int offset = 1) {
        if (!ptr)
            return 0;

        uintptr_t newAddr = ptr + *reinterpret_cast<int*>(ptr + offset) + (offset + 4);
        return newAddr;
    }
    template <int IIdx, typename TRet, typename... TArgs>
    static auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
        using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
        return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
    }
    template <typename R, typename... Args>
    auto GetFunc(void* func) -> R(*)(Args...) {
        return reinterpret_cast<R(*)(Args...)>(func);
    }

    template <int IIdx, typename T, typename... TArgs>
    static inline auto GetVFunc(T* thisptr) {
        using Fn = decltype(((T*)nullptr)->*(reinterpret_cast<typename std::add_pointer<TRet(T::*)(TArgs...)>::type>(0)));
        return reinterpret_cast<Fn>((*static_cast<void***>(thisptr))[IIdx]);
    }

    template <typename ret>
    auto FuncFromSigOffset(uintptr_t sig, int offset) -> ret {
        if (sig != 0x0) {
            sig += offset + 4 + *reinterpret_cast<int*>(sig + offset);
        }
        return reinterpret_cast<ret>(sig);
    }



    template <typename T> // not related to memory LOL
    std::string combine(T t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    template <typename T, typename... Args> // not related to memory LOL
    std::string combine(T t, Args... args)
    {
        std::stringstream ss;
        ss << t << combine(args...);
        return ss.str();
    }

    static const uintptr_t range_start = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));

    template <typename T>
    bool CreateHook(void* pTarget, T pDetour, void* pOriginal, const char* sigId)
    {
        /*
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            if (MH_Initialize() != MH_OK)
            {
                logF(combine("Failed to initialize MinHook").c_str());
                running = false;
                return false;
            }
        }
        */
        uint64_t start = TimeUtil::getCurrentMs();
        if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pOriginal) != MH_OK)
        {
            logF(combine("[", pTarget, ",", sigId, "] Failed to create hook").c_str(), "FAIL");
            return false;
        }

        if (MH_EnableHook(pTarget) != MH_OK)
        {
            logF(combine("[", pTarget, ",", sigId, "] Failed to enable hook").c_str(), "FAIL");
            return false;
        }

        std::stringstream ss;
        ss << "Minecraft.Windows.exe+" << std::hex << (uintptr_t)pTarget - range_start;
        uint64_t time = TimeUtil::getCurrentMs() - start;

        logF(combine("[", ss.str().c_str(), ",", sigId, "] Successfully Hooked in ", time, "ms.").c_str(), "OKAY");

        return true;
    }

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))
    inline uintptr_t FindSignatureModule(const char* szSignature) {
        const char* pattern = szSignature;
        uintptr_t firstMatch = 0;
        static const auto rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
        static MODULEINFO miModInfo;
        static bool init = false;
        if (!init) {
            init = true;
            GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
        }
        static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

        BYTE patByte = GET_BYTE(pattern);
        const char* oldPat = pattern;

        for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
            if (!*pattern)
                return firstMatch;

            while (*(PBYTE)pattern == ' ')
                pattern++;

            if (!*pattern)
                return firstMatch;

            if (oldPat != pattern) {
                oldPat = pattern;
                if (*(PBYTE)pattern != '\?')
                    patByte = GET_BYTE(pattern);
            }

            if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
                if (!firstMatch)
                    firstMatch = pCur;

                if (!pattern[2] || !pattern[1])
                    return firstMatch;

                //if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?')
                //pattern += 3;

                //else
                pattern += 2;
            }
            else {
                pattern = szSignature;
                firstMatch = 0;
            }
        }
#ifdef _DEBUG
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
        const char* sig = szSignature;  // Put sig in here to access it in debugger
        // This will not get optimized away because we are in debug
        // Leave this in here to quickly find bad signatures in case of updates
        logF("Signature dead: %s", szSignature);
        if (false) {
            const char* msgToTheOverwhelmedDebugger = "SIGNATURE NOT FOUND";
            __debugbreak();
        }

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
        return 0u;
    }

    static void* addSignature(const char* sig)
    {
        return (void*)FindSignatureModule(sig);
    }
}