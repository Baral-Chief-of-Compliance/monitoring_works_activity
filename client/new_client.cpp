#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int client_socket;
    sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    char message[1024] = "Hello, Server!";
    send(client_socket, message, strlen(message), 0);

    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));
    std::cout << "Server replied: " << buffer << std::endl;

    close(client_socket);

    return 0;
}