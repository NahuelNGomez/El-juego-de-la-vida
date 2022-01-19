#include <iostream>
#include "celulas.h"

#include "impresiones.h"
#include "acciones.h"




#define MAX_FILAS 20
#define MAX_COLUMNAS 80
static const int CELULAS_TOTALES = 1600;
static const int VIVA = 1;
static const int MUERTA = 0;
static const int JUGANDO = 1;
static const int TERMINADO = 0;
static const int MAX_TURNOS = 1000;


int main(){
	juego_t juego;
	posicion_t posiciones_iniciales[MAX_CELULAS];
	int cantidad_inicial = 0;
	juego.celulas_vivas = 0;
	introduccion();
	//reglas();
	inicializar_celulas(&juego);
	mostrar_mapa(juego);
	pedir_datos(&juego, posiciones_iniciales, &cantidad_inicial);
	mostrar_toda_la_info(juego);
	jugar(&juego, posiciones_iniciales, cantidad_inicial);
	despedida();
	return 0;
}