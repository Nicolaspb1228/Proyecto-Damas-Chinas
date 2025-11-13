#include "pieza.h"

// Inicializa una pieza con sus valores
void inicializarPieza(Pieza* pieza, int fila, int col, char color) {
    pieza->fila = fila;
    pieza->columna = col;
    pieza->color = color;
    pieza->esDama = false;
    pieza->activa = true;
}

// Obtiene el símbolo para mostrar en el tablero
char obtenerSimbolo(const Pieza* pieza) {
    if (pieza->color == 'B') {
        return pieza->esDama ? 'B' : 'b';
    } else {
        return pieza->esDama ? 'N' : 'n';
    }
}

// Convierte una pieza en dama
void coronarPieza(Pieza* pieza) {
    pieza->esDama = true;
}

// Verifica si la pieza es una dama
bool esDamaPieza(const Pieza* pieza) {
    return pieza->esDama;
}

// Obtiene el color de la pieza
char obtenerColorPieza(const Pieza* pieza) {
    return pieza->color;
}

// Verifica si la pieza está activa
bool estaActivaPieza(const Pieza* pieza) {
    return pieza->activa;
}

// Desactiva una pieza (la captura)
void desactivarPieza(Pieza* pieza) {
    pieza->activa = false;
}
