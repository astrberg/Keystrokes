#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <curl/curl.h>

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
        if(wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
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

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR szArgs,int nCmdShow)
{

    // using curl to post keypresses.txt file to github repo
    auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/whoshuu/cpr/contributors?anon=true&key=value");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        
        char* url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
}

    InitHook();

    MSG msg; 

    /* Run the message pump. It will run until GetMessage() returns 0 */
    while (GetMessage (&msg, NULL, 0, 0) > 0)
    {
    }

    return 0;
}
