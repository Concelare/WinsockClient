#include <cstring>
#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

using namespace std;

int main() {

    WSADATA wsaData;
    constexpr WORD wVersionRequested = MAKEWORD(2, 2);

    if (const int wsaerr = WSAStartup(wVersionRequested, &wsaData); wsaerr != 0) {
        cerr << "[ERROR] The Winsock.dll not found\n";
        return 1;
    }

    cout << "[INFO] Successfully Loaded Winsock.dll" << endl;

    sockaddr_in clientService{};
    clientService.sin_family = AF_INET;

    InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(8080);

    auto clientSocket = INVALID_SOCKET;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET){
        cerr << "[ERROR] Socket Error: " <<  WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR){
        cerr << "[ERROR] Client: Failed to connect.\n";
        WSACleanup();
        return 1;
    }

    cout << "[INFO] Client: connect() is OK.\n[INFO] Client: Can start sending and receiving data...\n";
    const auto data = "s";
    const int byteCount = send(clientSocket, data, strlen(data), MSG_DONTROUTE);
    _sleep(1000);
    const auto data2 = "q";
    send(clientSocket, data2, strlen(data2), MSG_DONTROUTE);



    cout << "[INFO] Client: Successfully Sent " << byteCount << " Bytes of Data" << endl;

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}