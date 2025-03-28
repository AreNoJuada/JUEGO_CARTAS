// Juego.cpp
#include "Juego.h"
const vector<string> Juego::COLORES = {"🟦", "🟥", "🟩", "🟨"};

vector<Carta> Juego::crearMazo() {
    vector<Carta> nuevoMazo;
    for (const auto& color : COLORES) {
        for (int num = 1; num <= NUMEROS_POR_COLOR; ++num) {
            nuevoMazo.push_back({num, color});
        }
    }
    return nuevoMazo;
}

void Juego::repartirCartas() {
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

void Juego::mostrarMano(const Jugador& jugador) {
    cout << "Mano de " << jugador.nombre << ":\n";
    for (size_t i = 0; i < jugador.mano.size(); ++i) {
        cout << i+1 << ": " << jugador.mano[i].numero << jugador.mano[i].color << "  ";
    }
    cout << "\n";
}

int Juego::determinarGanador(const vector<Carta>& cartasJugadas, const string& colorRonda) {
    int ganador = 0;
    int maxNumero = -1;
    for (size_t i = 0; i < cartasJugadas.size(); ++i) {
        if (cartasJugadas[i].color == colorRonda && cartasJugadas[i].numero > maxNumero) {
            maxNumero = cartasJugadas[i].numero;
            ganador = i;
        }
    }
    return ganador;
}

void Juego::configurar() {
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

void Juego::jugar() {
    mazo = crearMazo();
    repartirCartas();
    jugadorInicial = 0;
    for (int ronda = 1; ronda <= cartasPorJugador; ++ronda) {
        cout << "\n=== RONDA " << ronda << " ===\n";
        vector<Carta> cartasJugadas;
        mostrarMano(jugadores[jugadorInicial]);
        int eleccion;
        cout << jugadores[jugadorInicial].nombre << ", elige una carta: ";
        cin >> eleccion; eleccion--;
        Carta cartaInicial = jugadores[jugadorInicial].mano[eleccion];
        string colorRonda = cartaInicial.color;
        jugadores[jugadorInicial].mano.erase(jugadores[jugadorInicial].mano.begin() + eleccion);
        cout << "Color de la ronda: " << colorRonda << "\n";
        cartasJugadas.push_back(cartaInicial);
        for (int i = 1; i < jugadores.size(); ++i) {
            int jugadorActual = (jugadorInicial + i) % jugadores.size();
            mostrarMano(jugadores[jugadorActual]);
            cout << jugadores[jugadorActual].nombre << ", elige una carta: ";
            cin >> eleccion; eleccion--;
            Carta cartaJugada = jugadores[jugadorActual].mano[eleccion];
            cartasJugadas.push_back(cartaJugada);
            jugadores[jugadorActual].mano.erase(jugadores[jugadorActual].mano.begin() + eleccion);
        }
        int ganadorRonda = determinarGanador(cartasJugadas, colorRonda);
        int jugadorGanador = (jugadorInicial + ganadorRonda) % jugadores.size();
        cout << "\nGanador de la ronda: " << jugadores[jugadorGanador].nombre << "\n";
        jugadores[jugadorGanador].cartas_ganadas += jugadores.size();
        jugadorInicial = jugadorGanador;
    }
}

void Juego::mostrarResultados() {
    cout << "\n=== RESULTADOS FINALES ===\n";
    for (const auto& jugador : jugadores) {
        cout << jugador.nombre << " obtuvo " << jugador.cartas_ganadas << " cartas\n";
    }
}