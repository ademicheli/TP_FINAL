#include "src/tp.h"
#include "src/menu.h"
#include <time.h>
#include <math.h>

#define TAMANIO_LINEA 100
#define ETAPA_INICIAL 0
#define ETAPA_SELECCION_POKEMON 1
#define ETAPA_CREACION_PISTA 2
#define ETAPA_CARRERA 3
#define ETAPA_REINTENTAR_CARRERA 4
#define ETAPA_FINAL 5

enum DIFICULTAD { 	FACIL,
					NORMAL,
					DIFICIL,
					IMPOSIBLE
				};

typedef struct estado{
	int etapa;
	int dificultad;
	int intentos_posibles;
	char *archivo;
	bool escape;
	TP *tp;
}estado_t;


bool inicio_visible_juego(void *contexto)
{	
	estado_t *estado = (estado_t*)contexto;
	if(estado->etapa == ETAPA_INICIAL)
		return true;
	return false;
}

bool visible(void *contexto)
{	

	return true;
}
bool siempre_visible(void *contexto)
{
	estado_t *estado = (estado_t*)contexto;
	return estado->etapa >= 0;
}

bool seleccionar_pokemon_visible(void *contexto)
{
	estado_t *estado = (estado_t*)contexto;
	if(estado->etapa == ETAPA_SELECCION_POKEMON)
		return true;
	return false;
}


void mostrar_pista_computadora(char *string)
{
	if(string){
		for(int i = 0; i  < strlen(string);i++){
			if(i % 2 == 0){
				string[i] = '?';
			}
		}
		printf("\nLa pista de tu rival tiene %li obstaculos, algunos estan escondidos detras de ? pero esperamos que estos te sirva de ayuda: %s \n",strlen(string),string);
		free(string);
	}
		
}


void asignar_pokemon_computadora(estado_t *estado)
{
	if(estado){

		char *listado_pokemones = tp_nombres_disponibles(estado->tp);
		const char *nombre = NULL;
		int cantidad_pokemones = tp_cantidad_pokemon(estado->tp);

		int indice_random = rand() % cantidad_pokemones;
        nombre = strtok(listado_pokemones, ",");
		for(int i = 0;i < indice_random; i++){
	        nombre = strtok(NULL, ",");
		}
		if (tp_seleccionar_pokemon(estado->tp, JUGADOR_1, nombre)) {

			printf("\n¡MIRA! El pokemon de tu rival es %s \n",nombre);
            free(listado_pokemones);
		}
	}
}

void crear_pista_por_dificultad(estado_t *estado)
{
	switch (estado->dificultad)
	{
	case FACIL:
            for (int i = 0; i < 12; i++) {
                tp_agregar_obstaculo(estado->tp, JUGADOR_1, rand() % 3, 0);
            }
            estado->intentos_posibles = 6;
		break;
	case NORMAL:
            for (int i = 0; i < 9; i++) {
                tp_agregar_obstaculo(estado->tp, JUGADOR_1, rand() % 3, 0);
            }
            estado->intentos_posibles = 4;

		break;
	case DIFICIL:
            for (int i = 0; i < 6; i++) {
                tp_agregar_obstaculo(estado->tp, JUGADOR_1, rand() % 3, 0);
            }
            estado->intentos_posibles = 3;

		break;
	case IMPOSIBLE:
            for (int i = 0; i < 3; i++) {
                tp_agregar_obstaculo(estado->tp, JUGADOR_1, rand() % 3, 0);
            }
            estado->intentos_posibles = 2;

	default:
		break;
	}
	char *string = tp_obstaculos_pista(estado->tp,JUGADOR_1);
	mostrar_pista_computadora(string);
}
int jugar(void *e)
{
	printf("\nEl juego ha iniciado\n");
	struct estado *estado = (struct estado *)e;
	estado->tp = tp_crear(estado->archivo);
	estado->etapa ++;
    printf("\nSelecciona una dificultad por su numero:\n");
    printf("1. Facil\n");
    printf("2. Normal\n");
    printf("3. Dificil\n");
    printf("4. Imposible\n");

    char entrada[100];
    int opcion_dificultad;

    while (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strlen(entrada)-1] = '\0'; 
        if (sscanf(entrada, "%d", &opcion_dificultad) == 1) {
            switch (opcion_dificultad) {
                case 1:
                    estado->dificultad = FACIL;
                    break;
                case 2:
                    estado->dificultad = NORMAL;
                    break;
                case 3:
                    estado->dificultad = DIFICIL;
                    break;
                case 4:
                    estado->dificultad = IMPOSIBLE;
                    break;
                default:
                    printf("Opcion de dificultad invalida, intentalo de nuevo\n");
                    continue; 
            }


            crear_pista_por_dificultad(estado);
			asignar_pokemon_computadora(estado);
			printf("¡Ahora es tu turno!");
            break; 
        } else {
            printf("Entrada invalida, intentalo de nuevo\n");
        }
    }
	return 1;
}


