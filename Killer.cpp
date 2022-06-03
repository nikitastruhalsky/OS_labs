#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>


bool killProcessById(unsigned long long id)
{
    HANDLE processToKill = OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)id);
    if (processToKill != NULL)
    {
        TerminateProcess(processToKill, 0);
        CloseHandle(processToKill);
        return true;
    }
    return false;
}

bool killProcessByName(const char* name)
{
    bool killed = false;
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    auto str = std::string(name);
    auto wstr = std::wstring(str.begin(), str.end());
    auto hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (std::wcscmp(pEntry.szExeFile, wstr.c_str()) == 0)
        {
            killed = killProcessById(pEntry.th32ProcessID);
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
    return killed;
}

void printState(bool killed, std::string name)
{
    if (killed)
    {
        std::cout << "\n[Process " << name << " was terminated]";
    }
    else
    {
        std::cout << "\n[An error occured while trying to terminate process " << name << ']';
    }
}


int main(int argc, char* argv[])
{
    char buffer[3000];
    auto got_var = GetEnvironmentVariableA("PROC_TO_KILL", buffer, 3000);
    int count = 0;
    int all_processes = 0;

    if (got_var)
    {
        std::stringstream names(buffer);
        while (names.getline(buffer, 3000, ','))
        {
            all_processes++;
            std::string str(buffer);
            str += +".exe";
            auto killed = killProcessByName(str.c_str());
            count += killed;
            printState(killed, str);
        }
    }

    std::cout << "\n[" << count << " of " << all_processes << " PROC_TO_KILL processes were terminated]";
    std::string flag = "";
    
    if (argc > 1)
    {
        flag = argv[0];
    }
    else
    {
        return 0;
    }

    if (flag[0] > '9' || flag[0] < '0')
    {
        std::string name(flag);
        auto killed = killProcessByName((name + ".exe").c_str());
        printState(killed, name);
    }
    else
    {
        auto killed = killProcessById(atoi(flag.c_str()));
        printState(killed, std::string(flag));
    }

    return 0;
}
