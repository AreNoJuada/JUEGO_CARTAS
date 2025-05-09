Documentación del Juego de Cartas por Color y Número

Repositorio Git: https://github.com/AreNoJuada/JUEGO_CARTAS

Hecho por:
👨‍💻 MATHYUS OROZCO
👨‍💻 JUAN DAVID ARENAS
👨‍💻 MIGUEL CORTES


📌 Descripción
Juego de cartas multijugador en C++ donde los participantes compiten por tener la carta más alta del color determinado en cada ronda, ahora con soporte para conexiones de red mediante sockets.

🎮 Características Principales
- ✅ **Modo multijugador en red** (Cliente-Servidor)
- ✅ Sistema de rondas con turnos rotativos
- ✅ Lógica basada en colores (🟦, 🟥, 🟩, 🟨) y números (1-9)
- ✅ Determinación automática del ganador
- ✅ Interfaz por consola intuitiva

🔹 Reglas del Juego
> Cada jugador recibe 4 cartas.

> El primer jugador define el color de la ronda.

> Los demás jugadores deben tirar una carta (aunque no tengan el color).

> Gana la ronda quien tenga la carta más alta del color inicial.

> Si nadie tiene el color, gana el jugador que inició la ronda.

> Al final, gana quien haya recolectado más cartas.

⚙️ Configuración
Requisitos:

Compilador C++

Sistema operativo compatible (Windows, Linux, macOS)

Compilación y Ejecución


📝 Clases Principales
1. Carta
Representa una carta con número (1-9) y color (🟦, 🟥, 🟩, 🟨).

2. Jugador
Nombre del jugador.
Cartas en su mano.
Cartas ganadas en rondas.

3. Juego 
Mazo de cartas (36 cartas: 4 colores × 9 números).
Repartición aleatoria de cartas.
Gestión de rondas y turnos.
Determinación del ganador.


🎯 Ejemplo de Ejecución

Bienvenido al juego de cartas por color y número!
Ingrese el número de jugadores (2-4): 3
Ingrese el número de cartas por jugador (1-9): 4

=== RONDA 1 ===

Mano de Jugador1: 1🟦 3🟥 7🟩 5🟨 
Jugador1, elige una carta (1-4): 1

Jugador1 inicia la ronda con 1🟦
Color de la ronda: 🟦

Mano de Jugador2: 2🟦 4🟥 6🟩 8🟨 
Jugador2, elige una carta (1-4): 1

Mano de Jugador3: 9🟦 2🟥 3🟩 4🟨 
Jugador3, elige una carta (1-4): 1

Ganador de la ronda: Jugador3 con 9🟦

¡Diviértete jugando! 🎲🃏



# Juego_cartas
modelamiento del juego de cartas de modo multijugador y con el lenguaje de c++
