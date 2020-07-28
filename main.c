#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "validaciones.h"
#include "articulos.h"

int menu();

int main()
{
    int seguir = 0;
    char path[25];
    char csv[15];
    strcpy(csv, ".csv");
    LinkedList* listaArticulos = ll_newLinkedList();
    LinkedList* listaArticulosMapeada = ll_newLinkedList();

    do
    {
        switch(menu())
        {
        case 1:
            utn_getCadena(path, 25, 2, "Ingrese nombre del archivo: ", "\nError ");
            strcat(path, csv);

            if(!cargarArticulosCSV(listaArticulos, path))
            {
                printf("\nArchivos cargados con exito en '%s'.\n", path);
            }
            else
            {
               printf("\nError.\n");
            }
        break;
        case 2:
            if(!ll_isEmpty(listaArticulos))
            {
                if(ll_sort(listaArticulos, sortByName, 1)==0)
                {
                    printf("Lista ordenada exitosamente.\n");
                }
                else
                {
                    printf("\nError.\n");
                }
            }
            else
            {
                printf("Debe cargar los datos primero.\n");
            }
            break;
        case 3:
            if(!ll_isEmpty(listaArticulos))
            {
                mostrarArticulos(listaArticulos);
            }
            else
            {
                printf("Debe cargar los datos primero.\n");
            }
            break;
        case 4:
            if(!ll_isEmpty(listaArticulos))
            {
                listaArticulosMapeada = ll_map(listaArticulos, map_descuento);

                if(listaArticulosMapeada != NULL)
                {
                    printf("Descuentos realizados con exito.\n");
                }
                else
                {
                    printf("\nError.\n");
                }
            }
            else
            {
                printf("Debe cargar los datos primero.\n");
            }
            break;
        case 5:
            if(!ll_isEmpty(listaArticulosMapeada))
            {
                if(!guardarCSV(listaArticulosMapeada, "articulosDescuento.csv"))
                {
                    mostrarArticulos(listaArticulosMapeada);
                    printf("Archivo creado con exito como 'articulosDescuento'.\n");
                }
                else
                {
                    printf("\nError.\n");
                }
            }
            else
            {
                printf("Debe cargar y mapear los datos primero.\n");
            }
            break;
        case 6:
            seguir = 1;
            break;
        }
        system("pause");
    }while(seguir ==0);

    return 0;
}

int menu()
{
    int opcion;

    system("cls");
    printf("----Menu----\n");
    printf("1. Cargar archivos.\n");
    printf("2. Ordenar lista.\n");
    printf("3. Imprimir lista.\n");
    printf("4. Realizar descuentos.\n");
    printf("5. Cargar descuentos en una lista.\n");
    printf("6. Salir.\n");

    utn_getEntero(&opcion, 2, "Ingrese opcion: ", "\nError ", 1, 6);

    return opcion;
}
