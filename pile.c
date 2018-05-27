#include "pile.h"
#include<string.h>

Queue* createElement(short nbr, char* kind, short color){
    Queue *e = (Queue*) malloc(sizeof(Queue));
    e->data.nbr = nbr;
    if(kind != NULL){
        e->data.kind = malloc(sizeof(char*) * (strlen(kind)+1));
        strcpy(e->data.kind, kind);
    }else e->data.kind = NULL;
    e->data.nbr = nbr;
    e->data.color = color;
    e->next = NULL;
    return e;
}

void push(Queue** q, Queue *e){
    if(*q == NULL) *q = e;
    else{
        Queue* e1 = e;
        e->next = *q;
        *q = e1;
    }
}

Queue* pop(Queue** q){
    if(*q != NULL){
        Queue* temp = *q;
        *q = (*q)->next;
        temp->next = NULL;
        return temp;
    }
    printf("\nerror : poping on an empty queue");
    system("exit");
}

Queue head(Queue* q){
    if(q != NULL){
        return *q;
    }
    printf("\ncan't read : queue's empty");
    system("exit");
}

int isEmpty(Queue* q){
    return q==NULL?1:0;
}

int size(Queue* q){
    int a=0;
    while(q != NULL){
        q=q->next;
        a++;
    }
    return a;
}
