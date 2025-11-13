#include "juego.h"
#include "menu.h"
#include <iostream>

using namespace std;

int main() {
    bool salir = false;
    
    while (!salir) {
        int opcion = mostrarMenuPrincipal();
        
        switch (opcion) {
            case 1: {
                // Nueva partida
                Juego juego;
                inicializarJuego(&juego);
                jugar(&juego);
                
                cout << "\n¿Deseas jugar otra partida? (s/n): ";
                char respuesta;
                cin >> respuesta;
                cin.ignore();
                
                if (respuesta != 's' && respuesta != 'S') {
                    salir = true;
                }
                break;
            }
            case 2:
                // Ver reglas
                mostrarReglas();
                break;
            case 3:
                // Créditos
                mostrarCreditos();
                break;
            case 4:
                // Salir
                salir = true;
                cout << "\n¡Gracias por jugar!\n\n";
                break;
            default:
                cout << "\nOpcion invalida. Intenta nuevamente.\n";
                pausar();
                break;
        }
    }
    
    return 0;
}
