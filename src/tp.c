#include "tp.h"
#include "./utils.h"
#include "./abb.h"
#include "./abb.h"
#include "./lista.h"

typedef struct obstaculo {
	char tipo;
} obstaculo_t;

typedef struct jugador {
	lista_t *pista;
	const struct pokemon_info *pokemon_seleccionado;
} jugador_t;
struct tp {
	abb_t *pokemones_disponibles;
	jugador_t *jugador_1;
	jugador_t *jugador_2;
};

jugador_t *crear_jugador()
{
	jugador_t *jugador = calloc(1, sizeof(jugador_t));
	if (!jugador) {
		return NULL;
	}
	jugador->pista = lista_crear();

	if (!jugador->pista) {
		free(jugador);
		return NULL;
	}
	return jugador;
}

struct pokemon_info *crear_pokemon(char *campo)
{
	struct pokemon_info *pokemon = malloc(sizeof(struct pokemon_info));
	if (!pokemon)
		return NULL;
	pokemon->nombre = malloc(sizeof(char) * (size_t)strlen(campo) + 1);
	if (!pokemon->nombre) {
		free(pokemon);
		return NULL;
	}

	return pokemon;
}
struct pokemon_info *completar_pokemon(struct pokemon_info *pokemon,
				       char *campo, int indice)
{
	switch (indice) {
	case NOMBRE_POKEMON:
		if (pokemon->nombre)
			strcpy(pokemon->nombre, campo);
		break;
	case FUERZA_POKEMON:
		pokemon->fuerza = atoi(campo);
		break;

	case DESTREZA_POKEMON:
		pokemon->destreza = atoi(campo);
		break;
	case INTELIGENCIA_POKEMON:
		pokemon->inteligencia = atoi(campo);
		break;
	default:
		break;
	}
	return pokemon;
}
int comparador_pokemon(void *pokemon1, void *pokemon2)
{
	struct pokemon_info *p1 = (struct pokemon_info *)pokemon1;
	struct pokemon_info *p2 = (struct pokemon_info *)pokemon2;
	char nombre_minusculas_1[strlen(p1->nombre) + 1];
	strcpy(nombre_minusculas_1, p1->nombre);

	char nombre_minusculas_2[strlen(p2->nombre) + 1];
	strcpy(nombre_minusculas_2, p2->nombre);

	str_tolower(nombre_minusculas_1);
	str_tolower(nombre_minusculas_2);

	return strcmp(nombre_minusculas_1, nombre_minusculas_2);
}

abb_t *mapear_pokemones(const char *archivo, abb_t *abb_pokemones)
{
	if (!archivo || !abb_pokemones)
		return NULL;

	FILE *archivo_con_pokemones = fopen(archivo, "r");
	;
	char linea[LINEA_SIZE];
	while (fgets(linea, sizeof(linea), archivo_con_pokemones)) {
		char *campo;
		int indice_campos = 0;
		campo = strtok(linea, ",");
		struct pokemon_info *pokemon = crear_pokemon(campo);
		while (campo) {
			indice_campos++;
			completar_pokemon(pokemon, campo, indice_campos);
			campo = strtok(NULL, ",");
		}
		abb_insertar(abb_pokemones, pokemon);
	}
	fclose(archivo_con_pokemones);
	return abb_pokemones;
}

TP *tp_crear(const char *nombre_archivo)
{
	if (!nombre_archivo)
		return NULL;
	if (!contiene_formato_correcto(nombre_archivo)) {
		return NULL;
	}

	TP *juego = calloc(1, sizeof(TP));
	if (!juego)
		return NULL;
	juego->pokemones_disponibles = abb_crear(comparador_pokemon);
	if (!juego->pokemones_disponibles) {
		free(juego);
		return NULL;
	}
	juego->jugador_1 = crear_jugador();
	if (!juego->jugador_1) {
		free(juego);
		return NULL;
	}
	juego->jugador_2 = crear_jugador();
	if (!juego->jugador_2) {
		free(juego->jugador_1);
		free(juego);
		return NULL;
	}
	mapear_pokemones(nombre_archivo, juego->pokemones_disponibles);

	return juego;
}

