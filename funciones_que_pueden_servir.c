/*
* Pre:
* Post:
*/
void iluminar_con_linterna_arriba (juego_t * juego, elemento_del_mapa_t elemento[], int pos_elemento_mapa){   
    if (juego->personaje.posicion.fil > elemento[pos_elemento_mapa].posicion.fil && juego->personaje.posicion.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (juego->personaje.posicion.fil > juego->amiga_chloe.fil && juego->personaje.posicion.col == juego->amiga_chloe.col){
        juego->chloe_visible = true;
    }else if (juego->personaje.mochila[POSICION_INICIAL_LINTERNA].movimientos_restantes <= MIN_CANTIDAD_MOVIMIENTOS && juego->personaje.ultimo_movimiento != MOVIMIENTO_ARRIBA){
        if (juego->personaje.posicion.fil == elemento[pos_elemento_mapa].posicion.fil && juego->personaje.posicion.col < elemento[pos_elemento_mapa].posicion.col){
            elemento[pos_elemento_mapa].visible = false;
        }else if (juego->personaje.posicion.fil == juego->amiga_chloe.fil && juego->personaje.posicion.col > juego->amiga_chloe.col){
            juego->chloe_visible = false;
        }
        printf("Te quedaste sin baterias :c, no puedes usar la linterna\n");
        sleep(5);
        juego->personaje.elemento_en_uso = MIN_CANTIDAD_ELEMENTOS_EN_USO;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_con_linterna_derecha (juego_t * juego, elemento_del_mapa_t elemento[], int pos_elemento_mapa){   
    if (juego->personaje.posicion.fil == elemento[pos_elemento_mapa].posicion.fil && juego->personaje.posicion.col < elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (juego->personaje.posicion.fil == juego->amiga_chloe.fil && juego->personaje.posicion.col < juego->amiga_chloe.col){
        juego->chloe_visible = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_con_linterna_izquierda (juego_t * juego, elemento_del_mapa_t elemento[], int pos_elemento_mapa){   
    if (juego->personaje.posicion.fil == elemento[pos_elemento_mapa].posicion.fil && juego->personaje.posicion.col > elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (juego->personaje.posicion.fil == juego->amiga_chloe.fil && juego->personaje.posicion.col > juego->amiga_chloe.col){
        juego->chloe_visible = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_con_linterna_abajo (juego_t * juego, elemento_del_mapa_t elemento[], int pos_elemento_mapa){   
    if (juego->personaje.posicion.fil < elemento[pos_elemento_mapa].posicion.fil && juego->personaje.posicion.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (juego->personaje.posicion.fil < juego->amiga_chloe.fil && juego->personaje.posicion.col == juego->amiga_chloe.col){
        juego->chloe_visible = true;
    }
}
/*
* Pre:
* Post:
*/
void hacer_acciones_linterna (juego_t * juego, elemento_del_mapa_t elemento[], int pos_elemento_mapa){   
    if (juego->personaje.mochila[POSICION_INICIAL_LINTERNA].movimientos_restantes > MIN_CANTIDAD_MOVIMIENTOS){
        if (juego->personaje.ultimo_movimiento == MOVIMIENTO_ARRIBA){
            iluminar_con_linterna_arriba (juego, elemento, pos_elemento_mapa);
        }else if(juego->personaje.ultimo_movimiento == MOVIMIENTO_DERECHA){
            iluminar_con_linterna_derecha (juego, elemento, pos_elemento_mapa);
        }else if(juego->personaje.ultimo_movimiento == MOVIMIENTO_IZQUIERDA){
            iluminar_con_linterna_izquierda (juego, elemento, pos_elemento_mapa);
        }else if(juego->personaje.ultimo_movimiento == MOVIMIENTO_ABAJO){
            iluminar_con_linterna_abajo (juego, elemento, pos_elemento_mapa);
        }
    }
    cargar_datos_elemento_del_mapa (juego, OBSTACULO_KOALA);
}





if (juego->personaje.ultimo_movimiento == MOVIMIENTO_ARRIBA)
                    iluminar_con_linterna_arriba (juego, juego->herramientas, j);
                else if (juego->personaje.ultimo_movimiento == MOVIMIENTO_ABAJO)
                    iluminar_con_linterna_abajo (juego, juego->herramientas, j);
                else if(juego->personaje.ultimo_movimiento == MOVIMIENTO_IZQUIERDA)
                    iluminar_con_linterna_izquierda (juego, juego->herramientas, j);
                else
                    iluminar_con_linterna_derecha (juego, juego->herramientas, j);
                //hacer_acciones_linterna(juego, juego->herramientas, j);

/*
* Pre:
* Post:
*/
bool es_un_movimiento_valido(coordenada_t personaje, char movimiento){
    bool es_movimiento_valido = false;
    if (movimiento == MOVIMIENTO_ARRIBA){
        if (personaje.fil > MIN_FIL_BOSQUE){
            es_movimiento_valido = true;
        }
    }else if(movimiento == MOVIMIENTO_ABAJO){
        if (personaje.fil < MAX_FIL_BOSQUE-1){
            es_movimiento_valido = true;
        }
    }else if(movimiento == MOVIMIENTO_DERECHA){
        if (personaje.col < MAX_COL_BOSQUE-1){
            es_movimiento_valido = true;
        }
    }else if(movimiento == MOVIMIENTO_IZQUIERDA){
        if (personaje.col > MIN_COL_BOSQUE){
            es_movimiento_valido = true;
        }
    }
    return es_movimiento_valido;
}

/*
* Pre:
* Post:
*/
bool es_valido_el_encendido (personaje_t * personaje, char jugada){
    bool se_puede_encender = false;
    int i = 0;
    while (i < personaje->cantidad_elementos && (!se_puede_encender)){
        if((personaje->mochila[i].tipo == jugada) && (personaje->mochila[i].movimientos_restantes > MIN_CANTIDAD_MOVIMIENTOS)){
            personaje->elemento_en_uso = i;
            se_puede_encender = true;
        }
        i++;
    }
    return se_puede_encender;
}

/*
* Pre:
* Post:
*/
bool es_jugada_valida (char jugada, personaje_t * personaje){
    return (es_un_movimiento_valido(personaje->posicion, jugada) || es_valido_el_encendido(personaje, jugada) || jugada == MOSTRAR_TIEMPO_RESTANTE);
}

/*
* Pre:
* Post:
*/
void preguntar_jugada (char * jugada, personaje_t * personaje){
    printf(COLOR_BLANCO"Ingrese una jugada de las que se indica en el glosario:\n");
	printf(COLOR_DORADO">> "COLOR_BLANCO);
    scanf(" %c", jugada);
	while (!es_una_jugada_valida(*jugada, personaje)){
		printf(COLOR_ROJO"\nError!"COLOR_BLANCO", La jugada ingresada es inválida :"COLOR_AZUL"'"COLOR_BLANCO"c, por favor elige entre las opciones del glosario:\n");
		printf(COLOR_DORADO">> "COLOR_BLANCO);
        scanf(" %c", jugada);
	}
}

/*
* Pre:
* Post:
*/
void encender_vela(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (distancia_manhattan(pos_personaje, elemento[pos_elemento_mapa].posicion) <= MAX_DISTANCIA_MANHATTAN_VELA){
        elemento[pos_elemento_mapa].visible = true;
    }else if (distancia_manhattan(pos_personaje, coordenada_chloe) <= MAX_DISTANCIA_MANHATTAN_VELA && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void encender_bengala(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_random_bengala, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (distancia_manhattan(pos_random_bengala, elemento[pos_elemento_mapa].posicion) <= MAX_DISTANCIA_MANHATTAN_BENGALA){
        elemento[pos_elemento_mapa].visible = true;
    }
    else if (distancia_manhattan(pos_random_bengala, coordenada_chloe) <= MAX_DISTANCIA_MANHATTAN_BENGALA && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_arriba (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool *chloe_visible){
    if (coordenada_personaje.fil > elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }
    else if (coordenada_personaje.fil > coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_derecha (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col < elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }
    else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col < coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_izquierda (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col > elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col > coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_abajo (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil < elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }
    else if (coordenada_personaje.fil < coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void encender_linterna(char ultimo_movimiento, elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (ultimo_movimiento == MOVIMIENTO_ARRIBA){
        iluminar_linterna_arriba (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_DERECHA){
        iluminar_linterna_derecha (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_IZQUIERDA){
        iluminar_linterna_izquierda (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_ABAJO){
        iluminar_linterna_abajo (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }
}
/*
* Pre:
* Post:
*/
void hacer_accion_encendido(juego_t *juego, char jugada, bool es_un_obstaculo, int pos_elemento_mapa, coordenada_t coordenada_bengala){
    if (jugada == ENCENDER_LINTERNA){
        if (es_un_obstaculo)
            encender_linterna(juego->personaje.ultimo_movimiento, juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_linterna(juego->personaje.ultimo_movimiento, juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada == ENCENDER_VELA){
        if (es_un_obstaculo)
            encender_vela(juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_vela(juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada == ENCENDER_BENGALA){
        if (es_un_obstaculo)
            encender_bengala(juego->obstaculos, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_bengala(juego->herramientas, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
    }
}
/*
* Pre:
* Post:
*/
void buscar_elemento_mochila(juego_t * juego, char jugada){
    int i = 0;
    bool se_encontro_elemento = false;
    while(i < juego->personaje.cantidad_elementos && !se_encontro_elemento){
        if (jugada == ENCENDER_LINTERNA && juego->personaje.mochila[i].tipo == HERRAMIENTA_LINTERNA){
            juego->personaje.elemento_en_uso = i;
            se_encontro_elemento = true;
        }else if(jugada == ENCENDER_BENGALA && juego->personaje.mochila[i].tipo == HERRAMIENTA_BENGALA){
            juego->personaje.elemento_en_uso = i;
            se_encontro_elemento = true;
        }else{
            juego->personaje.elemento_en_uso = i;
            se_encontro_elemento = true;
        }
    }
    if (!se_encontro_elemento)
        juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
}
/*
* Pre:
* Post:
*/
void jugar_turno_encendido(juego_t *juego, char jugada){
    int i = 0, j = 0;
    bool es_un_obstaculo = true;

    coordenada_t coordenada_bengala;
    coordenada_bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE);
    coordenada_bengala.col = valor_aleatorio(MAX_COL_BOSQUE);

    if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO){
        while (i < juego->cantidad_obstaculos){
            hacer_accion_encendido(juego, jugada, es_un_obstaculo, i, coordenada_bengala);
            i++;
        }
        while (j < juego->cantidad_herramientas){
            hacer_accion_encendido(juego, jugada, !es_un_obstaculo, j, coordenada_bengala);
            j++;
        }
        juego->personaje.ultimo_movimiento = jugada;
    }else if (juego->personaje.elemento_en_uso == NO_HAY_ELEMENTOS_EN_USO){
        juego->personaje.ultimo_movimiento = NO_HAY_ELEMENTOS_EN_USO;
        
    }
}









/*
*pre: Que número aleatorio sea válido (entre 0 y 1).
*post: Imprimirá por consola los bordes del bosque.
*/
void imprimir_bordes_bosque (int numero_aleatorio){
    if (numero_aleatorio - 1){
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " \n");
    }else{
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀\n");
    }
}

/*
* Pre:
* Post:
*/
void buscar_emoji_bosque(char bosque[MAX_FIL_BOSQUE][MAX_COL_BOSQUE], int fil, int col, bool visibilidad_chloe){
    if (bosque[fil][col] == OSO_PANDA){
        printf("🐼");
    }else if (bosque[fil][col] == OSO_PARDO){
        printf("🐻");
    }else if (bosque[fil][col] == OSO_POLAR){
        printf("❄️ ");
    }else if (bosque[fil][col] == CHLOE && visibilidad_chloe == true){
        printf("👩");
    }else if (bosque[fil][col] == OBSTACULO_PIEDRA){
        printf("🌑");
    }else if (bosque[fil][col] == OBSTACULO_ARBOL){
        printf("🌳");
    }else if (bosque[fil][col] == OBSTACULO_KOALA){
        printf("🐨");
    }else if (bosque[fil][col] == HERRAMIENTA_BENGALA){
        printf("🧨");
    }else if (bosque[fil][col] == HERRAMIENTA_VELA){
        printf("🕯 ");
    }else if (bosque[fil][col] == HERRAMIENTA_PILA){
        printf("🔋");
    }else{
        printf(COLOR_BLANCO " %c", bosque[fil][col]);
    }
}



/*
* Post: Imprimirá el glosario del juego con toda la información del mismo.
*/
void imprimir_glosario_juego(){
    printf(COLOR_DORADO "GLOSARIO:                                                     " COLOR_DORADO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "MOVIMIENTOS: ARRIBA (W), ABAJO (S), DERECHA (D), IZQUIERDA(A).\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "OBSTACULOS:  ARBOL (🌳), PIEDRA (🌑), KOALA (🐨)." COLOR_BLANCO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "PERSONAJES:  PARDO (🐻), PANDA  (🐼), POLAR (❄️ ), CHLOE(👩)." COLOR_BLANCO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "HERRAMIENTAS: BENGALA (🧨), PILA (🔋), VELA (🕯 )." COLOR_BLANCO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "ACCIONES: ENCENDER BENGALA (E), ENCENDER/APAGAR LINTERNA (L), ENCENDER/APAGAR VELA (V)." COLOR_BLANCO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "MOSTRAR: TIEMPO (T) " COLOR_BLANCO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "OBSERVACIONES: - La bengala una vez encendida, no se puede apagar " COLOR_BLANCO "\n");
    printf(COLOR_DORADO COLOR_BLANCO "                     - Puedes encender o apagar una herramienta de la mochila, usando el mismo botón" COLOR_BLANCO "\n\n");
}
/*
* Post: Imprimirá un mensaje por consola con las instrucciones del juego.
*/
void imprimir_instrucciones_juego(){
    printf(COLOR_DORADO "" COLOR_DORADO COLOR_BLANCO "¡HOLA!👋, Bienvenido al juego osos contra el reloj ⏱ \n\n");
    printf(COLOR_DORADO "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf(COLOR_DORADO "\t\t\t\t      INSTRUCCIONES                                                 " COLOR_DORADO "\n");
    printf(COLOR_DORADO "" COLOR_DORADO COLOR_BLANCO "El juego consiste en buscar a Chloe 👩 que se encuentra escondida en la oscuridad del bosque 🏕\n");
    printf(COLOR_BLANCO "\t° Se gana: cuando se encuentra a Chloe 👩 en un tiempo menor o igual a los 120 segundos (2 minutos)⏱️.\n");
    printf(COLOR_BLANCO "\t° Se pierde: cuando se encuentra a Chloe 👩 en un tiempo mayor a los 120 segundos (2 minutos)⏱️.\n\n");
    printf(COLOR_BLANCO "Mucha suerte 🍀, ¡confiamos en que lo lograrás!\n");
    printf(COLOR_DORADO "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n\n" COLOR_DORADO);
}










/*
* Pre:
* Post:
*/
void encender_vela(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (distancia_manhattan(pos_personaje, elemento[pos_elemento_mapa].posicion) <= MAX_DISTANCIA_MANHATTAN_VELA){
        elemento[pos_elemento_mapa].visible = true;
    }else if (distancia_manhattan(pos_personaje, coordenada_chloe) <= MAX_DISTANCIA_MANHATTAN_VELA && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void encender_bengala(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_random_bengala, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (distancia_manhattan(pos_random_bengala, elemento[pos_elemento_mapa].posicion) <= MAX_DISTANCIA_MANHATTAN_BENGALA){
        elemento[pos_elemento_mapa].visible = true;
    }else if (distancia_manhattan(pos_random_bengala, coordenada_chloe) <= MAX_DISTANCIA_MANHATTAN_BENGALA && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_arriba (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil > elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (coordenada_personaje.fil > coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_derecha (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col < elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col < coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_izquierda (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col > elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col > coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_abajo (elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil < elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col){
        elemento[pos_elemento_mapa].visible = true;
    }else if (coordenada_personaje.fil < coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false){
        (*chloe_visible) = true;
    }
}
/*
* Pre:
* Post:
*/
void encender_linterna(char ultimo_movimiento, elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (ultimo_movimiento == MOVIMIENTO_ARRIBA){
        iluminar_linterna_arriba (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_DERECHA){
        iluminar_linterna_derecha (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_IZQUIERDA){
        iluminar_linterna_izquierda (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }else if (ultimo_movimiento == MOVIMIENTO_ABAJO){
        iluminar_linterna_abajo (elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    }
}
/*
* Pre:
* Post:
*/
void hacer_accion_encendido (juego_t * juego, char jugada, bool es_un_obstaculo, int pos_elemento_mapa, coordenada_t coordenada_bengala){
    if (jugada == ENCENDER_LINTERNA){
        if (es_un_obstaculo)
            encender_linterna(juego->personaje.ultimo_movimiento, juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_linterna(juego->personaje.ultimo_movimiento, juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada == ENCENDER_VELA){
        if (es_un_obstaculo)
            encender_vela(juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_vela(juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada == ENCENDER_BENGALA){
        if (es_un_obstaculo)
            encender_bengala(juego->obstaculos, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
        else
            encender_bengala(juego->herramientas, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
    }
}
/*
* Pre:
* Post:
*/
void hacer_acciones_iluminacion (juego_t * juego, char jugada_elemento_en_uso){
    int i = 0, j = 0;
    bool es_un_obstaculo = true;
    coordenada_t coordenada_bengala;
    coordenada_bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE);
    coordenada_bengala.col = valor_aleatorio(MAX_COL_BOSQUE);

    if (juego->personaje.elemento_en_uso != NO_SE_ENCONTRO_ELEMENTO){
        while (i < juego->cantidad_obstaculos){
            hacer_accion_encendido(juego, jugada_elemento_en_uso, es_un_obstaculo, i, coordenada_bengala);
            i++;
        }
        while (j < juego->cantidad_herramientas){
            hacer_accion_encendido(juego, jugada_elemento_en_uso, !es_un_obstaculo, j, coordenada_bengala);
            j++;
        }
    }
}

/*
* Pre:
* Post:
*/
void descontar_tiempo_obstaculo_arbol (personaje_t * personaje){
    if (personaje->tipo != OSO_PARDO){
        personaje->tiempo_perdido += TIEMPO_PERDIDO_ARBOLES;
    }else if (personaje->tipo == OSO_PARDO && tipo_obstaculo == OBSTACULO_ARBOL){
        personaje->tiempo_perdido += TIEMPO_PERDIDO_ARBOLES/2;
    }else if (personaje->tipo != OSO_PARDO && tipo_obstaculo == OBSTACULO_PIEDRA){
        
    }
}
/*
* Pre:
* Post:
*/
void descontar_tiempo_obstaculo_piedra (personaje_t * personaje){
    if (personaje->tipo != OSO_POLAR){
        personaje->tiempo_perdido += TIEMPO_PERDIDO_PIEDRAS;
    }
}








/*
* Pre:
* Post:
*/
void jugar_turno_encendido(juego_t * juego, char jugada_actual){
    char jugada_encendido_elemento_en_uso = NO_HAY_JUGADA_ELEMENTO_USO;
    quitar_visibilidad_elementos_bosque(juego);
    if (jugada_actual == MOVIMIENTO_ABAJO || jugada_actual == MOVIMIENTO_ARRIBA || jugada_actual == MOVIMIENTO_DERECHA || jugada_actual == MOVIMIENTO_IZQUIERDA){
        if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO && juego->personaje.elemento_en_uso != NO_SE_ENCONTRO_ELEMENTO){
            buscar_jugada_encendido_elemento_en_uso(juego, &jugada_encendido_elemento_en_uso);
            hacer_acciones_iluminacion(juego, jugada_encendido_elemento_en_uso);
        }
    }else if(jugada_actual != MOVIMIENTO_ABAJO && jugada_actual != MOVIMIENTO_ARRIBA && jugada_actual != MOVIMIENTO_DERECHA && jugada_actual != MOVIMIENTO_IZQUIERDA){
        if (juego->personaje.elemento_en_uso == NO_HAY_ELEMENTOS_EN_USO){
            buscar_elemento_mochila(juego, jugada_actual);
            if (juego->personaje.elemento_en_uso != NO_SE_ENCONTRO_ELEMENTO){
                hacer_acciones_iluminacion(juego, jugada_actual);
                if (jugada_actual == ENCENDER_LINTERNA)
                    cargar_datos_elemento_mapa(juego, OBSTACULO_KOALA);
            }
        }else if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO && juego->personaje.elemento_en_uso != NO_SE_ENCONTRO_ELEMENTO){
            buscar_jugada_encendido_elemento_en_uso(juego, &jugada_encendido_elemento_en_uso);
            if (jugada_actual != jugada_encendido_elemento_en_uso)
                hacer_acciones_iluminacion(juego, jugada_actual);
            else if (jugada_actual == jugada_encendido_elemento_en_uso && jugada_actual != ENCENDER_BENGALA)
                juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
                    
        }
    }
}










if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO && juego->personaje.elemento_en_uso != NO_SE_ENCONTRO_ELEMENTO){
        hacer_acciones_iluminacion (juego, jugada_encendido_elemento_en_uso);
        /*
        if (jugada_actual == HERRAMIENTA_LINTERNA){
            cargar_datos_elemento_mapa(juego, OBSTACULO_KOALA);
        }
        */
    }
    /*
    else if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO && (jugada_actual == jugada_encendido_elemento_en_uso)){
        if ( (jugada_actual != ENCENDER_BENGALA) || (jugada_actual == ENCENDER_BENGALA && juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes <= MIN_CANT_MOVIMIENTOS)){
            quitar_visibilidad_elementos_bosque (juego);
            juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
        }
    }
    */

    printf("ELEMENTO EN USO: %c\n", juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);
    printf("POS ELEMENTO EN USO: %i\n", juego->personaje.elemento_en_uso);
    printf("CANTIDAD MOVIMIENTOS LINTERNA: %i\n", juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes);
    printf("JUGADA EN USO: %c\n",jugada_encendido_elemento_en_uso);
    //sleep(5);

/*
* Post: Imprimirá por consola el glosario del juego con toda la información del mismo.
*/
void imprimir_glosario_juego(){
    printf(COLOR_DORADO "GLOSARIO:                                                     " COLOR_DORADO "\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "MOVIMIENTOS: ARRIBA (W) ABAJO (S) DERECHA (D) IZQUIERDA(A)\n\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "ACCIONES:    ENCENDER BENGALA (E) ENCENDER/APAGAR LINTERNA (L)" COLOR_BLANCO "\n");
    printf(COLOR_DORADO COLOR_BLANCO "                   ENCENDER/APAGAR VELA (V) MOSTRAR TIEMPO (T)" COLOR_BLANCO "\n\n");
    printf(COLOR_DORADO "----->" COLOR_DORADO COLOR_BLANCO "SIMBOLOGÍA:  PARDO 🐻 PANDA  🐼 POLAR ❄️ CHLOE👩  (PERSONAJES)" COLOR_BLANCO "\n");
    printf(COLOR_BLANCO "\t\t   ARBOL 🌳 PIEDRA 🌑 KOALA 🐨 (OBSTACULOS)" COLOR_BLANCO "\n");
    printf(COLOR_BLANCO "\t\t   BENGALA 🧨 PILA 🔋 VELA 🕯  (HERRAMIENTAS)" COLOR_BLANCO "\n\n");
}



/*
* Pre:
* Post:
*/
void realizar_movimiento_bengalas(juego_t * juego){
    coordenada_t coordenada_bengala;
    for (int i = 0; i < juego->cantidad_herramientas; i++){
        if (juego->herramientas[i].tipo == HERRAMIENTA_BENGALA){
            coordenada_bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE);
            coordenada_bengala.col = valor_aleatorio(MAX_COL_BOSQUE);
            while (!es_posicion_valida (*juego, coordenada_bengala)){
                coordenada_bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE);
                coordenada_bengala.col = valor_aleatorio(MAX_COL_BOSQUE);
            }
            juego->herramientas[i].posicion.fil = coordenada_bengala.fil;
            juego->herramientas[i].posicion.col = coordenada_bengala.col;
        }
    }
}

/*
* Pre: 
* Post:
*/
void encender_vela(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if(elemento[pos_elemento_mapa].posicion.fil == pos_personaje.fil-1 || elemento[pos_elemento_mapa].posicion.fil == pos_personaje.fil+1){
        if (elemento[pos_elemento_mapa].posicion.col == pos_personaje.col-1) 
            elemento[pos_elemento_mapa].visible = true;
        else if (elemento[pos_elemento_mapa].posicion.col == pos_personaje.col) 
            elemento[pos_elemento_mapa].visible = true;
        else if (elemento[pos_elemento_mapa].posicion.col == pos_personaje.col+1) 
            elemento[pos_elemento_mapa].visible = true;
    }else if(elemento[pos_elemento_mapa].posicion.fil == pos_personaje.fil){
        if (elemento[pos_elemento_mapa].posicion.col == pos_personaje.col-1 || elemento[pos_elemento_mapa].posicion.col == pos_personaje.col+1)
            elemento[pos_elemento_mapa].visible = true;
    }
}

/*
* Pre:
* Post:
*/
void encender_bengala(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t pos_random_bengala, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (distancia_manhattan(pos_random_bengala, elemento[pos_elemento_mapa].posicion) <= MAX_DISTANCIA_MANHATTAN_BENGALA)
        elemento[pos_elemento_mapa].visible = true;
    else if (distancia_manhattan(pos_random_bengala, coordenada_chloe) <= MAX_DISTANCIA_MANHATTAN_BENGALA && (*chloe_visible) == false)
        (*chloe_visible) = true;
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_arriba(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil > elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col)
        elemento[pos_elemento_mapa].visible = true;
    else if (coordenada_personaje.fil > coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_derecha(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col < elemento[pos_elemento_mapa].posicion.col)
        elemento[pos_elemento_mapa].visible = true;
    else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col < coordenada_chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_izquierda(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil == elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col > elemento[pos_elemento_mapa].posicion.col)
        elemento[pos_elemento_mapa].visible = true;
    else if (coordenada_personaje.fil == coordenada_chloe.fil && coordenada_personaje.col > coordenada_chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}
/*
* Pre:
* Post:
*/
void iluminar_linterna_abajo(elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (coordenada_personaje.fil < elemento[pos_elemento_mapa].posicion.fil && coordenada_personaje.col == elemento[pos_elemento_mapa].posicion.col)
        elemento[pos_elemento_mapa].visible = true;
    else if (coordenada_personaje.fil < coordenada_chloe.fil && coordenada_personaje.col == coordenada_chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}
/*
* Pre:
* Post:
*/
void encender_linterna (char ultimo_movimiento, elemento_del_mapa_t elemento[], int pos_elemento_mapa, coordenada_t coordenada_personaje, coordenada_t coordenada_chloe, bool * chloe_visible){
    if (ultimo_movimiento == MOVIMIENTO_ARRIBA) 
        iluminar_linterna_arriba(elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_DERECHA) 
        iluminar_linterna_derecha(elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_IZQUIERDA) 
        iluminar_linterna_izquierda(elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_ABAJO) 
        iluminar_linterna_abajo(elemento, pos_elemento_mapa, coordenada_personaje, coordenada_chloe, chloe_visible);
}
/*
* Pre:
* Post:
*/
void hacer_accion_encendido (juego_t * juego, char jugada_actual, bool es_un_obstaculo, int pos_elemento_mapa, coordenada_t coordenada_bengala){
    if (jugada_actual == ENCENDER_LINTERNA){
        if (es_un_obstaculo)
            encender_linterna(juego->personaje.ultimo_movimiento, juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else encender_linterna(juego->personaje.ultimo_movimiento, juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada_actual == ENCENDER_VELA){
        if (es_un_obstaculo)
            encender_vela(juego->obstaculos, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else encender_vela(juego->herramientas, pos_elemento_mapa, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada_actual == ENCENDER_BENGALA){
        if (es_un_obstaculo)
            encender_bengala(juego->obstaculos, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
        else encender_bengala(juego->herramientas, pos_elemento_mapa, coordenada_bengala, juego->amiga_chloe, &juego->chloe_visible);
    }
}
/*
* Pre:
* Post:
*/
void hacer_accion_iluminacion (juego_t * juego, char jugada_encendido_elemento_en_uso){
    int i = 0, j = 0;
    bool es_un_obstaculo = true;
    coordenada_t coordenada_bengala;
    coordenada_bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE), coordenada_bengala.col = valor_aleatorio(MAX_COL_BOSQUE);
    while (i < juego->cantidad_obstaculos){
        hacer_accion_encendido(juego, jugada_encendido_elemento_en_uso, es_un_obstaculo, i, coordenada_bengala);
        i++;
    }
    while (j < juego->cantidad_herramientas){
        hacer_accion_encendido(juego, jugada_encendido_elemento_en_uso, !es_un_obstaculo, j, coordenada_bengala);
        j++;
    }
}

//POR SI NO SIRVE LO QUE VOY APROBAR 
/*
* Pre: -> Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*         las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*         las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la vela, y lo dejará en estado visible verdadero.
*/
void encender_vela(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if(elemento[pos_elemento].posicion.fil == personaje.fil-1 || elemento[pos_elemento].posicion.fil == personaje.fil+1){
        if (elemento[pos_elemento].posicion.col == personaje.col-1) 
            elemento[pos_elemento].visible = true;
        else if (elemento[pos_elemento].posicion.col == personaje.col) 
            elemento[pos_elemento].visible = true;
        else if (elemento[pos_elemento].posicion.col == personaje.col+1) 
            elemento[pos_elemento].visible = true;
    }else if(elemento[pos_elemento].posicion.fil == personaje.fil || chloe.fil == personaje.fil){
        if (elemento[pos_elemento].posicion.col == personaje.col-1 || elemento[pos_elemento].posicion.col == personaje.col+1)
            elemento[pos_elemento].visible = true;
        else if ((chloe.col == personaje.col-1 || chloe.col == personaje.col+1) && (*chloe_visible) == false)
            (*chloe_visible) = true;
    }
    if((chloe.fil == personaje.fil-1 || chloe.fil == personaje.fil+1) && (*chloe_visible) == false){
        if (chloe.col == personaje.col-1) (*chloe_visible) = true;
        else if (chloe.col == personaje.col) (*chloe_visible) = true;
        else if (chloe.col == personaje.col+1) (*chloe_visible) = true;
    }
}

/*
* Pre: -> Que el parámetro bengala y chloe sean una posición válida, es decir, con filas y columnas válidas
*         las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*         las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la bengala, y lo dejará en estado visible verdadero.
*/
void encender_bengala(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t bengala, coordenada_t chloe, bool * chloe_visible){
    if (distancia_manhattan(bengala, elemento[pos_elemento].posicion) <= MAX_DISTANCIA_MANHATTAN_BENGALA)
        elemento[pos_elemento].visible = true;
    if (distancia_manhattan(bengala, chloe) <= MAX_DISTANCIA_MANHATTAN_BENGALA && (*chloe_visible) == false)
        (*chloe_visible) = true;
}

/*
* Pre: Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*      las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*      las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la linterna, y lo dejará en estado visible verdadero.
*/
void iluminar_arriba_linterna(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if (personaje.fil > elemento[pos_elemento].posicion.fil && personaje.col == elemento[pos_elemento].posicion.col)
        elemento[pos_elemento].visible = true;
    if (personaje.fil > chloe.fil && personaje.col == chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}

/*
* Pre: Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*      las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*      las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la linterna, y lo dejará en estado visible verdadero.
*/
void iluminar_derecha_linterna(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if (personaje.fil == elemento[pos_elemento].posicion.fil && personaje.col < elemento[pos_elemento].posicion.col)
        elemento[pos_elemento].visible = true;
    if (personaje.fil == chloe.fil && personaje.col < chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}

/*
* Pre: Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*      las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*      las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la linterna, y lo dejará en estado visible verdadero.
*/
void iluminar_izquierda_linterna(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if (personaje.fil == elemento[pos_elemento].posicion.fil && personaje.col > elemento[pos_elemento].posicion.col)
        elemento[pos_elemento].visible = true;
    if (personaje.fil == chloe.fil && personaje.col > chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}

/*
* Pre: Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*      las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*      las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la linterna, y lo dejará en estado visible verdadero.
*/
void iluminar_abajo_linterna(elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if (personaje.fil < elemento[pos_elemento].posicion.fil && personaje.col == elemento[pos_elemento].posicion.col)
        elemento[pos_elemento].visible = true;
    if (personaje.fil < chloe.fil && personaje.col == chloe.col && (*chloe_visible) == false)
        (*chloe_visible) = true;
}

/*
* Pre: -> Que el parámetro personaje y chloe sean una posición válida, es decir, con filas y columnas válidas
*         las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE )
*         las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
*      -> Que el parámetro ultimo_movimiento sea un movimiento válido (W,A,S,D).
* Post: Verificará cual (Árbol (A), Piedra (R), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación de la linterna, y lo dejará en estado visible verdadero.
*/
void encender_linterna (char ultimo_movimiento, elemento_del_mapa_t elemento[], int pos_elemento, coordenada_t personaje, coordenada_t chloe, bool * chloe_visible){
    if (ultimo_movimiento == MOVIMIENTO_ARRIBA) 
        iluminar_arriba_linterna(elemento, pos_elemento, personaje, chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_DERECHA) 
        iluminar_derecha_linterna(elemento, pos_elemento, personaje, chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_IZQUIERDA) 
        iluminar_izquierda_linterna(elemento, pos_elemento, personaje, chloe, chloe_visible);
    else if (ultimo_movimiento == MOVIMIENTO_ABAJO) 
        iluminar_abajo_linterna(elemento, pos_elemento, personaje, chloe, chloe_visible);
}

/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que el parámetro jugada_actual sea una jugada de encendido válido (L,V,E).
*      -> Que el parámetro bengala sea una posición válida, es decir, con fila y columna válida
*         las filas son válidas entre estos rangos (fil >= MIN_FIL_BOSQUE Y fil < MAX_FIL_BOSQUE)
*         las columnas son válidas entre estos rangos (col >= MIN_COL_BOSQUE Y col <  MAX_COL_BOSQUE).
* Post: Encenderá una herramienta de la mochila del personaje, según sea el valor del parámetro jugada_actual (L,V,E).
*/
void hacer_accion_encendido (juego_t * juego, char jugada_actual, bool es_un_obstaculo, int pos_elemento, coordenada_t bengala){
    if (jugada_actual == ENCENDER_LINTERNA){
        if (es_un_obstaculo)
            encender_linterna(juego->personaje.ultimo_movimiento, juego->obstaculos, pos_elemento, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else encender_linterna(juego->personaje.ultimo_movimiento, juego->herramientas, pos_elemento, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada_actual == ENCENDER_VELA){
        if (es_un_obstaculo)
            encender_vela(juego->obstaculos, pos_elemento, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
        else encender_vela(juego->herramientas, pos_elemento, juego->personaje.posicion, juego->amiga_chloe, &juego->chloe_visible);
    }else if (jugada_actual == ENCENDER_BENGALA){
        if (es_un_obstaculo)
            encender_bengala(juego->obstaculos, pos_elemento, bengala, juego->amiga_chloe, &juego->chloe_visible);
        else encender_bengala(juego->herramientas, pos_elemento, bengala, juego->amiga_chloe, &juego->chloe_visible);
    }
}

/*
* Pre: -> Que el parámetro juego venga con todos sus campos correctamente cargados.
*      -> Que la jugada_encendido sea una jugada de iluminación válida (L,V,E).
* Post: Verificará cual (Árbol (A), Piedra (P), Koala (K), Pila (B), Bengala (E), Vela (V) ó Chloe(C)).
*       está en el rango de iluminación según sea el tipo de jugada de iluminación
*       y los dejará en estado visible verdadero, si están dentro de dicho rango.
*       
*/
void hacer_acciones_iluminacion(juego_t * juego, char jugada_encendido){
    int i = 0, j = 0;
    bool es_un_obstaculo = true;
    coordenada_t bengala;
    bengala.fil = valor_aleatorio(MAX_FIL_BOSQUE), bengala.col = valor_aleatorio(MAX_COL_BOSQUE);
    if (juego->personaje.elemento_en_uso != NO_HAY_ELEMENTOS_EN_USO){
        //Obstaculos y herramientas
        while (i < juego->cantidad_obstaculos){
            hacer_accion_encendido(juego, jugada_encendido, es_un_obstaculo, i, bengala);
            i++;
        }
        while (j < juego->cantidad_herramientas){
            hacer_accion_encendido(juego, jugada_encendido, !es_un_obstaculo, j, bengala);
            j++;
        }
        if (jugada_encendido == ENCENDER_LINTERNA) 
            cargar_datos_elemento_bosque(juego, OBSTACULO_KOALA);
    } 
}

void imprimir_bordes_bosque(int numero_aleatorio){
    if (numero_aleatorio != MAX_NUMERO_ALEATORIO_BOSQUE-1){
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫" COLOR_NEGRO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫");
        printf(COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " " COLOR_DORADO "╫" COLOR_BLANCO " \n");
    }else{
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫");
        printf(COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀" COLOR_DORADO "╫" COLOR_BLANCO "▀\n");
    }
}

bool esta_en_la_mochila(int movimientos_restantes, char tipo_herramienta, char jugada){
    return (movimientos_restantes > MIN_CANT_MOVIMIENTOS && tipo_herramienta == jugada);
}

void buscar_elemento_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int tope_mochila, char jugada, int elemento_en_uso){
    int i = 0;
    bool se_encontro_elemento = false;
    while(i < tope_mochila && !se_encontro_elemento){
        if(esta_en_la_mochila(mochila[i].movimientos_restantes, mochila[i].tipo, jugada)){
            se_encontro_elemento = true;
            elemento_en_uso = i;
        }i++;
    }
    if (!se_encontro_elemento) juego->personaje.elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
}


/*
* Pre: -> Que el parámetro tope_mochila > 0.
*      -> Que la jugada_actual corresponda a una jugada válida (E,V,L).
* Post: Buscará un elemento en la mochila del personaje.
*/
void buscar_elemento_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int tope_mochila, char jugada, int elemento_en_uso){
    int i = 0;
    bool se_encontro_elemento = false;
    while(i < tope_mochila && !se_encontro_elemento){
        if(esta_en_la_mochila(mochila[i].movimientos_restantes, mochila[i].tipo, jugada)){
            se_encontro_elemento = true;
            elemento_en_uso = i;
        }i++;
    }
    if (!se_encontro_elemento) elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
}

/*
* Pre: -> Que el parámetro tope_mochila > 0.
*      -> Que la jugada_actual corresponda a una jugada válida (E,V,L).
* Post: Buscará un elemento en la mochila del personaje.
*/
void buscar_elemento_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int tope_mochila, char jugada, int elemento_en_uso){
    int i = 0;
    bool se_encontro_elemento = false;
    while(i < tope_mochila && !se_encontro_elemento){
        if(esta_en_la_mochila(mochila[i].movimientos_restantes, mochila[i].tipo, jugada)){
            se_encontro_elemento = true;
            elemento_en_uso = i;
        }i++;
    }
    if (!se_encontro_elemento) elemento_en_uso = NO_HAY_ELEMENTOS_EN_USO;
}