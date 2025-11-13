#ifndef JUEGO_H
#define JUEGO_H

#include "estructuras.h"
#include <vector>


void inicializarJuego(Juego* juego);
void configurarJugadores(Juego* juego);
void configurarModoJuego(Juego* juego);
void inicializarPiezasJuego(Juego* juego);
void jugar(Juego* juego);
void jugarTurno(Juego* juego);
void cambiarTurno(Juego* juego);
bool solicitarMovimiento(int& origenF, int& origenC, int& destinoF, int& destinoC);
bool ejecutarMovimiento(Juego* juego, int origenF, int origenC, int destinoF, int destinoC);
bool esMovimientoSimpleValido(Juego* juego, int origenF, int origenC, int destinoF, int destinoC);
bool esCapturaValida(Juego* juego, int origenF, int origenC, int destinoF, int destinoC, int& capturaF, int& capturaC);
bool existeCapturaPara(Juego* juego, char color);
void obtenerCapturasDisponibles(Juego* juego, int fila, int col, std::vector<Movimiento>& capturas);
bool puedeCapturarMas(Juego* juego, int fila, int col);
void realizarCapturaMultiple(Juego* juego, int fila, int col);
void verificarCoronacion(Juego* juego, int fila, int col);
bool verificarVictoria(Juego* juego);
bool tieneMovimientosValidos(Juego* juego, char color);
void mostrarEstadoJuego(Juego* juego);
void mostrarEstadisticas(Juego* juego);
void mostrarGanador(Juego* juego);
Jugador* obtenerJugadorActual(Juego* juego);
Jugador* obtenerJugadorOponente(Juego* juego);
char obtenerColorActual(Juego* juego);
char obtenerColorOponente(Juego* juego);

#endif
