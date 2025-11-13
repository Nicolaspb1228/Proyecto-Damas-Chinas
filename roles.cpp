#include "estructuras.h"
#include <iostream>

using namespace std;

// Inicializa un rol con sus habilidades específicas
void inicializarRol(Rol* rol, TipoRol tipo) {
    rol->tipo = tipo;
    
    switch(tipo) {
        case ROL_REY:
            rol->nombre = "Rey";
            rol->descripcion = "Poder absoluto - Control total del juego";
            rol->icono = "👑";
            
            // Habilidad 1: Turno Doble
            rol->habilidades[0].nombre = "Turno Doble";
            rol->habilidades[0].descripcion = "Jugar dos turnos seguidos";
            rol->habilidades[0].usosRestantes = 1;
            rol->habilidades[0].cooldownActual = 0;
            rol->habilidades[0].cooldownMaximo = 0;
            rol->habilidades[0].esUsoUnico = true;
            
            // Habilidad 2: Revivir Pieza
            rol->habilidades[1].nombre = "Revivir Pieza";
            rol->habilidades[1].descripcion = "Recuperar una pieza capturada";
            rol->habilidades[1].usosRestantes = 1;
            rol->habilidades[1].cooldownActual = 0;
            rol->habilidades[1].cooldownMaximo = 0;
            rol->habilidades[1].esUsoUnico = true;
            
            // Habilidad 3: Decreto Real
            rol->habilidades[2].nombre = "Decreto Real";
            rol->habilidades[2].descripcion = "Ver todos los movimientos validos del rival";
            rol->habilidades[2].usosRestantes = 999;
            rol->habilidades[2].cooldownActual = 0;
            rol->habilidades[2].cooldownMaximo = 5;
            rol->habilidades[2].esUsoUnico = false;
            break;
            
        case ROL_GUERRERO:
            rol->nombre = "Guerrero";
            rol->descripcion = "Maestro del combate - Especialista en capturas";
            rol->icono = "⚔️";
            
            // Habilidad 1: Furia de Batalla
            rol->habilidades[0].nombre = "Furia de Batalla";
            rol->habilidades[0].descripcion = "Proxima captura cuenta doble (elimina 2 piezas)";
            rol->habilidades[0].usosRestantes = 2;
            rol->habilidades[0].cooldownActual = 0;
            rol->habilidades[0].cooldownMaximo = 0;
            rol->habilidades[0].esUsoUnico = false;
            
            // Habilidad 2: Sacrificio Táctico
            rol->habilidades[1].nombre = "Sacrificio Tactico";
            rol->habilidades[1].descripcion = "Sacrifica 1 pieza para mover otra 2 veces";
            rol->habilidades[1].usosRestantes = 999;
            rol->habilidades[1].cooldownActual = 0;
            rol->habilidades[1].cooldownMaximo = 7;
            rol->habilidades[1].esUsoUnico = false;
            
            // Habilidad 3: Sed de Sangre
            rol->habilidades[2].nombre = "Sed de Sangre";
            rol->habilidades[2].descripcion = "Capturas obligatorias para ambos por 3 turnos";
            rol->habilidades[2].usosRestantes = 1;
            rol->habilidades[2].cooldownActual = 0;
            rol->habilidades[2].cooldownMaximo = 0;
            rol->habilidades[2].esUsoUnico = true;
            break;
            
        case ROL_MAGO:
            rol->nombre = "Mago";
            rol->descripcion = "Maestro de lo arcano - Manipula el tablero";
            rol->icono = "🧙";
            
            // Habilidad 1: Teletransporte
            rol->habilidades[0].nombre = "Teletransporte";
            rol->habilidades[0].descripcion = "Mueve una pieza a cualquier casilla vacia";
            rol->habilidades[0].usosRestantes = 1;
            rol->habilidades[0].cooldownActual = 0;
            rol->habilidades[0].cooldownMaximo = 0;
            rol->habilidades[0].esUsoUnico = true;
            
            // Habilidad 2: Coronación Mágica
            rol->habilidades[1].nombre = "Coronacion Magica";
            rol->habilidades[1].descripcion = "Convierte un peon en dama instantaneamente";
            rol->habilidades[1].usosRestantes = 999;
            rol->habilidades[1].cooldownActual = 0;
            rol->habilidades[1].cooldownMaximo = 8;
            rol->habilidades[1].esUsoUnico = false;
            
            // Habilidad 3: Congelar
            rol->habilidades[2].nombre = "Congelar";
            rol->habilidades[2].descripcion = "Congela una pieza enemiga por 2 turnos";
            rol->habilidades[2].usosRestantes = 2;
            rol->habilidades[2].cooldownActual = 0;
            rol->habilidades[2].cooldownMaximo = 0;
            rol->habilidades[2].esUsoUnico = false;
            break;
            
        default:
            rol->nombre = "Sin Rol";
            rol->descripcion = "Modo clasico sin habilidades";
            rol->icono = "👤";
            break;
    }
}