int tp_cantidad_pokemon(TP *tp)
{
	if (!tp || !tp->pokemones_disponibles)
		return 0;
	return (int)abb_tamanio(tp->pokemones_disponibles);
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (!tp || !nombre)
		return NULL;
	struct pokemon_info pokemon_a_buscar;
	pokemon_a_buscar.nombre = (char *)nombre;
	return (const struct pokemon_info *)abb_buscar(
		tp->pokemones_disponibles, &pokemon_a_buscar);
}

bool agregar_nombre_al_string(void *elemento, void *auxiliar)
{
	if (!elemento || !auxiliar)
		return false;

	struct pokemon_info *pokemon_actual = (struct pokemon_info *)elemento;
	char **string = (char **)auxiliar;
	size_t longitud_string = strlen(*string);
	size_t longitud_pokemon_actual = strlen(pokemon_actual->nombre);

	size_t nuevo_tamano = longitud_string + longitud_pokemon_actual + 2;

	char *string_auxiliar = realloc(*string, nuevo_tamano);
	if (!string_auxiliar)
		return false;

	*string = string_auxiliar;

	strcat(*string, pokemon_actual->nombre);
	strcat(*string, ",");

	return true;
}

char *tp_nombres_disponibles(TP *tp)
{
	if (!tp)
		return NULL;
	char *nombres_disponibles = calloc(1, sizeof(char));
	if (!nombres_disponibles)
		return NULL;
	abb_con_cada_elemento(tp->pokemones_disponibles, INORDEN,
			      agregar_nombre_al_string, &nombres_disponibles);
	size_t longitud = strlen(nombres_disponibles);
	if (longitud > 0 && nombres_disponibles[longitud - 1] == ',') {
		nombres_disponibles[longitud - 1] = '\0';
	}
	return nombres_disponibles;
}

bool validar_seleccion_jugador(jugador_t *jugador, const char *nombre)
{
	if (!jugador)
		return false;

	if (jugador->pokemon_seleccionado &&
	    jugador->pokemon_seleccionado->nombre) {
		str_tolower(jugador->pokemon_seleccionado->nombre);
		str_tolower((char*)nombre);
		
		if (strcmp(jugador->pokemon_seleccionado->nombre, nombre) ==
		    0) {
			return false;
		}
	}
	return true;
}

bool asignar_pokemon(jugador_t *jugador, const struct pokemon_info *pokemon)
{
	if (!jugador || !pokemon)
		return false;

	jugador->pokemon_seleccionado = pokemon;
	return true;
}
void asignar_jugadores(TP *tp, enum TP_JUGADOR jugador,
		       jugador_t **jugador_actual, jugador_t **jugador_rival)
{
	if (jugador == JUGADOR_1) {
		if (jugador_actual)
			*jugador_actual = tp->jugador_1;
		if (jugador_rival)
			*jugador_rival = tp->jugador_2;
	} else if (jugador == JUGADOR_2) {
		if (jugador_actual)
			*jugador_actual = tp->jugador_2;
		if (jugador_rival)
			*jugador_rival = tp->jugador_1;
	}
}
bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	if (!tp || !nombre)
		return false;

	jugador_t *jugador_actual = NULL;
	jugador_t *jugador_rival = NULL;

	asignar_jugadores(tp, jugador, &jugador_actual, &jugador_rival);

	if (validar_seleccion_jugador(jugador_rival, nombre)) {
		const struct pokemon_info *pokemon =
			tp_buscar_pokemon(tp, nombre);
		if (pokemon)
			return asignar_pokemon(jugador_actual, pokemon);
	}
	return false;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	if (!tp) {
		return NULL;
	}
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	if (jugador_actual->pokemon_seleccionado)
		return jugador_actual->pokemon_seleccionado;
	return NULL;
}
void destruir_obstaculo(obstaculo_t *obstaculo)
{
	if (obstaculo)
		free(obstaculo);
	return;
}

