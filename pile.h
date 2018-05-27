#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

typedef struct card{
    short nbr;
    char* kind;
    short color;
}Card;

//sorry it's a stack
typedef struct queue{
    Card data;
    struct queue* next;
}Queue;

Queue* createElement(short nbr, char* kind, short color);
void push(Queue** q, Queue* e);
Queue* pop(Queue** q);
Queue head(Queue* q);
int isEmpty(Queue* q);
int size(Queue* q);



#endif // PILE_H_INCLUDED
