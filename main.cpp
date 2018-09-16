#include <stdio.h>
#include <windows.h>
#include <fstream>

HHOOK _hook;
BOOL _bool;
int counter;
int Save(int counter);


// When keyboard key is pressed CALLBACK
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        // Valid input key down
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            counter += 1;
            Save(counter);
        }
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void InitHook()
{
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0)))
    {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONHAND);
    }

}


int Save(int counter)
{
    std::ofstream file("keypresses.txt", std::ofstream::out);

    file << counter << std::endl;

    file.close();
    return 0;
}


void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR szArgs,int nCmdShow)
{

    HideConsole();

    InitHook();

    MSG msg; 

    /* Run the message pump. It will run until GetMessage() returns 0 */
    while (GetMessage (&msg, NULL, 0, 0) > 0)
    {
    }

    return 0;
}
