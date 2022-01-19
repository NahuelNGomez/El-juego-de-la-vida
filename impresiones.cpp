#include <iostream>
#include "celulas.h"
#include "acciones.h"
#include "impresiones.h"

#define MAX_FILAS 20
#define MAX_COLUMNAS 80

static const int CELULAS_TOTALES = 1600;
static const int VIVA = 1;
static const int MUERTA = 0;
static const int JUGANDO = 1;
static const int TERMINADO = 0;
static const int MAX_TURNOS = 1000;

void introduccion(){

	std::cout <<"							--------------------------------" << std::endl;
	std::cout <<"							BIENVENIDO A EL JUEGO DE LA VIDA " << std::endl;
	std::cout <<"							--------------------------------" << std::endl;

	std::cout <<"Bienvenido Señor, en este laboratorio se está por crear vida y usted será el responsable de que ocurra!" << std::endl;
	std::cout <<"Comencemos con los experimentos...." << std::endl;
}

void reglas(){
	std::cout << "El juego se basa en....." << std::endl;
}

void inicializar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	for(int i = 0; i < MAX_FILAS; i++){
		for(int j = 0; j < MAX_COLUMNAS; j++){
			terreno[i][j] = '-';

		}
	}

	for (int i = 0; i < CELULAS_TOTALES; i++){
		if(juego.celulas[i].Estado == VIVA){
			terreno[juego.celulas[i].posicion.Fila][juego.celulas[i].posicion.Columna] = 'V';
		}
	}

}

void imprimir_parte_inferior(){
	
	std::cout << "  ╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;

}

void imprimir_parte_superior(){
	for (int j = 0; j < MAX_COLUMNAS; j++){
		if(j == 0){
			std::cout << "  ║ "<< j+1<< " ";
		} else if (j < 9){
			std::cout << "| "<< j+1;
		} else{
			std::cout << "|"<< j+1;
		}
	}



	std::cout << std::endl;
	std::cout << "  ╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
}



void imprimir_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS]){
	
	imprimir_parte_superior();

	for(int i = 0; i < MAX_FILAS; i++){
		if( i < 9){
			std::cout << i+1 << " ║ ";
		} else {
			std::cout << i+1 << "║ ";
		}
		for(int j = 0; j < MAX_COLUMNAS; j++){
			std::cout << terreno[i][j] << "  ";
		}
		std::cout << "║" << std::endl;
	}
	imprimir_parte_inferior();

}


void mostrar_mapa(juego_t juego){
	char terreno[MAX_FILAS][MAX_COLUMNAS];

	inicializar_terreno(terreno, juego);
	imprimir_terreno(terreno); 

	}

void despedida(){
	std::cout << "MUCHAS GRACIAS POR JUGAR A 'EL JUEGO DE LA VIDA'! c: <3";
}

void mostrar_toda_la_info(juego_t juego){
	mostrar_mapa(juego);
	std::cout << " DETALLES DEL JUEGO:" << std::endl;
	std::cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << std::endl; 
	std::cout << " ■ Celulas vivas: " << juego.celulas_vivas << std::endl;
	std::cout << " ■ Celulas muertas:" << CELULAS_TOTALES-(juego.celulas_vivas) << std::endl;
	for(int i = 0; i < MAX_CELULAS; i++){
		if(juego.celulas[i].Estado == VIVA){
			std::cout << "LA CELULA N°:" << i+1 << " Se encuentra en la posicion.... FILA="<< juego.celulas[i].posicion.Fila << " y COLUMNA="<< juego.celulas[i].posicion.Columna;
			std::cout << std::endl;
		}
		
	}
}