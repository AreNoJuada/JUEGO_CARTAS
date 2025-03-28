
// main.cpp
#include "Juego.h"
#include <ctime>

int main() {
    srand(time(0));
    Juego juego;
    juego.configurar();
    juego.jugar();
    juego.mostrarResultados();
    return 0;
}