obstaculo_t *crear_obstaculo(enum TP_OBSTACULO tipo)
{
	obstaculo_t *obstaculo = calloc(1, sizeof(obstaculo_t));
	if (!obstaculo) {
		return NULL;
	}

	switch (tipo) {
	case OBSTACULO_FUERZA:
		obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_FUERZA;
		break;
	case OBSTACULO_DESTREZA:
		obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_DESTREZA;
		break;
	case OBSTACULO_INTELIGENCIA:
		obstaculo->tipo = (char)IDENTIFICADOR_OBSTACULO_INTELIGENCIA;
		break;
	default:
		destruir_obstaculo(obstaculo);
		return NULL;
	}

	return obstaculo;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	if (!tp)
		return ERROR_OBSTACULOS;
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	obstaculo_t *obstaculo_a_añadir = crear_obstaculo(obstaculo);
	if(obstaculo_a_añadir) {
		if (lista_insertar_en_posicion(jugador_actual->pista,
					       obstaculo_a_añadir,
					       (size_t)posicion)){
			return (unsigned)lista_tamanio(jugador_actual->pista);
		}
	}
	destruir_obstaculo(obstaculo_a_añadir);
	return ERROR_OBSTACULOS;
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	if (!tp)
		return ERROR_OBSTACULOS;
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	obstaculo_t *obstaculo_a_quitar =
		(obstaculo_t *)lista_quitar_de_posicion(jugador_actual->pista,
							(size_t)posicion);
	if (obstaculo_a_quitar) {
		destruir_obstaculo(obstaculo_a_quitar);
		return (unsigned)lista_tamanio(jugador_actual->pista);
	}
	return 0;
}

void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	while (lista_tamanio(jugador_actual->pista) > 0) {
		obstaculo_t *obstaculo =
			(obstaculo_t *)lista_quitar(jugador_actual->pista);
		destruir_obstaculo(obstaculo);
	}
	return;
}

bool mostrar_obstaculos(void *elemento, void *auxiliar)
{
	if (!elemento || !auxiliar)
		return false;

	obstaculo_t *obstaculo = (obstaculo_t *)elemento;
	char **string = (char **)auxiliar;

	size_t longitud_string = strlen(*string);
	size_t longitud_tipo = 1;

	char *aux = realloc(*string, longitud_string + longitud_tipo + 2);
	if (!aux)
		return false;
	*string = aux;

	strncat(*string, &obstaculo->tipo, 1);
	return true;
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp)
		return NULL;
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	if (jugador_actual) {
		if(jugador_actual->pista && lista_tamanio(jugador_actual->pista) > 0 ){
		char *string = calloc(10, sizeof(char));
		if (!string)
			return NULL;
		lista_con_cada_elemento(jugador_actual->pista,
					mostrar_obstaculos, &string);
		size_t longitud = strlen(string);
		if (longitud > 0 && string[longitud - 1] == ',') {
			string[longitud - 1] = '\0';
		}
		return string;
		}
	}
	return NULL;
}

/**
 * Esta estructura facilita el uso de la funcion de iterador interno
 * de la "pista" para poder  actualizar
 * sin problema las distintas variables,
 * a medida que se calcula el tiempo por cada 
 * obstaculo del pokemon
 */
typedef struct {
	const struct pokemon_info *pokemon;
	int tiempo_total;
	int n_fuerza;
	int n_destreza;
	int n_inteligencia;
	char **string;
} contexto_t;

int actualizar_tiempos(int cualidad_pokemon, int *n_cualidad_a_aumentar,
		       int *n_cualidad_reseteo_1, int *n_cualidad_reseteo_2)
{
	int tiempo = 10 - cualidad_pokemon - *n_cualidad_a_aumentar;
	(*n_cualidad_a_aumentar)++;
	*n_cualidad_reseteo_1 = 0;
	*n_cualidad_reseteo_2 = 0;
	return tiempo;
}

