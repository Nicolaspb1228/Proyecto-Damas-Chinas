#ifndef PIEZA_H
#define PIEZA_H

#include "estructuras.h"

// Funciones para manejo de piezas
void inicializarPieza(Pieza* pieza, int fila, int col, char color);
char obtenerSimbolo(const Pieza* pieza);
void coronarPieza(Pieza* pieza);
bool esDamaPieza(const Pieza* pieza);
char obtenerColorPieza(const Pieza* pieza);
bool estaActivaPieza(const Pieza* pieza);
void desactivarPieza(Pieza* pieza);

#endif
