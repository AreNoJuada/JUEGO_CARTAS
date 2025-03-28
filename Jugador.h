

// Jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

#include "Carta.h"
#include <vector>
using namespace std;

class Jugador {
public:
    string nombre;
    vector<Carta> mano;
    int cartas_ganadas = 0;
};

#endif // JUGADOR_H