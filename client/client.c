#include <stdio.h>
#include <winsock2.h>
#include <string.h>
// #include <Windows.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int main(){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    
    char login[256];
    printf("Enter your login: ");
    scanf("%s", login);

    


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
    // memset(&server, 0, sizeof server);
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
    char *sendbuf = "{'hello': 'hi'}";
    // send(s, sendbuf, (int)strlen(sendbuf),  0);
    // printf("Connected.");
    // closesocket(s);
    // WSACleanup();

    while (1){
        // printf("%s\n", username);
        // printf("%s\n", userdomain);
        // printf("%s\n",sendbuf);
        send(s, send_data, (int)strlen(send_data),  0);
        Sleep(1000);
    }
    return 0;
}