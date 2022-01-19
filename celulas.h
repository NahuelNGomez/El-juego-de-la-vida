#ifndef celulas_H
#define celulas_H

#define MAX_CELULAS 1600

typedef struct Posicion{
	int Fila;
	int Columna;
} posicion_t;

typedef struct Celulas{
	posicion_t posicion;
	int CelulasVecinas;
	bool Estado;
	bool EstadoProximo;
} celula_t;

typedef struct Juego{
	
	celula_t celulas[MAX_CELULAS];
	int celulas_vivas;
	bool EstadoJuego;

} juego_t;

#endif