int salir(void *e)
{
    printf("¡Te retiraste del estadio, fin del juego!\n");

	struct estado *estado = (struct estado *)e;
    if(estado->tp){
        tp_destruir(estado->tp);
    }
	estado->escape = true;
	return estado->etapa;
}

int seleccion_pokemon(void *contexto)
{
	struct estado *estado = (struct estado *)contexto;
	printf("\n\nSelecciona tu Pokemon, aqui puedes ver nuestra pokedex :\n");
	char *lista_pokemones = tp_nombres_disponibles(estado->tp);
	printf("\n %s\n \n",lista_pokemones);
	free(lista_pokemones);
	char pokemon_elegido[50];
  
    while (fgets(pokemon_elegido, sizeof(pokemon_elegido), stdin) != NULL) {
        pokemon_elegido[strlen(pokemon_elegido)-1] = '\0';
        if (tp_seleccionar_pokemon(estado->tp, JUGADOR_2, pokemon_elegido)) {
			printf("\n \nHas elegido a %s , gran eleccion!\n\n",pokemon_elegido);
			printf("\n Ahora puedes armar tu pista !");

            estado->etapa++;
            break;
        }

        printf("Selecciona un Pokemon valido:\n");
    }
	return 1;
}

bool armar_pista_visible(void *contexto)
{
	estado_t *estado = (estado_t *)contexto;
	return estado->etapa == ETAPA_CREACION_PISTA;
}

int armar_pista(void *contexto) {
    estado_t *estado = (estado_t *)contexto;
    int tipo_obstaculo;
    char respuesta[4];
    int leidos;

    printf("\nIntroduce el tipo de obstáculo (0 = fuerza, 1 = destreza, 2 = inteligencia): ");
    leidos = scanf("%d", &tipo_obstaculo);
    while (leidos != 1 || tipo_obstaculo < 0 || tipo_obstaculo > 2) {
        printf("obstaculo invalida. Introduce el tipo de obstaculo valido (0 = fuerza, 1 = destreza, 2 = inteligencia): ");
        while (getchar() != '\n');
        leidos = scanf("%d", &tipo_obstaculo);
    }
    tp_agregar_obstaculo(estado->tp, JUGADOR_2, tipo_obstaculo, 0);
    
    while (1) {
        printf("¿Quieres añadir otro obstáculo? (si/no): ");
        leidos = scanf("%3s", respuesta);
        while (leidos != 1 || (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0)) {
            printf("obstaculo invalido \n¿Quieres añadir otro obstáculo? (si/no): ");
            while (getchar() != '\n');
            leidos = scanf("%3s", respuesta);
        }
        if (strcmp(respuesta, "no") == 0) {
            break;
        }
        printf("Introduce el tipo de obstaculo (0 = fuerza, 1 = destreza, 2 = inteligencia): ");
        leidos = scanf("%d", &tipo_obstaculo);
        while (leidos != 1 || tipo_obstaculo < 0 || tipo_obstaculo > 2) {
            printf("obstaculo invalido  \nIntroduce el tipo de obstáculo (0 = fuerza, 1 = destreza, 2 = inteligencia): ");
            while (getchar() != '\n');
            leidos = scanf("%d", &tipo_obstaculo);
        }
        tp_agregar_obstaculo(estado->tp, JUGADOR_2, tipo_obstaculo, 0);
    }
    
    char *pista_creada = tp_obstaculos_pista(estado->tp, JUGADOR_2);
    printf("\nEsta es tu pista: %s\n", pista_creada);
    estado->etapa++;
    free(pista_creada);
    getchar(); 

    return 0;
}

int correr_carrera(void * contexto)
{
    estado_t *estado = (estado_t *)contexto;
    unsigned int tiempo_rival = tp_calcular_tiempo_pista(estado->tp, JUGADOR_1);
    unsigned int tiempo_jugador = tp_calcular_tiempo_pista(estado->tp, JUGADOR_2);
    printf("\nQue carreron!! tiempo rival : %i  tu tiempo : %i \n",tiempo_rival,tiempo_jugador);

    double puntaje = 100 - 100 * fabs(tiempo_rival - tiempo_jugador) / (tiempo_rival + tiempo_jugador);
    
    if(puntaje < 0)
        puntaje = 0.0f;
    if(estado->intentos_posibles  > 0){
        printf("\nTras un largo esfuerzo de tu pokemon, has obtenido este puntaje: %.2f\n", puntaje);
        printf("Puedes mejorarlo, te quedan %i veces si no te conformas con eso! \n",estado->intentos_posibles);
        estado->intentos_posibles --;
        estado->etapa ++;
        return 0;
    }
    printf("\n Ups ! Tu pokemon ya no tiene energía para correr, debe descansar, prueba más tarde !Hasta lueguito!");
    printf("\n Tu puntaje final es: %.2f\n", puntaje);
    estado->etapa = ETAPA_FINAL;
    return 0;

}

bool modificar_pista_visible(void *contexto)
{   
        if(contexto){
        estado_t *estado = (estado_t *)contexto;
        return estado->etapa == ETAPA_REINTENTAR_CARRERA;
        }
        return false;
}

