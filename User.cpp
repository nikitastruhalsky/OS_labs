#include <iostream>
#include <windows.h>
#include <winbase.h>
#include <tlhelp32.h>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

struct process
{
    const DWORD ID;
    const std::wstring NAME;

    process(DWORD id, std::wstring name) : ID(id), NAME(name) {};
};

std::vector<process> getActiveProcesses()
{
    std::vector<process> processes;
    HANDLE snShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    auto hRes = Process32First(snShot, &pEntry);
    while (hRes)
    {
        processes.push_back(process(pEntry.th32ProcessID, std::wstring(pEntry.szExeFile)));
        hRes = Process32Next(snShot, &pEntry);
    }
    CloseHandle(snShot);
    return processes;
}

void killerProcess(std::string command)
{
    std::string str_ = command;
    char* proc = (char*)command.c_str();
    STARTUPINFOA startUpInf = { 0 };
    PROCESS_INFORMATION procInf = { 0 };
    if (CreateProcessA("C:\\Users\\Owner\\Desktop\\FAMCS\\OS\\Processes\\Killer\\x64\\Debug\\Killer.exe", proc, NULL, NULL, FALSE, 0, NULL, NULL, &startUpInf, &procInf))
    {
        WaitForSingleObject(procInf.hProcess, INFINITE);
        CloseHandle(procInf.hProcess);
        CloseHandle(procInf.hThread);
    }
}

void printProcesses(std::vector<process> vec)
{
    for (auto x : vec)
    {
        std::wcout << "\nID:  " << x.ID << "  NAME:  " << x.NAME;
    }
}


int main()
{
    SetEnvironmentVariableA("PROC_TO_KILL", "Telegram,notepad++");
    auto currentActiveProcesses = getActiveProcesses();
    for (auto x : currentActiveProcesses)
    {
        if (x.NAME == L"Telegram.exe" || x.NAME == L"notepad++.exe")
        {
            std::wcout << '\n' << x.NAME << " process is active";
        }
    }
    killerProcess("");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    _putenv("PROC_TO_KILL");
    bool killed = true;
    auto check = getActiveProcesses();
    for (auto x : check)
    {
        if (x.NAME == L"Telegram.exe" || x.NAME == L"notepad++.exe")
        {
            std::wcout << '\n' << x.NAME << " process was not terminated";
            killed = false;
        }
    }
    if (killed)
    {
        std::cout << "\nProcesses are terminated\n";
    }

    return 0;
}
