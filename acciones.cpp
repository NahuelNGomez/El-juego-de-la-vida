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


void inicializar_celulas(juego_t* juego){
	int pos_columna;
	for (int i = 0; i < MAX_CELULAS; i++){
		juego->celulas[i].Estado = MUERTA;
	}
	for(int i = 0; i < MAX_CELULAS; i++){
			juego->celulas[i].posicion.Fila = i/80;
			pos_columna = i;
			while(pos_columna >= 80){
				pos_columna -= 80;
			}
			juego->celulas[i].posicion.Columna = pos_columna;
	}
}



void verificar_cantidad_de_celulas(int* celulas_vivas){

	while(*celulas_vivas < 0 || *celulas_vivas >1600){
		std::cout << "El número ingresado es incorrecto. Por favor escribirlo de nuevo";
		std::cin >> *celulas_vivas;
	}

}

bool verificar_posicion(celula_t celulas[MAX_CELULAS], celula_t celula_actual, int celulas_posicionadas){
	bool posicion_correcta = true;
	if(celula_actual.posicion.Fila > 20 || celula_actual.posicion.Fila < 0 || celula_actual.posicion.Columna < 0 || celula_actual.posicion.Columna > 80){
		std::cout << "Tenga presente que la posicion tiene que estar dentro de los parámetros";
		std::cout << "TOPE FILAS MAXIMAS = 20  - TOPE COLUMNAS MAXIMAS = 80";
		posicion_correcta = false;
	}
	
	
	for(int i = 0; i < MAX_CELULAS; i++){
		if((celula_actual.posicion.Fila == celulas[i].posicion.Fila && celula_actual.posicion.Columna == celulas[i].posicion.Columna) && celulas[i].Estado == VIVA){
			std::cout << "Existe una celula ubicada en esa ubicación. :/";
			posicion_correcta = false;
		}
	}

	return posicion_correcta;

}

void pedir_posicion(celula_t celulas[MAX_CELULAS], int CelulasIniciales, int celulas_posicionadas, posicion_t posiciones_iniciales[MAX_CELULAS]){
		celula_t celula_actual;
	
		std::cout <<"Fila de la celula N°"<< celulas_posicionadas+1 << ":";
		std::cin  >> celula_actual.posicion.Fila;
		std::cout <<"Columna de la celula N°"<< celulas_posicionadas+1 << ":";
		std::cin  >> celula_actual.posicion.Columna;
		(celula_actual.posicion.Fila)--;
		(celula_actual.posicion.Columna)--;
		while(!verificar_posicion(celulas, celula_actual, celulas_posicionadas)){
		std::cout <<"Introduzca otra vez la fila de la celula N°"<< celulas_posicionadas+1 << " :";
		std::cin  >> (celula_actual.posicion.Fila);
		std::cout <<"Introduzca otra vez la Columna de la celula N°"<< celulas_posicionadas+1 << ":";
		std::cin  >> (celula_actual.posicion.Columna);
		(celula_actual.posicion.Fila)--;
		(celula_actual.posicion.Columna)--;
		}
		for(int i = 0; i < MAX_CELULAS; i++){
			if(celula_actual.posicion.Fila == celulas[i].posicion.Fila && celula_actual.posicion.Columna == celulas[i].posicion.Columna){
				celulas[i].Estado = VIVA;
				posiciones_iniciales[celulas_posicionadas].Fila = celula_actual.posicion.Fila;
				posiciones_iniciales[celulas_posicionadas].Columna = celula_actual.posicion.Columna;

			}
		}
	
}

void posicionar_celulas(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS]){
	int celulas_posicionadas = 0;
	inicializar_celulas(juego);
	mostrar_mapa(*juego);
	for(int i = 0; i < juego->celulas_vivas; i++){
		pedir_posicion(juego->celulas, juego->celulas_vivas, celulas_posicionadas, posiciones_iniciales);
		celulas_posicionadas++;
		system("clear");
		mostrar_mapa(*juego);
	}
}

