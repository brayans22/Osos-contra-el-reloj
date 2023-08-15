#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_de_personalidad.h"

#define COLOR_BLANCO "\x1b[37m" 
#define COLOR_ROJO   "\x1b[31m" 
#define COLOR_DORADO "\x1b[33m" 

const char OSO_POLAR = 'I', OSO_PANDA = 'P', OSO_PARDO = 'G';
const char CANAL_TELEVISION_ANIME = 'A', CANAL_TELEVISION_MUSICA_POP = 'M', CANAL_TELEVISION_LIMPIEZA = 'L';
const char VIANDA_PESCADO = 'P', VIANDA_BAMBU = 'B', VIANDA_FOCA = 'F';
const int MULTIPLICADOR_CANAL_LIMPIEZA = 1, MULTIPLICADOR_CANAL_ANIME = 2, MULTIPLICADOR_CANAL_MUSICA_POP = 3;
const int PUNTOS_VIANDA_FOCA = 3, PUNTOS_VIANDA_BAMBU = 6, PUNTOS_VIANDA_PESCADO = 9;
const int PISO_MIN_TORRE = 1, PISO_MAX_TORRE = 18;
const int FUERZA_MIN_GRITO = 1, FUERZA_MAX_GRITO = 18;
const int PUNTOS_MIN_OSO_PANDA = 25, PUNTOS_MAX_OSO_PANDA = 43;
const int PUNTOS_MIN_OSO_PARDO = 44, PUNTOS_MAX_OSO_PARDO = 63;
const int MAX_CANTIDAD_DE_PREGUNTAS = 4;

