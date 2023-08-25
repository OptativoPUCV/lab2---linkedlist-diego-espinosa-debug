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
  List* list = (List*) malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if (!list->head)return NULL;
  list->current = list->head;
  return(list->head->data);
}

void * nextList(List * list) {
  if(!list->current)return NULL;
  if(!list->current->next)return NULL;
  list->current = list->current->next;
  return(list->current->data);
}

void * lastList(List * list) {
  if (!list->tail)return NULL;
  list->current = list->tail;
  return(list->current->data);
}

void * prevList(List * list) {
  if(!list->current)return NULL;
  if(!list->current->prev)return NULL;
  list->current = list->current->prev;
  return(list->current->data);
}

void pushFront(List * list, void * data) {
  Node* nuevo = createNode(data);
  
  if(list->head == NULL)
  {
    list->head = nuevo;
    list->tail = nuevo;
    
  }else{
    nuevo->next = list->head;
    if(list->head)
    {
      list->head->prev = nuevo;
    }
    list->head = nuevo;
    nuevo->prev = NULL;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nuevo = createNode(data);
  
  if(list->current == list->head)
  {
    pushFront(list,data);
    
  }else if(list->current == list->tail){
    list->current->next = nuevo;
    nuevo->prev = list->current;
    
  }else{
    
    nuevo->prev = list->current;
    nuevo->next = list->current->next;
    list->current->next = nuevo;
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
  
  if(list->current == list->head){
    Node* aux = list->current->next;
    aux->prev = NULL;
    list->head = aux;
    free(list->current);
    list->current = list->head;
  }else if(list->current == list->tail){
    Node* aux = list->current->prev;
    aux->next = NULL;
    list->tail = aux;
    free(list->current);
    list->current = list->head;
  }else{
    Node* aux = list->current->next;
    Node* auxPrev = list->current->prev;
    aux->prev = list->current->prev;
    auxPrev->next = list->current->next;
    free(list->current);
    list->current = list->head;
  }
  
  return list->current;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}