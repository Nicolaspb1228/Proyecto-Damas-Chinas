#ifndef HABILIDADES_H
#define HABILIDADES_H

#include "estructuras.h"

void mostrarMenuHabilidades(Juego* juego);
bool ejecutarHabilidad(Juego* juego, int numeroHabilidad);
bool habilidadRey_TurnoDoble(Juego* juego);
bool habilidadRey_RevivirPieza(Juego* juego);
bool habilidadRey_DecretoReal(Juego* juego);
bool habilidadGuerrero_FuriaBatalla(Juego* juego);
bool habilidadGuerrero_SacrificioTactico(Juego* juego);
bool habilidadGuerrero_SedSangre(Juego* juego);
bool habilidadMago_Teletransporte(Juego* juego);
bool habilidadMago_CoronacionMagica(Juego* juego);
bool habilidadMago_Congelar(Juego* juego);
void actualizarEfectosActivos(Juego* juego);
void agregarEfecto(Juego* juego, const char* nombre, int turnos, bool ambos, char jugador);
bool tieneEfectoActivo(Juego* juego, const char* nombre);

#endif