void pedir_datos(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int* cantidad_inicial){
 
	//CUANTAS CELULAS SE INICIAN

	std::cout << "Como observarás, este es nuestro laboratorio. Cada posicion tiene una fila y columna." << std::endl;
	std::cout << "Antes de comenzar a posicionar a nuestras celulas, quiero que me digas cuantas celulas deseas que inicien vivas (entre 1 a 1600)." << std::endl;
	//std::cout << "Ten en cuenta, que a menor cantidad de células, el juego se volverá cada vez mas dificil.";
	std::cout <<"Dime ¿Cuántas celulas quieres colocar?";
	std::cin >> juego->celulas_vivas;
	verificar_cantidad_de_celulas(&(juego->celulas_vivas));
	std::cout << "Muchas gracias, ahora deberá posicionar cada una de esas celulas que eligio ("<< juego->celulas_vivas << ")" << std::endl;
	(*cantidad_inicial) = juego->celulas_vivas;
	//POSICIONAR CADA CELULA
	posicionar_celulas(juego, posiciones_iniciales);
}

void computar_celulas_vecinas(juego_t* juego, int celula_actual){
	juego->celulas[celula_actual].CelulasVecinas = 0;

	for (int i = 0; i < MAX_CELULAS; i++){
		if(juego->celulas[i].Estado == VIVA && (i != celula_actual)){
			if(juego->celulas[i].posicion.Fila == juego->celulas[celula_actual].posicion.Fila){
				if((juego->celulas[i].posicion.Columna)+1 == juego->celulas[celula_actual].posicion.Columna){
					juego->celulas[celula_actual].CelulasVecinas++;
				} else if((juego->celulas[i].posicion.Columna)-1 == juego->celulas[celula_actual].posicion.Columna){
					juego->celulas[celula_actual].CelulasVecinas++;
				} 
			} else if(juego->celulas[i].posicion.Columna == juego->celulas[celula_actual].posicion.Columna){
				if((juego->celulas[i].posicion.Fila)+1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} else if((juego->celulas[i].posicion.Fila)-1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} 
			} else if((juego->celulas[i].posicion.Columna)+1 == juego->celulas[celula_actual].posicion.Columna){
				if((juego->celulas[i].posicion.Fila)+1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} else if((juego->celulas[i].posicion.Fila)-1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} 
			} else if((juego->celulas[i].posicion.Columna)-1 == juego->celulas[celula_actual].posicion.Columna){
				if((juego->celulas[i].posicion.Fila)+1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} else if((juego->celulas[i].posicion.Fila)-1 == juego->celulas[celula_actual].posicion.Fila){
					juego->celulas[celula_actual].CelulasVecinas++;
				} 
			}
		} 
	}
}


void verificar_celula_muerta(juego_t* juego, int celula_actual){
	computar_celulas_vecinas(juego, celula_actual);

	if(juego->celulas[celula_actual].CelulasVecinas == 3){
		juego->celulas[celula_actual].EstadoProximo = VIVA;
	} else {
		juego->celulas[celula_actual].EstadoProximo = MUERTA;
	}
}

void verificar_celula_viva(juego_t* juego, int celula_actual){
	computar_celulas_vecinas(juego, celula_actual);

	if(juego->celulas[celula_actual].CelulasVecinas == 2 || juego->celulas[celula_actual].CelulasVecinas == 3){
		juego->celulas[celula_actual].EstadoProximo = VIVA;
	} else {
		juego->celulas[celula_actual].EstadoProximo = MUERTA;
	}
}


void Jugar_Turno(juego_t* juego){
	for(int i = 0; i < CELULAS_TOTALES; i++){
		if(juego->celulas[i].Estado == MUERTA){
			verificar_celula_muerta(juego, i);
		} else if(juego->celulas[i].Estado == VIVA){
			verificar_celula_viva(juego, i);
		}
		
	}
}
void cambiar_estados(juego_t* juego, int* celulas_nuevas, int* celulas_muertas){
	juego->celulas_vivas = 0;
	for(int i = 0; i < MAX_CELULAS; i++){
		if(juego->celulas[i].EstadoProximo == VIVA && juego->celulas[i].Estado == MUERTA){
			juego->celulas[i].Estado = VIVA;
			juego->celulas_vivas++;
			(*celulas_nuevas)++;
		} else if (juego->celulas[i].EstadoProximo == VIVA){
			juego->celulas[i].Estado = VIVA;
			juego->celulas_vivas++;
		} else if(juego->celulas[i].EstadoProximo == MUERTA && juego->celulas[i].Estado == VIVA){
			juego->celulas[i].Estado = MUERTA;
			(*celulas_muertas)++;
		} else {
			juego->celulas[i].Estado = MUERTA;
		}
	}
}


