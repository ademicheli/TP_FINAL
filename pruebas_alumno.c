#include "pa2m.h"
#include "src/tp.h"
#include "src/utils.h"
void prueba_simple()
{
	int i = 14;
	int j = 18;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

void prueba_creacion_tp()
{
	pa2m_afirmar(tp_crear("asdgioqjr") == NULL,
		     "Pruebo crear un TP con archivo de formato incorrecto");
	pa2m_afirmar(tp_crear("") == NULL, "Pruebo crear un TP sin archivo 1");
	pa2m_afirmar(tp_crear(NULL) == NULL,
		     "Pruebo crear un TP sin archivo 1");
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "Pruebo crear un TP con el archivo de ejemplo");
	pa2m_afirmar(tp_cantidad_pokemon(tp) == 125,
		     "La cantidad de pokemones es 125");
	tp_destruir(tp);
}
void prueba_tiempo_obstaculos()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(
		tp_calcular_tiempo_pista(tp, JUGADOR_1) == 0,
		"No puedo calcular el tiempo por obstáculo si no hay pokemon seleccionado");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Caterpie"),
		     "Puedo seleccionar a Caterpie para el jugador 1");

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Dragonite"),
		     "Puedo seleccionar a Dragonite para el jugador 2");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Dragonite") == false,
		     "No puedo seleccionar a Caterpie para el jugador 1 (porque el jugador 2 lo tiene)");
	pa2m_afirmar(
		tp_calcular_tiempo_pista(tp, JUGADOR_1) == 0,
		"No puedo calcular el tiempo por obstáculo si no hay pista disponible");
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 1);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 2);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 4);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 5);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 6);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 7);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 8);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 8);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 1);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_FUERZA, 2);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 4);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 5);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 6);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 7);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 8);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 8);

	char *pista_jugador = tp_obstaculos_pista(tp, JUGADOR_1);
	char *obstaculos_pista_caterpie = "IFDDDDII";
	pa2m_afirmar(strcmp(pista_jugador, obstaculos_pista_caterpie) == 0,
		     "Puedo obtener los obstaculos de la pista del jugador 1");
	free(pista_jugador);
	pista_jugador = tp_obstaculos_pista(tp, JUGADOR_2);
	char *obstaculos_pista_dragonite = "IFDDDDII";
	pa2m_afirmar(strcmp(pista_jugador, obstaculos_pista_dragonite) == 0,
		     "Puedo obtener los obstaculos de la pista del jugador 2");
	free(pista_jugador);

	const unsigned caterpie_tiempos = 36;
	char *caterpie_pista = "9,7,2,1,0,0,9,8";

	char *string_caterpie = tp_tiempo_por_obstaculo(tp, JUGADOR_1);
	pa2m_afirmar(
		strcmp(string_caterpie, caterpie_pista) == 0,
		"Puedo calcular los tiempos de obstáculos para Caterpie (9,7,2,1,0,0,9,8)");

	free(string_caterpie);

	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_1) ==
			     caterpie_tiempos,
		     "El tiempo de Caterpie es el correcto");

	const unsigned dragonite_tiempos = 6;
	char *dragonite_pista = "2,1,0,0,0,0,2,1";

	char *string = tp_tiempo_por_obstaculo(tp, JUGADOR_2);
	if (string) {
		pa2m_afirmar(
			strcmp(string, dragonite_pista) == 0,
			"Puedo ver los tiempos de obstáculos para Dragonite (2,1,0,0,0,0,2,1)");
		free(string);
	}
	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_2) ==
			     dragonite_tiempos,
		     "El tiempo de Dragonite es el correcto");

	tp_destruir(tp);
}

void prueba_pistas()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
    char *string_g = tp_obstaculos_pista(tp,JUGADOR_1);
    pa2m_afirmar(string_g == NULL, "Inicialmente no hay obstaculos en la pista del jugador 1");
    pa2m_afirmar(tp_agregar_obstaculo(tp,JUGADOR_1,OBSTACULO_FUERZA,0) > 0,"Puedo agregar un obstaculo de fuerza al jugador 1 en la poscion 0 F");
    pa2m_afirmar(tp_agregar_obstaculo(tp,JUGADOR_1,OBSTACULO_DESTREZA,0) > 0,"Puedo agregar un obstaculo de destreza al jugador 1 en la poscion 0 DF");
    pa2m_afirmar(tp_agregar_obstaculo(tp,JUGADOR_1,OBSTACULO_INTELIGENCIA,4) > 0,"Puedo agregar un obstaculo de destreza al jugador 4 en la poscion 0 DFI");
    string_g = tp_obstaculos_pista(tp,JUGADOR_1);
    pa2m_afirmar(strcmp(string_g,"DFI") == 0 , "Son correctas las inserciones ");
    free(string_g);
    pa2m_afirmar(tp_quitar_obstaculo(tp,JUGADOR_1,0) == 2, "Pude quitar un obstaculo de la pista");
    tp_limpiar_pista(tp,JUGADOR_1);
    pa2m_afirmar(tp_obstaculos_pista(tp,JUGADOR_1) == NULL,"Pude limpiar la pista del jugador 1");
    tp_destruir(tp);
}
int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();
	pa2m_nuevo_grupo("\nprueba de creacion de TP");
	prueba_creacion_tp();
	pa2m_nuevo_grupo("\nprueba de tiempo de TP");
	prueba_tiempo_obstaculos();
	pa2m_nuevo_grupo("\nprueba de pista de TP");
    prueba_pistas();
	return pa2m_mostrar_reporte();
}
