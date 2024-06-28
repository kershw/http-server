#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <pthread.h>

#define WIN_PORT "80"
#define PORT_VALUE 80
#define BUFFER_SIZE 1024

int connect_to_client(SOCKET ClientSocket) {
    char recvBuffer[BUFFER_SIZE];
    int recvResult, sendResult;
    int recvBufferLen = BUFFER_SIZE;

    while (recvResult > 0) {
        recvResult = recv(ClientSocket, recvBuffer, recvBufferLen, 0);
        if (recvResult > 0) {
            // Here we handle what to do when we have received data.
        } else if (recvResult == 0) {
            // Connection is closed by client
        } else {
            // Here receiving the data has failed, so we need to close the socket as connection has been compromised.
            printf("Receiving the data has failed with error code: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;

        }

    }
    return 0;

}

int main(int argc, char const* argv[]) {

    struct addrinfo *addrResult = NULL, hints;
    int statusCode;

    SOCKET ListenSocket = INVALID_SOCKET;

    SecureZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Initialize winsock
    WSADATA wsaData;
    if (WSAStartup(0B0000001000000010, &wsaData) != 0) {
        printf("Error in starting up the windows socket service\n");
        return 1;
    }

    // Gets address info
    statusCode = getaddrinfo(NULL, WIN_PORT, &hints, &addrResult);
    if (statusCode != 0 ) {
        printf("getaddrinfo failed. Error code: %d\n", statusCode);
        WSACleanup();
        return 1;
    }

    // Creating socket
    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol); 
    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket creation: %ld\n", WSAGetLastError());
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Binds the socket
    statusCode = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (statusCode == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        freeaddrinfo(addrResult);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    SOCKET ClientSocket;
    // Listen loop
    while (1) {
        statusCode = listen(ListenSocket, SOMAXCONN);
        if (statusCode == SOCKET_ERROR) {
            printf("Listen failed with error code: %ld\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        ClientSocket = INVALID_SOCKET;
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("Accept failed with error code: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        connect_to_client(ClientSocket);
    }



    WSACleanup();
    return 0;
}
