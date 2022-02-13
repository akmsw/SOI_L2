/**
 * @file linked_list.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com)
 * @brief Desarrollo de una lista simplemente enlazada.
 * @version 1.0
 * @since 2021-08-20
 */

// Librerías a utilizar.

#include <stdio.h>
#include <stdlib.h>

// Definición de estructura para nodos.

typedef struct node
{
    int value;
    struct node *next;
} node;

// Prototipado de funciones.

void print_list(node *);
void insert_at_end(node **, int val);

// Programa principal.

int main(void)
{
    node *head = NULL;

    for (int i = 0; i < 10; i++)
        insert_at_end(&head, i);

    print_list(head);

    return 0;
}

/**
 * @brief Esta función se encarga de imprimir la lista.
 * 
 * @details Comenzamos desde el nodo inicial imprimiendo
 *          el parámetro 'value' en pantalla. Luego, con
 *          el pivote auxiliar, vamos moviéndonos de nodo
 *          en nodo repitiendo el proceso de impresión
 *          hasta llegar al nodo vacío (el final de la lista).
 * 
 * @param head Nodo inicial de la lista.
 */
void print_list(node *head)
{
    node *aux = head;

    while (aux != NULL)
    {
        fprintf(stdout, "%d - ", aux->value);

        aux = aux->next;
    }

    fprintf(stdout, "\n");
}

/**
 * @brief Esta función inserta un nodo al final de la
 *        lista.
 * 
 * @details Se aloca memoria para un nuevo nodo, se le
 *          asigna el valor recibido por parámetro y se
 *          hace que apunte a NULL porque será el nuevo
 *          nodo final de la lista.
 *          Si la lista está vacía (*head == NULL), entonces
 *          este nodo creado será la cabeza.
 *          Sino, recorro la lista hasta encontrar el nodo
 *          final, y lo intercambio con el nuevo nodo creado.
 * 
 * @param head Nodo cabeza de la lista.
 * @param value El valor del campo 'value' del nodo.
 */
void insert_at_end(node **head, int value)
{
    node *new_node = malloc(sizeof(node));

    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL)
        *head = new_node;
    else
    {
        node *aux = *head;

        while (aux->next != NULL)
            aux = aux->next;
        
        aux->next = new_node;
    }
}