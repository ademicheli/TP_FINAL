#ifndef MENU_H
#define MENU_H

#include "tp.h"
#include "lista.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ERROR_OPCION -1

typedef struct menu menu_t;

struct menu_opcion
{
    const char *clave;
    const char *descripcion;
    int (*funcion)(void*);
    bool (*visible)(void*);
};
 

/**
 * Crea un menu,
 * devuelve un puntero a una esctructura menu,
 * o NULL en caso de error
 */
menu_t *menu_crear();

/**
 * Dado un menú,
 * libera la memoria pedida por el mismo
 */
void menu_destruir(menu_t *menu);


/**
 * Dado un menu y una clave,descripcion y una funcion que devuelve 
 * un entero, menu_agregar_funcion añade al menu dicha funcion y devuelve
 * el menú o NULL en caso de error
 */
menu_t *menu_agregar_funcion(menu_t *menu, struct menu_opcion opcion);


/**
 * Dado un menu y una clave,
 * modifica la descripcion del menu,
 * o no se realiza la modificacion nada en caso de error
 */
void modificar_opcion(menu_t *menu, char* clave);

/**
 * Dado un menu y una clave,
 * ejecuta la función correspondiente a dicha clave,
 * devuelve el retorno de la función,
 * o un valor definido incorrecto en caso de error
 */
int menu_funcion(menu_t *menu, char *clave, void *contexto);

/**
 * Dado un menu,
 * se muestra y devuelve el menu,
 * o NULL en caso de error
 */
menu_t *menu_mostrar(menu_t *menu,void *contexto);

/**
 * Dado un menu,
 * esta funcion muestra por pantalla las funciones que contiene,
 * y la descripción,
 * o no muestra nada en caso de error
 */
void menu_mostrar_ayuda(menu_t* menu);

#endif // MENU_H