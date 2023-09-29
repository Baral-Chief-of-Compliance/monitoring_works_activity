#define WIN32_LEAN_AND_MEAN
// #define _WIN32_WINNT 0x501


#include<iostream>
#include<windows.h>
#include<winsock2.h>
#include<ws2tcpip.h>


using namespace std;



int main(){

    WSADATA wsaData;
    addrinfo hints;
    addrinfo* addrResult = NULL;
    SOCKET ConnectSocket = INVALID_SOCKET;

    const char* sendBuffer = "hello from client";

    int result;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0){
        cout << "WSAStartup faild, result =" << result << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo("localhost", "3000", &hints, &addrResult);
    if (result !=0){
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET){
        cout << "Socket creation failed" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);

    if (result == SOCKET_ERROR){
        cout << "Unable connect to server" << endl;
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        cout << "" << endl;
        WSACleanup();
        return 1;
    }

    result = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), 0);

    if (result == SOCKET_ERROR){
        cout << "send failed, error: " << result << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }  

    cout << "Bytes sent: " << result << "bytes" << endl;

    result = shutdown(ConnectSocket, SD_SEND);
    if(result == SOCKET_ERROR){
        cout << "Shatdown error: " << result << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
}