#define _WIN32_WINNT 0x0501   // required for getaddrinfo to be defined in <ws2tcpip.h>
#define WIN32_LEAN_AND_MEAN

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "5025"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "socket.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


int socket_status;
struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET client_socket = INVALID_SOCKET;

int socket_init(char *host_name) 
{ 

    WSADATA wsaData;

    // Initialize Winsock
    socket_status = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (socket_status != 0) {
        printf("WSAStartup failed with error: %d\n", socket_status);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    socket_status = getaddrinfo(host_name, DEFAULT_PORT, &hints, &result);
    if ( socket_status != 0 ) {
        printf("getaddrinfo failed with error: %d\n", socket_status);
        WSACleanup();
        return 1;
    }
    printf("WSAGetLastError: %d\n", WSAGetLastError());

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL; ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        client_socket = socket(ptr->ai_family, ptr->ai_socktype,  ptr->ai_protocol);
        
        if (client_socket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        
        int rc;
        int opt = 10000;
        int opt_len = sizeof(int);
        
        rc = getsockopt(client_socket, SOL_SOCKET, SO_SNDBUF, (char*)&opt, (socklen_t*)(&opt_len));
         
        // Connect to server.
        socket_status = connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (socket_status == SOCKET_ERROR) {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    

    freeaddrinfo(result);

    if (client_socket == INVALID_SOCKET) {
        printf("Unable to connect to server: %s\n", host_name);
        WSACleanup();
        return 1;
    }

    int opt_len, opt, rc;
    opt_len = sizeof(int);
    printf("Successfully connected to Socket Server: %s\n", host_name);
    

    // rc = getsockopt(client_socket, SOL_SOCKET, SO_RCVBUF, (char*)&opt, &opt_len);
    // printf("%d: %d", rc, opt);
    // rc = setsockopt(client_socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&opt, (socklen_t)opt_len);
    // printf("%d: %d\n", rc, opt);
    


    return 0;
}




void socket_close()
{

    char sock_msg[80];

    // shutdown the connection since no more data will be sent
    socket_status = shutdown(client_socket, SD_SEND);

    if (socket_status == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // // Receive until the peer closes the connection
    // do {

    //     socket_status = recv(connected_socket, sock_msg, sizeof(sock_msg), 0);
    //     if ( socket_status > 0 ) 
    //         printf("Bytes received: %d\n", socket_status);
    //     else if ( socket_status == 0 )
    //         printf("Connection closed\n");
    //     else
    //         printf("recv failed with error: %d\n", WSAGetLastError());

    // } while( socket_status > 0 );

    // cleanup
    closesocket(client_socket);
    WSACleanup();

    exit(1);
}

