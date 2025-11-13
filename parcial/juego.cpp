#include "juego.h"
#include "tablero.h"
#include "pieza.h"
#include "jugador.h"
#include "roles.h"
#include "habilidades.h"
#include <iostream>
#include <limits>   
#include <cmath>
#include <cstdlib>
#include <vector>   

void inicializarJuego(Juego* juego) {
    inicializarTablero(&juego->tablero);
    configurarModoJuego(juego);
    configurarJugadores(juego);
    inicializarPiezasJuego(juego);
    juego->turnoActual = 1;
    juego->juegoTerminado = false;
    juego->numEfectosActivos = 0;
} 
void configurarModoJuego(Juego* juego) {
    std::cout << "\n*******************************************\n";
    std::cout << "*        MODO DE JUEGO                   *\n";
    std::cout << "********************************************\n\n";
    std::cout << "1. Modo con Roles (NUEVO)\n";
    std::cout << "2. Modo Clasico (sin habilidades)\n\n";
    std::cout << "Selecciona el modo: ";
    
    int opcion;
    std::cin >> opcion;
    std::cin.ignore();
    
    juego->modoRoles = (opcion == 1);
}
void configurarJugadores(Juego* juego) {
    std::string nombre;
    
    std::cout << "\n=== CONFIGURACION DE JUGADORES ===\n";
    std::cout << "Nombre del Jugador 1 (Blancas): ";
    getline(std::cin, nombre);
    inicializarJugador(&juego->jugador1, nombre.empty() ? "Jugador 1" : nombre, 'B');
    
    if (juego->modoRoles) {
        TipoRol rol = seleccionarRol(juego->jugador1.nombre);
        inicializarRol(&juego->jugador1.rol, rol);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "\nNombre del Jugador 2 (Negras): ";
    getline(std::cin, nombre);
    inicializarJugador(&juego->jugador2, nombre.empty() ? "Jugador 2" : nombre, 'N');
    
    if (juego->modoRoles) {
        TipoRol rol = seleccionarRol(juego->jugador2.nombre);
        inicializarRol(&juego->jugador2.rol, rol);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void inicializarPiezasJuego(Juego* juego) {
    int indice = 0;
    
    // Crear piezas negras (filas 0-3)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            if (esCasillaOscura(i, j)) {
                inicializarPieza(&juego->piezas[indice], i, j, 'N');
                juego->piezas[indice].congelada = false;
                juego->piezas[indice].turnosCongelada = 0;
                colocarPiezaEn(&juego->tablero, &juego->piezas[indice], i, j);
                indice++;
            }
        }
    }
    // Crear piezas blancas (filas 6-9)
    for (int i = 6; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (esCasillaOscura(i, j)) {
                inicializarPieza(&juego->piezas[indice], i, j, 'B');
                juego->piezas[indice].congelada = false;
                juego->piezas[indice].turnosCongelada = 0;
                colocarPiezaEn(&juego->tablero, &juego->piezas[indice], i, j);
                indice++;
            }
        }
    }
    
    juego->numPiezas = indice;
}

void jugar(Juego* juego) {
    while (!juego->juegoTerminado) {
        jugarTurno(juego);
    }
    mostrarGanador(juego);
}

void jugarTurno(Juego* juego) {
    mostrarEstadoJuego(juego);
    
    char colorActual = obtenerColorActual(juego);
    
    if (existeCapturaPara(juego, colorActual)) {
        std::cout << "¡ATENCION! Tienes capturas obligatorias disponibles.\n";
    }
    
    int origenF, origenC, destinoF, destinoC;
    
    while (true) {
        if (!solicitarMovimiento(origenF, origenC, destinoF, destinoC)) {
            continue;
        }
        
        if (ejecutarMovimiento(juego, origenF, origenC, destinoF, destinoC)) {
            break;
        }
    }
    
    if (verificarVictoria(juego)) {
        juego->juegoTerminado = true;
        return;
    }
    
    cambiarTurno(juego);
}

bool solicitarMovimiento(int& origenF, int& origenC, int& destinoF, int& destinoC) {
    std::cout << "\nIngresa el movimiento (formato: filaOrigen colOrigen filaDestino colDestino)\n";
    std::cout << "Ejemplo: 6 1 5 0 (mueve la pieza de [6,1] a [5,0])\n";
    std::cout << "Ingresa -1 -1 -1 -1 para ver estadisticas\n";
    std::cout << "Ingresa -2 -2 -2 -2 para usar habilidad\n";
    std::cout << "Tu movimiento: ";
    
    if (!(std::cin >> origenF >> origenC >> destinoF >> destinoC)) {  
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Entrada inválida. Intente nuevamente.\n";
        return false;
    }
    
    return true;
}