/*
* Post: Imprimirá un mensaje de bienvenida al test de personalidad por consola.
*/
void imprimir_mensaje_bienvenida(){
	system(" clear ");
	printf(COLOR_DORADO" ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
	printf(COLOR_DORADO" ║               * BIENVENIDO FANÁTICO DE LOS OSOS AL JUEGO DE OSOS CONTRA EL RELOJ *                ║\n");
	printf(COLOR_DORADO" ║" COLOR_BLANCO" A continuación, Se te harán 4 preguntas para determinar que personalidad, de oso escandaloso eres"COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║" COLOR_BLANCO" para poder afrontar,la búsqueda de Chloe que está desaparecida :c                                "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t                                                                                            "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t° Polar (I): Reacción rápida, le encanta la limpieza, sabe yoga                             "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t             artes marciales, patinar, tejer y LE ASUSTAN LOS PEPINOS.                      "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t                                                                                            "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t° Panda (P): Inseguro, sensible, tierno, vegetariano, le gusta el anime                      "COLOR_DORADO"║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t             el celular es su alma rectangular y SE ENAMORA RÁPIDO.                          "COLOR_DORADO"║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t                                                                                            "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t° Pardo (G): Líder, hiperactivo, ruidoso, charlatan, ama el cine, la cultura pop             "COLOR_DORADO"║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t             y HACE TODO LO POSIBLE PARA HACER LO CORRECTO.                                  "COLOR_DORADO"║""\n");
	printf(COLOR_DORADO" ║ "COLOR_BLANCO"\t                                                                                            "COLOR_DORADO" ║""\n");
	printf(COLOR_DORADO" ║"COLOR_BLANCO" Dicho todo eso, empecemos...                                                                      "COLOR_DORADO"║""\n");
	printf(COLOR_DORADO " ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝""\n"COLOR_BLANCO);
}

/*
* Post: -> Devolverá true si el canal de television es (ANIME (A), MUSICA POP (M), LIMPIEZA (L)).
*		-> Devolverá false en caso contrario.
*/
bool es_canal_de_tv_valido(char canal_television){
	return ((canal_television == CANAL_TELEVISION_ANIME) || (canal_television == CANAL_TELEVISION_MUSICA_POP) || (canal_television == CANAL_TELEVISION_LIMPIEZA));
}

/*
* Post: Imprimirá un mensaje por consola preguntando el canal de televisión, 
*       y almacenará dicha respuesta en el parámetro canal_de_televisión 
*		hasta que sea válida (ANIME (A), MUSICA POP (M), LIMPIEZA (L)).
*/
void preguntar_canal_television(char * canal_television){
	printf(COLOR_BLANCO"\n1) Si te dieran a elegir para ver un canal de televisión entre estás opciones:\n");
	printf(COLOR_BLANCO"   ["COLOR_DORADO"Anime-->(A), Musica Pop-->(M), Limpieza-->(L)" COLOR_BLANCO"] ¿Cuál elegirías?\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
	scanf(" %c", canal_television);
	while (!es_canal_de_tv_valido(*canal_television)){
		printf(COLOR_ROJO"   Error!"COLOR_BLANCO", por favor no hagas trampa :"COLOR_DORADO"'"COLOR_BLANCO"c y elige una opción válida\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
		scanf(" %c", canal_television);
	}
}

/*
* Post: -> Devolverá true si la vianda es válida (BAMBU (B), FOCA (F), PESCADO (P)).
*		-> Devolverá false en caso contrario.
*/
bool es_vianda_valida(char vianda){
	return ( (vianda == VIANDA_BAMBU) || (vianda == VIANDA_FOCA) || (vianda == VIANDA_PESCADO) );
}

/*
* Post: Imprimirá un mensaje por consola preguntandole al usuario que vianda quiere, 
*		y almacenará dicha respuesta en el parámetro vianda 
*       hasta que sea válida (BAMBU (B), FOCA (F), PESCADO (P)).
*/
void preguntar_vianda(char * vianda){
	printf(COLOR_BLANCO"\n2) Suponiendo que estás en una isla y solo puedes llevar un alimento como vianda entre estás opciones:\n");
	printf(COLOR_BLANCO"   ["COLOR_DORADO"Bambú-->(B), Pescado-->(P), Focas-->(F)" COLOR_BLANCO"] ¿Cuál elegirías?\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
	scanf(" %c", vianda);
	while (!es_vianda_valida(*vianda)){
		printf(COLOR_ROJO"   Error!"COLOR_BLANCO", por favor no hagas trampa :"COLOR_DORADO"'"COLOR_BLANCO"c y elige una opción válida\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
		scanf(" %c", vianda);
	}
}

/*
* Post: -> Devolverá true si el piso de la torre esta entre estos valores inclusive (1 y 18).
*		-> Devolverá false en caso contrario.
*/
bool es_piso_torre_valido(int piso_torre){
	return ((piso_torre >= PISO_MIN_TORRE) && (piso_torre <= PISO_MAX_TORRE));
}

/*
* Post: Imprimirá un mensaje por consola preguntandole al usuario en que piso de la torre quiere vivir, 
*		y almacenará dicha respuesta en el parámetro piso_torre 
*       hasta que sea válida, es decir, entre (1 y 18) inclusive.
*/
void preguntar_piso_torre (int * piso_torre){
	printf(COLOR_BLANCO"\n3) Suponiendo que te comprás una torre de 18 pisos con tus dos hermanos\n");
	printf(COLOR_BLANCO"   ["COLOR_DORADO"piso más bajo-->(1) , piso más alto-->(18)" COLOR_BLANCO"] ¿En qué piso te gustaría vivir?\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
	scanf("%i", piso_torre);
	while (!es_piso_torre_valido(*piso_torre)){
		printf(COLOR_ROJO"   Error!"COLOR_BLANCO", por favor no hagas trampa :"COLOR_DORADO"'"COLOR_BLANCO"c y elige una opción válida\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
		scanf("%i", piso_torre);
	}
}

/*
* Post: -> Devolverá true si el la fuerza del grito esta entre estos valores inclusive (1 y 18).
*		-> Devolverá false en caso contrario.
*/
bool es_fuerza_grito_valida (int fuerza_grito){
	return ((fuerza_grito >= FUERZA_MIN_GRITO) && (fuerza_grito <= FUERZA_MAX_GRITO));
}

/*
* Post: Imprimirá un mensaje por consola preguntandole al usuario la fuerza del grito, 
*       y almacenará dicha respuesta en el parámetro fuerza_grito 
*       hasta que sea válida, es decir, entre (1 y 18) inclusive.
*/
void preguntar_fuerza_grito (int * fuerza_grito){
	printf(COLOR_BLANCO"\n4) Suponiendo que te encuentras una rata (y no es ratatouille) donde las opciones son:\n");
	printf(COLOR_BLANCO"   ["COLOR_DORADO"no gritar-->(1) , desgarrarse-->(18)" COLOR_BLANCO"] ¿Qué tan fuerte gritarías?\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
	scanf("%i", fuerza_grito);
	while (!es_fuerza_grito_valida(*fuerza_grito)){
		printf(COLOR_ROJO"   Error!"COLOR_BLANCO", por favor no hagas trampa :"COLOR_DORADO"'"COLOR_BLANCO"c y elige una opción válida\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
		scanf("%i", fuerza_grito);
	}
}

/*
* Pre: -> Que el párametro canal_television venga cargado con un canal de television válido (Anime (A), Musica Pop (M), Limpieza (L)).
*      -> Usar constantes para el párametro canal_television.
* Post: Retornará el multiplicador por canal de telvisión que corresponda (Anime (1 punto), Musica Pop (2 puntos), Limpieza (3 puntos)).
*/
int multiplicador_canal_television (char canal_television){
	int multiplicador_canal_television = MULTIPLICADOR_CANAL_LIMPIEZA; // Asigno un valor de multiplicador de canal de televisión por defecto.
	if (canal_television == CANAL_TELEVISION_ANIME)
		multiplicador_canal_television = MULTIPLICADOR_CANAL_ANIME;
	else if (canal_television == CANAL_TELEVISION_MUSICA_POP)
		multiplicador_canal_television = MULTIPLICADOR_CANAL_MUSICA_POP;
	return multiplicador_canal_television;
}

/*
* Pre: -> Que el párametro vianda venga cargado con una vianda válida (Bambu (B), Pescado (P), Focas (F)).
*      -> Usar constantes para el párametro vianda.
* Post: Retornará los puntos por alimento que correspondan (Foca (3 puntos), Bambu (6 puntos),  Pescado (9 puntos)).
*/
int puntos_alimento (char vianda){
	int puntos_alimento = PUNTOS_VIANDA_BAMBU; // Asigno un valor por defecto para los puntos por alimento.
	if (vianda == VIANDA_FOCA) puntos_alimento = PUNTOS_VIANDA_FOCA;
	else if (vianda == VIANDA_PESCADO) puntos_alimento = PUNTOS_VIANDA_PESCADO;
	return puntos_alimento;
}

/*
* Pre: -> Que los párametros vengan correctamente cargados y sean constantes 
*	   -> El párametro canal_television es válido si esta entre estos valores (Anime (A), Musica Pop (M), Limpieza (L))
*	   -> El párametro vianda es válido si está entre estos valores (Bambu (B), Pescado (P), Focas (F))
*	      Los puntos_piso_torre y puntos_fuerza_grito, son válidos si estan entre estos valores inclusive (1 y 18).
* Post: Retornará la cantidad de puntos totales de la personalidad. 
*/
int puntos_totales_personalidad (char canal_television, char vianda, int puntos_piso_torre, int puntos_fuerza_grito){
	return ( (multiplicador_canal_television  (canal_television) * puntos_alimento (vianda) ) + (puntos_piso_torre + puntos_fuerza_grito) );
}

/*
* Pre: Que el párametro venga correctamente cargado y sea constantes.
* Post: Retornará el tipo de personalidad que corresponda según sea el caso.
*/
char tipo_personalidad(int puntos_totales_personalidad){
	char tipo_personalidad = OSO_POLAR; // Asigno un valor por defecto para el tipo de personalidad de oso.
	if (puntos_totales_personalidad >= PUNTOS_MIN_OSO_PARDO && puntos_totales_personalidad <= PUNTOS_MAX_OSO_PARDO)
		tipo_personalidad = OSO_PARDO;
	else if (puntos_totales_personalidad >= PUNTOS_MIN_OSO_PANDA && puntos_totales_personalidad <= PUNTOS_MAX_OSO_PANDA)
		tipo_personalidad = OSO_PANDA;
	return tipo_personalidad;
}

/*
* Post: Imprimirá un mensaje por consola indicando el resultado del test, con su respectivo tipo de oso y los puntos totales obtenidos, según sea el caso.
*/
void imprimir_resultado_test (char tipo_personalidad, int puntos_totales_personalidad){
	system(" clear ");
	printf(COLOR_DORADO" ╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
	printf(COLOR_DORADO" ║                        * FELICIDADES PUDIMOS ENCONTRAR UNA PERSONALIDAD DE OSO ESCANDALOSO QUE COINCIDA CONTIGO Y ES.....               ║ \n");
	if(tipo_personalidad == OSO_POLAR)
		printf(COLOR_DORADO" ║ "COLOR_BLANCO"                ------------------> - Polar (%c) - ❄️  (Te asustan los pepinos) con un total de %i puntos. <-------------------"COLOR_DORADO"           ║""\n",OSO_POLAR, puntos_totales_personalidad);
	else if (tipo_personalidad == OSO_PANDA)
		printf(COLOR_DORADO" ║ "COLOR_BLANCO"               -------------------> - Panda (%c) - 🐼  (Te enamoras rápido) con un total de %i puntos. <-------------------"COLOR_DORADO"              ║""\n",OSO_PANDA, puntos_totales_personalidad);
	else
		printf(COLOR_DORADO" ║ "COLOR_BLANCO"                 ---------> - Pardo (%c) - 🐻  (Haces todo lo posible para hacer lo correcto) con un total de %i puntos. <--------- "COLOR_DORADO"     ║""\n",OSO_PARDO, puntos_totales_personalidad);
	printf(COLOR_DORADO " ╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"COLOR_BLANCO);
	printf(COLOR_DORADO"     ~"COLOR_BLANCO"   Ahora que ya sabes que personalidad de oso escandaloso eres, ¿estás listo para comenzar la aventura de buscar a chloe?....  "COLOR_DORADO" ~       ""\n");
}

/*
* Post: Llamará a las funciones que realizan las preguntas correspondientes del test.
*/
void realizar_preguntas_test (char * canal_television, char * vianda, int * piso_torre, int * fuerza_grito){
	preguntar_canal_television(canal_television);
	preguntar_vianda(vianda);
	preguntar_piso_torre(piso_torre);
	preguntar_fuerza_grito (fuerza_grito);
}

void test_de_personalidad(char * personalidad_detectada){
	char canal_television = CANAL_TELEVISION_LIMPIEZA, alimento_vianda = VIANDA_PESCADO;
	int piso_torre = PISO_MIN_TORRE, fuerza_grito = FUERZA_MIN_GRITO, puntos_personalidad = PUNTOS_MAX_OSO_PANDA;
	imprimir_mensaje_bienvenida();
	realizar_preguntas_test (&canal_television, &alimento_vianda, &piso_torre, &fuerza_grito);
	puntos_personalidad = puntos_totales_personalidad (canal_television, alimento_vianda, piso_torre, fuerza_grito);
	(*personalidad_detectada) = tipo_personalidad  (puntos_personalidad);
	system (" clear ");
	imprimir_resultado_test ((*personalidad_detectada), puntos_personalidad);
}