#ifndef __OSOS_CONTRA_RELOJ_H__
#define __OSOS_CONTRA_RELOJ_H__
#include <stdbool.h>
#define MAX_OBSTACULOS 600
#define MAX_HERRAMIENTAS 600

typedef struct coordenada { 
	int fil;
	int col; 
} coordenada_t;

typedef struct elemento_del_mapa { 
	char tipo;
	coordenada_t posicion; 
	bool visible;
} elemento_del_mapa_t;

typedef struct elemento_mochila {
	char tipo;
	int movimientos_restantes;
} elemento_mochila_t;

typedef struct personaje {
	char tipo;
	coordenada_t posicion; 
	elemento_mochila_t mochila[MAX_HERRAMIENTAS];
	int cantidad_elementos;
	int elemento_en_uso; // -1 si no hay nada en uso, o posicion del vector de lo que esta en uso.
	double tiempo_perdido;
	char ultimo_movimiento;
} personaje_t;

typedef struct juego {
	elemento_del_mapa_t obstaculos[MAX_OBSTACULOS];
	int cantidad_obstaculos;
	elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS];
	int cantidad_herramientas;
	personaje_t personaje;
	coordenada_t amiga_chloe;
	bool chloe_visible;
} juego_t;

/*
 * Inicializará el juego, cargando toda la información inicial
 * y los datos del personaje. 
*/
void inicializar_juego(juego_t * juego, char tipo_personaje);
/*
* Mostrará el juego por pantalla.
* Se recomienda mostrar todo lo que sea de utilidad para el jugador.
*/
void mostrar_juego(juego_t juego);
/*
* Recibe un juego con todas sus estructuras válidas.
* El juego se dará por ganado si el personaje encontró a Chloe dentro del tiempo estipulado.
* El juego se dará por perdido , si el personaje encontró a Chloe en un plazo mayor al limite dado.
* Devolverá:* -> 0 si el estado es jugando.
* -> -1 si el estado es perdido.
* -> 1 si el estado es ganado.
*/
int estado_juego(juego_t juego);
/*
* -> s: Si el personaje debe moverse para la abajo.
* -> d: Si el personaje debe moverse para la derecha.
* -> l: Si el personaje quiere encender una linterna.
* -> v: Si el personaje quiere encender una vela.
* -> b: Si el personaje quiere encender la bengala.
* -> t: Si el personaje quiere ver el tiempo restante.
* En caso de que querer activar una herramienta , y no tenga mas movimientos , no deberá
* activarse ninguna ventaja.
* Si se aprieta una tecla de iluminación y esta ya está siendo usada , se desactivará colocando
* el bool elemento_en_uso en -1.
*/
void realizar_jugada(juego_t * juego , char jugada);
/*
* Devolvera true en caso de ser una jugada valida (W,A,S,D,L,V,E o T)
* Devolvera false en caso contrario.
*/
bool es_jugada_valida (char jugada);

#endif /* __OSOS_CONTRA_RELOJ_H__ */