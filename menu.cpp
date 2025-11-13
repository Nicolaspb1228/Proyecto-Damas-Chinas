#include "menu.h"
#include <iostream>
#include <limits>
#include <cstdlib>

int mostrarMenuPrincipal() {
    limpiarPantalla();
    
    std::cout << "\n";
    std::cout << "******************************************\n";
    std::cout << "*                                        *\n";
    std::cout << "*     DAMAS INTERNACIONALES (10x10)      *\n";
    std::cout << "*                                        *\n";
    std::cout << "******************************************\n";
    std::cout << "\n";
    std::cout << "  1. Nueva Partida\n";
    std::cout << "  2. Ver Reglas\n";
    std::cout << "  3. Creditos\n";
    std::cout << "  4. Salir\n";
    std::cout << "\n";
    std::cout << "  Selecciona una opcion: ";
    
    int opcion;
    if (!(std::cin >> opcion)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcion;
}

void mostrarReglas() {
    limpiarPantalla();
    
    std::cout << "\n";
    std::cout << "*****************************************\n";
    std::cout << "*          REGLAS DEL JUEGO             *\n";
    std::cout << "*****************************************\n";
    std::cout << "\n";
    std::cout << "OBJETIVO:\n";
    std::cout << "  Capturar o bloquear todas las piezas del oponente.\n\n";
    
    std::cout << "CONFIGURACION:\n";
    std::cout << "  - Tablero de 10x10 con casillas claras y oscuras.\n";
    std::cout << "  - Cada jugador inicia con 20 piezas en las casillas oscuras.\n";
    std::cout << "  - Las piezas solo se mueven por casillas oscuras.\n\n";
    
    std::cout << "MOVIMIENTOS:\n";
    std::cout << "  PIEZAS NORMALES (peones):\n";
    std::cout << "    - Se mueven en diagonal hacia adelante, una casilla.\n";
    std::cout << "    - Capturan saltando sobre una pieza enemiga hacia una\n";
    std::cout << "      casilla vacia detras de ella.\n\n";
    
    std::cout << "  DAMAS:\n";
    std::cout << "    - Se coronan al llegar a la ultima fila del oponente.\n";
    std::cout << "    - Pueden moverse en diagonal en cualquier direccion.\n";
    std::cout << "    - Pueden moverse multiples casillas en una sola jugada.\n";
    std::cout << "    - Pueden capturar a cualquier distancia.\n\n";
    
    std::cout << "CAPTURAS:\n";
    std::cout << "  - Las capturas son OBLIGATORIAS cuando estan disponibles.\n";
    std::cout << "  - Se pueden realizar capturas multiples en un mismo turno.\n";
    std::cout << "  - Una pieza captura saltando sobre una pieza enemiga.\n\n";
    
    std::cout << "VICTORIA:\n";
    std::cout << "  - Gana quien capture todas las piezas del oponente.\n";
    std::cout << "  - O quien bloquee al oponente sin movimientos validos.\n\n";
    
    std::cout << "NOTACION:\n";
    std::cout << "  b = peon blanco    |  B = DAMA blanca\n";
    std::cout << "  n = peon negro     |  N = DAMA negra\n";
    std::cout << "  · = casilla oscura vacia\n\n";
    
    pausar();
}

void mostrarCreditos() {
    limpiarPantalla();
    
    std::cout << "\n";
    std::cout << "*****************************************\n";
    std::cout << "*              CREDITOS                 *\n";
    std::cout << "*****************************************\n";
    std::cout << "\n";
    std::cout << "  Proyecto: Damas Internacionales\n";
    std::cout << "  Lenguaje: C++\n";
    std::cout << "\n";
    std::cout << "  Desarrollado como proyecto academico\n";
    std::cout << "  para el curso de Pensamiento Algoritmico.\n";
    std::cout << "\n";
    std::cout << "  Implementa las reglas oficiales de las\n";
    std::cout << "  Damas Internacionales en un tablero 10x10.\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "  Integrantes:\n";
    std::cout << "  Oscar Suarez y Nicolas Perez.\n";
    std::cout << "\n";
    
    pausar();
}
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    std::cout << "\nPresiona ENTER para continuar...";
    std::cin.get();
}