bool ejecutarMovimiento(Juego* juego, int origenF, int origenC, int destinoF, int destinoC) {
    if (origenF == -1) {
        mostrarEstadisticas(juego);
        return false;
    }
    
    if (origenF == -2 && juego->modoRoles) {
        mostrarMenuHabilidades(juego);
        int numHab;
        std::cout << "\nSelecciona habilidad (0-3): ";
        std::cin >> numHab;
        if (numHab > 0) {
            ejecutarHabilidad(juego, numHab);
        }
        return false;
    }
    
    if (!esDentroDelTablero(origenF, origenC) || !esDentroDelTablero(destinoF, destinoC)) {
        std::cout << "Error: Coordenadas fuera del tablero.\n";
        return false;
    }
    
    // Verificar que hay una pieza
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, origenF, origenC);
    if (pieza == nullptr) {
        std::cout << "Error: No hay ninguna pieza en la posicion de origen.\n";
        return false;
    }
    // Verificar si está congelada
    if (pieza->congelada) {
        std::cout << "Error: Esta pieza esta congelada por " << pieza->turnosCongelada << " turnos.\n";
        return false;
    }
    
    // Verificar que es del jugador actual
    if (obtenerColorPieza(pieza) != obtenerColorActual(juego)) {
        std::cout << "Error: Esa pieza no te pertenece.\n";
        return false;
    }
    
    // Verificar capturas obligatorias
    if (existeCapturaPara(juego, obtenerColorActual(juego))) {
        int capturaF, capturaC;
        if (!esCapturaValida(juego, origenF, origenC, destinoF, destinoC, capturaF, capturaC)) {
            std::cout << "Error: Debes realizar una captura obligatoria.\n";
            return false;
        }
        

        moverPiezaEn(&juego->tablero, origenF, origenC, destinoF, destinoC);
        eliminarPiezaEn(&juego->tablero, capturaF, capturaC);
        incrementarCapturaJugador(obtenerJugadorActual(juego));
        
        // Verificar furia del guerrero 
        if (obtenerJugadorActual(juego)->furiaActiva) {
            std::cout << "\n ¡FURIA DE BATALLA! Eliminando pieza adicional...\n";
            // Buscar otra pieza enemiga cercana y eliminarla
            char colorEnemigo = obtenerColorOponente(juego);
            bool encontrada = false;
            for (int i = destinoF-2; i <= destinoF+2 && !encontrada; i++) {
                for (int j = destinoC-2; j <= destinoC+2 && !encontrada; j++) {
                    if (esDentroDelTablero(i, j)) {
                        Pieza* p = obtenerPiezaEn(&juego->tablero, i, j);
                        if (p != nullptr && p->color == colorEnemigo) {
                            eliminarPiezaEn(&juego->tablero, i, j);
                            incrementarCapturaJugador(obtenerJugadorActual(juego));
                            encontrada = true;
                            std::cout << "Pieza adicional eliminada en [" << i << "," << j << "]\n";
                        }
                    }
                }
            }
            obtenerJugadorActual(juego)->furiaActiva = false;
        }
        
        std::cout << "\n¡Captura realizada!\n";
        
        verificarCoronacion(juego, destinoF, destinoC);
        
        // Verificar capturas múltiples
        if (puedeCapturarMas(juego, destinoF, destinoC)) {
            std::cout << "\n¡Puedes capturar mas piezas!\n";
            mostrarTablero(&juego->tablero);
            realizarCapturaMultiple(juego, destinoF, destinoC);
        }
        
        incrementarMovimientoJugador(obtenerJugadorActual(juego));
        return true;
    }
    
    // Movimiento simple
    if (esMovimientoSimpleValido(juego, origenF, origenC, destinoF, destinoC)) {
        moverPiezaEn(&juego->tablero, origenF, origenC, destinoF, destinoC);
        verificarCoronacion(juego, destinoF, destinoC);
        incrementarMovimientoJugador(obtenerJugadorActual(juego));
        return true;
    }
    
    std::cout << "Error: Movimiento invalido.\n";
    return false;
}

