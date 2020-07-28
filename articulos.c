#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articulos.h"
#define NOMBRE_TAM 15

int mostrarArticulos(LinkedList* lista)
{
    int retorno = 1;
	int tam;
	eArticulo* pArticulo;

	if(lista != NULL)
	{
	    tam = ll_len(lista);

		printf("\n  ID    Articulo     Precio   Medida      Rubro\n\n");

		for(int i =0; i<tam; i++)
		{
		    pArticulo = (eArticulo*)ll_get(lista,i);
			if(pArticulo != NULL)
			{
				mostrarArticulo(pArticulo);
				retorno = 0;
			}
		}
        printf("\n\n");
	}
	return retorno;
}

int mostrarArticulo(eArticulo* pArticulo)
{
    int retorno = 1;
    int auxId;
    char auxNombre[15];
    float auxPrecio;
    int auxMedida;
    int auxIdRubro;
    char rubro[40];

    if(!articulo_getId(pArticulo, &auxId)
    && !articulo_getNombre(pArticulo, auxNombre)
    && !articulo_getPrecio(pArticulo, &auxPrecio)
    && !articulo_getMedida(pArticulo, &auxMedida)
    && !articulo_getIdRubro(pArticulo, &auxIdRubro))
    {
        if(auxIdRubro == 1)
        {
            strcpy(rubro, "Cuidado de ropa.");
        }
        else if(auxIdRubro == 2)
        {
            strcpy(rubro, "Limpieza y desinfecion.");
        }
        else if(auxIdRubro == 3)
        {
            strcpy(rubro, "Cuidado personal e higiene.");
        }
        else if(auxIdRubro == 4)
        {
            strcpy(rubro, "Cuidado del automotor.");
        }
        printf("%3d   %12s   %8.2f    %3d    %-30s  \n", auxId, auxNombre, auxPrecio, auxMedida, rubro);
        retorno = 0;
    }
    else
    {
        printf("\nError");
    }
    return retorno;
}

int cargarArticulosCSV(LinkedList* lista, char* path)
{
    int retorno = 1;
    char buffer[5][30];
    int cant;
    eArticulo* aux;

    FILE* f;
    f = fopen(path, "r");

    if(f != NULL)
    {
        fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
        while(!feof(f))
        {
            cant = fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

            if (cant == 5)
            {
                aux = articulo_newParamS(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
                if(aux != NULL)
                {
                    ll_add(lista, aux);
                    retorno = 0;
                }
            }
            else
            {
                break;
            }
        }
    }
    fclose(f);
    return retorno;
}

eArticulo* articulo_newParamS(char* id, char* nombre, char* precio, char*medida, char* idRubro)
{
    eArticulo* nuevo = (eArticulo*) malloc(sizeof(eArticulo));

	if(nuevo != NULL)
	{
		if(    articulo_setId(nuevo, atoi(id))
            || articulo_setNombre(nuevo, nombre)
            || articulo_setPrecio(nuevo,(float) atoi(precio))
            || articulo_setMedida(nuevo, atoi(medida))
            || articulo_setIdRubro(nuevo, atoi(idRubro)))
		{
			free(nuevo);
			nuevo = NULL;
		}
	}
	return nuevo;
}

int articulo_setId(eArticulo* this, int id)
{
    int retorno = 1;

	if(this != NULL && id >=0)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}

int articulo_getId(eArticulo* this, int* id)
{
   int retorno = 1;

	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}

int articulo_setNombre(eArticulo* this,char* nombre)
{
    int retorno = 1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(this->nombre, nombre);
		retorno = 0;
    }
	return retorno;
}

int articulo_getNombre(eArticulo* this,char* nombre)
{
    int retorno = 1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		retorno = 0;
	}
	return retorno;
}

int articulo_setPrecio(eArticulo* this, float precio)
{
    int retorno = 1;

	if(this != NULL && precio >=0)
	{
		this->precio = precio;
		retorno = 0;
	}
	return retorno;
}

int articulo_getPrecio(eArticulo* this, float* precio)
{
   int retorno = 1;

	if(this != NULL && precio != NULL)
	{
		*precio = this->precio;
		retorno = 0;
	}
	return retorno;
}

int articulo_setMedida(eArticulo* this, int medida)
{
    int retorno = 1;

	if(this != NULL && medida >=0)
	{
		this->medida = medida;
		retorno = 0;
	}
	return retorno;
}

int articulo_getMedida(eArticulo* this, int* medida)
{
   int retorno = 1;

	if(this != NULL && medida != NULL)
	{
		*medida = this->medida;
		retorno = 0;
	}
	return retorno;
}

int articulo_setIdRubro(eArticulo* this, int rubroId)
{
    int retorno = 1;

	if(this != NULL && rubroId >=0)
	{
		this->rubroId = rubroId;
		retorno = 0;
	}
	return retorno;
}

int articulo_getIdRubro(eArticulo* this, int* rubroId)
{
   int retorno = 1;

	if(this != NULL && rubroId != NULL)
	{
		*rubroId = this->rubroId;
		retorno = 0;
	}
	return retorno;
}

int guardarCSV(LinkedList* lista, char* path)
{
    int retorno = 1;
	FILE* pFile;
	eArticulo* pArticulo;
	int auxId;
	char auxNombre[15];
	float auxPrecio;
	int auxMedida;
	int auxIdRubro;

	pFile = fopen(path, "w");

	if(pFile != NULL)
	{
	    retorno = 0;
		fprintf(pFile, "id,articulo,precio,medida,id rubro\n");

        for(int i = 1; i < ll_len(lista); i++)
        {
            pArticulo = ll_get(lista, i);

            if(   !articulo_getId(pArticulo, &auxId)
               && !articulo_getNombre(pArticulo, auxNombre)
               && !articulo_getPrecio(pArticulo, &auxPrecio)
               && !articulo_getMedida(pArticulo, &auxMedida)
               && !articulo_getIdRubro(pArticulo, &auxIdRubro))
               {
                   fprintf(pFile, "%d,%s,%.2f,%d,%d\n", auxId, auxNombre, auxPrecio, auxMedida, auxIdRubro);
               }
        }
        fclose(pFile);
	}
	return retorno;
}

int sortByName(void* aux1, void* aux2)
{
	int retorno = 0;
	char name1[NOMBRE_TAM];
	char name2[NOMBRE_TAM];

	articulo_getNombre(aux1, name1);
	articulo_getNombre(aux2, name2);

	if(strcmp(name1, name2) > 0)
	{
		retorno = 1;
	}
	else if(strcmp(name1, name2) < 0)
	{
		retorno = -1;
	}
	return retorno;
}

void* map_descuento(void* articulo)
{
    void* retorno;
    eArticulo* x;
    float auxPrecio;
    int auxRubro;
    float descuento;

    if(articulo != NULL)
    {
        x = (eArticulo*) articulo;

        articulo_getPrecio(x, &auxPrecio);
        articulo_getIdRubro(x, &auxRubro);

        if(auxRubro == 1 && auxPrecio >=120)
        {
            descuento = auxPrecio * 20/100;
            auxPrecio = auxPrecio - descuento;
            articulo_setPrecio(x, auxPrecio);
        }
        else if(auxRubro == 2 && auxPrecio <=200)
        {
            descuento = auxPrecio *10/100;
            auxPrecio = auxPrecio - descuento;
            articulo_setPrecio(x, auxPrecio);
        }
        retorno = x;
    }
    return retorno;
}

