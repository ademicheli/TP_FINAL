#include "./abb.h"
#include "./abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define CERO 0
#define FACTOR_DE_COMPARACION 0
abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;
	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (!arbol)
		return NULL;
	arbol->comparador = comparador;
	return arbol;
}
nodo_abb_t *nodo_abb_insertar(abb_t *arbol, nodo_abb_t *nodo, void *elemento)

{
	/*
		Recibe el arbol donde se realiza la insersion el nodo donde inician las comparaciones y el elemento a comparar
		para mantener la propiedad de un abb.
		La función devuelve el nodo actual (o el nuevo nodo si nodo era NULL).
	*/
	if (!nodo) {
		struct nodo_abb *nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
		if (!nodo_nuevo) {
			free(arbol);
			return NULL;
		}
		nodo_nuevo->elemento = elemento;
		return nodo_nuevo;
	}
	int comparador = arbol->comparador(nodo->elemento, elemento);
	if (comparador <= FACTOR_DE_COMPARACION) {
		nodo->derecha =
			nodo_abb_insertar(arbol, nodo->derecha, elemento);

	} else {
		nodo->izquierda =
			nodo_abb_insertar(arbol, nodo->izquierda, elemento);
	}
	return nodo;
}

void *nodo_abb_buscar(abb_t *arbol, nodo_abb_t *nodo, void *elemento)
{
	/*
		Recibe el arbol, el nodo donde inicia las comparaciones y el elemento a buscar
		nodo_abb_buscar devuelve el elemento encontrado o NULL si el elemento no se encuentra en el árbol.
	*/
	if (!nodo) {
		return NULL;
	}
	int comparacion = arbol->comparador(nodo->elemento, elemento);

	if (comparacion == FACTOR_DE_COMPARACION) {
		return nodo->elemento;
	}
	if (comparacion < FACTOR_DE_COMPARACION) {
		return nodo_abb_buscar(arbol, nodo->derecha, elemento);
	}
	return nodo_abb_buscar(arbol, nodo->izquierda, elemento);
}

void *obtener_predecesor_inorden(nodo_abb_t *raiz)
{
	/*
	Recibe una raíz de un subárbol,
	devuelve el predecesor inorden o NULL en caso de error.
	*/
	if (!raiz)
		return NULL;
	nodo_abb_t *actual = raiz->izquierda;
	while (actual->derecha) {
		actual = actual->derecha;
	}
	return actual->elemento;
}
void *abb_quitar_hoja_o_con_hijo(abb_t *arbol, nodo_abb_t *raiz_actual,
				 nodo_abb_t *nodo_a_eliminar)
{
	/*
	Recibe un arbol , la raiz actual, y el nodo que se liberará 
	Devuelve el siguiente nodo del subarbol que se eliminó o NULL en caso de error.
	*/
	if (!raiz_actual)
		return NULL;
	nodo_abb_t *siguiente = nodo_a_eliminar->izquierda ?
					nodo_a_eliminar->izquierda :
					nodo_a_eliminar->derecha;
	if (nodo_a_eliminar == arbol->nodo_raiz) {
		arbol->nodo_raiz = siguiente;
	}
	free(nodo_a_eliminar);
	arbol->tamanio--;
	return siguiente;
}

