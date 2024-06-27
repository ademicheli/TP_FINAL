// #include "src/abb_estructura_privada.h"
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>
#include <stdio.h>
// #include "src/abb.c"
// #include "src/utils.c"
// #include "src/lista.c"
#include <ctype.h>
// #define CANTIDAD_OBSTACULOS_MODO_FACIL 3
// #define CANTIDAD_OBSTACULOS_MODO_NORMAL 6
// #define CANTIDAD_OBSTACULOS_MODO_DIFICIL 9
// #define CANTIDAD_OBSTACULOS_MODO_IMPOSIBLE 12
// #define CAMPOS_ARCHIVO_VALIDO 4
// #define NOMBRE_POKEMON 1
// #define FUERZA_POKEMON 2
// #define	DESTREZA_POKEMON 3
// #define INTELIGENCIA_POKEMON 4
// #define LINEA_SIZE 256
// #include <stdbool.h>

// #define IDENTIFICADOR_OBSTACULO_FUERZA 'F'
// #define IDENTIFICADOR_OBSTACULO_DESTREZA 'D'
// #define IDENTIFICADOR_OBSTACULO_INTELIGENCIA 'I'

// enum TP_JUGADOR { JUGADOR_1, JUGADOR_2 };

// enum TP_OBSTACULO {
// 	OBSTACULO_FUERZA,
// 	OBSTACULO_DESTREZA,
// 	OBSTACULO_INTELIGENCIA
// };

// typedef struct tp TP;
// struct pokemon_info {
// 	char *nombre;
// 	int fuerza, destreza, inteligencia;
// };
// typedef struct obstaculo {
// 	char tipo;
// }obstaculo_t;
// typedef struct menu {

// 	int cantidad_partidas_jugadas;
// 	int *opciones;
// 	char *historial;
// 	int *estadisticas;
	
// }menu_t;



// typedef struct jugador {
// 	lista_t *pista;
// 	const struct pokemon_info *pokemon_seleccionado;
// }jugador_t;

// struct tp {
// 	abb_t	*pokemones_disponibles;
// 	jugador_t *jugador_1;
// 	jugador_t *jugador_2;
// };



// jugador_t* crear_jugador() {
//     jugador_t* jugador = calloc(1, sizeof(jugador_t));
//     if (!jugador) {
//         printf("Error: No se pudo asignar memoria para el jugador.\n");
//         return NULL;
//     }
// 	jugador->pista = lista_crear();

//     if (!jugador->pista) {
//         printf("Error: No se pudo asignar memoria para la pista del jugador.\n");
//         free(jugador);
//         return NULL;
//     }

//     return jugador;
// }

// void imprimir_pokemon(void *dato) {
//     struct pokemon_info *pokemon = (struct pokemon_info *)dato;
//     printf("Nombre: %s, Fuerza: %d, Destreza: %d, Inteligencia: %d\n", pokemon->nombre, pokemon->fuerza, pokemon->destreza, pokemon->inteligencia);
// }

// void imprimir_abb_recursivo(struct nodo_abb *nodo, void (*imprimir)(void *)) {
//     if (nodo == NULL) {
//         return;
//     }

//     imprimir_abb_recursivo(nodo->izquierda, imprimir);
//     imprimir_pokemon(nodo->elemento);
//     imprimir_abb_recursivo(nodo->derecha, imprimir);
// }


// void imprimir_abb(abb_t *abb) {
//     if (abb == NULL) {
//         printf("El árbol está vacío.\n");
//         return;
//     }

//     printf("Pokémon en el árbol:\n");
//     imprimir_abb_recursivo(abb->nodo_raiz, imprimir_pokemon);
// }
// struct pokemon_info *crear_pokemon(char *campo)
// {
// 	struct pokemon_info *pokemon = malloc(sizeof(struct pokemon_info));			
// 	if(!pokemon)
// 		return NULL;
//     pokemon->nombre = malloc(sizeof(char) * strlen(campo)+1);
//     if(!pokemon->nombre){
//             free(pokemon);
//             return NULL;
//     }
            
