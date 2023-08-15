//BIBLIOTECAS
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "osos_contra_reloj.h"
#include "utiles.h"
#include "time.h"
//EMOJIS
#define EMOJI_POLAR "\u2744\uFE0F"
#define EMOJI_PARDO "\U0001f43b"
#define EMOJI_PANDA "\U0001f43c"
#define EMOJI_CHLOE "\U0001f469"
#define EMOJI_VELA  "\U0001f56f\uFE0F"
#define EMOJI_PILA "\U0001f50b"
#define EMOJI_BENGALA "\U0001f9e7"
#define EMOJI_PIEDRA "\U0001f311"
#define EMOJI_KOALA "\U0001f428"
#define EMOJI_ARBOL "\U0001f333"
#define EMOJI_CRONOMETRO "\u23F1\uFE0F"
#define EMOJI_BOSQUE "\U0001f3d5\uFE0F"
#define EMOJI_TREBOL "\u2618\uFE0F"
#define EMOJI_CAJA_NEGRA "\U0001f54b"
//PERSONAJES
#define OSO_POLAR 'I'
#define OSO_PARDO 'G'
#define OSO_PANDA 'P'
#define CHLOE 'C'
#define COL_INICIAL_PERSONAJE 0
#define COL_INICIAL_CHLOE 20
#define TIEMPO_INICIAL_PERDIDO_PERSONAJE 0
#define MOVIMIENTO_ARRIBA 'W'
#define MOVIMIENTO_ABAJO 'S'
#define MOVIMIENTO_IZQUIERDA 'A'
#define MOVIMIENTO_DERECHA 'D'
#define MOVIMIENTO_DEFAULT 'D'
//HERRAMIENTAS (MOCHILA Y RECOLECTABLES)
#define CANT_MIN_HERRAMIENTAS 0
#define HERRAMIENTA_LINTERNA 'L'
#define HERRAMIENTA_VELA 'V'
#define HERRAMIENTA_BENGALA 'E'
#define HERRAMIENTA_PILA 'B'
#define ENCENDER_LINTERNA 'L'
#define ENCENDER_VELA 'V'
#define ENCENDER_BENGALA 'E'
#define MAX_CANT_PILAS 30
#define MAX_CANT_VELAS 30
#define MAX_CANT_BENGALAS 10
#define MIN_CANT_MOVIMIENTOS 0
#define MIN_CANTIDAD_ELEMENTOS_MOCHILA 0
#define NO_HAY_ELEMENTOS_EN_USO -1
#define CANT_MOVIMIENTOS_LINTERNA 10
#define CANT_MOVIMIENTOS_VELA 5
#define CANT_MOVIMIENTOS_BENGALA 3
#define CANT_VELAS_MOCHILA 4
#define PLUS_MOVIMIENTOS_LINTERNA_PARDO 5
#define PLUS_CANT_VELAS_POLAR 2
#define PLUS_CANT_BENGALAS_PARDO 2
#define MIN_POS_HERRAMIENTA 0
#define TIEMPO_MOSTRAR_CHLOE_PANDA 30.00
#define MOVIMIENTOS_PILA_RECOLECTABLE 5
#define POS_INICIAL_LINTERNA 0
#define MAX_DISTANCIA_MANHATTAN_VELA 2
#define MAX_DISTANCIA_MANHATTAN_BENGALA 3
#define MIN_CANT_MOVIMIENTOS 0
//BOSQUE
#define MIN_FIL_BOSQUE 0
#define MIN_COL_BOSQUE 0
#define MAX_FIL_BOSQUE 20
#define MAX_COL_BOSQUE 30
#define MAX_NUMERO_ALEATORIO_BOSQUE 2
#define MAX_IMPRESIONES_BORDES 31
#define ESPACIO_VACIO ' '
//OBSTACULOS
#define OBSTACULO_ARBOL 'A'
#define OBSTACULO_PIEDRA 'R'
#define OBSTACULO_KOALA 'K'
#define MAX_CANT_ARBOLES_BOSQUE 350
#define MAX_CANT_PIEDRAS_BOSQUE 80
#define MIN_CANT_OBSTACULOS 0
#define TIEMPO_PERDIDO_PIEDRAS 2.0
#define TIEMPO_PERDIDO_ARBOLES 1.0
//JUEGO
#define TIEMPO_INICIAL 0
#define MOSTRAR_TIEMPO_RESTANTE 'T'
#define ESTADO_JUGANDO 0
#define ESTADO_TERMINADO -1
#define ELEMENTO_MOCHILA 'M'
#define ELEMENTO_MAPA 'X'
//COLORES
#define COLOR_DORADO "\x1b[33m"
#define COLOR_BLANCO "\x1b[37m"
#define COLOR_NEGRO "\x1b[30m"


