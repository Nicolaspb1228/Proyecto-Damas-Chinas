#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

struct Rol;


struct Pieza {
    int fila;
    int columna;
    char color;      // 'B' = Blanco, 'N' = Negro
    bool esDama;
    bool activa;     // false si fue capturada
    bool congelada;  // true si está congelada por habilidad
    int turnosCongelada;
};


struct EfectoActivo {
    std::string nombre;
    int turnosRestantes;
    bool afectaAmbosJugadores;
    char jugadorAfectado; // 'B' o 'N'
};


enum TipoRol {
    ROL_NINGUNO,
    ROL_REY,
    ROL_GUERRERO,
    ROL_MAGO
};


struct Habilidad {
    std::string nombre;
    std::string descripcion;
    int usosRestantes;
    int cooldownActual;
    int cooldownMaximo;
    bool esUsoUnico;
};


struct Rol {
    TipoRol tipo;
    std::string nombre;
    std::string descripcion;
    std::string icono;
    Habilidad habilidades[3];
};
struct Jugador {
    std::string nombre;
    char color;
    int piezasCapturadas;
    int movimientosRealizados;
    int piezasRestantes;
    Rol rol;  
    int turnosJugados;
    bool tieneTurnoExtra;  
    bool furiaActiva;  // Para habilidad de guerrero
};


struct Tablero {
    Pieza* casillas[10][10];  /
};


struct Movimiento {
    int origenF, origenC;
    int destinoF, destinoC;
    bool esCaptura;
    int capturaF, capturaC;
};


struct Juego {
    Tablero tablero;
    Jugador jugador1;
    Jugador jugador2;
    int turnoActual;  // 1 o 2
    bool juegoTerminado;
    Pieza piezas[40]; // Array de todas las piezas (20 por jugador)
    int numPiezas;
    EfectoActivo efectosActivos[5];
    int numEfectosActivos;
    bool modoRoles;  // Si se juega con roles o modo clásico
};

#endif
