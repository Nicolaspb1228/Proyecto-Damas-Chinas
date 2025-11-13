#ifndef ROLES_H
#define ROLES_H

#include "estructuras.h"
#include <string>

// Funciones de gestión de roles
void inicializarRol(Rol* rol, TipoRol tipo);
void mostrarRolesDisponibles();
TipoRol seleccionarRol(const std::string& nombreJugador);
void mostrarHabilidadesRol(const Rol* rol);
void mostrarDetalleRol(TipoRol tipo);
void actualizarCooldowns(Rol* rol);
bool puedeUsarHabilidad(const Rol* rol, int indiceHabilidad);
void usarHabilidad(Rol* rol, int indiceHabilidad);
std::string obtenerNombreRol(TipoRol tipo);

#endif
