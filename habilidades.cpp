#include "habilidades.h"
#include "estructuras.h"
#include "roles.h"
#include "tablero.h"
#include "pieza.h"
#include "jugador.h"
#include <iostream>
#include <cstdlib>

// Declaraciones de funciones externas
extern Jugador* obtenerJugadorActual(Juego* juego);
extern char obtenerColorActual(Juego* juego);


void mostrarMenuHabilidades(Juego* juego) {
    Jugador* jugador = obtenerJugadorActual(juego);
    
    if (jugador->rol.tipo == ROL_NINGUNO) {
        std::cout << "\nNo tienes habilidades disponibles (modo clasico).\n";
        return;
    }
    
    std::cout << "\n╔═══════════════════════════════════════════════╗\n";
    std::cout << "║  " << jugador->rol.icono << " MENU DE HABILIDADES\n";
    std::cout << "╚═══════════════════════════════════════════════╝\n";
    
    for (int i = 0; i < 3; i++) {
        Habilidad& hab = jugador->rol.habilidades[i];
        std::cout << "\n[" << (i + 1) << "] " << hab.nombre;
        
        if (hab.cooldownActual > 0) {
            std::cout << " [COOLDOWN: " << hab.cooldownActual << " turnos]";
        } else if (hab.usosRestantes == 0) {
            std::cout << " [SIN USOS]";
        } else if (hab.esUsoUnico) {
            std::cout << " [DISPONIBLE]";
        } else {
            std::cout << " [DISPONIBLE]";
        }
        
        std::cout << "\n    " << hab.descripcion << "\n";
    }
    
    std::cout << "\n[0] Cancelar\n";
}


bool ejecutarHabilidad(Juego* juego, int numeroHabilidad) {
    if (numeroHabilidad == 0) return false;
    
    Jugador* jugador = obtenerJugadorActual(juego);
    int indice = numeroHabilidad - 1;
    
    if (!puedeUsarHabilidad(&jugador->rol, indice)) {
        std::cout << "\n[X] No puedes usar esta habilidad ahora.\n";
        return false;
    }
    
    bool exito = false;

    switch(jugador->rol.tipo) {
        case ROL_REY:
            if (numeroHabilidad == 1) exito = habilidadRey_TurnoDoble(juego);
            else if (numeroHabilidad == 2) exito = habilidadRey_RevivirPieza(juego);
            else if (numeroHabilidad == 3) exito = habilidadRey_DecretoReal(juego);
            break;
            
        case ROL_GUERRERO:
            if (numeroHabilidad == 1) exito = habilidadGuerrero_FuriaBatalla(juego);
            else if (numeroHabilidad == 2) exito = habilidadGuerrero_SacrificioTactico(juego);
            else if (numeroHabilidad == 3) exito = habilidadGuerrero_SedSangre(juego);
            break;
            
        case ROL_MAGO:
            if (numeroHabilidad == 1) exito = habilidadMago_Teletransporte(juego);
            else if (numeroHabilidad == 2) exito = habilidadMago_CoronacionMagica(juego);
            else if (numeroHabilidad == 3) exito = habilidadMago_Congelar(juego);
            break;
            
        default:
            break;
    }
    
    if (exito) {
        usarHabilidad(&jugador->rol, indice);
    }
    
    return exito;
}

//  HABILIDADES DEL REY 

bool habilidadRey_TurnoDoble(Juego* juego) {
    Jugador* jugador = obtenerJugadorActual(juego);
    jugador->tieneTurnoExtra = true;
    std::cout << "\n[REY] Turno doble activado! Jugaras dos veces seguidas.\n";
    return true;
}

