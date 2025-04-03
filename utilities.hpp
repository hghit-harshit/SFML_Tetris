#pragma once
#pragma comment(lib,"Shlwapi.lib")
#define RUNNING_WINDOWS
#include <iostream>
#include <string>
#include <algorithm>

namespace Utils
{   
    #ifdef RUNNING_WINDOWS 
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <Shlwapi.h>

    inline std::wstring GetWorkingDirectory()
    {
        HMODULE hModule = GetModuleHandle(nullptr);
        if(hModule)
        {
            wchar_t path[256] = {};
            GetModuleFileName(hModule,path,sizeof(path));
            PathRemoveFileSpec(path);  
            return std::wstring(path) + L"\\";
        }
        return L"";
    }

    #elif defined RUNNING_LINUX
    #include <unistd.h>
    inline std::string GetWorkingDirectory()
    {
        char cwd[256];
        if(getcwd(cwd,sizeof(cwd)) != nullptr)
        {
            return std::string(cwd) + std::string("/");
        }
        return "";
    }

    #endif
}