bool mostrar_tiempo_obstaculos(void *elemento, void *auxiliar)
{
	if (!elemento || !auxiliar)
		return false;
	obstaculo_t *obstaculo = (obstaculo_t *)elemento;
	contexto_t *contexto = (contexto_t *)auxiliar;
	const struct pokemon_info *pokemon = contexto->pokemon;
	if (!pokemon)
		return false;
	size_t tamaño = strlen(*contexto->string) + 2;
	char *string_auxiliar = realloc(*contexto->string, tamaño * 2);
	if (!string_auxiliar)
		return false;
	*contexto->string = string_auxiliar;
	int tiempo = 0;

	switch (obstaculo->tipo) {
	case IDENTIFICADOR_OBSTACULO_FUERZA:
		tiempo = actualizar_tiempos(pokemon->fuerza,
					    &(contexto->n_fuerza),
					    &(contexto->n_destreza),
					    &(contexto->n_inteligencia));
		break;
	case IDENTIFICADOR_OBSTACULO_DESTREZA:
		tiempo = actualizar_tiempos(pokemon->destreza,
					    &(contexto->n_destreza),
					    &(contexto->n_fuerza),
					    &(contexto->n_inteligencia));
		break;
	case IDENTIFICADOR_OBSTACULO_INTELIGENCIA:
		tiempo = actualizar_tiempos(pokemon->inteligencia,
					    &(contexto->n_inteligencia),
					    &(contexto->n_fuerza),
					    &(contexto->n_destreza));
		break;

	default:
		break;
	}
	if (tiempo < 0) {
		tiempo = 0;
	}
	char tiempo_a_letra = (char)(tiempo + '0');
	strcat(*contexto->string, &tiempo_a_letra);
	strcat(*contexto->string, ",");

	return true;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp)
		return NULL;
	jugador_t *jugador_actual = NULL;
	asignar_jugadores(tp, jugador, &jugador_actual, NULL);
	if (jugador_actual) {
		char *historial_carrera = calloc(1, sizeof(char));
		if (!historial_carrera)
			return NULL;

		contexto_t contexto = { jugador_actual->pokemon_seleccionado,
					0,
					0,
					0,
					0,
					&historial_carrera };

		lista_con_cada_elemento(jugador_actual->pista,
					mostrar_tiempo_obstaculos, &contexto);

		size_t longitud = strlen(historial_carrera);

		if (longitud > 0 && historial_carrera[longitud - 1] == ',') {
			historial_carrera[longitud - 1] = '\0';
		}

		return historial_carrera;
	}
	return NULL;
}
unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp)
		return ERROR_OBSTACULOS;
	int tiempo = 0;
	char *string = tp_tiempo_por_obstaculo(tp, jugador);
	if (string) {
		for (int i = 0; i < strlen(string); i++) {
			if (string[i] != ',') {
				int numero = string[i] - '0';
				tiempo += numero;
			}
		}
		free(string);
		return (unsigned)tiempo;
	}
	return ERROR_OBSTACULOS;
}
void destruir_pokemon(void *elemento)
{
	if (!elemento)
		return;

	struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
	free(pokemon->nombre);
	free(pokemon);
}

void destruir_jugador(TP *tp, enum TP_JUGADOR jugador_id)
{
	jugador_t *jugador = NULL;
	asignar_jugadores(tp, jugador_id, &jugador, NULL);

	if (jugador) {
		if (jugador->pista) {
			tp_limpiar_pista(tp, jugador_id);
			lista_destruir(jugador->pista);
		}
		free(jugador);
	}
	return;
}

void tp_destruir(TP *tp)
{
	if (!tp)
		return;

	abb_destruir_todo(tp->pokemones_disponibles, destruir_pokemon);
	if (tp->jugador_1) {
		destruir_jugador(tp, JUGADOR_1);
	}
	if (tp->jugador_2) {
		destruir_jugador(tp, JUGADOR_2);
	}
	free(tp);
}