// Verifica si un movimiento simple es válido
bool esMovimientoSimpleValido(Juego* juego, int origenF, int origenC, int destinoF, int destinoC) {
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, origenF, origenC);
    if (pieza == nullptr) return false;
    if (!estaVaciaCasilla(&juego->tablero, destinoF, destinoC)) {
        return false;
    }
    if (!esCasillaOscura(destinoF, destinoC)) {
        return false;
    }
    int deltaF = destinoF - origenF;
    int deltaC = destinoC - origenC;
    
    if (esDamaPieza(pieza)) {
        if (abs(deltaF) != abs(deltaC)) {
            return false;
        }
        
        int dirF = (deltaF > 0) ? 1 : -1;
        int dirC = (deltaC > 0) ? 1 : -1;
        int pasos = abs(deltaF);
        
        for (int i = 1; i < pasos; i++) {
            if (!estaVaciaCasilla(&juego->tablero, origenF + i * dirF, origenC + i * dirC)) {
                return false;
            }
        }
        
        return true;
    }
    
    if (abs(deltaF) != 1 || abs(deltaC) != 1) {
        return false;
    }
    
    if (obtenerColorPieza(pieza) == 'B') {
        return deltaF == -1;
    } else {
        return deltaF == 1;
    }
}

bool esCapturaValida(Juego* juego, int origenF, int origenC, int destinoF, int destinoC,
                     int& capturaF, int& capturaC) {
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, origenF, origenC);
    if (pieza == nullptr) return false;
    
    if (!estaVaciaCasilla(&juego->tablero, destinoF, destinoC)) {
        return false;
    }
    
    int deltaF = destinoF - origenF;
    int deltaC = destinoC - origenC;
    
    // Dama
    if (esDamaPieza(pieza)) {
        if (abs(deltaF) != abs(deltaC) || abs(deltaF) < 2) {
            return false;
        }
        
        int dirF = (deltaF > 0) ? 1 : -1;
        int dirC = (deltaC > 0) ? 1 : -1;
        int pasos = abs(deltaF);
        
        bool encontro = false;
        int tempF = -1, tempC = -1;
        
        for (int i = 1; i < pasos; i++) {
            int checkF = origenF + i * dirF;
            int checkC = origenC + i * dirC;
            
            if (!estaVaciaCasilla(&juego->tablero, checkF, checkC)) {
                Pieza* piezaCamino = obtenerPiezaEn(&juego->tablero, checkF, checkC);
                
                if (encontro) return false;
                
                if (obtenerColorPieza(piezaCamino) == obtenerColorPieza(pieza)) {
                    return false;
                }
                
                encontro = true;
                tempF = checkF;
                tempC = checkC;
            }
        }
        
        if (encontro) {
            capturaF = tempF;
            capturaC = tempC;
            return true;
        }
        
        return false;
    }
    
    // Pieza normal
    if (abs(deltaF) != 2 || abs(deltaC) != 2) {
        return false;
    }
    
    capturaF = origenF + deltaF / 2;
    capturaC = origenC + deltaC / 2;
    
    Pieza* piezaCapturada = obtenerPiezaEn(&juego->tablero, capturaF, capturaC);
    if (piezaCapturada == nullptr || 
        obtenerColorPieza(piezaCapturada) == obtenerColorPieza(pieza)) {
        return false;
    }
    
    return true;
}
bool existeCapturaPara(Juego* juego, char color) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Pieza* pieza = obtenerPiezaEn(&juego->tablero, i, j);
            if (pieza != nullptr && obtenerColorPieza(pieza) == color) {
                std::vector<Movimiento> capturas;
                obtenerCapturasDisponibles(juego, i, j, capturas);
                if (!capturas.empty()) {
                    return true;
                }
            }
        }
    }
    return false;
}

void obtenerCapturasDisponibles(Juego* juego, int fila, int col, std::vector<Movimiento>& capturas) {
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr) return;
    
    int direcciones[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    
    if (esDamaPieza(pieza)) {
        for (int d = 0; d < 4; d++) {
            int dirF = direcciones[d][0];
            int dirC = direcciones[d][1];
            
            for (int dist = 2; dist < 10; dist++) {
                int destinoF = fila + dist * dirF;
                int destinoC = col + dist * dirC;
                
                if (!esDentroDelTablero(destinoF, destinoC)) break;
                if (!estaVaciaCasilla(&juego->tablero, destinoF, destinoC)) break;
                
                int capturaF, capturaC;
                if (esCapturaValida(juego, fila, col, destinoF, destinoC, capturaF, capturaC)) {
                    Movimiento mov;
                    mov.origenF = fila;
                    mov.origenC = col;
                    mov.destinoF = destinoF;
                    mov.destinoC = destinoC;
                    mov.esCaptura = true;
                    mov.capturaF = capturaF;
                    mov.capturaC = capturaC;
                    capturas.push_back(mov);
                }
            }
        }
    } else {
        for (int d = 0; d < 4; d++) {
            int destinoF = fila + 2 * direcciones[d][0];
            int destinoC = col + 2 * direcciones[d][1];
            
            if (!esDentroDelTablero(destinoF, destinoC)) continue;
            
            int capturaF, capturaC;
            if (esCapturaValida(juego, fila, col, destinoF, destinoC, capturaF, capturaC)) {
                Movimiento mov;
                mov.origenF = fila;
                mov.origenC = col;
                mov.destinoF = destinoF;
                mov.destinoC = destinoC;
                mov.esCaptura = true;
                mov.capturaF = capturaF;
                mov.capturaC = capturaC;
                capturas.push_back(mov);
            }
        }
    }
}

