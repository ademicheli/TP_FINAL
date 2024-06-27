#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "./abb.h"
#include "./lista.h"
#include <ctype.h>

#define CAMPOS_ARCHIVO_VALIDO 4
#define NOMBRE_POKEMON 1
#define FUERZA_POKEMON 2
#define DESTREZA_POKEMON 3
#define INTELIGENCIA_POKEMON 4
#define LINEA_SIZE 256
#define ERROR_OBSTACULOS 0


/**
 * Dado un string* ,
 * transforma el string a minusculas
 */
void str_tolower(char *str);
/**
 * Dado un nombre de archivo ,
 * devuelve true si el nombre es valido o false en caso de error
 */
bool nombre_archivo_valido(const char *nombre_archivo);
/**
 * Dado un campo y un indice,
 * devuelve true si el campo es válido o false en caso de error
 */
bool campo_valido(const char *campo, int indice);
/**
 * Dada una linea, 
 * valida que tenga el formato adecuado
 * devuelve true si el formato es válido o false en caso de error
 */
bool validar_linea(char *linea);
/**
 * Dado un archivo,
 * procesa la informacion del mismo y
 * devuelve true en caso de pasar todas las validaciones
 * o false en caso de error
 */
bool contiene_formato_correcto(const char *nombre_archivo);

#endif