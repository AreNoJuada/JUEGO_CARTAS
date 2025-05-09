#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP "127.0.0.1"  // Cambiar por IP del servidor (ej: "10.2.12.76")
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

    // Iniciar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al iniciar Winsock\n";
        return 1;
    }

    // Crear socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear socket\n";
        WSACleanup();
        return 1;
    }

    // Configurar dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Conectar al servidor
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error al conectar con el servidor\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Registrarse
    std::string nombre;
    std::cout << "Ingresa tu nombre: ";
    std::getline(std::cin, nombre);
    send(clientSocket, nombre.c_str(), nombre.size() + 1, 0);

    // Recibir mensajes del servidor
    char buffer[BUFFER_SIZE];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            std::cout << std::string(buffer, bytesReceived) << "\n";

            // Si el servidor pide una jugada
            if (std::string(buffer, bytesReceived).find("Elige una carta") != std::string::npos) {
                std::string seleccion;
                std::getline(std::cin, seleccion);
                send(clientSocket, seleccion.c_str(), seleccion.size() + 1, 0);
            }
        } else if (bytesReceived == 0) {
            std::cout << "Conexión cerrada por el servidor\n";
            break;
        } else {
            std::cerr << "Error de conexión\n";
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}