void verificar_estado(char decision, juego_t* juego){
	if(decision == 'J'){
		juego->EstadoJuego = JUGANDO; 
	} else if((decision) == 'S' || (decision) == 'R'){
		juego->EstadoJuego = TERMINADO;
	} 

}

void mostrar_estadisticas(juego_t juego, int celulas_nuevas, int celulas_muertas, int muertos_por_turnos[MAX_TURNOS], int nacimientos_por_turnos[MAX_TURNOS], int turnos){
	int muertos_totales = 0;
	int nacimientos_totales = 0;
	int promedio_muertos = 0;
	int promedio_nacimientos = 0;
	std::cout << " ■ TURNO N° "<< turnos<< std::endl;
	std::cout << " ■ CANTIDAD DE CELULAS VIVAS = "<< juego.celulas_vivas<< std::endl;
	std::cout << " ■ NUEVAS CELULAS EN ULTIMO TURNO = "<< celulas_nuevas<< std::endl;
	std::cout << " ■ CELULAS MUERTAS EN ULTIMO TURNO = "<< celulas_muertas<< std::endl;

	for(int i = 0; i < turnos; i++){
		muertos_totales += muertos_por_turnos[i];
		nacimientos_totales += nacimientos_por_turnos[i];
	}

	promedio_nacimientos = nacimientos_totales/turnos;
	promedio_muertos = muertos_totales/turnos;

	std::cout << " ■ PROMEDIO DE NUEVAS CELULAS = "<< promedio_nacimientos<< std::endl;
	std::cout << " ■ PROMEDIO DE CELULAS MUERTAS = "<< promedio_muertos<< std::endl;

}

void cargar_muertos_y_nacimientos(int muertos_por_turnos[MAX_TURNOS], int nacimientos_por_turnos[MAX_TURNOS], int turnos, int celulas_muertas, int celulas_nuevas){
	muertos_por_turnos[turnos-1] = celulas_muertas;
	nacimientos_por_turnos[turnos-1] = celulas_nuevas;
}

void verificar_decision(char* decision){
	while((*decision) != 'J' && (*decision) != 'S' && (*decision) != 'R'){
		std::cout << "Por favor, introduzca una letra válida. (SALIR = 'S' / JUGAR PROXIMO TURNO = 'J'/ REINICIAR = 'R')" << std::endl;
		std::cin >> *decision;
	}
}


void inicializar_posiciones(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int cantidad_inicial){
	for(int i = 0; i < cantidad_inicial; i++){
		for(int j = 0; j < MAX_CELULAS; j++){
			if(posiciones_iniciales[i].Fila == juego->celulas[j].posicion.Fila && posiciones_iniciales[i].Columna == juego->celulas[j].posicion.Columna){
				juego->celulas[j].Estado = VIVA;
			}
		} 
	}
}
void resetear_juego(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int cantidad_inicial){
	inicializar_celulas(juego);
	inicializar_posiciones(juego, posiciones_iniciales, cantidad_inicial);
}

void jugar(juego_t* juego, posicion_t posiciones_iniciales[MAX_CELULAS], int cantidad_inicial){		
	char decision = 'R';
	int muertos_por_turnos[MAX_TURNOS];
	int nacimientos_por_turnos[MAX_TURNOS];
	int turnos = 0;
	int celulas_nuevas = 0;
	int celulas_muertas = 0;
	juego->EstadoJuego = JUGANDO;

	while(decision == 'R'){
		juego->EstadoJuego = JUGANDO;
		turnos = 0;
		resetear_juego(juego, posiciones_iniciales, cantidad_inicial);
		while(juego->EstadoJuego == JUGANDO){
			turnos++;
			celulas_nuevas = 0;
			celulas_muertas = 0;
			Jugar_Turno(juego);
			cambiar_estados(juego, &celulas_nuevas, &celulas_muertas);
			cargar_muertos_y_nacimientos(muertos_por_turnos, nacimientos_por_turnos, turnos, celulas_muertas, celulas_nuevas);
			mostrar_mapa(*juego);
			mostrar_estadisticas(*juego, celulas_nuevas, celulas_muertas, muertos_por_turnos, nacimientos_por_turnos, turnos);
			std::cout << "Que desea hacer señor? (SALIR = 'S' / JUGAR PROXIMO TURNO = 'J'/ REINICIAR = 'R')";
			std::cin >> decision;
			verificar_decision(&decision);
			verificar_estado(decision, juego);

		}

	}
}