bool puedeCapturarMas(Juego* juego, int fila, int col) {
    std::vector<Movimiento> capturas;
    obtenerCapturasDisponibles(juego, fila, col, capturas);
    return !capturas.empty();
}

void realizarCapturaMultiple(Juego* juego, int fila, int col) {
    while (puedeCapturarMas(juego, fila, col)) {
        std::vector<Movimiento> capturas;
        obtenerCapturasDisponibles(juego, fila, col, capturas);
        
        std::cout << "\nCapturas disponibles desde [" << fila << "," << col << "]:\n";
        for (size_t i = 0; i < capturas.size(); i++) {
            std::cout << i + 1 << ". Mover a [" << capturas[i].destinoF << "," 
                 << capturas[i].destinoC << "]\n";
        }
        
        int opcion;
        std::cout << "Selecciona una captura (1-" << capturas.size() << ") o 0 para terminar: ";
        std::cin >> opcion;
        
        if (opcion < 1 || opcion > (int)capturas.size()) {
            break;
        }
        
        Movimiento mov = capturas[opcion - 1];
        moverPiezaEn(&juego->tablero, mov.origenF, mov.origenC, mov.destinoF, mov.destinoC);
        eliminarPiezaEn(&juego->tablero, mov.capturaF, mov.capturaC);
        incrementarCapturaJugador(obtenerJugadorActual(juego));
        
        fila = mov.destinoF;
        col = mov.destinoC;
        
        verificarCoronacion(juego, fila, col);
        
        std::cout << "\n¡Captura realizada!\n";
        mostrarTablero(&juego->tablero);
    }
}

void verificarCoronacion(Juego* juego, int fila, int col) {
    Pieza* pieza = obtenerPiezaEn(&juego->tablero, fila, col);
    if (pieza == nullptr || esDamaPieza(pieza)) return;
    
    if (obtenerColorPieza(pieza) == 'B' && fila == 0) {
        coronarPieza(pieza);
        std::cout << "\n¡¡¡CORONACION!!! La pieza se ha convertido en DAMA.\n";
    }
    
    if (obtenerColorPieza(pieza) == 'N' && fila == 9) {
        coronarPieza(pieza);
        std::cout << "\n¡¡¡CORONACION!!! La pieza se ha convertido en DAMA.\n";
    }
}

bool verificarVictoria(Juego* juego) {
    char colorOponente = obtenerColorOponente(juego);
    
    if (contarPiezasColor(&juego->tablero, colorOponente) == 0) {
        return true;
    }
    
    if (!tieneMovimientosValidos(juego, colorOponente)) {
        return true;
    }
    
    return false;
}

