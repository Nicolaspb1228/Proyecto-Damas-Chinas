#include "jugador.h"
#include "roles.h"


void inicializarJugador(Jugador* jugador, const std::string& nombre, char color) {
    jugador->nombre = nombre;
    jugador->color = color;
    jugador->piezasCapturadas = 0;
    jugador->movimientosRealizados = 0;
    jugador->piezasRestantes = 20;
    jugador->turnosJugados = 0;
    jugador->tieneTurnoExtra = false;
    jugador->furiaActiva = false;
    inicializarRol(&jugador->rol, ROL_NINGUNO);
}
void incrementarCapturaJugador(Jugador* jugador) {
    jugador->piezasCapturadas++;
}

void incrementarMovimientoJugador(Jugador* jugador) {
    jugador->movimientosRealizados++;
}
void reiniciarEstadisticasJugador(Jugador* jugador) {
    jugador->piezasCapturadas = 0;
    jugador->movimientosRealizados = 0;
    jugador->piezasRestantes = 20;
}
std::string obtenerColorNombreJugador(const Jugador* jugador) {
    return (jugador->color == 'B') ? "Blancas" : "Negras";
}
void actualizarPiezasRestantes(Jugador* jugador, int cantidad) {
    jugador->piezasRestantes = cantidad;
}
