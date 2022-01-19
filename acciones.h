#ifndef ACCIONES_H
#define ACCIONES_H

void inicializar_celulas(juego_t* juego);

void pedir_datos(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int* cantidad_inicial);

void jugar(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int cantidad_inicial);

#endif