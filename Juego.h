

// Juego.h
#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include <iostream>
#include <algorithm>
#include <random>

class Juego {
private:
    static const vector<string> COLORES;
    static const int NUMEROS_POR_COLOR = 9;

    vector<Jugador> jugadores;
    vector<Carta> mazo;
    int cartasPorJugador;
    int jugadorInicial;

    vector<Carta> crearMazo();
    void repartirCartas();
    void mostrarMano(const Jugador& jugador);
    int determinarGanador(const vector<Carta>& cartasJugadas, const string& colorRonda);

public:
    void configurar();
    void jugar();
    void mostrarResultados();
};

#endif // JUEGO_H