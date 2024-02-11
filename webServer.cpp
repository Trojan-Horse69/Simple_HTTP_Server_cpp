// webServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "iostream"
#include "targetver.h"
#include <tchar.h>

using namespace std;

int main(int argc, char* argv[])
{
    SOCKET serverSocket, acceptSocket;
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

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket():" << WSAGetLastError() << endl; //WSAGetLastError keeps track of what's happening with the socket and will give some
        //specific information about what the problem is/was that prevented the creation of the socket
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "bind() is OK!" << endl;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
    }
    else {
        cout << "listen() is OK, I'm waiting for connections..." << endl;
    }

   
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    cout << "Accepted connection" << endl;
    system("pause");
    WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