void *nodo_abb_quitar(abb_t *arbol, nodo_abb_t *raiz_actual, void *elemento,
		      void **elemento_quitado)
{
	/*
	Recibe el arbol donde se eliminara el nodo, la raiz actual donde inicia las comparaciones,
	el elemento a quitar y un puntero del elemento a eliminar.
	Busca en el arbol un elemento igual al provisto (utilizando la funcion de
 	 comparación) y si lo encuentra lo quita del arbol y lo devuelve.
	Al eliminar con dos hijos, se reemplaza el nodo con el predecesor inorden.
	Devuelve la raiz del nodo a quitar o NULL en caso de error.
    */
	if (!raiz_actual) {
		return NULL;
	}
	int comparacion = arbol->comparador(raiz_actual->elemento, elemento);
	if (comparacion == FACTOR_DE_COMPARACION) {
		if (elemento_quitado != NULL) {
			*elemento_quitado = raiz_actual->elemento;
		}

		if (!raiz_actual->derecha || !raiz_actual->izquierda) {
			return abb_quitar_hoja_o_con_hijo(arbol, raiz_actual,
							  raiz_actual);
		}
		void *predecesor = obtener_predecesor_inorden(raiz_actual);
		raiz_actual->elemento = predecesor;
		raiz_actual->izquierda = nodo_abb_quitar(
			arbol, raiz_actual->izquierda, predecesor, NULL);
		return raiz_actual;
	}

	if (comparacion < FACTOR_DE_COMPARACION) {
		raiz_actual->derecha =
			nodo_abb_quitar(arbol, raiz_actual->derecha, elemento,
					elemento_quitado);
	}
	raiz_actual->izquierda = nodo_abb_quitar(arbol, raiz_actual->izquierda,
						 elemento, elemento_quitado);

	return raiz_actual;
}

void nodo_abb_destruir(nodo_abb_t *raiz)
{
	/*
	Recibe un un puntero nodo_abb_t 
	Destruye el arbol liberando la memoria reservada por el mismo.
	*/
	if (!raiz) {
		return;
	}
	nodo_abb_destruir(raiz->izquierda);
	nodo_abb_destruir(raiz->derecha);
	free(raiz);
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	arbol->nodo_raiz = nodo_abb_insertar(arbol, arbol->nodo_raiz, elemento);
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	void *resultado = NULL;
	nodo_abb_quitar(arbol, arbol->nodo_raiz, elemento, &resultado);
	return resultado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	void *elemento_buscado = NULL;
	elemento_buscado = nodo_abb_buscar(arbol, arbol->nodo_raiz, elemento);
	return elemento_buscado;
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol)
		return true;
	return arbol->tamanio == CERO;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return CERO;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	if (!arbol)
		return;
	nodo_abb_destruir(arbol->nodo_raiz);
	free(arbol);
}

