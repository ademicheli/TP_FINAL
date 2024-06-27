#include "./utils.h"
#define CANTIDAD_OBSTACULOS_MODO_FACIL 3
#define CANTIDAD_OBSTACULOS_MODO_NORMAL 6
#define CANTIDAD_OBSTACULOS_MODO_DIFICIL 9
#define CANTIDAD_OBSTACULOS_MODO_IMPOSIBLE 12
#define CAMPOS_ARCHIVO_VALIDO 4
#define NOMBRE_POKEMON 1
#define FUERZA_POKEMON 2
#define DESTREZA_POKEMON 3
#define INTELIGENCIA_POKEMON 4
#define LINEA_SIZE 256


void str_tolower(char *str)
{
	for (int i = 0; str[i]; i++) {
		str[i] = (char)tolower(str[i]);
	}
}

bool nombre_archivo_valido(const char *nombre_archivo)
{
	int longitud_formato = 4;
	char formato_aceptado[] = ".txt";

	int longitud_nombre_archivo = (int)strlen(nombre_archivo);

	if (longitud_nombre_archivo < longitud_formato) {
		return false;
	}
	for (int i = 0; i < longitud_formato; i++) {
		if (formato_aceptado[i] !=
		    nombre_archivo[longitud_nombre_archivo - longitud_formato +
				   i]) {
			return false;
		}
	}
	return true;
}
bool campo_valido(const char *campo, int indice)
{
	if (indice == NOMBRE_POKEMON) {
		return strlen(campo) > 0;
	}
	return campo != NULL;
}
bool validar_linea(char *linea)
{
	char *campo;
	int indice_campos = 0;
	campo = strtok(linea, ",");
	while (campo) {
		indice_campos++;
		if (!campo_valido(campo, indice_campos)) {
			return false;
		}
		campo = strtok(NULL, ",");
	}
	return indice_campos == CAMPOS_ARCHIVO_VALIDO;
}

bool contiene_formato_correcto(const char *nombre_archivo)
{
	if (!nombre_archivo) {
		return false;
	}
	if (!nombre_archivo_valido(nombre_archivo)) {
		return false;
	}
	FILE *archivo_a_leer = fopen(nombre_archivo, "r");
	if (!archivo_a_leer) {
		return false;
	}
	char linea[LINEA_SIZE];
	while (fgets(linea, sizeof(linea), archivo_a_leer)) {
		if (!validar_linea(linea)) {
			fclose(archivo_a_leer);
			return false;
		}
	}
	fclose(archivo_a_leer);
	return true;
}
