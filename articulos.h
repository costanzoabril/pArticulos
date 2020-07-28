#ifndef ARTICULOS_H_INCLUDED
#define ARTICULOS_H_INCLUDED
#include "LinkedList.h"

typedef struct
{
    int id;
    char nombre[15];
    float precio;
    int medida;
    int rubroId;
}eArticulo;

/** \brief Imprime la lista de articulos
 * \param LinkedList* lista
 * \return 0 en caso de exito, 1 en caso de error
 */
int mostrarArticulos(LinkedList* lista);

/** \brief Imprime un articulo recibiendo su puntero como param
 * \param eArticulo* pArticulo
 * \return 0 en caso de exito, 1 en caso de error
 */
int mostrarArticulo(eArticulo* pArticulo);

/** \brief Carga los datos de un archivo csv
 * \param LinkedList* lista
 * \param char* path
 * \return 0 en caso de exito, 1 en caso de error
 */
int cargarArticulosCSV(LinkedList* lista, char* path);

/** \brief Crea un nuevo articulo recibiendo informacion como parametros
 * \param
 * \param
 * \param
 * \param
 * \return puntero al nuevo articulo
 */
eArticulo* articulo_newParamS(char* id, char* nombre, char* precio, char*medida, char* idRubro);

/** \brief Guarda los datos en un archivo csv en forma de texto
 * \param LinkedList* lista
 * \param char* path
 * \return 0 en caso de exito, 1 en caso de error
 */
int guardarCSV(LinkedList* lista, char* path);

/** \brief Asigna un id validado
 * \param eArticulo* this
 * \param int id
 * \return 0 en caso de exito, 1 en caso de error
 */
int articulo_setId(eArticulo* this, int id);

/** \brief Accede al campo id
 * \param eArticulo* this
 * \param int* id
 * \return 0 en caso de exito, 1 en caso de error
 */
int articulo_getId(eArticulo* this, int* id);
int articulo_setNombre(eArticulo* this,char* nombre);
int articulo_getNombre(eArticulo* this,char* nombre);
int articulo_setPrecio(eArticulo* this, float precio);
int articulo_getPrecio(eArticulo* this, float* precio);
int articulo_setMedida(eArticulo* this, int medida);
int articulo_getMedida(eArticulo* this, int* medida);
int articulo_setIdRubro(eArticulo* this, int idRubro);
int articulo_getIdRubro(eArticulo* this, int* idRubro);

/** \brief Ordena segun el nombre
 * \param void* aux1
 * \param void* aux2
 * \return 0 en caso de ser iguales, 1 si el aux1 es mayor, o -1 si el aux2 es mayor
 */
int sortByName(void* aux1, void* aux2);

/** \brief Realiza descuento a los elementos que cumplen con el criterio
 * \param void* articulo
 * \return void
 */
void* map_descuento(void* articulo);



#endif // ARTICULOS_H_INCLUDED