// 	return pokemon;
// }
// struct pokemon_info *completar_pokemon(struct pokemon_info *pokemon, char * campo, int indice)
// {
// 		switch (indice)
// 			{
// 			case 1:
//                 if(pokemon->nombre)
//                     strcpy(pokemon->nombre,campo);
// 				break;
// 			case 2:
// 				pokemon->fuerza = atoi(campo);
// 				break;

// 			case 3:
// 				pokemon->destreza = atoi(campo);
// 				break;
// 			case 4:
// 				pokemon->inteligencia = atoi(campo);
// 				break;
// 			default:
// 				break;
// 			}
// 		return pokemon;
// }


// int comparador_pokemon(void *pokemon1, void *pokemon2) {
//     struct pokemon_info *p1 = (struct pokemon_info *)pokemon1;
//     struct pokemon_info *p2 = (struct pokemon_info *)pokemon2;
// 	char nombre_minusculas_1[strlen(p1->nombre) + 1];
//     strcpy(nombre_minusculas_1, p1->nombre);
// 	char nombre_minusculas_2[strlen(p2->nombre) + 1];
//     strcpy(nombre_minusculas_2, p2->nombre);
//     str_tolower(nombre_minusculas_1);
//     str_tolower(nombre_minusculas_2);

//     return strcmp(nombre_minusculas_1,nombre_minusculas_2);
// }
// abb_t *mapear_pokemones(const char *archivo, abb_t *abb_pokemones)
// {
// 	if(!archivo || !abb_pokemones)
// 		return NULL;

// 	FILE *archivo_con_pokemones = fopen(archivo, "r");;
// 	char linea[256];
// 	while (fgets(linea,sizeof(linea),archivo_con_pokemones))
// 	{
// 		char *campo;
// 		int indice_campos = 0;
// 		campo = strtok(linea,",");
// 		struct pokemon_info *pokemon = crear_pokemon(campo);
// 		while (campo)
// 		{	
// 			indice_campos++;
// 			completar_pokemon(pokemon,campo,indice_campos);
// 			campo = strtok(NULL,",");
// 		}
// 		abb_insertar(abb_pokemones,pokemon);
		
// 	}
// 	fclose(archivo_con_pokemones);
// 	return abb_pokemones;
// }

// void destruir_pokemon(void *elemento)
// {
//     if (!elemento)
//         return;
    
//     struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
//     free(pokemon->nombre); 
//     free(pokemon);   
// }
// TP *tp_crear(const char *nombre_archivo) {
//     if (!nombre_archivo || !contiene_formato_correcto(nombre_archivo)) {
//         printf("Error: Nombre de archivo inválido o formato incorrecto.\n");
//         return NULL;
//     }

//     TP *juego = calloc(1, sizeof(TP));
//     if (!juego) {
//         printf("Error: No se pudo asignar memoria para el juego.\n");
//         return NULL;
//     }

//     juego->pokemones_disponibles = abb_crear(comparador_pokemon);
//     if (!juego->pokemones_disponibles) {
//         printf("Error: No se pudo crear el ABB de pokemones.\n");
//         free(juego);
//         return NULL;
//     }

//     juego->jugador_1 = crear_jugador();
//     if (!juego->jugador_1) {
//         printf("Error: No se pudo crear el jugador 1.\n");
//         abb_destruir_todo(juego->pokemones_disponibles,destruir_pokemon);
//         free(juego);
//         return NULL;
//     }

//     juego->jugador_2 = crear_jugador();
//     if (!juego->jugador_2) {
//         printf("Error: No se pudo crear el jugador 2.\n");
//         abb_destruir_todo(juego->pokemones_disponibles,destruir_pokemon);
//         free(juego->jugador_1);
//         free(juego);
//         return NULL;
//     }

//     if (!mapear_pokemones(nombre_archivo, juego->pokemones_disponibles)) {
//         printf("Error: No se pudieron mapear los pokemones desde el archivo.\n");
//         abb_destruir_todo(juego->pokemones_disponibles,destruir_pokemon);
//         free(juego->jugador_1);
//         free(juego->jugador_2);
//         free(juego);
//         return NULL;
//     }

//     printf("Juego creado correctamente.\n");
//     return juego;
// }

