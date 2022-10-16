#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")

std::string getUpdates(int update_id = 0);
int getLastMessage(const std::string&);
int getLastId(const std::string&);
int getUpdateId(const std::string&);
void start();

int x = 0;
int y = 0;
int max_x = GetSystemMetrics(SM_CXFULLSCREEN);
int max_y = GetSystemMetrics(SM_CYFULLSCREEN);

int main()
{
    start();
    std::string str = getUpdates();
    int update_id = getUpdateId(str);
    str = std::string(str.rbegin(), str.rend());
    int id = getLastId(str);

    SetCursorPos(x, y);

    while (1) {
        str = getUpdates(update_id);
        str = std::string(str.rbegin(), str.rend());
        int new_id = getLastId(str);

        if(new_id==id){
            continue;
        }
        else {
            id = new_id;
            int n = getLastMessage(str);
            if (n == 1) {
                if (x <= max_x - 10) {
                    x += 10;
                }
                else {
                    x = max_x;
                }
                SetCursorPos(x, y);
            }
            else if (n == 2) {
                if (y <= max_y - 10) {
                    y += 10;
                }
                else {
                    y = max_y;
                }
                SetCursorPos(x, y);
            }
            else if (n == 3) {
                if (x >= 10) {
                    x -= 10;
                }
                else {
                    x = 0;
                }
                SetCursorPos(x, y);
            }
            else if (n == 4) {
                if (y >= 10) {
                    y -= 10;
                }
                else {
                    y = 0;
                }
                SetCursorPos(x, y);
            }
            else if (n == 5) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
            else {
                break;
            }
            update_id += 1;
        }
    }
    
}

std::string getUpdates(int update_id) {
    std::string oldp = "";
    std::string req;
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    char* pszOutBuffer;
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;

    if (update_id == 0)
        req = "/bot5611424035:AAGD8fSl3qQm4KxeUxCtq0j0ikitiLJR3U8/getUpdates";
    else
        req = "/bot5611424035:AAGD8fSl3qQm4KxeUxCtq0j0ikitiLJR3U8/getUpdates?offset=" + std::to_string(update_id);

    std::wstring wreq = std::wstring(req.begin(), req.end());
    hSession = WinHttpOpen(L"WinHTTP Zubai/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    hConnect = WinHttpConnect(hSession, L"api.telegram.org", INTERNET_DEFAULT_HTTPS_PORT, 0);
    hRequest = WinHttpOpenRequest(hConnect, L"POST", wreq.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, -1, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    oldp = "";
    do {
        dwSize = 0;
        WinHttpQueryDataAvailable(hRequest, &dwSize);
        pszOutBuffer = new char[dwSize + 1];
        ZeroMemory(pszOutBuffer, dwSize + 1);
        WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);
        oldp += pszOutBuffer;
        delete[] pszOutBuffer;
    } while (dwSize > 0);
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return oldp;
}

int getLastMessage(const std::string& s) {
    std::string num = "";
    bool ifB = false;
    for (char i : s) {
        if (i == '\"') {
            if (ifB) {
                num = std::string(num.rbegin(), num.rend());
                return atoi(num.c_str());
            }
            else {
                ifB = true;
            }
        }
        else if (i >= '0' && i <= '9') {
            num += i;
        }
        else if(ifB) {
            return -1;
        }
    }
}

int getLastId(const std::string& s) {
    int i = 0;
    std::string id = "";
    while (i < s.length()) {
        if (s[i] == 'm' && s[i + 1] == 'o' && s[i + 2] == 'r' && s[i + 3] == 'f') {
            int ii = 0;
            while (s[i + 6 + ii] >= '0' && s[i + 6 + ii] <= '9') {
                id += s[i + 6 + ii];
                ii += 1;
            }
            break;
        }
        i += 1;
    }
    id = std::string(id.rbegin(), id.rend());
    int idd = atoi(id.c_str());
    return idd;
}

int getUpdateId(const std::string& s) {
    int i = 0;
    std::string id = "";
    while (i < s.length()) {
        if (s[i] == 'u' && s[i + 1] == 'p' && s[i + 2] == 'd' && s[i + 3] == 'a') {
            int ii = 0;
            while (s[i + 11 + ii] >= '0' && s[i + 11 + ii] <= '9') {
                id += s[i + 11 + ii];
                ii += 1;
            }
            break;
        }
        i += 1;
    }
    int idd = atoi(id.c_str());
    return idd;
}

void start() {
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;

    char data[1000] = "{\"chat_id\": 854936011,\"text\" : \"Start\",\"reply_markup\" : {\"keyboard\": [[{\"text\": \"A\"},{\"text\": \"4\"},{ \"text\": \"B\" }],[{\"text\": \"3\"},{\"text\": \"5\"},{ \"text\": \"1\" }],[{\"text\": \"C\"},{\"text\": \"2\"},{ \"text\": \"D\" }]]}}";
    
    hSession = WinHttpOpen(L"WinHTTP Zubai/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    hConnect = WinHttpConnect(hSession, L"api.telegram.org", INTERNET_DEFAULT_HTTPS_PORT, 0);
    hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/bot5611424035:AAGD8fSl3qQm4KxeUxCtq0j0ikitiLJR3U8/sendMessage", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(hRequest, L"Content-Type: application/json\r\n", -1, (LPVOID)data, 1000, 1000, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}