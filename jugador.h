#ifndef JUGADOR_H
#define JUGADOR_H

#include "estructuras.h"
#include <string>


void inicializarJugador(Jugador* jugador, const std::string& nombre, char color);
void incrementarCapturaJugador(Jugador* jugador);
void incrementarMovimientoJugador(Jugador* jugador);
void reiniciarEstadisticasJugador(Jugador* jugador);
std::string obtenerColorNombreJugador(const Jugador* jugador);
void actualizarPiezasRestantes(Jugador* jugador, int cantidad);

#endif