// int tp_cantidad_pokemon(TP *tp)
// {	
// 	if(!tp || !tp->pokemones_disponibles)
// 		return 0;
// 	return (int)abb_tamanio(tp->pokemones_disponibles);
// }

// const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
// {
//     if (!tp || !nombre)
//         return NULL;
//     struct pokemon_info pokemon_a_buscar;
//     pokemon_a_buscar.nombre = (char *)nombre;
//     const struct pokemon_info *pokemon_buscado =  (const struct pokemon_info *)abb_buscar(tp->pokemones_disponibles, &pokemon_a_buscar);
//     if(pokemon_buscado)
//         return pokemon_buscado;
//     return NULL;
// }

// bool agregar_nombre_al_string(void *elemento, void *auxiliar) {
//     if (!elemento || !auxiliar) 
//         return false;

//     struct pokemon_info *pokemon_actual = (struct pokemon_info *)elemento;
//     char **string = (char **)auxiliar;
//     size_t longitud_string = strlen(*string);
//     size_t longitud_pokemon_actual = strlen(pokemon_actual->nombre);

//     size_t nuevo_tamano = longitud_string + longitud_pokemon_actual + 2;

//     char *string_auxiliar = realloc(*string, nuevo_tamano);
//     if (!string_auxiliar) 
//         return false;

//     *string = string_auxiliar;


//     strcat(*string, pokemon_actual->nombre);
//     strcat(*string,",");

//     return true;
// }

// char *tp_nombres_disponibles(TP *tp)
// {
// 	if(!tp)
// 		return NULL;
// 	char *nombres_disponibles = calloc(1,sizeof(char));
// 	if(!nombres_disponibles)
// 		return NULL;
// 	abb_con_cada_elemento(tp->pokemones_disponibles,INORDEN,agregar_nombre_al_string,&nombres_disponibles);
// 	size_t longitud = strlen(nombres_disponibles);
//     if (longitud > 0 && nombres_disponibles[longitud - 1] == ',') {
//             nombres_disponibles[longitud - 1] = '\0';
//     }
// 	return nombres_disponibles;
// }



// bool validar_seleccion_jugador(jugador_t *jugador, const char *nombre)
// {
//     if (!jugador)
//         return false;

//     if (jugador->pokemon_seleccionado && jugador->pokemon_seleccionado->nombre){
// 	 if(strcmp(jugador->pokemon_seleccionado->nombre, nombre) == 0)
//     {
//         printf("Error: El Pokémon ya está seleccionado por otro jugador.\n");
//         return false;
//     }
// 	}
//     return true;
// }

// bool asignar_pokemon(jugador_t *jugador, const struct pokemon_info *pokemon)
// {
//     if (!jugador || !pokemon)
//         return false;

//     jugador->pokemon_seleccionado = pokemon;
//     return true;
// }
// void asignar_jugadores(TP *tp, enum TP_JUGADOR jugador, jugador_t **jugador_actual, jugador_t **jugador_rival)
// {
//     if(!tp)
//         return;
//     if (jugador == JUGADOR_1)
//     {
// 		if(jugador_actual)
//         	*jugador_actual = tp->jugador_1;
// 		if(jugador_rival)
//         	*jugador_rival = tp->jugador_2;
//     }
//     else if (jugador == JUGADOR_2)
//     {
// 		if(jugador_actual)
//        		*jugador_actual = tp->jugador_2;
//         if(jugador_rival)
// 			*jugador_rival = tp->jugador_1;
//     }
// }

// bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
// {
//     if (!tp || !nombre)
//         return false;

//     jugador_t *jugador_actual;
//     jugador_t *jugador_rival;

//     asignar_jugadores(tp, jugador, &jugador_actual, &jugador_rival);

//     if (validar_seleccion_jugador(jugador_rival, nombre)){
//     	const struct pokemon_info *pokemon = tp_buscar_pokemon(tp, nombre);
//    		if (pokemon)
//         	return asignar_pokemon(jugador_actual, pokemon);
// 	}
//     return false;
// }