bool tieneMovimientosValidos(Juego* juego, char color) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Pieza* pieza = obtenerPiezaEn(&juego->tablero, i, j);
            if (pieza == nullptr || obtenerColorPieza(pieza) != color) continue;
            
            std::vector<Movimiento> capturas;
            obtenerCapturasDisponibles(juego, i, j, capturas);
            if (!capturas.empty()) return true;
            
            int direcciones[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
            
            if (esDamaPieza(pieza)) {
                for (int d = 0; d < 4; d++) {
                    for (int dist = 1; dist < 10; dist++) {
                        int destinoF = i + dist * direcciones[d][0];
                        int destinoC = j + dist * direcciones[d][1];
                        
                        if (!esDentroDelTablero(destinoF, destinoC)) break;
                        if (!estaVaciaCasilla(&juego->tablero, destinoF, destinoC)) break;
                        
                        if (esMovimientoSimpleValido(juego, i, j, destinoF, destinoC)) {
                            return true;
                        }
                    }
                }
            } else {
                int dirFila = (color == 'B') ? -1 : 1;
                
                for (int dc = -1; dc <= 1; dc += 2) {
                    int destinoF = i + dirFila;
                    int destinoC = j + dc;
                    
                    if (esDentroDelTablero(destinoF, destinoC) &&
                        esMovimientoSimpleValido(juego, i, j, destinoF, destinoC)) {
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}
void cambiarTurno(Juego* juego) {
    Jugador* jugadorActual = obtenerJugadorActual(juego);
    
    if (jugadorActual->tieneTurnoExtra) {
        std::cout << "\n[REY] ¡Tienes un turno extra! Juega nuevamente.\n";
        jugadorActual->tieneTurnoExtra = false;
        return; // No cambiar turno
    }
    if (juego->modoRoles) {
        actualizarCooldowns(&jugadorActual->rol);
        jugadorActual->turnosJugados++;
    }
    
    actualizarEfectosActivos(juego);
    
    juego->turnoActual = (juego->turnoActual == 1) ? 2 : 1;
}

void mostrarEstadoJuego(Juego* juego) {
    system("clear || cls");
    
    std::cout << "\n";
    std::cout << "****************************************\n";
    if (juego->modoRoles) {
        std::cout << "  DAMAS EPICAS - MODO ROLES  \n";
    } else {
        std::cout << "  DAMAS INTERNACIONALES (10x10)  \n";
    }
    std::cout << "****************************************\n";
    
    mostrarTablero(&juego->tablero);
    
    Jugador* actual = obtenerJugadorActual(juego);
    std::cout << "Turno actual: " << actual->nombre << " (" 
         << obtenerColorNombreJugador(actual) << ")";
    
    if (juego->modoRoles && actual->rol.tipo != ROL_NINGUNO) {
        std::cout << " " << actual->rol.icono << " " << actual->rol.nombre;
    }
    std::cout << "\n";
    std::cout << "Piezas restantes - " << juego->jugador1.nombre << ": " 
         << contarPiezasColor(&juego->tablero, 'B') << " | "
         << juego->jugador2.nombre << ": " << contarPiezasColor(&juego->tablero, 'N') << "\n";
    
    if (juego->numEfectosActivos > 0) {
        std::cout << "\n[*] Efectos activos:\n";
        for (int i = 0; i < juego->numEfectosActivos; i++) {
            std::cout << "  • " << juego->efectosActivos[i].nombre 
                 << " (" << juego->efectosActivos[i].turnosRestantes << " turnos)\n";
        }
    }
    
    std::cout << "========================================\n";
}

void mostrarEstadisticas(Juego* juego) {
    std::cout << "\n=== ESTADISTICAS DEL JUEGO ===\n";
    std::cout << juego->jugador1.nombre << " (" << obtenerColorNombreJugador(&juego->jugador1) << "):\n";
    std::cout << "  - Piezas capturadas: " << juego->jugador1.piezasCapturadas << "\n";
    std::cout << "  - Movimientos realizados: " << juego->jugador1.movimientosRealizados << "\n";
    std::cout << "  - Piezas restantes: " << contarPiezasColor(&juego->tablero, 'B') << "\n\n";
    
    std::cout << juego->jugador2.nombre << " (" << obtenerColorNombreJugador(&juego->jugador2) << "):\n";
    std::cout << "  - Piezas capturadas: " << juego->jugador2.piezasCapturadas << "\n";
    std::cout << "  - Movimientos realizados: " << juego->jugador2.movimientosRealizados << "\n";
    std::cout << "  - Piezas restantes: " << contarPiezasColor(&juego->tablero, 'N') << "\n";
    std::cout << "==============================\n\n";
}

// Muestra el ganador
void mostrarGanador(Juego* juego) {
    system("clear || cls");
    mostrarTablero(&juego->tablero);
    
    Jugador* ganador = obtenerJugadorActual(juego);
    
    std::cout << "\n";
    std::cout << "****************************************\n";
    std::cout << "*          ¡JUEGO TERMINADO!          *\n";
    std::cout << "****************************************\n";
    std::cout << "*                                      *\n";
    std::cout << "*  GANADOR: " << ganador->nombre;
    
    int espacios = 25 - ganador->nombre.length();
    for (int i = 0; i < espacios; i++) std::cout << " ";
    std::cout << "*\n";
    
    std::cout << "*                                      *\n";
    std::cout << "****************************************\n\n";
    
    mostrarEstadisticas(juego);
}

Jugador* obtenerJugadorActual(Juego* juego) {
    return (juego->turnoActual == 1) ? &juego->jugador1 : &juego->jugador2;
}
Jugador* obtenerJugadorOponente(Juego* juego) {
    return (juego->turnoActual == 1) ? &juego->jugador2 : &juego->jugador1;
}
char obtenerColorActual(Juego* juego) {
    return obtenerJugadorActual(juego)->color;
}
char obtenerColorOponente(Juego* juego) {
    return obtenerJugadorOponente(juego)->color;
}
