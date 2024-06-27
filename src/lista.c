#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t cantidad_elementos;
};

struct lista_iterador {
	nodo_t *nodo_actual;
	struct lista *lista_a_iterar;
};
lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(struct lista));
	if (!lista) {
		return NULL;
	}
	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista) {
		return NULL;
	}
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo) {
		free(lista);
		return NULL;
	}
	nuevo_nodo->elemento = elemento;

	if (!(lista->nodo_inicio)) {
		lista->nodo_inicio = nuevo_nodo;
	} else {
		lista->nodo_final->siguiente = nuevo_nodo;
	}
	lista->nodo_final = nuevo_nodo;
	lista->cantidad_elementos++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista) {
		return NULL;
	}

	if (posicion >= (lista->cantidad_elementos)) {
		return lista_insertar(lista, elemento);
	}
	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *nodo_auxiliar = calloc(1, sizeof(nodo_t));
	if (!nodo_auxiliar) {
		free(lista);
		return NULL;
	}
	nodo_auxiliar->elemento = elemento;
	if (posicion == 0) {
		nodo_auxiliar->siguiente = nodo_actual;
		lista->nodo_inicio = nodo_auxiliar;
		lista->cantidad_elementos++;
		return lista;
	}

	for (int it = 0; it < (posicion - 1); it++) {
		nodo_actual = nodo_actual->siguiente;
	}
	nodo_auxiliar->siguiente = nodo_actual->siguiente;
	nodo_actual->siguiente = nodo_auxiliar;
	if (!nodo_auxiliar->siguiente) {
		lista->nodo_final = nodo_auxiliar;
	}
	lista->cantidad_elementos++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}
	nodo_t *nodo_actual = lista->nodo_inicio;
	void *elemento_a_quitar;

	if (lista->cantidad_elementos == 1) {
		elemento_a_quitar = nodo_actual->elemento;
		lista->nodo_inicio = lista->nodo_final = NULL;
		free(nodo_actual);
		lista->cantidad_elementos--;
		return elemento_a_quitar;
	}
	nodo_t *nodo_auxiliar = NULL;

	while (nodo_actual->siguiente) {
		nodo_auxiliar = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
	}

	elemento_a_quitar = nodo_actual->elemento;
	free(nodo_auxiliar->siguiente);
	lista->nodo_final = nodo_auxiliar;
	nodo_auxiliar->siguiente = NULL;
	lista->cantidad_elementos--;
	return elemento_a_quitar;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista) {
		return NULL;
	}
	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *nodo_auxiliar = NULL;

	void *elemento_a_quitar;

	if (posicion >= lista->cantidad_elementos) {
		elemento_a_quitar = lista_quitar(lista);
		free(nodo_auxiliar);
		return elemento_a_quitar;
	}
	if (posicion == 0) {
		nodo_auxiliar = nodo_actual->siguiente;
		elemento_a_quitar = nodo_actual->elemento;
		free(nodo_actual);
		lista->nodo_inicio = nodo_auxiliar;
		lista->cantidad_elementos--;
		return elemento_a_quitar;
	}
	for (int it = 0; it < (posicion - 1); it++) {
		nodo_actual = nodo_actual->siguiente;
	}
	nodo_auxiliar = nodo_actual->siguiente;
	nodo_actual->siguiente = nodo_auxiliar->siguiente;
	elemento_a_quitar = nodo_auxiliar->elemento;
	free(nodo_auxiliar);
	lista->cantidad_elementos--;
	return elemento_a_quitar;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || (posicion >= lista->cantidad_elementos)) {
		return NULL;
	}
	nodo_t *nodo_actual = lista->nodo_inicio;
	for (int it = 0; it < posicion; it++) {
		nodo_actual = nodo_actual->siguiente;
	}
	return nodo_actual->elemento;
}
void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador) {
		return NULL;
	}
	nodo_t *nodo_actual = lista->nodo_inicio;
	while (nodo_actual) {
		if (comparador(nodo_actual->elemento, contexto) == 0) {
			return nodo_actual->elemento;
		}
		nodo_actual = nodo_actual->siguiente;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (!lista) {
		return true;
	}
	return lista->cantidad_elementos == 0;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista) {
		return 0;
	}
	return lista->cantidad_elementos;
}

void lista_destruir(lista_t *lista)
{
	if (!lista) {
		return;
	}
	nodo_t *actual = lista->nodo_inicio;
	while (actual) {
		nodo_t *siguiente = actual->siguiente;

		lista->cantidad_elementos--;
		free(actual);

		actual = siguiente;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!(lista)) {
		return;
	}
	nodo_t *actual = lista->nodo_inicio;
	while (actual) {
		nodo_t *siguiente = actual->siguiente;

		if (funcion) {
			funcion(actual->elemento);
			lista->cantidad_elementos--;
		}
		free(actual);
		actual = siguiente;
	}

	free(lista);
	return;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista) {
		return NULL;
	}
	lista_iterador_t *it_lista = calloc(1, sizeof(struct lista_iterador));
	if (!it_lista) {
		free(lista);
		return NULL;
	}

	it_lista->lista_a_iterar = lista;
	it_lista->nodo_actual = lista->nodo_inicio;

	return it_lista;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || !(iterador->lista_a_iterar) ||
	    !(iterador->nodo_actual)) {
		return false;
	}
	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador ||
	    !(iterador->lista_a_iterar || !iterador->nodo_actual)) {
		return false;
	}

	if (iterador->nodo_actual == iterador->lista_a_iterar->nodo_final) {
		iterador->nodo_actual = NULL;
		return false;
	}

	iterador->nodo_actual = iterador->nodo_actual->siguiente;
	if (!iterador->nodo_actual) {
		return false;
	}
	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!(iterador) || !iterador->nodo_actual ||
	    !iterador->lista_a_iterar) {
		return NULL;
	}
	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador) {
		return;
	}
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!(lista) || !(funcion)) {
		return 0;
	}
	size_t nodos_iterados = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;
	if (!nodo_actual) {
		return 0;
	}
	bool seguir_iterando = true;

	while (nodo_actual && seguir_iterando) {
		nodo_t *siguiente = nodo_actual->siguiente;
		nodos_iterados++;
		seguir_iterando = funcion(nodo_actual->elemento, contexto);
		nodo_actual = siguiente;
	}
	return nodos_iterados;
}