// const struct pokemon_info *tp_pokemon_seleccionado(TP *tp, enum TP_JUGADOR jugador)
// {
//     if (!tp)
//         return NULL;
// 	jugador_t *jugador_actual;
// 	asignar_jugadores(tp,jugador,&jugador_actual,NULL);
// 	if(jugador_actual)
// 		return jugador_actual->pokemon_seleccionado;
// 	return NULL;
// }

// typedef struct {
//     jugador_t *jugador_actual;
//     unsigned tiempo_total;
// } contexto_t;

// bool calcular_tiempo_obstaculo(void *elemento, void *contexto) {
//     obstaculo_t *obstaculo = (obstaculo_t *)elemento;
//     contexto_t *ctx = (contexto_t *)contexto;
//     jugador_t *jugador_actual = ctx->jugador_actual;

// 	if(!jugador_actual->pokemon_seleccionado)
// 		return false;
//     unsigned int *tiempo_total = &(ctx->tiempo_total);
//     static int n_fuerza = 0, n_destreza = 0, n_inteligencia = 0;
//     int tiempo;

//     if (obstaculo->tipo == IDENTIFICADOR_OBSTACULO_FUERZA) {
//         tiempo = 10 - (int)jugador_actual->pokemon_seleccionado->fuerza - n_fuerza;
//         n_fuerza++;
//         n_destreza = 0;
//         n_inteligencia = 0;

//     } else if (obstaculo->tipo == IDENTIFICADOR_OBSTACULO_DESTREZA)  {
//         tiempo = 10 - (int)jugador_actual->pokemon_seleccionado->destreza - n_destreza;
//         n_destreza++;
//         n_fuerza = 0;
//         n_inteligencia = 0;
//     } else if (obstaculo->tipo == IDENTIFICADOR_OBSTACULO_INTELIGENCIA ) {
//         tiempo = 10 - (int)jugador_actual->pokemon_seleccionado->inteligencia - n_inteligencia;
//         n_inteligencia++;
//         n_fuerza = 0;
//         n_destreza = 0;
//      } else {
//         return false; 
//     }

//     if (tiempo < 0) {
//         tiempo = 0;
//     }
//     *tiempo_total += (unsigned int)tiempo;
//     return true; 
// }

// unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
// {
// 	jugador_t *jugador_unico = NULL;
// 	asignar_jugadores(tp,jugador,&jugador_unico,NULL);
// 	if(!tp || !jugador_unico)
// 		return ERROR_OBSTACULOS;
// 	if(!jugador_unico->pokemon_seleccionado || lista_tamanio(jugador_unico->pista) == 0)
// 		return ERROR_OBSTACULOS;	
// 	unsigned tiempo = 0;
//     contexto_t contexto = {jugador_unico, tiempo};
// 	lista_con_cada_elemento(jugador_unico->pista,calcular_tiempo_obstaculo,&contexto);
// 	return contexto.tiempo_total;
// }
// obstaculo_t* crear_obstaculo(enum TP_OBSTACULO tipo) {
//     obstaculo_t *obstaculo = calloc(1, sizeof(obstaculo_t));
//     if (!obstaculo) {
//         printf("Error: No se pudo asignar memoria para el obstáculo.\n");
//         return NULL;
//     }

//     switch(tipo) {
//         case OBSTACULO_FUERZA:
//             obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_FUERZA;
//             break;
//         case OBSTACULO_DESTREZA:
//             obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_DESTREZA;
//             break;
//         case OBSTACULO_INTELIGENCIA:
//             obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_INTELIGENCIA;
//             break;
//         default:
//             printf("Error: Tipo de obstáculo desconocido.\n");
//             free(obstaculo);
//             return NULL;
//     }

//     return obstaculo;
// }
// unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
// 			      enum TP_OBSTACULO obstaculo, unsigned posicion)
// {
// 	if(!tp)
// 		return ERROR_OBSTACULOS;
// 	jugador_t *jugador_actual;
// 	asignar_jugadores(tp,jugador,&jugador_actual,NULL);
// 	obstaculo_t *obstaculo_a_añadir = crear_obstaculo(obstaculo);

