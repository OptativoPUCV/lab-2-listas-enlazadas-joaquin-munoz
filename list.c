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
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}