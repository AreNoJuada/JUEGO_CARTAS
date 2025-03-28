#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <random>
using namespace std;

class Carta {
public:
    int numero;
    string color;
};

class Jugador {
public:
    string nombre;
    vector<Carta> mano;
    int cartas_ganadas = 0;
};

class Juego {
private:
    static const vector<string> COLORES;
    static const int NUMEROS_POR_COLOR = 9;

    vector<Jugador> jugadores;
    vector<Carta> mazo;
    int cartasPorJugador;
    int jugadorInicial;

    vector<Carta> crearMazo() {
        vector<Carta> nuevoMazo;
        for (const auto& color : COLORES) {
            for (int num = 1; num <= NUMEROS_POR_COLOR; ++num) {
                nuevoMazo.push_back({num, color});
            }
        }
        return nuevoMazo;
    }

    void repartirCartas() {
        random_device rd;
        mt19937 g(rd());
        shuffle(mazo.begin(), mazo.end(), g);
        
        for (int i = 0; i < cartasPorJugador; ++i) {
            for (auto& jugador : jugadores) {
                if (!mazo.empty()) {
                    jugador.mano.push_back(mazo.back());
                    mazo.pop_back();
                }
            }
        }
    }

    void mostrarMano(const Jugador& jugador) {
        cout << "Mano de " << jugador.nombre << ":\n";
        for (size_t i = 0; i < jugador.mano.size(); ++i) {
            cout << i+1 << ": " << jugador.mano[i].numero 
                      << jugador.mano[i].color << "  ";
        }
        cout << "\n";
    }

    int determinarGanador(const vector<Carta>& cartasJugadas, const string& colorRonda) {
        int ganador = 0;
        int maxNumero = -1;
        
        for (size_t i = 0; i < cartasJugadas.size(); ++i) {
            if (cartasJugadas[i].color == colorRonda) {
                if (cartasJugadas[i].numero > maxNumero) {
                    maxNumero = cartasJugadas[i].numero;
                    ganador = i;
                }
            }
        }
        
        return ganador;
    }

public:
    void configurar() {
        cout << "Bienvenido al juego de cartas por color y número!\n";
        
        int numJugadores;
        cout << "Ingrese el número de jugadores (2-4): ";
        cin >> numJugadores;

        cout << "Ingrese el número de cartas por jugador (1-9): ";
        cin >> cartasPorJugador;

        jugadores.resize(numJugadores);
        for (int i = 0; i < numJugadores; ++i) {
            cout << "Nombre del jugador " << i+1 << ": ";
            cin >> jugadores[i].nombre;
        }
    }

    void jugar() {
        mazo = crearMazo();
        repartirCartas();
        jugadorInicial = 0;

        for (int ronda = 1; ronda <= cartasPorJugador; ++ronda) {
            cout << "\n=== RONDA " << ronda << " ===\n";
            
            vector<Carta> cartasJugadas;

            mostrarMano(jugadores[jugadorInicial]);
            int eleccion;
            cout << jugadores[jugadorInicial].nombre 
                      << ", elige una carta (1-" 
                      << jugadores[jugadorInicial].mano.size() << "): ";
            cin >> eleccion;
            eleccion--;

            Carta cartaInicial = jugadores[jugadorInicial].mano[eleccion];
            string colorRonda = cartaInicial.color;

            jugadores[jugadorInicial].mano.erase(
                jugadores[jugadorInicial].mano.begin() + eleccion
            );

            cout << "\n" << jugadores[jugadorInicial].nombre 
                      << " inicia la ronda con " 
                      << cartaInicial.numero << cartaInicial.color << "\n";
            cout << "Color de la ronda: " << colorRonda << "\n\n";

            cartasJugadas.push_back(cartaInicial);

            for (int i = 1; i < jugadores.size(); ++i) {
                int jugadorActual = (jugadorInicial + i) % jugadores.size();
                
                mostrarMano(jugadores[jugadorActual]);
                cout << jugadores[jugadorActual].nombre 
                          << ", elige una carta (1-" 
                          << jugadores[jugadorActual].mano.size() << "): ";
                cin >> eleccion;
                eleccion--;

                Carta cartaJugada = jugadores[jugadorActual].mano[eleccion];
                cartasJugadas.push_back(cartaJugada);

                jugadores[jugadorActual].mano.erase(
                    jugadores[jugadorActual].mano.begin() + eleccion
                );

                cout << jugadores[jugadorActual].nombre << " juega " 
                          << cartaJugada.numero << cartaJugada.color << "\n";
            }

            int ganadorRonda = determinarGanador(cartasJugadas, colorRonda);
            int jugadorGanador = (jugadorInicial + ganadorRonda) % jugadores.size();

            cout << "\nGanador de la ronda: " 
                      << jugadores[jugadorGanador].nombre 
                      << " con " << cartasJugadas[ganadorRonda].numero 
                      << cartasJugadas[ganadorRonda].color << "\n";

            jugadores[jugadorGanador].cartas_ganadas += jugadores.size();

            jugadorInicial = jugadorGanador;
        }
    }

    void mostrarResultados() {
        cout << "\n=== RESULTADOS FINALES ===\n";
        for (const auto& jugador : jugadores) {
            cout << jugador.nombre << " obtuvo " 
                      << jugador.cartas_ganadas << " cartas\n";
        }

        auto ganadorFinal = max_element(jugadores.begin(), jugadores.end(), 
            [](const Jugador& a, const Jugador& b) {
                return a.cartas_ganadas < b.cartas_ganadas;
            });

        cout << "\n¡¡¡ " << ganadorFinal->nombre 
                  << " es el ganador con " 
                  << ganadorFinal->cartas_ganadas 
                  << " cartas obtenidas !!!\n";
    }
};

const vector<string> Juego::COLORES = {"🟦", "🟥", "🟩", "🟨"};

int main() {
    srand(time(0));

    Juego juego;
    juego.configurar();
    juego.jugar();
    juego.mostrarResultados();

    return 0;
}