// 	if(lista_insertar_en_posicion(jugador_actual->pista,obstaculo_a_añadir,(size_t)posicion))
// 		return (unsigned)lista_tamanio(jugador_actual->pista);
// 	return ERROR_OBSTACULOS;
// }

// void destruir_obstaculo(obstaculo_t *obstaculo)
// {
// 	if(obstaculo)
// 		free(obstaculo);
// 	return;
// }

// unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
// {
// 	if(!tp)
// 		return ERROR_OBSTACULOS;
// 	jugador_t *jugador_actual;
// 	asignar_jugadores(tp,jugador,&jugador_actual,NULL);
// 	obstaculo_t *obstaculo_a_quitar = (obstaculo_t*)lista_quitar_de_posicion(jugador_actual->pista,(size_t)posicion);
// 	if(obstaculo_a_quitar){
// 		destruir_obstaculo(obstaculo_a_quitar);
// 		return (unsigned)lista_tamanio(jugador_actual->pista);
// 	}
// 	return 0;
// }

// bool mostrar_obstaculos(void *elemento, void*auxiliar)
// {
//     if (!elemento || !auxiliar) return false;

//     obstaculo_t *obstaculo = (obstaculo_t*)elemento;
//     char **string = (char **)auxiliar;


//     size_t longitud_string = strlen(*string);
//     size_t longitud_tipo = 1;

//     char *aux = realloc(*string, longitud_string + longitud_tipo + 2);
//     if (!aux) return false;
//     *string = aux;

//     strncat(*string, &obstaculo->tipo, 1);
//     strcat(*string, ",");

//     return true;
// }


// char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
// {
// 	if(!tp)
// 		return NULL;
// 	jugador_t *jugador_actual;
// 	asignar_jugadores(tp,jugador,&jugador_actual,NULL);
// 	if(jugador_actual){
// 		char *string = calloc(10,sizeof(char));
// 		if(!string)
// 			return NULL;
// 		lista_con_cada_elemento(jugador_actual->pista,mostrar_obstaculos,&string);
// 		size_t longitud = strlen(string);
//         if (longitud > 0 && string[longitud - 1] == ',') {
//             string[longitud - 1] = '\0';
//         }
// 		return string;
// 	}
// 	return NULL;
// }


// bool mostrar_elemento(void *elemento, void *contexto) {
//     obstaculo_t *obstaculo = (obstaculo_t *)elemento;
// 	if(obstaculo)
//     	printf("Obstáculo: %c\n", obstaculo->tipo);
//     return true; // Continuar iterando
// }


// void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
// {

// 	jugador_t *jugador_actual;
// 	asignar_jugadores(tp,jugador,&jugador_actual,NULL);
// 	while(lista_tamanio(jugador_actual->pista) > 0){
// 		obstaculo_t *obstaculo = (obstaculo_t *)lista_quitar(jugador_actual->pista);
// 		destruir_obstaculo(obstaculo);
// 	}
// 	return;
// }






// void destruir_jugador(TP *tp, enum TP_JUGADOR jugador_id)
// {

// 	jugador_t *jugador;
// 	asignar_jugadores(tp,jugador_id,&jugador,NULL);

// 	if(jugador){
// 		if(jugador->pista){
// 			tp_limpiar_pista(tp,jugador_id);
// 			free(jugador->pista);
// 		}
// 	free(jugador);
// 	}
// 	return;
// }

// void tp_destruir(TP *tp)
// {	
// 	if(!tp)
// 		return;

//     abb_destruir_todo(tp->pokemones_disponibles, destruir_pokemon);

//     if (tp->jugador_1) {
// 		destruir_jugador(tp,JUGADOR_1);
//     }
//     if (tp->jugador_2) {
// 		destruir_jugador(tp,JUGADOR_2);
//     }	
//     free(tp);
// }






int main()
{
    char stringNum[5] ="12";
    int suma = 0;
    //de char a int 
    for(int i = 0; i < (int)strlen(stringNum);i++)
    {   
        int num = stringNum[i]-'0';
        suma += num;
    }
    //de int a  char
    int numero = 1;
    char letra = numero+'0'; 
    
    printf("%i\n",suma);
    printf("%c",letra);
	return 0;
}