// Muestra todos los roles disponibles
void mostrarRolesDisponibles() {
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║           ROLES DISPONIBLES                  ║\n";
    cout << "╚═══════════════════════════════════════════════╝\n\n";
    
    cout << "👑 1. REY - Poder Absoluto\n";
    cout << "   • Turno Doble (1 uso)\n";
    cout << "   • Revivir Pieza (1 uso)\n";
    cout << "   • Decreto Real (cooldown 5 turnos)\n";
    cout << "   Estilo: Control y dominio del juego\n\n";
    
    cout << "⚔️  2. GUERRERO - Maestro del Combate\n";
    cout << "   • Furia de Batalla (2 usos)\n";
    cout << "   • Sacrificio Tactico (cooldown 7 turnos)\n";
    cout << "   • Sed de Sangre (1 uso)\n";
    cout << "   Estilo: Agresivo y ofensivo\n\n";
    
    cout << "🧙 3. MAGO - Maestro Arcano\n";
    cout << "   • Teletransporte (1 uso)\n";
    cout << "   • Coronacion Magica (cooldown 8 turnos)\n";
    cout << "   • Congelar (2 usos)\n";
    cout << "   Estilo: Tactico y estrategico\n\n";
    
    cout << "👤 4. SIN ROL - Modo Clasico\n";
    cout << "   Sin habilidades especiales\n\n";
}

// Permite al jugador seleccionar un rol
TipoRol seleccionarRol(const string& nombreJugador) {
    mostrarRolesDisponibles();
    
    int opcion;
    cout << nombreJugador << ", selecciona tu rol (1-4): ";
    cin >> opcion;
    
    switch(opcion) {
        case 1: return ROL_REY;
        case 2: return ROL_GUERRERO;
        case 3: return ROL_MAGO;
        case 4: return ROL_NINGUNO;
        default:
            cout << "Opcion invalida. Asignando ROL_NINGUNO.\n";
            return ROL_NINGUNO;
    }
}

// Muestra las habilidades disponibles de un rol
void mostrarHabilidadesRol(const Rol* rol) {
    if (rol->tipo == ROL_NINGUNO) {
        cout << "\nNo tienes habilidades (modo clasico).\n";
        return;
    }
    
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║  " << rol->icono << " HABILIDADES DE " << rol->nombre << "\n";
    cout << "╚═══════════════════════════════════════════════╝\n";
    
    for (int i = 0; i < 3; i++) {
        cout << "\n[" << (i + 1) << "] " << rol->habilidades[i].nombre << "\n";
        cout << "    " << rol->habilidades[i].descripcion << "\n";
        
        if (rol->habilidades[i].cooldownActual > 0) {
            cout << "    ⏳ Cooldown: " << rol->habilidades[i].cooldownActual << " turnos\n";
        } else if (rol->habilidades[i].usosRestantes == 0) {
            cout << "    ❌ Sin usos restantes\n";
        } else if (rol->habilidades[i].esUsoUnico) {
            cout << "    ✨ Disponible (" << rol->habilidades[i].usosRestantes << " uso)\n";
        } else if (rol->habilidades[i].usosRestantes < 999) {
            cout << "    ✅ Disponible (" << rol->habilidades[i].usosRestantes << " usos)\n";
        } else {
            cout << "    ✅ Disponible\n";
        }
    }
    cout << "\n";
}

// Muestra detalles de un rol específico
void mostrarDetalleRol(TipoRol tipo) {
    Rol rol;
    inicializarRol(&rol, tipo);
    
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║  " << rol.icono << " " << rol.nombre << "\n";
    cout << "╚═══════════════════════════════════════════════╝\n";
    cout << rol.descripcion << "\n";
    
    mostrarHabilidadesRol(&rol);
}

// Actualiza los cooldowns de las habilidades
void actualizarCooldowns(Rol* rol) {
    for (int i = 0; i < 3; i++) {
        if (rol->habilidades[i].cooldownActual > 0) {
            rol->habilidades[i].cooldownActual--;
        }
    }
}

// Verifica si se puede usar una habilidad
bool puedeUsarHabilidad(const Rol* rol, int indiceHabilidad) {
    if (indiceHabilidad < 0 || indiceHabilidad >= 3) {
        return false;
    }
    
    const Habilidad& hab = rol->habilidades[indiceHabilidad];
    
    // Verificar cooldown
    if (hab.cooldownActual > 0) {
        return false;
    }
    
    // Verificar usos restantes
    if (hab.usosRestantes <= 0) {
        return false;
    }
    
    return true;
}

// Usa una habilidad (reduce usos y activa cooldown)
void usarHabilidad(Rol* rol, int indiceHabilidad) {
    if (indiceHabilidad < 0 || indiceHabilidad >= 3) {
        return;
    }
    
    Habilidad& hab = rol->habilidades[indiceHabilidad];
    
    // Reducir usos si no es ilimitado
    if (hab.usosRestantes < 999) {
        hab.usosRestantes--;
    }
    
    // Activar cooldown
    hab.cooldownActual = hab.cooldownMaximo;
    
    cout << "\n✨ ¡Habilidad '" << hab.nombre << "' activada!\n";
}

// Obtiene el nombre de un tipo de rol
string obtenerNombreRol(TipoRol tipo) {
    switch(tipo) {
        case ROL_REY: return "Rey";
        case ROL_GUERRERO: return "Guerrero";
        case ROL_MAGO: return "Mago";
        default: return "Sin Rol";
    }
}