bool habilidadRey_RevivirPieza(Juego* juego) {
    Jugador* jugador = obtenerJugadorActual(juego);
    char color = jugador->color;
    
    // Buscar una pieza capturada
    Pieza* piezaRevivir = nullptr;
    for (int i = 0; i < juego->numPiezas; i++) {
        if (juego->piezas[i].color == color && !juego->piezas[i].activa) {
            piezaRevivir = &juego->piezas[i];
            break;
        }
    }
    
    if (piezaRevivir == nullptr) {
        std::cout << "\n[X] No tienes piezas capturadas para revivir.\n";
        return false;
    }
    
    // Buscar una casilla vacía para revivir
    std::cout << "\nIngresa la posicion donde revivir la pieza (fila columna): ";
    int fila, col;
    std::cin >> fila >> col;
    
    if (!esDentroDelTablero(fila, col) || !estaVaciaCasilla(&juego->tablero, fila, col)) {
        std::cout << "\n[X] Posicion invalida.\n";
        return false;
    }

        // Revivir la pieza
    piezaRevivir->activa = true;
    piezaRevivir->fila = fila;
    piezaRevivir->columna = col;
    colocarPiezaEn(&juego->tablero, piezaRevivir, fila, col);
    
    std::cout << "\n[REY] Pieza revivida en [" << fila << "," << col << "]!\n";
    return true;
}

bool habilidadRey_DecretoReal(Juego* juego) {
    std::cout << "\n[REY] DECRETO REAL: Analizando movimientos del rival...\n\n";
    
    // Mostrar información de las piezas del oponente
    char colorOponente = (obtenerColorActual(juego) == 'B') ? 'N' : 'B';
    int piezasConMovimientos = 0;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Pieza* pieza = obtenerPiezaEn(&juego->tablero, i, j);
            if (pieza != nullptr && pieza->color == colorOponente) {
                bool tieneMovimientos = false;
                
                // Verificar si tiene movimientos 
                int dirs[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
                for (int d = 0; d < 4; d++) {
                    int nf = i + dirs[d][0];
                    int nc = j + dirs[d][1];
                    if (esDentroDelTablero(nf, nc) && estaVaciaCasilla(&juego->tablero, nf, nc)) {
                        tieneMovimientos = true;
                        break;
                    }
                }
                
                if (tieneMovimientos) {
                    std::cout << "• Pieza en [" << i << "," << j << "] ";
                    std::cout << (pieza->esDama ? "(DAMA)" : "(peon)");
                    std::cout << " tiene movimientos disponibles\n";
                    piezasConMovimientos++;
                }
            }
        }
    }
    
    if (piezasConMovimientos == 0) {
        std::cout << "El rival no tiene movimientos obvios disponibles.\n";
    }
    
    return true;
}

//  HABILIDADES DEL GUERRERO 

bool habilidadGuerrero_FuriaBatalla(Juego* juego) {
    Jugador* jugador = obtenerJugadorActual(juego);
    jugador->furiaActiva = true;
    std::cout << "\n[GUERRERO] FURIA DE BATALLA! Tu proxima captura eliminara 2 piezas.\n";
    return true;
}

bool habilidadGuerrero_SacrificioTactico(Juego* juego) {
    char color = obtenerColorActual(juego);
    
    std::cout << "\nSelecciona la pieza a sacrificar (fila columna): ";
    int fila, col;
    std::cin >> fila >> col;
    
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr || pieza->color != color) {
        std::cout << "\n[X] Pieza invalida.\n";
        return false;
    }
    
    // Sacrificar pieza
    eliminarPiezaEn(&juego->tablero, fila, col);
    
    std::cout << "\nSelecciona la pieza que se movera 2 veces (fila columna): ";
    std::cin >> fila >> col;
    
    pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr || pieza->color != color) {
        std::cout << "\n[X] Pieza invalida.\n";
        return false;
    }
    
    std::cout << "\n[GUERRERO] Sacrificio realizado! La pieza [" << fila << "," << col;
    std::cout << "] puede moverse 2 veces este turno.\n";
    std::cout << "(Implementa tus dos movimientos normalmente)\n";
    
    return true;
}

bool habilidadGuerrero_SedSangre(Juego* juego) {
    agregarEfecto(juego, "Sed de Sangre", 3, true, 'X');
    std::cout << "\n[GUERRERO] SED DE SANGRE! Capturas obligatorias para ambos jugadores por 3 turnos.\n";
    return true;
}

//  HABILIDADES DEL MAGO 

