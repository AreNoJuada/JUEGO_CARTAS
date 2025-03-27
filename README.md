Documentación del Juego de Cartas por Color y Número
Repositorio Git: https://github.com/tu-usuario/juego-cartas-color-numero

📌 Descripción
Juego de cartas en C++ donde los jugadores compiten por tener la carta más alta del color determinado por el primer jugador en cada ronda.

🔹 Reglas del Juego
Cada jugador recibe 4 cartas (configurable).

El primer jugador define el color de la ronda.

Los demás jugadores deben tirar una carta (aunque no tengan el color).

Gana la ronda quien tenga la carta más alta del color inicial.

Si nadie tiene el color, gana el jugador que inició la ronda.

Al final, gana quien haya recolectado más cartas.

⚙️ Configuración
Requisitos
Compilador C++ (g++, Clang, MSVC)

Sistema operativo compatible (Windows, Linux, macOS)

Compilación y Ejecución
bash
Copy
g++ -o juego juego.cpp
./juego
🎮 Funcionalidades
✅ Menú interactivo para configurar jugadores y cartas.
✅ Lógica de juego basada en colores y números.
✅ Sistema de rondas con turnos rotativos.
✅ Determinación automática del ganador por ronda y final.

📂 Estructura del Código
plaintext
Copy
📁 juego-cartas-color-numero/
├── 📄 juego.cpp          # Código principal del juego
├── 📄 README.md          # Documentación (este archivo)
└── 📄 LICENSE            # Licencia (opcional)
📝 Clases Principales
1. Carta
Representa una carta con número (1-9) y color (🟦, 🟥, 🟩, 🟨).

2. Jugador
Nombre del jugador.

Cartas en su mano.

Cartas ganadas en rondas.

3. Juego (Lógica Principal)
Mazo de cartas (36 cartas: 4 colores × 9 números).

Repartición aleatoria de cartas.

Gestión de rondas y turnos.

Determinación del ganador.

🎯 Ejemplo de Ejecución
plaintext
Copy
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
📜 Licencia
Este proyecto está bajo la licencia MIT.

📌 ¿Cómo Contribuir?
Haz un fork del repositorio.

Crea una rama (git checkout -b feature/nueva-funcionalidad).

Haz commit de tus cambios (git commit -m "Añade nueva funcionalidad").

Haz push a la rama (git push origin feature/nueva-funcionalidad).

Abre un Pull Request.

📧 Contacto
✉️ tu-email@example.com

¡Diviértete jugando! 🎲🃏


# juego_cartas
modelamiento del juego de cartas al estilo Crash, para de modo multijugador y con el lenguaje de c++
