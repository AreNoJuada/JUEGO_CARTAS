#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include "Juego.h"

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

class ServidorJuego {
private:
    std::vector<SOCKET> clientSockets;
    Juego juego;

    void enviarMensaje(SOCKET sock, const std::string& msg) {
        send(sock, msg.c_str(), msg.size() + 1, 0);
    }

    std::string recibirMensaje(SOCKET sock) {
        char buffer[BUFFER_SIZE];
        int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            return std::string(buffer, bytesReceived);
        }
        return "";
    }

public:
    void ejecutar() {
        WSADATA wsaData;
        SOCKET serverSocket;
        sockaddr_in serverAddr;

        // Iniciar Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Error al iniciar Winsock\n";
            return;
        }

        // Crear socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Error al crear socket\n";
            WSACleanup();
            return;
        }

        // Configurar dirección
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(PORT);

        // Enlazar socket
        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Error al enlazar socket\n";
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        // Escuchar conexiones
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Error al escuchar\n";
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "Servidor iniciado. Esperando jugadores...\n";

        // Aceptar jugadores (2-4)
        int numJugadores = 2; // Puedes ajustar esto
        for (int i = 0; i < numJugadores; ++i) {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Error al aceptar jugador " << i + 1 << "\n";
                continue;
            }
            clientSockets.push_back(clientSocket);
            std::string nombre = recibirMensaje(clientSocket);
            juego.jugadores.push_back({nombre, {}, 0});
            enviarMensaje(clientSocket, "Esperando a más jugadores...");
            std::cout << "Jugador conectado: " << nombre << "\n";
        }

        // Iniciar juego
        juego.mazo = juego.crearMazo();
        juego.repartirCartas();

        for (int ronda = 1; ronda <= juego.cartasPorJugador; ++ronda) {
            enviarMensajeATodos("\n=== RONDA " + std::to_string(ronda) + " ===");
            
            // Procesar jugadas
            std::vector<Carta> cartasJugadas;
            std::string colorRonda;

            for (int i = 0; i < juego.jugadores.size(); ++i) {
                SOCKET sock = clientSockets[i];
                Jugador& jugador = juego.jugadores[i];

                // Enviar mano al jugador
                std::string manoStr;
                for (size_t j = 0; j < jugador.mano.size(); ++j) {
                    manoStr += std::to_string(j + 1) + ": " + 
                              std::to_string(jugador.mano[j].numero) + 
                              jugador.mano[j].color + "  ";
                }
                enviarMensaje(sock, "Tu mano: " + manoStr + "\nElige una carta (1-" + std::to_string(jugador.mano.size()) + "): ");

                // Recibir jugada
                int eleccion = std::stoi(recibirMensaje(sock)) - 1;
                cartasJugadas.push_back(jugador.mano[eleccion]);
                jugador.mano.erase(jugador.mano.begin() + eleccion);

                if (i == 0) colorRonda = cartasJugadas[0].color;
            }

            // Determinar ganador
            int ganador = juego.determinarGanador(cartasJugadas, colorRonda);
            juego.jugadores[ganador].cartas_ganadas += juego.jugadores.size();
            enviarMensajeATodos("Ganador de la ronda: " + juego.jugadores[ganador].nombre);
        }

        // Mostrar resultados
        std::string resultados = "\n=== RESULTADOS ===";
        for (auto& jugador : juego.jugadores) {
            resultados += "\n" + jugador.nombre + ": " + std::to_string(jugador.cartas_ganadas) + " puntos";
        }
        enviarMensajeATodos(resultados);

        // Cerrar conexiones
        for (SOCKET sock : clientSockets) closesocket(sock);
        closesocket(serverSocket);
        WSACleanup();
    }

    void enviarMensajeATodos(const std::string& msg) {
        for (SOCKET sock : clientSockets) {
            enviarMensaje(sock, msg);
        }
    }
};

int main() {
    ServidorJuego servidor;
    servidor.ejecutar();
    return 0;
}
        // Jugar las rondas
        jugadorInicial = 0;
        for (int ronda = 1; ronda <= cartasPorJugador; ++ronda) {
            enviarMensajeATodos("\n=== RONDA " + std::to_string(ronda) + " ===\n");

            // Jugar cartas
            std::vector<Carta> cartasJugadas;
            std::string colorRonda;

            for (int i = 0; i < jugadores.size(); ++i) {
                int jugadorActual = (jugadorInicial + i) % jugadores.size();
                
                // Enviar mano al jugador
                std::string manoStr;
                for (size_t j = 0; j < jugadores[jugadorActual].mano.size(); ++j) {
                    manoStr += std::to_string(j+1) + ": " + 
                              std::to_string(jugadores[jugadorActual].mano[j].numero) + 
                              jugadores[jugadorActual].mano[j].color + "  ";
                }
                enviarMensaje(clientSockets[jugadorActual], "Tu mano: " + manoStr + "\nElige una carta: ");

                // Recibir selección
                std::string seleccionStr = recibirMensaje(clientSockets[jugadorActual]);
                int eleccion = std::stoi(seleccionStr) - 1;

                Carta cartaJugada = jugadores[jugadorActual].mano[eleccion];
                jugadores[jugadorActual].mano.erase(jugadores[jugadorActual].mano.begin() + eleccion);
                cartasJugadas.push_back(cartaJugada);

                if (i == 0) {
                    colorRonda = cartaJugada.color;
                    enviarMensajeATodos("Color de la ronda: " + colorRonda);
                }

                enviarMensajeATodos(jugadores[jugadorActual].nombre + " jugó: " + 
                                   std::to_string(cartaJugada.numero) + cartaJugada.color);
            }

            // Determinar ganador
            int ganadorRonda = determinarGanador(cartasJugadas, colorRonda);
            int jugadorGanador = (jugadorInicial + ganadorRonda) % jugadores.size();
            jugadores[jugadorGanador].cartas_ganadas += jugadores.size();
            jugadorInicial = jugadorGanador;

            enviarMensajeATodos("\nGanador de la ronda: " + jugadores[jugadorGanador].nombre + "\n");
        }

        // Mostrar resultados finales
        std::string resultados = "\n=== RESULTADOS FINALES ===\n";
        for (const auto& jugador : jugadores) {
            resultados += jugador.nombre + " obtuvo " + std::to_string(jugador.cartas_ganadas) + " cartas\n";
        }
        enviarMensajeATodos(resultados);

        // Cerrar sockets
        for (SOCKET sock : clientSockets) {
            closesocket(sock);
        }
        closesocket(serverSocket);
        WSACleanup();
    }
};

int main() {
    ServidorJuego servidor;
    servidor.ejecutar();
    return 0;
}