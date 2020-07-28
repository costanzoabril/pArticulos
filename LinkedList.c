#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* newList;

    newList = (LinkedList*) malloc(sizeof(LinkedList));
    if(newList != NULL)
    {
        newList->size = 0;
        newList->pFirstNode = NULL;
    }
    return newList;
}


/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int cant = -1;

    if(this != NULL)
    {
        cant = this->size;
    }
    return cant;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        pNode = this->pFirstNode;

        if(nodeIndex > 0)
        {
            for(int i=0; i<nodeIndex; i++)
            {
                pNode = pNode->pNextNode;
            }
        }
    }
    return pNode;
}


/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int retorno = -1;
    Node* newNode;
    Node* anterior;

    if(this != NULL && nodeIndex >=0 && nodeIndex <= ll_len(this))
    {
        newNode = (Node*) malloc(sizeof(Node));

        if(newNode != NULL)
        {
            newNode->pElement = pElement;
            newNode->pNextNode = NULL;

            if(nodeIndex == 0)
            {
                newNode ->pNextNode = this->pFirstNode;
                this->pFirstNode = newNode;
            }
            else
            {
                anterior = getNode(this, nodeIndex - 1);
                newNode->pNextNode = anterior->pNextNode;
                anterior->pNextNode = newNode;
            }

            this->size++;
            retorno = 0;
        }
    }
    return retorno;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    return addNode(this, ll_len(this), pElement);
    //addNode ya valida this y devuelve 0 o -1
}


/** \brief Retorna un puntero al elemento que se encuentra en el indice especificado
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* pElement = NULL;
    Node* pNode;

    pNode = getNode(this, index);
    //getNode ya valida this y el index
    if(pNode != NULL)
    {
        pElement = pNode->pElement;
    }
    return pElement;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int retorno = -1;
    Node* pNode;

    pNode = getNode(this, index);

    if(pNode != NULL)
    {
        pNode->pElement = pElement;
        retorno = 0;
    }
    return retorno;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int retorno = -1;
    Node* pNode;
    Node* pLastNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        pNode = getNode(this, index);
        if(pNode != NULL)
        {
            if(index == 0)
            {
                this->pFirstNode = pNode->pNextNode;
                free(pNode);
                this->size--;
                retorno = 0;
            }
            else
            {
                pLastNode = getNode(this, index -1);
                if(pLastNode != NULL)
                {
                    pLastNode->pNextNode = pNode->pNextNode;
                    free(pNode);
                    this->size--;
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int retorno = -1;

    if(this != NULL)
    {
        while(ll_len(this) != 0)
        {
            ll_remove(this, 0);
        }
        retorno = 0;
    }
    return retorno;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int retorno = -1;

	if (this != NULL && ll_clear(this) ==0)
	{
		free(this);
		retorno = 0;
	}
    return retorno;
}


/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int retorno = -1;
    Node* pNode;

    if(this != NULL)
    {
        for(int i = 0; i<ll_len(this); i++)
        {
            pNode = getNode(this, i);

            if(pNode != NULL && pNode->pElement == pElement)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}


/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int retorno = -1;

    if(this != NULL)
    {
        retorno = 1;

        if(ll_len(this))
        {
            retorno = 0;
        }
    }
    return retorno;
}


/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement);
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* pElement = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        pElement = ll_get(this, index);
        if(ll_remove(this, index) == -1)
        {
            pElement = NULL;
        }
    }
    return pElement;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int retorno = -1;

    if(this != NULL)
    {
        retorno = 0;

        if(ll_indexOf(this, pElement) >= 0)
        {
            retorno = 1;
        }
    }
    return retorno;
}


/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int retorno = -1;

    if(this != NULL && this2 != NULL)
    {
        retorno = 1;
        for(int i=0; i<ll_len(this2); i++)
        {
            if(!ll_contains(this, ll_get(this2, i)))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}


/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(!(this == NULL || from <0 || from > ll_len(this) || to <= from || to > ll_len(this)))
    {
        cloneArray = ll_newLinkedList();

    	if(cloneArray != NULL)
    	{
    		for(int i = from; i < to; i++)
			{
				ll_add(cloneArray, ll_get(this, i));
			}
    	}
    }
    return cloneArray;
}


/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    return ll_subList(this, 0, ll_len(this));
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int retorno = -1;
    void* auxElement;
    int tam;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
        tam = ll_len(this);

        for(int i=0; i<tam; i++)
        {
            for(int j=i+1; j<tam; j++)
            {
                if(((pFunc(ll_get(this, i), ll_get(this, j)) >0 && order)) || (pFunc(ll_get(this, i), ll_get(this, j)) <0 && !order))
                {
                    auxElement = ll_get(this, i);
                    ll_set(this, i, ll_get(this, j));
                    ll_set(this, j, auxElement);
                }
            }
        }
        retorno = 0;
    }
    return retorno;
}

/** \brief Filtra los datos segun la funcion que se le pase
 * \param LinkedList* this Puntero a la lista
 * \param int (*pFunc)(void*) Funcion de criterio para filtrar
 * \return listaFiltrada
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
    LinkedList* listaFiltrada = NULL;
    void* auxElement = NULL;

    if(this != NULL && pFunc != NULL)
    {
        listaFiltrada = ll_newLinkedList();

        if(listaFiltrada != NULL)
        {
            for(int i=0; i<ll_len(this); i++)
            {
                auxElement = (ll_get(this, i));
                if(pFunc(auxElement))
                {
                    ll_add(listaFiltrada, auxElement);
                }
            }
        }
    }
    return listaFiltrada;
}

/** \brief Ejecuta la funcion pasada por parametro en cada elemento de la lista
 * \param LinkedList* this Puntero a la lista
 * \param void (*pFunc)(void*) Funcion de criterio
 * \return listaMapeada
 */
LinkedList* ll_map(LinkedList* this, void* (*pFunc)(void*))
{
    LinkedList* listaMapeada = NULL;
    void* auxElement = NULL;

    if(this != NULL && pFunc != NULL)
    {
        listaMapeada = ll_newLinkedList();

        if(listaMapeada != NULL)
        {
            for(int i=0; i<ll_len(this); i++)
            {
                auxElement = (ll_get(this, i));
                auxElement = pFunc(auxElement);

                if(auxElement != NULL)
                {
                   ll_add(listaMapeada, auxElement);
                }
            }
        }
    }
    return listaMapeada;
}
