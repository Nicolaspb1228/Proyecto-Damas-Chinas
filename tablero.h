#ifndef TABLERO_H
#define TABLERO_H
#include "estructuras.h"

void inicializarTablero(Tablero* tablero);
void limpiarTablero(Tablero* tablero);
void mostrarTablero(const Tablero* tablero);
bool esCasillaOscura(int fila, int col);
bool esDentroDelTablero(int fila, int col);
bool estaVaciaCasilla(const Tablero* tablero, int fila, int col);
Pieza* obtenerPiezaEn(const Tablero* tablero, int fila, int col);
void colocarPiezaEn(Tablero* tablero, Pieza* pieza, int fila, int col);
void eliminarPiezaEn(Tablero* tablero, int fila, int col);
void moverPiezaEn(Tablero* tablero, int origenF, int origenC, int destinoF, int destinoC);
int contarPiezasColor(const Tablero* tablero, char color);

#endif