/*
* Pre: Que el párametro jugada_actual sea una jugada de movimiento válida (W,A,S,D)
* Post: Devolvera true en caso de ser un movimiento válido o false en caso contrario.
*/
bool es_jugada_movimiento_valido(char jugada){
    return (jugada == MOVIMIENTO_ABAJO || jugada == MOVIMIENTO_ARRIBA || jugada == MOVIMIENTO_DERECHA || jugada == MOVIMIENTO_IZQUIERDA);
}
/*
* Pre: Que el párametro jugada sea una jugada de encendido válida (L,V,E).
* Post: Devolvera true en caso de ser una jugada de encendido válida (L,V,E) o false en caso contrario.
*/
bool es_jugada_encendido_valido(char jugada){
    return (jugada == ENCENDER_BENGALA || jugada == ENCENDER_LINTERNA || jugada == ENCENDER_VELA);
}
/*
* Pre:  Que el parámetro bosque venga correctamente inicializado.
* Post: Cargará un elemento del mapa de tipo (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V)) en una posición del bosque.
*/
void cargar_elemento_bosque(elemento_del_mapa_t elemento[], int tope_elementos, char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE]){
    for (int i = 0; i < tope_elementos; i++)
        if (elemento[i].visible) bosque[elemento[i].posicion.fil][elemento[i].posicion.col] = elemento[i].tipo;
}
/*
* Post: Imprimirá por consola el glosario del juego con toda la información del mismo.
*/
void imprimir_glosario_juego(){
    printf(COLOR_DORADO "GLOSARIO:                                                     " COLOR_DORADO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "MOVIMIENTOS: ARRIBA (W) ABAJO (S) DERECHA (D) IZQUIERDA(A)\n\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "ACCIONES:    ENCENDER BENGALA (E) ENCENDER/APAGAR LINTERNA (L)" COLOR_BLANCO "\n");
    printf(COLOR_DORADO COLOR_BLANCO "                   ENCENDER/APAGAR VELA (V) MOSTRAR TIEMPO (T)" COLOR_BLANCO "\n\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "SIMBOLOGÍA:  PARDO %s PANDA %s POLAR %s  CHLOE %s (PERSONAJES)\n", EMOJI_PARDO, EMOJI_PANDA, EMOJI_POLAR, EMOJI_CHLOE);
    printf(COLOR_BLANCO "\t\t   ARBOL %s PIEDRA %s KOALA %s (OBSTACULOS)" COLOR_BLANCO "\n", EMOJI_ARBOL, EMOJI_PIEDRA, EMOJI_KOALA);
    printf(COLOR_BLANCO "\t\t   BENGALA %s PILA %s VELA %s  (HERRAMIENTAS)" COLOR_BLANCO "\n\n", EMOJI_BENGALA, EMOJI_PILA, EMOJI_VELA);
}
/*
* post: Imprimirá por consola los bordes del bosque.
*/
void imprimir_bordes_bosque(int numero){
    for (int i = 0; i < MAX_IMPRESIONES_BORDES; i++){
        if (numero != MAX_NUMERO_ALEATORIO_BOSQUE-1) printf(COLOR_BLANCO " " COLOR_DORADO "╫");
        else printf(COLOR_BLANCO "▀" COLOR_DORADO "╫");
    } printf("\n");
}
/*
* Post: Retornará un valor aleatorio entre los valores que indique el parámetro rango (rango puede ser cualquier valor).
*/
int valor_aleatorio(int rango){
    return (rand() % rango);
}
/*
* Pre: Que el parámetro tipo_herramienta sea válido (Vela (V), Bengala (E), Linterna (L)).
* Post: Agregará una herramienta a la mochila del personaje.
*/
void agregar_elemento_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int * cantidad_elementos, char tipo_herramienta, int movimientos_restantes){
    mochila[(*cantidad_elementos)].tipo = tipo_herramienta;
    mochila[(*cantidad_elementos)].movimientos_restantes = movimientos_restantes;
    (*cantidad_elementos)++;
}
/*
* Pre: Que el párametro personaje venga con todos sus campos correctamente cargados.
* Post: Cargará todos los elementos iniciales en la mochila del personaje (Velas (V), Bengalas (E), Linterna (L)).
*/
void cargar_elementos_iniciales_mochila(personaje_t * personaje){
    int tope_velas_mochila = CANT_VELAS_MOCHILA;
    if (personaje->tipo == OSO_PARDO)
        agregar_elemento_mochila(personaje->mochila, &(personaje->cantidad_elementos), HERRAMIENTA_LINTERNA, (CANT_MOVIMIENTOS_LINTERNA + PLUS_MOVIMIENTOS_LINTERNA_PARDO));
    else
        agregar_elemento_mochila(personaje->mochila, &(personaje->cantidad_elementos), HERRAMIENTA_LINTERNA, CANT_MOVIMIENTOS_LINTERNA);
    if (personaje->tipo == OSO_POLAR) 
        tope_velas_mochila += PLUS_CANT_VELAS_POLAR;
    for (int i = personaje->cantidad_elementos; i < (tope_velas_mochila + 1); i++)
        agregar_elemento_mochila(personaje->mochila, &(personaje->cantidad_elementos), HERRAMIENTA_VELA, CANT_MOVIMIENTOS_VELA);
    if (personaje->tipo == OSO_PANDA){
        for (int j = personaje->cantidad_elementos; j < (tope_velas_mochila + 1 + PLUS_CANT_BENGALAS_PARDO); j++)
            agregar_elemento_mochila(personaje->mochila, &(personaje->cantidad_elementos), HERRAMIENTA_BENGALA, CANT_MOVIMIENTOS_BENGALA);
    }
}
/*
* Pre: Que los parámetros personaje y elemento sean válidos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Retornanara la distancia manhattan entre dos posiciones.
*/
int distancia_manhattan(coordenada_t personaje, coordenada_t elemento){
    return ((abs((personaje.fil - elemento.fil))) + (abs((personaje.col - elemento.col))));
}
/*
* Pre: Que el parámetro tipo_personaje venga cargado con un personaje válido (Polar (I), Pardo (G), Panda (P)).
* Post: Cargará todos los campos del parámetro personaje, dejandolos en un estado válido.
*/
void cargar_datos_iniciales_personaje(personaje_t * personaje, char tipo_personaje){
    personaje->tipo = tipo_personaje;
    personaje->posicion.fil = valor_aleatorio(MAX_FIL_BOSQUE), personaje->posicion.col = COL_INICIAL_PERSONAJE;
    personaje->cantidad_elementos = MIN_CANTIDAD_ELEMENTOS_MOCHILA;
    personaje->elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
    personaje->tiempo_perdido = TIEMPO_INICIAL_PERDIDO_PERSONAJE;
    personaje->ultimo_movimiento = MOVIMIENTO_DEFAULT;
    cargar_elementos_iniciales_mochila(personaje);
}
/*
* Pre: Que los parámetros chloe y personaje sean válidos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Retornará true si la posición de chloe es != de la del personaje o false en caso contrario.
*/
bool es_coordenada_valida_chloe(coordenada_t chloe, coordenada_t personaje){
    return ((chloe.fil != personaje.fil) && (chloe.col != personaje.col));
}
/*
* Pre: Que el parámetro personaje sea válido (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Cargará todos los datos de chloe.
*/
void cargar_datos_chloe(coordenada_t * chloe, coordenada_t personaje, bool * chloe_visible){
    chloe->fil = valor_aleatorio(MAX_FIL_BOSQUE);
    chloe->col = valor_aleatorio(MAX_COL_BOSQUE);
    while (!es_coordenada_valida_chloe((*chloe), personaje)){
        chloe->fil = valor_aleatorio(MAX_FIL_BOSQUE);
        chloe->col = valor_aleatorio(MAX_COL_BOSQUE);
    }
    (*chloe_visible) = false;
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro posicion sea válido (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Retornará true si el parámetro posicion no coincide con la posicion de un (personaje, chloe, o algún elemento previamente cargado) o false en caso contrario.
*/
bool es_posicion_valida_bosque(juego_t juego, coordenada_t posicion){
    int i = 0, j = 0;
    bool es_posicion_valida = true;
    if ((juego.amiga_chloe.fil == posicion.fil) && (juego.amiga_chloe.col == posicion.col)) es_posicion_valida = false;
    else if ((juego.personaje.posicion.fil == posicion.fil) && (juego.personaje.posicion.col == posicion.col)) es_posicion_valida = false;
    while ((i < juego.cantidad_obstaculos) && (es_posicion_valida)){
        if ((juego.obstaculos[i].posicion.fil == posicion.fil) && (juego.obstaculos[i].posicion.col == posicion.col))
            es_posicion_valida = false;
        i++;
    }
    while ((j < juego.cantidad_herramientas) && (es_posicion_valida)){
        if ((juego.herramientas[j].posicion.fil == posicion.fil) && (juego.herramientas[j].posicion.col == posicion.col))
            es_posicion_valida = false;
        j++;
    }
    return es_posicion_valida;
}
/*
* Pre: -> Que el parámetro tipo venga cargado con un (Árbol (A), Piedra (R), Koala (K), Vela (V), Bengala (E), Pila (B)).
*      -> Que el parámetro pos_elemento pertenezca a el vector de structs de obstacúlos o herramientas.
*      -> Que el parámetro elemento sea válido (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Agregará un elemento al vector elemento_mapa con sus respectivos campos cargados.
*/
void agregar_elemento_mapa(char tipo, elemento_del_mapa_t elemento_mapa[], int * tope_elemento, coordenada_t elemento){
    elemento_mapa[(*tope_elemento)].posicion.fil = elemento.fil;
    elemento_mapa[(*tope_elemento)].posicion.col = elemento.col;
    elemento_mapa[(*tope_elemento)].tipo = tipo;
    elemento_mapa[(*tope_elemento)].visible = false;
    (*tope_elemento)++;
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro tipo venga cargado con un elemento del bosque válido (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V)).
* Post: Cargará los datos de un elemento del bosque.
*/
void cargar_datos_elemento_bosque(juego_t * juego, char tipo){
    coordenada_t aleatoria;
    aleatoria.fil = valor_aleatorio(MAX_FIL_BOSQUE);
    aleatoria.col = valor_aleatorio(MAX_COL_BOSQUE);
    while (!es_posicion_valida_bosque(*juego, aleatoria)){
        aleatoria.fil = valor_aleatorio(MAX_FIL_BOSQUE);
        aleatoria.col = valor_aleatorio(MAX_COL_BOSQUE);
    }
    if ((tipo == OBSTACULO_ARBOL) || (tipo == OBSTACULO_PIEDRA) || (tipo == OBSTACULO_KOALA))        
        agregar_elemento_mapa(tipo, juego->obstaculos, &(juego->cantidad_obstaculos), aleatoria);
    else agregar_elemento_mapa(tipo, juego->herramientas, &(juego->cantidad_herramientas), aleatoria);   
}
/*
* Post: Llenará todas las posiciones del bosque con un ESPACIO_VACIO, dejando el bosque correctamente inicializado.
*/
void llenar_bosque(char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE]){
    for (int i = 0; i < MAX_FIL_BOSQUE; i++){
        for (int j = 0; j < MAX_COL_BOSQUE; j++) 
            bosque[i][j] = ESPACIO_VACIO;
    }
}
/*
* Pre: Que el parámetro bosque venga con todos sus elementos cargados (personaje, chloe, herramientas, obstaculos y ESPACIO_VACIO).     
* Post: Imprimirá un elemento del bosque.
*/
void imprimir_elemento_bosque(char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE], int fil, int col, bool visibilidad_chloe){
    if (bosque[fil][col] == OSO_PANDA) printf("%s",EMOJI_PANDA);
    else if (bosque[fil][col] == OSO_PARDO) printf("%s", EMOJI_PARDO);
    else if (bosque[fil][col] == OSO_POLAR) printf("%s ",EMOJI_POLAR);
    else if (bosque[fil][col] == CHLOE && visibilidad_chloe == true) printf("%s",EMOJI_CHLOE);
    else if (bosque[fil][col] == OBSTACULO_PIEDRA) printf("%s",EMOJI_PIEDRA);
    else if (bosque[fil][col] == OBSTACULO_ARBOL) printf("%s",EMOJI_ARBOL);
    else if (bosque[fil][col] == OBSTACULO_KOALA) printf("%s",EMOJI_KOALA);
    else if (bosque[fil][col] == HERRAMIENTA_BENGALA) printf("%s",EMOJI_BENGALA);
    else if (bosque[fil][col] == HERRAMIENTA_VELA) printf("%s ",EMOJI_VELA);
    else if (bosque[fil][col] == HERRAMIENTA_PILA) printf("%s",EMOJI_PILA);
    else printf("%s",EMOJI_CAJA_NEGRA);
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro bosque venga con todos sus elementos cargados (personaje, chloe, herramientas, obstaculos y ESPACIO_VACIO).
* Post: Imprimirá el bosque por consola.
*/
void imprimir_bosque(juego_t juego, char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE]){
    int numero_aleatorio = valor_aleatorio(MAX_NUMERO_ALEATORIO_BOSQUE);
    printf(COLOR_BLANCO" 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
    imprimir_bordes_bosque (numero_aleatorio);
    for (int i = 0; i < MAX_FIL_BOSQUE; i++){
        for (int j = 0; j < MAX_COL_BOSQUE; j++) 
            imprimir_elemento_bosque(bosque, i, j, juego.chloe_visible);
        if (numero_aleatorio != MAX_NUMERO_ALEATORIO_BOSQUE - 1) 
            printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " ");
        else printf(COLOR_BLANCO "■" COLOR_DORADO "╫" COLOR_BLANCO "▀");    
        printf(COLOR_BLANCO"%i" COLOR_BLANCO,i);
        printf("\n");
    }
    imprimir_bordes_bosque(numero_aleatorio);
    printf(COLOR_BLANCO" 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
}
/*
* Pre: -> Que el parámetro movimiento, sea un movimiento válido (W,A,S,D).
*      -> Que el parámetro personaje sea una posición válida, es decir, con fila y columna válida
*         las filas y columnas son válidas sí (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Retornará true si al hacer el movimiento coincide con una posición válida o false en caso contrario.   
*/
bool se_puede_realizar_movimiento(coordenada_t personaje, char movimiento){
    bool es_movimiento_valido = false;
    if ((movimiento == MOVIMIENTO_ARRIBA && personaje.fil > MIN_FIL_BOSQUE) || (movimiento == MOVIMIENTO_ABAJO && personaje.fil < MAX_FIL_BOSQUE - 1))
        es_movimiento_valido = true;
    else if ((movimiento == MOVIMIENTO_IZQUIERDA && personaje.col > MIN_COL_BOSQUE) || (movimiento == MOVIMIENTO_DERECHA && personaje.col < MAX_COL_BOSQUE - 1))
        es_movimiento_valido = true;
    return es_movimiento_valido;
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que la jugada_actual sea una jugada de movimiento válida (W,A,S,D).
* Post: Realizará el movimiento del personaje.
*/
void realizar_movimiento_personaje(juego_t * juego, char jugada_actual){
    if (jugada_actual == MOVIMIENTO_ARRIBA) juego->personaje.posicion.fil--;
    else if (jugada_actual == MOVIMIENTO_ABAJO) juego->personaje.posicion.fil++;
    else if (jugada_actual == MOVIMIENTO_IZQUIERDA) juego->personaje.posicion.col--;
    else if (jugada_actual == MOVIMIENTO_DERECHA) juego->personaje.posicion.col++;
}
/*
* Post: Imprimirá por consola las instrucciones del juego.
*/
void imprimir_instrucciones_juego(){
    printf(COLOR_DORADO "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf(COLOR_DORADO "\t\t\t\t               INSTRUCCIONES                                                 " COLOR_DORADO "\n");
    printf(COLOR_DORADO "" COLOR_DORADO COLOR_BLANCO "El juego consiste en buscar a Chloe %s que se encuentra escondida en la oscuridad del bosque %s\n",EMOJI_CHLOE, EMOJI_BOSQUE);
    printf(COLOR_BLANCO "\t° Se gana: cuando se encuentra a Chloe %s en un tiempo menor o igual a los 120 segundos (2 minutos)%s.\n",EMOJI_CHLOE, EMOJI_CRONOMETRO);
    printf(COLOR_BLANCO "\t° Se pierde: cuando se encuentra a Chloe %s en un tiempo mayor a los 120 segundos (2 minutos)%s.\n",EMOJI_CHLOE, EMOJI_CRONOMETRO);
    printf(COLOR_BLANCO "Mucha suerte %s, ¡confiamos en que lo lograrás!\n",EMOJI_TREBOL);
    printf(COLOR_DORADO "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n" COLOR_DORADO);
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro cantidad_elementos venga cargado con una cantidad > 0.
*      -> Que el parámetro posición a eliminar, coincida con la posición de un elemento de la mochila del personaje o de las herramientas.
*      -> Que el parámetro tipo_elemento sea un elemento válido (M,X).
* Post: Eliminará una herramienta de la mochila (M) del personaje (Bengala (E), Vela (V)) ó en caso contrario del bosque (X) (Pila(B), Bengala (E), Vela (V)).
*/
void eliminar_elemento(juego_t * juego, int * cantidad_elementos, int posicion_a_eliminar, char tipo_elemento){
    for (int i = posicion_a_eliminar; i < (*cantidad_elementos) - 1; i++){
        if (tipo_elemento == ELEMENTO_MOCHILA) juego->personaje.mochila[i] = juego->personaje.mochila[i + 1];
        else juego->herramientas[i] = juego->herramientas[i + 1];
    }
    (*cantidad_elementos)--;
}
/*
* Pre: -> Que el parámetro personaje venga con todos sus campos correctamente cargados.
*      -> Que el parámetro tipo_obstaculo sea de tipo (Árbol (A), Piedra (P)).
* Post: Descontará tiempo al personaje, si se encuentra en la misma posición que un obstacúlo.
*/
void descontar_tiempo_personaje(personaje_t * personaje, char tipo_obstaculo){
    if (personaje->tipo != OSO_PARDO && tipo_obstaculo == OBSTACULO_ARBOL) 
        personaje->tiempo_perdido += TIEMPO_PERDIDO_ARBOLES;
    else if (personaje->tipo == OSO_PARDO && tipo_obstaculo == OBSTACULO_ARBOL) 
        personaje->tiempo_perdido += TIEMPO_PERDIDO_ARBOLES/2;
    else if (personaje->tipo != OSO_POLAR && tipo_obstaculo == OBSTACULO_PIEDRA) 
        personaje->tiempo_perdido += TIEMPO_PERDIDO_PIEDRAS;
}
/*
* Pre: Que el parámetro juego venga con todos sus campos correctamente cargados.
* Post: Cambiará la posición del personaje.
*/
void cambiar_posicion_personaje(juego_t * juego){
    coordenada_t personaje;
    personaje.fil = valor_aleatorio(MAX_FIL_BOSQUE);
    personaje.col = COL_INICIAL_PERSONAJE;
    while (!es_posicion_valida_bosque(*juego, personaje)) personaje.fil = valor_aleatorio(MAX_FIL_BOSQUE);
    juego->personaje.posicion.fil = personaje.fil;
    juego->personaje.posicion.col = COL_INICIAL_PERSONAJE;
}
/*
* Post: Imprimira por consola la cantidad de tiempo en juego.
*/
void mostrar_tiempo(double tiempo_perdido){
    printf("° El tiempo en juego %s: %.2lf segundos\n", EMOJI_CRONOMETRO, tiempo_actual() + tiempo_perdido);
    sleep(1);
}
/*
* Pre: Que el parámetro juego venga con todos sus campos correctamente cargados.
* Post: Verificará si el personaje está en la misma posición que un obstacúlo, y en caso afirmativo, se hará la accion que según correspondan,
*       dependiendo de que tipo de herramienta sea (Vela (V), Árbol (A), Piedra (R)).
*/
void hacer_accion_obstaculo(juego_t * juego){
    int i = 0;
    bool se_encontro_obstaculo = false;
    while ((i < juego->cantidad_obstaculos) && (!se_encontro_obstaculo)){
        if ((juego->personaje.posicion.fil == juego->obstaculos[i].posicion.fil) && (juego->personaje.posicion.col == juego->obstaculos[i].posicion.col)){
            if (juego->obstaculos[i].tipo == OBSTACULO_ARBOL) 
                descontar_tiempo_personaje(&(juego->personaje), OBSTACULO_ARBOL);
            else if (juego->obstaculos[i].tipo == OBSTACULO_PIEDRA) 
                descontar_tiempo_personaje(&(juego->personaje), OBSTACULO_PIEDRA);
            else cambiar_posicion_personaje(juego);
            se_encontro_obstaculo = true;
        }
        i++;
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro posicion_herramienta, pertenezca a la posición de una herramienta en el vector de herramientas del parámetro juego.
* Post: Retornará true si la posición del personaje es la misma que la de una herramienta (Vela (V), Bengala (E), Pila (B)) ó false en caso contrario.
*/
bool se_recolecto_herramienta(juego_t * juego, int * posicion_herramienta){
    bool se_encontro_herramienta = false;
    int i = 0;
    while ((i < juego->cantidad_herramientas) && (!se_encontro_herramienta)){
        if ((juego->personaje.posicion.fil == juego->herramientas[i].posicion.fil) && (juego->personaje.posicion.col == juego->herramientas[i].posicion.col)){
            se_encontro_herramienta = true;
            (*posicion_herramienta) = i;
        }
        i++;
    }
    return se_encontro_herramienta;
}
/*
* Pre: Que el parámetro juego venga con todos sus campos correctamente cargados.
* Post: -> agregará una herramienta del bosque a la mochila del personaje, cuando el personaje pise una herramienta (Vela (V), Pila (B), Bengala (E)).
*       -> se eliminará dicho elemento del bosque, en caso de haber sido agregado a la mochila.
*/
void hacer_accion_herramienta_bosque(juego_t * juego){
    int posicion_herramienta = MIN_POS_HERRAMIENTA;
    if (se_recolecto_herramienta(juego, &posicion_herramienta)){
        if (juego->herramientas[posicion_herramienta].tipo == HERRAMIENTA_PILA)
            juego->personaje.mochila[POS_INICIAL_LINTERNA].movimientos_restantes += MOVIMIENTOS_PILA_RECOLECTABLE;
        else if (juego->herramientas[posicion_herramienta].tipo == HERRAMIENTA_VELA)
            agregar_elemento_mochila(juego->personaje.mochila, &(juego->personaje.cantidad_elementos), HERRAMIENTA_VELA, CANT_MOVIMIENTOS_VELA);
        else if (juego->herramientas[posicion_herramienta].tipo == HERRAMIENTA_BENGALA)
            agregar_elemento_mochila(juego->personaje.mochila, &(juego->personaje.cantidad_elementos), HERRAMIENTA_BENGALA, CANT_MOVIMIENTOS_BENGALA);
        eliminar_elemento(juego, &(juego->cantidad_herramientas), posicion_herramienta, ELEMENTO_MAPA);
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
* Post: En caso de haber un elemento en uso de la mochila, se le descontarán movimientos y se eliminará, si el mismo quedo con movimientos_restantes <= 0.
*/
void hacer_acciones_herramienta_mochila(juego_t * juego){
    if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO){
        if (juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes > MIN_CANT_MOVIMIENTOS)
            juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes--;
        if (juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes <= MIN_CANT_MOVIMIENTOS){
            if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo != HERRAMIENTA_LINTERNA)
                eliminar_elemento(juego, &(juego->personaje.cantidad_elementos), juego->personaje.elemento_en_uso, ELEMENTO_MOCHILA);
            juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
        }
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que la jugada_actual corresponda a una jugada de movimiento válida (W,A,S,D).
* Post: Realizará el turno de movimiento.
*/
void realizar_turno_movimiento(juego_t * juego, char jugada_actual){
    if (se_puede_realizar_movimiento(juego->personaje.posicion, jugada_actual)){
        realizar_movimiento_personaje(juego, jugada_actual);
        hacer_acciones_herramienta_mochila(juego);
        hacer_accion_obstaculo(juego);
        hacer_accion_herramienta_bosque(juego);
        juego->personaje.ultimo_movimiento = jugada_actual;
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada, sea una jugada de encendido válida (L,V,E).
* Post: Buscará un elemento del tipo (Vela (V), Linterna(L), Bengala (E)).
*/
void buscar_elemento_mochila(juego_t * juego, char jugada, int * pos_elemento){
    int i = 0;
    bool se_encontro_elemento = false;
    while(i < juego->personaje.cantidad_elementos && !se_encontro_elemento){
        if (juego->personaje.mochila[i].movimientos_restantes > MIN_CANT_MOVIMIENTOS){
            if (jugada == ENCENDER_LINTERNA && juego->personaje.mochila[i].tipo == HERRAMIENTA_LINTERNA){
                (*pos_elemento) = i;
                se_encontro_elemento = true;
            }else if(jugada == ENCENDER_BENGALA && juego->personaje.mochila[i].tipo == HERRAMIENTA_BENGALA){
                (*pos_elemento) = i;
                se_encontro_elemento = true;
            }else if (jugada ==  ENCENDER_VELA && juego->personaje.mochila[i].tipo == HERRAMIENTA_VELA){
                (*pos_elemento) = i;
                se_encontro_elemento = true;
            }
        }i++;
    }
    if(!se_encontro_elemento) (*pos_elemento) = NO_HAY_ELEMENTOS_EN_USO;
}
/*
* Pre: -> Que los parámetros personaje y elemento sean válidos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
*      -> Que el parámetro ultimo movimiento sea un movimiento válido (W,A,S,D).
* Post: Encenderá la linterna, y dejará visible el elemento (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe (C)).
*       En caso de que dicho elemento, esté dentro del rango de iluminación de la linterna.
*/
void encender_linterna(bool * visibilidad_elemento, coordenada_t elemento, char ultimo_movimiento, coordenada_t personaje){
    if (ultimo_movimiento == MOVIMIENTO_ARRIBA && personaje.fil > elemento.fil && personaje.col == elemento.col)
        (*visibilidad_elemento) = true;
    else if (ultimo_movimiento == MOVIMIENTO_DERECHA && personaje.fil == elemento.fil && personaje.col < elemento.col)
        (*visibilidad_elemento) = true;
    else if (ultimo_movimiento == MOVIMIENTO_IZQUIERDA && personaje.fil == elemento.fil && personaje.col > elemento.col)
        (*visibilidad_elemento) = true;
    else if (ultimo_movimiento == MOVIMIENTO_ABAJO && personaje.fil < elemento.fil && personaje.col == elemento.col)
        (*visibilidad_elemento) = true;
}
/*
* Pre: -> Que los parámetros bengala y elemento sean válidos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Encenderá la linterna, y dejará visible el elemento (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe (C)).
*       En caso de que dicho elemento, esté dentro del rango de iluminación de la bengala.
*/
void encender_bengala(bool * visibilidad_elemento, coordenada_t elemento, coordenada_t bengala){
    if (distancia_manhattan(bengala, elemento) <= MAX_DISTANCIA_MANHATTAN_BENGALA) (*visibilidad_elemento) = true;
}
/*
* Pre: -> Que los parámetros personaje y elemento sean válidos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Encenderá la linterna, y dejará visible el elemento (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe (C)).
*       En caso de que dicho elemento, esté dentro del rango de iluminación de la vela.
*/
void encender_vela(bool * visibilidad_elemento, coordenada_t elemento, coordenada_t personaje){
    if((elemento.fil == personaje.fil-1 || elemento.fil == personaje.fil+1) && elemento.col == personaje.col-1) 
        (*visibilidad_elemento) = true;
    else if((elemento.fil == personaje.fil-1 || elemento.fil == personaje.fil+1) && elemento.col == personaje.col) 
        (*visibilidad_elemento) = true;
    else if((elemento.fil == personaje.fil-1 || elemento.fil == personaje.fil+1) && elemento.col == personaje.col+1) 
        (*visibilidad_elemento) = true;
    else if((elemento.col == personaje.col-1 || elemento.col == personaje.col+1) && elemento.fil == personaje.fil)
        (*visibilidad_elemento) = true;
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada_encendido sea una jugada de encendido válida (L,V,E).
*      -> Que el parámetro bengala sea válido (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
*      -> Que el parámetro pos_elemento, pertenezca a una posición del vector de structs de obstacúlos o herramientas. 
* Post: Encenderá la linterna, y dejará visible el elemento (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V), Chloe (C)).
*       En caso de que dicho elemento, esté dentro del rango de iluminación de la vela.
*/
void iluminar_elemento_mapa(juego_t * juego, char jugada_encendido, bool es_un_obstaculo, coordenada_t bengala, int pos_elemento){
    char ultimo_movimiento = juego->personaje.ultimo_movimiento;
    coordenada_t personaje;
    personaje = juego->personaje.posicion;
    if (jugada_encendido == ENCENDER_LINTERNA){
        if (es_un_obstaculo) 
            encender_linterna(&juego->obstaculos[pos_elemento].visible, juego->obstaculos[pos_elemento].posicion, ultimo_movimiento, personaje);
        else 
            encender_linterna(&juego->herramientas[pos_elemento].visible, juego->herramientas[pos_elemento].posicion, ultimo_movimiento, personaje);
    }else if (jugada_encendido == ENCENDER_VELA){
        if (es_un_obstaculo) 
            encender_vela(&juego->obstaculos[pos_elemento].visible, juego->obstaculos[pos_elemento].posicion, personaje);
        else 
            encender_vela(&juego->herramientas[pos_elemento].visible, juego->herramientas[pos_elemento].posicion, personaje);
    }else if (jugada_encendido == ENCENDER_BENGALA){
         if (es_un_obstaculo) 
            encender_bengala(&juego->obstaculos[pos_elemento].visible, juego->obstaculos[pos_elemento].posicion, bengala);
        else 
            encender_bengala(&juego->herramientas[pos_elemento].visible, juego->herramientas[pos_elemento].posicion, bengala);
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada_encendido sea una jugada de encendido válida (L,V,E).
*      -> Que el parámetro bengala sea una posición válida (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE ) y (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Hará la accion de iluminación que correspenda, según la jugada de encendido.
*/
void iluminar_chloe(juego_t * juego, coordenada_t bengala, char jugada_encendido){
    if (jugada_encendido == ENCENDER_LINTERNA)
        encender_linterna(&juego->chloe_visible, juego->amiga_chloe, juego->personaje.ultimo_movimiento, juego->personaje.posicion);
    else if (jugada_encendido == ENCENDER_VELA)
        encender_vela(&juego->chloe_visible, juego->amiga_chloe, juego->personaje.posicion);
    else if (jugada_encendido == ENCENDER_BENGALA)
        encender_bengala(&juego->chloe_visible, juego->amiga_chloe, bengala);
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que la jugada_encendido sea una jugada de encendido válida (L,V,E).
* Post: Verificará cual (Árbol (A), Piedra (P), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)) está en el rango de iluminación
*       y los dejará en estado visible verdadero, si están dentro de dicho rango (el rango cambia dependiendo de la jugada de encendido).
*/
void hacer_acciones_iluminacion(juego_t * juego, char jugada_encendido){
    bool es_un_obstaculo = true;
    coordenada_t bengala;
    bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE), bengala.col = valor_aleatorio(MAX_COL_BOSQUE);
    if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO){
        for (int i = 0; i < juego->cantidad_obstaculos; i++)
            iluminar_elemento_mapa(juego, jugada_encendido, es_un_obstaculo, bengala, i);
        for (int j = 0; j < juego->cantidad_herramientas; j++)
            iluminar_elemento_mapa(juego, jugada_encendido, !es_un_obstaculo, bengala, j);
        iluminar_chloe(juego, bengala, jugada_encendido);
        if (jugada_encendido == ENCENDER_LINTERNA) 
            cargar_datos_elemento_bosque(juego, OBSTACULO_KOALA);
    } 
}
/*
* Pre: Que el parámetro juego venga con todos sus campos correctamente cargados.
* Post: Pondrá en estado no visible a los elementos del bosque (Chloe (C), Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V)).
*/
void quitar_visibilidad_bosque(juego_t * juego){
    for (int i = 0; i < juego->cantidad_obstaculos; i++) juego->obstaculos[i].visible = false;
    for (int j = 0; j < juego->cantidad_herramientas; j++) juego->herramientas[j].visible = false;
    if (juego->personaje.tipo != OSO_PANDA) juego->chloe_visible = false;
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada_actual sea una jugada válida de encendido (E,V,L). 
* Post: Activará el bloque de acciones del turno de encendido.
*/
void activar_bloque_acciones_encendido(juego_t * juego, char jugada_actual){
    int pos_elemento = NO_HAY_ELEMENTOS_EN_USO;
    buscar_elemento_mochila(juego, jugada_actual, &pos_elemento);
    if (pos_elemento != NO_HAY_ELEMENTOS_EN_USO){
        juego->personaje.elemento_en_uso = pos_elemento; // Lo cambio, si encontre el elemento pedido en la mochila.
        quitar_visibilidad_bosque(juego);
        hacer_acciones_iluminacion(juego, jugada_actual);
        hacer_acciones_herramienta_mochila(juego);
    }
}
/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada_actual sea una jugada válida de encendido (E,V,L). 
* Post: Realizará el turno de encendido.
*/
void realizar_turno_encendido (juego_t * juego, char jugada_actual){
    if (es_jugada_movimiento_valido(jugada_actual)){
        quitar_visibilidad_bosque(juego);
        hacer_acciones_iluminacion(juego, juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);
    }else if(!es_jugada_movimiento_valido(jugada_actual) && jugada_actual != MOSTRAR_TIEMPO_RESTANTE){
        if (juego->personaje.elemento_en_uso == NO_HAY_ELEMENTOS_EN_USO)
            activar_bloque_acciones_encendido(juego, jugada_actual);
        else if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO){
            if (jugada_actual == juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo && jugada_actual != ENCENDER_BENGALA){
                quitar_visibilidad_bosque(juego);
                juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;  
            }else if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo != ENCENDER_BENGALA && jugada_actual != ENCENDER_BENGALA)
                activar_bloque_acciones_encendido(juego, jugada_actual);
            else if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo != ENCENDER_BENGALA && jugada_actual == ENCENDER_BENGALA)
                activar_bloque_acciones_encendido(juego, jugada_actual);
        }
    }
}
void inicializar_juego(juego_t * juego, char tipo_personaje){
    juego->cantidad_obstaculos = 0, juego->cantidad_herramientas = 0;
    cargar_datos_iniciales_personaje (&(juego->personaje), tipo_personaje);
    cargar_datos_chloe(&(juego->amiga_chloe), juego->personaje.posicion, &(juego->chloe_visible));
    cargar_datos_elemento_bosque(juego, OBSTACULO_KOALA);
    for (int i = juego->cantidad_obstaculos; i < (MAX_CANT_ARBOLES_BOSQUE + MAX_CANT_PIEDRAS_BOSQUE + 1); i++){
        if (i < MAX_CANT_ARBOLES_BOSQUE) cargar_datos_elemento_bosque(juego, OBSTACULO_ARBOL);
        else cargar_datos_elemento_bosque(juego, OBSTACULO_PIEDRA);
    }
    for (int j = 0; j < (MAX_CANT_PILAS + MAX_CANT_VELAS + MAX_CANT_BENGALAS); j++){
        if (j < MAX_CANT_BENGALAS) cargar_datos_elemento_bosque(juego, HERRAMIENTA_BENGALA);
        else if ((j >= MAX_CANT_BENGALAS) && (j < MAX_CANT_BENGALAS + MAX_CANT_PILAS)) cargar_datos_elemento_bosque(juego, HERRAMIENTA_PILA);
        else cargar_datos_elemento_bosque(juego, HERRAMIENTA_VELA);
    }
}
void mostrar_juego(juego_t juego){
    char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE];
    llenar_bosque(bosque);
    cargar_elemento_bosque(juego.obstaculos, juego.cantidad_obstaculos, bosque);
    cargar_elemento_bosque(juego.herramientas, juego.cantidad_herramientas, bosque);
    if (juego.chloe_visible) bosque[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
    bosque[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;
    imprimir_instrucciones_juego();
    imprimir_bosque(juego, bosque);
    imprimir_glosario_juego();
}
int estado_juego(juego_t juego){
    int estado = ESTADO_JUGANDO;
    if ((juego.personaje.posicion.fil == juego.amiga_chloe.fil) && (juego.personaje.posicion.col == juego.amiga_chloe.col))
        estado = ESTADO_TERMINADO;
    return estado;
}
bool es_jugada_valida(char jugada_actual){
    return (es_jugada_movimiento_valido(jugada_actual) || es_jugada_encendido_valido(jugada_actual) || jugada_actual == MOSTRAR_TIEMPO_RESTANTE);
}
void realizar_jugada (juego_t * juego, char jugada_actual){
    realizar_turno_movimiento(juego, jugada_actual);
    realizar_turno_encendido (juego, jugada_actual);  
    if ((!juego->chloe_visible) && (juego->personaje.tipo == OSO_PANDA) && ( (juego->personaje.tiempo_perdido + tiempo_actual()) >= TIEMPO_MOSTRAR_CHLOE_PANDA))
        juego->chloe_visible = true;   
    if (jugada_actual == MOSTRAR_TIEMPO_RESTANTE) mostrar_tiempo(juego->personaje.tiempo_perdido);
}