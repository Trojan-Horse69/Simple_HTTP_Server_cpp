#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "targetver.h"
#include <tchar.h>

using namespace std;

int main()
{

    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "The Winstock dll not found!" << endl;
        return 0;
    }
    else {
        cout << "The Winstock dll found!" << endl;
        cout << "The status:" << wsaData.szSystemStatus << endl;
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket():" << WSAGetLastError() << endl; //WSAGetLastError keeps track of what's happening with the socket and will give some
        //specific information about what the problem is/was that prevented the creation of the socket
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);
    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client: connect() is OK!" << endl;
        cout << "Client: Can start sending and receiving data..." << endl;
    }
    system("pause");
    WSACleanup();
    return 0;

    char buffer[200];
    printf("Enter your message ");
    cin.getline(buffer,200);
    int byteCount = send(clientSocket, buffer, 200, 0);
    if (byteCount == SOCKET_ERROR) {
        printf("Server send error %ld.\n", WSAGetLastError());
        return -1;
    }
    else {
        printf("Server:sent %ld bytes \n", byteCount);
    }
}