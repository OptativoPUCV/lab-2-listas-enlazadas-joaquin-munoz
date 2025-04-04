#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = 0;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if(list->current) return list->current->data; //pregunta si hay un primer dato , si es asi lo retorna 
    return NULL;
}

void * nextList(List * list) {
    if (list->current!=NULL) list->current = list->current->next; //pregunta si existe un nodo actual si es asi pasa al siguiente
    if (list->current!=NULL)return list->current->data;     //si el siguiente existe retorna su valor 
    return NULL;
}

void * lastList(List * list) {
    list->current = list->head;
    while(list->current->next != NULL){
        list->current = list->current->next;
    }
    if(list->current != NULL){
        return list->current->data;
    }
    return NULL;
}


void * prevList(List * list) {
    if (list->current!=NULL) list->current = list->current->prev; 
    if (list->current!=NULL) return list->current->data;  
    return NULL;  
}

void pushFront(List * list, void * data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL) {//pregunta si la lista o la posicion no existe
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;  // Manejo de error si malloc falla
    }
    newNode->data = data;
    Node* izq = list->current;
    Node* der = izq->next;
    
    newNode->prev = izq;
    newNode->next = der;
    izq->next = newNode;
                                        // Si `der` existía, su `prev` debe apuntar al nuevo nodo
    if (der != NULL) {
        der->prev = newNode;
    } else {
                                        // Si `current` era el último nodo, `newNode` se convierte en `tail`
        list->tail = newNode;
    }
    
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) { //si list esta vacia 
        return NULL;  
    }

    void* data = list->current->data;  // Guardamos el dato 
    Node* nodoAEliminar = list->current;

    // Determinar el nodo siguiente antes de eliminar `current`
    Node* siguiente = nodoAEliminar->next;
    if (nodoAEliminar == list->head) {   //si es que el nodo a eliminar fuera el primero
        list->head = siguiente;
    }
    if (nodoAEliminar == list->tail) {    //si es que el nodo a eliminar fuera el ultimo
        list->tail = nodoAEliminar->prev;
    }

    // Conectar los nodos prev y next
    

    if (nodoAEliminar->prev != NULL) {  //nodoAEliminar->prev->next apunta a lo que apunta el anterior en el next 
        nodoAEliminar->prev->next = nodoAEliminar->next;
    }
    if (nodoAEliminar->next != NULL) {    //nodoAEliminar->next->prev apunta a lo que apunta el anterior en el next 
        nodoAEliminar->next->prev = nodoAEliminar->prev;     
    }
    list->current = siguiente;

    free(nodoAEliminar);  // Liberamos memoria del nodo eliminado
    return data;  // Retornamos el dato del nodo eliminado
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}