void nodo_abb_destruir_todo(nodo_abb_t *raiz, void (*destructor)(void *))
{
	/*
		Recibe un nodo de un arbol a partir del cual se inicia la destrucción del abb y una funcion destructora,
		destruye todo el arbol y aplica la funcion destructora al elemento.
		 
	*/
	if (!raiz)
		return;
	nodo_abb_destruir_todo(raiz->derecha, destructor);
	nodo_abb_destruir_todo(raiz->izquierda, destructor);
	destructor(raiz->elemento);
	free(raiz);
}
void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;
	if (!destructor) {
		abb_destruir(arbol);
		return;
	}
	nodo_abb_destruir_todo(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_con_cada_elemento_inorden(nodo_abb_t *nodo, bool *continuar,
				     bool (*funcion)(void *, void *), void *aux,
				     size_t *contador)
{
	/*
 	Recorre el arbol e invoca la funcion con cada elemento almacenado en el mismo
  	como primer parámetro. El puntero aux se pasa como segundo parámetro a la
 	función. Si la función devuelve false, se finaliza el recorrido aun si quedan
 	elementos por recorrer. Si devuelve true se sigue recorriendo mientras queden
 	elementos.
 	Realiza el recorrido INORDER.
 	Devuelve la cantidad de veces que fue invocada la función o 0 en caso de error. 
	*/
	if (!nodo) {
		return CERO;
	}
	abb_con_cada_elemento_inorden(nodo->izquierda, continuar, funcion, aux,
				      contador);

	if (*continuar) {
		(*contador)++;
		if (!funcion(nodo->elemento, aux)) {
			*continuar = false;
		}
	}
	if (*continuar)
		abb_con_cada_elemento_inorden(nodo->derecha, continuar, funcion,
					      aux, contador);

	return (*contador);
}

size_t abb_con_cada_elemento_preorden(nodo_abb_t *nodo, bool *continuar,
				      bool (*funcion)(void *, void *),
				      void *aux, size_t *contador)
{
	/*
 	Recorre el arbol e invoca la funcion con cada elemento almacenado en el mismo
  	como primer parámetro. El puntero aux se pasa como segundo parámetro a la
 	función. Si la función devuelve false, se finaliza el recorrido aun si quedan
 	elementos por recorrer. Si devuelve true se sigue recorriendo mientras queden
 	elementos.
 	Realiza el recorrido PREORDER.
 	Devuelve la cantidad de veces que fue invocada la función o 0 en caso de error.
	*/
	if (!nodo) {
		return CERO;
	}

	if (*continuar) {
		(*contador)++;
		if (!funcion(nodo->elemento, aux)) {
			*continuar = false;
		}
	}

	abb_con_cada_elemento_preorden(nodo->izquierda, continuar, funcion, aux,
				       contador);
	abb_con_cada_elemento_preorden(nodo->derecha, continuar, funcion, aux,
				       contador);

	return *contador;
}

size_t abb_con_cada_elemento_postorden(nodo_abb_t *nodo, bool *continuar,
				       bool (*funcion)(void *, void *),
				       void *aux, size_t *contador)
{
	/*
 	Recorre el arbol e invoca la funcion con cada elemento almacenado en el mismo
  	como primer parámetro. El puntero aux se pasa como segundo parámetro a la
 	función. Si la función devuelve false, se finaliza el recorrido aun si quedan
 	elementos por recorrer. Si devuelve true se sigue recorriendo mientras queden
 	elementos.
 	Realiza el recorrido POSTORDER.
 	Devuelve la cantidad de veces que fue invocada la función o 0 en caso de error.
	*/
	if (!nodo) {
		return CERO;
	}

	abb_con_cada_elemento_postorden(nodo->izquierda, continuar, funcion,
					aux, contador);
	abb_con_cada_elemento_postorden(nodo->derecha, continuar, funcion, aux,
					contador);
	if (*continuar) {
		(*contador)++;
		if (!funcion(nodo->elemento, aux)) {
			*continuar = false;
		}
	}
	return *contador;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return CERO;
	size_t contador_funcion = FACTOR_DE_COMPARACION;
	bool seguir_operando = true;
	if (recorrido == INORDEN) {
		contador_funcion = abb_con_cada_elemento_inorden(
			arbol->nodo_raiz, &seguir_operando, funcion, aux,
			&contador_funcion);
	}
	if (recorrido == PREORDEN) {
		contador_funcion = abb_con_cada_elemento_preorden(
			arbol->nodo_raiz, &seguir_operando, funcion, aux,
			&contador_funcion);
	}
	if (recorrido == POSTORDEN) {
		contador_funcion = abb_con_cada_elemento_postorden(
			arbol->nodo_raiz, &seguir_operando, funcion, aux,
			&contador_funcion);
	}
	return contador_funcion;
}
bool almacenar_elemento(void *elemento, void *aux)
{
	/*
	recibe un puntero void y recibe aux quien tiene que ser un puntero a un array de tres punteros:
       - El primer puntero tiene que ser un puntero a un array de punteros , que será utilizado para almacenar los elementos.
       - El segundo puntero tiene que ser un puntero a un size_t, que representa el tamaño del array.
       - El tercer puntero tiene que ser un puntero a un size_t, que actúa como un contador de los elementos almacenados en el array.
	Si elemento es NULL, la función devuelve false y se modifica el array.
    Si el contador es mayor o igual al tamaño del array, la función devuelve false y no realiza ningún cambio en el array.
    Si elemento no es NULL y hay espacio en el array :
      		 - El elemento se almacena en la posición actual del contador en el array.
     		 - El contador se incrementa en 1.
       		 - La función devuelve true.
	*/
	void **array = ((void ***)aux)[0];
	size_t *tamanio_array = (size_t *)((void **)aux)[1];
	size_t *contador = (size_t *)((void **)aux)[2];

	if (!elemento)
		return false;
	if (*contador >= *tamanio_array) {
		return false;
	}
	array[*contador] = elemento;
	(*contador)++;
	return true;
}
size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array)
		return CERO;
	size_t elementos_recorridos = 0;
	void *aux[3] = { array, &tamanio_array, &elementos_recorridos };
	abb_con_cada_elemento(arbol, recorrido, almacenar_elemento, aux);

	return elementos_recorridos;
}