bool habilidadMago_Teletransporte(Juego* juego) {
    char color = obtenerColorActual(juego);
    
    std::cout << "\nSelecciona la pieza a teletransportar (fila columna): ";
    int origenF, origenC;
    std::cin >> origenF >> origenC;
    
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, origenF, origenC);
    if (pieza == nullptr || pieza->color != color) {
        std::cout << "\n[X] Pieza invalida.\n";
        return false;
    }
    
    std::cout << "Ingresa el destino (fila columna): ";
    int destinoF, destinoC;
    std::cin >> destinoF >> destinoC;
    
    if (!esDentroDelTablero(destinoF, destinoC) || 
        !estaVaciaCasilla(&juego->tablero, destinoF, destinoC) ||
        !esCasillaOscura(destinoF, destinoC)) {
        std::cout << "\n[X] Destino invalido.\n";
        return false;
    }
    
    moverPiezaEn(&juego->tablero, origenF, origenC, destinoF, destinoC);
    std::cout << "\n[MAGO] TELETRANSPORTE! Pieza movida de [" << origenF << "," << origenC;
    std::cout << "] a [" << destinoF << "," << destinoC << "]\n";
    
    return true;
}

bool habilidadMago_CoronacionMagica(Juego* juego) {
    char color = obtenerColorActual(juego);
    
    std::cout << "\nSelecciona el peon a coronar (fila columna): ";
    int fila, col;
    std::cin >> fila >> col;
    
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr || pieza->color != color || pieza->esDama) {
        std::cout << "\n[X] Debe ser un peon propio.\n";
        return false;
    }
    
    coronarPieza(pieza);
    std::cout << "\n[MAGO] CORONACION MAGICA! El peon es ahora una DAMA.\n";
    
    return true;
}

bool habilidadMago_Congelar(Juego* juego) {
    char colorOponente = (obtenerColorActual(juego) == 'B') ? 'N' : 'B';
    
    std::cout << "\nSelecciona la pieza enemiga a congelar (fila columna): ";
    int fila, col;
    std::cin >> fila >> col;
    
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr || pieza->color != colorOponente) {
        std::cout << "\n[X] Debe ser una pieza enemiga.\n";
        return false;
    }
    
    pieza->congelada = true;
    pieza->turnosCongelada = 2;
    
    std::cout << "\n[MAGO] CONGELADA! La pieza [" << fila << "," << col;
    std::cout << "] no podra moverse por 2 turnos.\n";
    
    return true;
}

//  FUNCIONES AUXILIARES 

void actualizarEfectosActivos(Juego* juego) {
    // Actualizar turnos de efectos
    for (int i = 0; i < juego->numEfectosActivos; i++) {
        juego->efectosActivos[i].turnosRestantes--;
        
        if (juego->efectosActivos[i].turnosRestantes <= 0) {
            // Eliminar efecto 
            for (int j = i; j < juego->numEfectosActivos - 1; j++) {
                juego->efectosActivos[j] = juego->efectosActivos[j + 1];
            }
            juego->numEfectosActivos--;
            i--;
        }
    }
    
    // Actualizar piezas congeladas
    for (int i = 0; i < juego->numPiezas; i++) {
        if (juego->piezas[i].congelada) {
            juego->piezas[i].turnosCongelada--;
            if (juego->piezas[i].turnosCongelada <= 0) {
                juego->piezas[i].congelada = false;
                std::cout << "\n[HIELO] Una pieza se ha descongelado.\n";
            }
        }
    }
}

void agregarEfecto(Juego* juego, const char* nombre, int turnos, bool ambos, char jugador) {
    if (juego->numEfectosActivos < 5) {
        juego->efectosActivos[juego->numEfectosActivos].nombre = nombre;
        juego->efectosActivos[juego->numEfectosActivos].turnosRestantes = turnos;
        juego->efectosActivos[juego->numEfectosActivos].afectaAmbosJugadores = ambos;
        juego->efectosActivos[juego->numEfectosActivos].jugadorAfectado = jugador;
        juego->numEfectosActivos++;
    }
}

bool tieneEfectoActivo(Juego* juego, const char* nombre) {
    for (int i = 0; i < juego->numEfectosActivos; i++) {
        if (juego->efectosActivos[i].nombre == nombre) {
            return true;
        }
    }
    return false;
}