int modificar_pista(void *contexto)
{
    estado_t *estado = (estado_t *)contexto;

    int opcion;
    do {
        printf("Pista actual del jugador:\n");
        char *pista_actual = tp_obstaculos_pista(estado->tp, JUGADOR_2);
        printf("%s\n", pista_actual);
        free(pista_actual);
        printf("Seleccione una opcion:\n");
        printf("1. Añadir obstaculo\n");
        printf("2. Quitar obstaculo\n");
        printf("3. Terminar modificación\n");

        if (scanf("%d", &opcion) != 1) {
            fprintf(stderr, "Error: entrada invalida.\n");
            getchar(); 

        }
        getchar(); 

        switch (opcion)
        {
        case 1:
            printf("Introduce el tipo de obstaculo (0 = fuerza, 1 = destreza, 2 = inteligencia): ");
            int tipo;
            if (scanf("%d", &tipo) != 1) {
                fprintf(stderr, "Error: obstaculo invalida\n");
                return -1;
            }
            getchar();
            tp_agregar_obstaculo(estado->tp, JUGADOR_2, tipo, 0);
            printf("Obstaculo añadido!\n");
            break;
        case 2:
            printf("Introduce la posición del obstáculo a quitar: ");
            int posicion;
            if (scanf("%d", &posicion) != 1) {
                fprintf(stderr, "Error: posicioon invalida\n");
                return -1;
            }
            getchar();
            tp_quitar_obstaculo(estado->tp, JUGADOR_2, (unsigned int)posicion);
            printf("Obstaculo en la posicion %d quitado!\n", posicion);
            break;
        case 3:
            printf("Modificación de pista finalizada\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 3); 

    estado->etapa--;
    return 0;
}
bool correr_carrera_visible( void *contexto){
    if(contexto){
    estado_t *estado = (estado_t*)contexto;
    return estado->etapa == ETAPA_CARRERA;
    }
    return false;
}

int main(int argc, char const *argv[]) {


	//Se recomienda pasar el archivo de texto con los pokemon como argumento al ejecutar el programa
    

    srand((unsigned int)time(NULL));
	menu_t *menu = menu_crear();
	estado_t estado = { .etapa = 0, .escape = false, .tp = NULL, .dificultad = 0, .intentos_posibles = 0,.archivo ="ejemplo/pokemones.txt" };


    struct menu_opcion opcion_jugar = {
        .clave = "jugar",
        .descripcion = "Inicia el juego de carrera Pokémon",
        .funcion = jugar,
        .visible = inicio_visible_juego
    };

    struct menu_opcion opcion_ayuda = {
        .clave = "ayuda",
        .descripcion = "Muestra la ayuda del juego",
        .funcion = NULL,  
        .visible = NULL   
    };

    struct menu_opcion opcion_salir = {
        .clave = "salir",
        .descripcion = "Finaliza el juego y termina la ejecución",
        .funcion = salir,
        .visible = siempre_visible,
    };

    struct menu_opcion opcion_elegir_pokemon = {
        .clave = "seleccionar pokemon",
        .descripcion = "Selecciona la dificultad del juego",
        .funcion = seleccion_pokemon,
        .visible = seleccionar_pokemon_visible 
    };

    struct menu_opcion opcion_crear_pista = {
        .clave = "crear pista",
        .descripcion = "Crea la pista de obstaculos",
        .funcion = armar_pista,
        .visible = armar_pista_visible  
    };

    struct menu_opcion opcion_correr_carrera = {
        .clave = "correr",
        .descripcion = "Corre la carrera de obstaculos",
        .funcion = correr_carrera,
        .visible = correr_carrera_visible  
    };

    struct menu_opcion opcion_reintentar = {
        .clave = "reintentar carrera",
        .descripcion = "Reintenta la carrera para mejorar el puntaje",
        .funcion = modificar_pista, 
        .visible = modificar_pista_visible 
    };
    menu_agregar_funcion(menu, opcion_jugar);
    menu_agregar_funcion(menu, opcion_ayuda);
    menu_agregar_funcion(menu, opcion_elegir_pokemon);
    menu_agregar_funcion(menu, opcion_crear_pista);
    menu_agregar_funcion(menu, opcion_correr_carrera);
    menu_agregar_funcion(menu, opcion_reintentar);
    menu_agregar_funcion(menu, opcion_salir);

    char respuesta[TAMANIO_LINEA];

    printf("Bienvenido a las CARRERAS POKEMON (presiona cualquier tecla para iniciar)");
    while (!estado.escape && fgets(respuesta, TAMANIO_LINEA, stdin) != NULL) {
        respuesta[strlen(respuesta)-1] = '\0'; 
        menu_funcion(menu, respuesta, &estado);

        if (!estado.escape) {
            printf("\nSelecciona una opción:\n");
            menu_mostrar(menu, &estado);
        }
    }

    menu_destruir(menu);

    return 0;
}