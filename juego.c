#include "osos_contra_reloj.h"
#include "test_de_personalidad.h"
#include "utiles.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define OSO_POLAR 'I'
#define ESTADO_JUGANDO 0
#define ESTADO_TERMINADO -1
#define JUGADA_POR_DEFAULT 'D'
#define COLOR_ROJO   "\x1b[31m"
#define COLOR_DORADO "\x1b[33m"
#define COLOR_BLANCO "\x1b[37m"
#define COLOR_AZUL   "\x1b[34m" 
#define MENSAJE_CARGA_JUEGO "Aguarde c:, Estamos cargando el juego..."
#define MAX_CANTIDAD_PREGUNTAS_TEST 4
#define TIEMPO_MAX_JUEGO 120
#define EMOJI_CRONOMETRO "\u23F1\uFE0F"

/*
* Post: Imprimirá un mensaje de carga del juego.
*/
void imprimir_mensaje_carga_juego (char mensaje[MAX_LETRAS]){
	for (int i = 0; i < MAX_CANTIDAD_PREGUNTAS_TEST; i++){
		printf(COLOR_DORADO" ○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○\n\n");
		printf(COLOR_DORADO"  "COLOR_BLANCO"                  -----> %s %i %% <----- "COLOR_DORADO"                                         ""\n", mensaje, i*MAX_CANTIDAD_PREGUNTAS_TEST*8);
		printf(COLOR_DORADO" ○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○○\n");
        sleep(1);
    }
    system(" clear ");
}
/*
* Post: Imprimirá un mensaje con el resultado del juego.
*/
void mostrar_mensaje_resultado_juego (int estado_juego, char tipo_personaje, double tiempo_jugado){
    system(" clear ");
    printf("Tu tiempo fue : %.2lf segundos %s\n",tiempo_jugado, EMOJI_CRONOMETRO);
    if (estado_juego == ESTADO_TERMINADO && tiempo_jugado > TIEMPO_MAX_JUEGO){
        printf(COLOR_ROJO"¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤""\n"COLOR_BLANCO);
        printf(COLOR_ROJO"¤---------------->"COLOR_ROJO COLOR_BLANCO" LO SIENTO :c PERDISTE NO ENCONTRASTE A CHLOE"COLOR_ROJO" <----------------¤""\n"COLOR_ROJO);
        printf(COLOR_ROJO"¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤""\n"COLOR_BLANCO);
    }else{
        printf(COLOR_DORADO"¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤""\n"COLOR_BLANCO);
        printf(COLOR_DORADO"¤-------------->"COLOR_DORADO COLOR_BLANCO" FELICIDADES GANASTE! ENCONTRASTE A CHLOE c:"COLOR_DORADO" <---------------¤""\n"COLOR_DORADO);
        printf(COLOR_DORADO"¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤""\n"COLOR_BLANCO);
    }
}
/*
* Post: Imprimirá un mensaje por consola preguntandole al usuario la jugada que quiere hacer y almacenará dicha respuesta hasta que sea válida (W,A,S,D,E,L,V ó T).
*/
void preguntar_jugada (char * jugada){
    printf(COLOR_BLANCO"Ingrese una jugada:\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
    scanf(" %c", jugada);
	while (!es_jugada_valida(*jugada)){
		printf(COLOR_ROJO"\nError!"COLOR_BLANCO", La jugada ingresada es inválida :"COLOR_AZUL"'"COLOR_BLANCO"c\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
        scanf(" %c", jugada);
	}
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada venga con una jugada válida (W,S,D,A,L,E,V O T).
* Post: Jugará un turno del juego.
*/
void jugar_turno (juego_t * juego, char * jugada){
    mostrar_juego(*juego);
    preguntar_jugada(jugada);
    realizar_jugada(juego, *jugada);
    system(" clear ");
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada venga con una jugada válida (W,S,D,A,L,E,V O T).
* Post: Pondrá el juego en marcha.
*/
void jugar_juego (juego_t * juego, char * jugada){
    iniciar_cronometro();
    while (estado_juego(*juego) == ESTADO_JUGANDO) 
        jugar_turno(juego, jugada);
    if (estado_juego(*juego) == ESTADO_TERMINADO)  
        juego->personaje.tiempo_perdido += detener_cronometro();
}

int main(){
    char tipo_personaje = OSO_POLAR, jugada = JUGADA_POR_DEFAULT; // Asigno un personaje y jugada por defecto.
    juego_t juego;
    srand ((unsigned)time(NULL));
    test_de_personalidad(&tipo_personaje);
    inicializar_juego(&juego, tipo_personaje);
    imprimir_mensaje_carga_juego(MENSAJE_CARGA_JUEGO);
    jugar_juego(&juego, &jugada);
    mostrar_mensaje_resultado_juego(estado_juego(juego), tipo_personaje, juego.personaje.tiempo_perdido);
    return 0;
}