
#include "menu.h"

struct menu{
	lista_t *opciones;
};
menu_t *menu_crear(){
	menu_t *menu = calloc(1,sizeof(menu_t));
	if(!menu)
		return NULL;
	menu->opciones = lista_crear();
	if(!menu->opciones){
		free(menu);
		return NULL;
	}
	return menu;
}

struct menu_opcion *copiar_opcion(struct menu_opcion opcion)
{
	struct menu_opcion *copia_de_opcion  = malloc(sizeof(struct menu_opcion));
	if(copia_de_opcion){
		memcpy(copia_de_opcion,&opcion,sizeof(struct menu_opcion));
		return copia_de_opcion;
	}
	return NULL;
}

menu_t *menu_agregar_funcion(menu_t *menu, struct menu_opcion opcion){
	if(menu){
		lista_insertar(menu->opciones,copiar_opcion(opcion));
		return menu;
	}
	return NULL;
}
void modificar_opcion(menu_t *menu, char* clave)
{

}

int menu_funcion(menu_t *menu, char *clave, void *contexto)
{
	for(size_t i = 0; i < lista_tamanio(menu->opciones);i++){
		struct menu_opcion *opcion_actual = (struct menu_opcion *)lista_elemento_en_posicion(menu->opciones,i);
		if(!opcion_actual->visible || !opcion_actual->funcion)
			continue;

		if(strcmp(opcion_actual->clave,clave) == 0 && opcion_actual->visible(contexto)){
			return opcion_actual->funcion(contexto);
		}
	}
	return ERROR_OPCION;
}


bool mostrar_opcion(void *opcion, void *contexto)
{
	struct menu_opcion *opcion_del_menu = (struct menu_opcion *)opcion;
	if(opcion_del_menu->visible && opcion_del_menu->visible(contexto))
		printf("\t%s \n", opcion_del_menu->clave);
	return true;
}

menu_t *menu_mostrar(menu_t *menu, void *contexto)
{
	if(menu){
		lista_con_cada_elemento(menu->opciones,mostrar_opcion,contexto);
	}
	return NULL;
}

bool mostrar_ayuda(void *opcion, void *contexto)
{
	struct menu_opcion *opcion_del_menu = (struct menu_opcion *)opcion;
	printf("\t%s \t%s \n", opcion_del_menu->clave, opcion_del_menu->descripcion);
	return true;
}
void menu_mostrar_ayuda(menu_t* menu){
	if(menu){
		lista_con_cada_elemento(menu->opciones,mostrar_ayuda,NULL);
	}
}

void destructora_de_opciones(void *opcion){
	if(opcion){
		free(opcion);
	}
	return;
}

void menu_destruir(menu_t *menu)
{
	if(menu){
		lista_destruir_todo(menu->opciones,destructora_de_opciones);
		free(menu);
	}
	return;
}