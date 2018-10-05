#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>

HHOOK _hook;
BOOL _bool;
int counter;
bool press;
int Save(int counter);

// When keyboard key is pressed CALLBACK
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    if (nCode >= 0)
    {

        // Valid input key down
        if ((wParam == WM_KEYDOWN || wParam == WM_KEYDOWN) && !press)
        {
            press = true;
            counter += 1;
            Save(counter);
        }
        if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
        {
            press = false;
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

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append((char *)ptr, size * nmemb);
    return size * nmemb;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR szArgs, int nCmdShow)
{

    InitHook();

    MSG msg;

    /* Run the message pump. It will run until GetMessage() returns 0 */
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
    }

    return 0;
}
