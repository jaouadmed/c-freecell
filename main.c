#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pile.c"
#include "pile.h"

Queue* GQS[8];
Queue* HQS[4];
Queue* SQS[4];


char* red(char * s){
    char* ch=malloc(sizeof(char));
    strcat(ch, "\033[;31m");
    strcat(ch, s);
    strcat(ch, "\033[0m");
    return ch;
}

void initGame(){

    int i, j, k=0, l=7;
    short c=0;
    char* kinds[]={HEART, SPADE, DIAMOND,  CLUB};
    Queue* IQS[52];

    for(i=0; i<4; i++){
        c=c==1?0:1;
        for(j=0; j<13; j++){
            IQS[k] = NULL;
            IQS[k++] = createElement((short)j+1, kinds[i], c);
        }
    }

    for(i=0; i<8; i++) GQS[i] = NULL;
    for(i=0; i<4; i++) HQS[i] = NULL;
    for(i=0; i<4; i++) SQS[i] = NULL;

    for(i=0; i<51; i++){
        j= (time(NULL)*(rand()/100))%(51-i);
        push(&GQS[l=l==0?7:l-1], IQS[j]);
        for(k=j; k<51-i; k++) IQS[k] = IQS[k+1];
    }
    push(&GQS[time(NULL)%8], IQS[0]);
}

void display(){

    char a='A';
    int i;
    Queue* pt;

    fflush(stdout);
    system("clear");
    for(i=0; i<8; i++){
        pt = GQS[i];
        printf("\n\n%c : ", a++);
        while(pt != NULL){
            fflush(stdout);
            printf("\t|%d : %s|", pt->data.nbr, (pt->data.color==1?red(pt->data.kind):pt->data.kind));
            pt = pt->next;
        }
    }

    printf("\n\n===================================================================");

    for(i=0; i<4; i++){
        pt = HQS[i];
        printf("\n\n%c (HELPER %d): ", a++, i+1);
        while(pt != NULL){
            fflush(stdout);
            printf("\t|%d : %s|", pt->data.nbr, (pt->data.color==1?red(pt->data.kind):pt->data.kind));
            pt = pt->next;
        }
    }
    printf("\n\n===================================================================");
    a='W';
    for(i=0; i<4; i++){
        pt = SQS[i];
        printf("\n\n%c (SORTED %d): ", a++, i+1);
        while(pt != NULL){
            fflush(stdout);
            printf("\t|%d : %s|", pt->data.nbr, (pt->data.color==1?red(pt->data.kind):pt->data.kind));
            pt = pt->next;
        }
    }
}



int fromTo(Queue** q1, Queue** q2){
    if(isEmpty(*q2) && isEmpty(*q1)) return -1;
    else if((isEmpty(*q2) && !isEmpty(*q1)) || ((*q1)->data.nbr < (*q2)->data.nbr && ((*q1)->data.nbr==1?(*q2)->data.nbr==2:(*q2)->data.nbr%(*q1)->data.nbr==1) && (*q1)->data.color != (*q2)->data.color)){
        Queue* e = pop(q1);
        e->next = NULL;
        push(q2, e);
        return 0;
    }
    return -1;
}

int fromTo1(Queue** q1, Queue** q2){
    if(isEmpty(*q2) && isEmpty(*q1)) return -1;
    else if((isEmpty(*q2) && !isEmpty(*q1)) || ((*q1)->data.nbr > (*q2)->data.nbr && ((*q2)->data.nbr==1?(*q1)->data.nbr==2:(*q1)->data.nbr%(*q2)->data.nbr==1) && (*q1)->data.color == (*q2)->data.color && !strcmp((*q1)->data.kind, (*q2)->data.kind))){
        push(q2, pop(q1));
        return 0;
    }
    return -1;
}

int win(){
    int i;
    for(i=0; i<4; i++)
        if(SQS[i] == NULL || SQS[i]->data.nbr != 13) return 0;
    return -1;
}

int main(){
    int i;

    initGame();
    char *cmd=malloc(1);
    Queue* qq;
    while(1){
        display();
        printf("\n\n>>>");
        gets(cmd);
        if(strlen(cmd) != 2){
            puts("The command should be 2 letters EX 'AB'.");
            gets(cmd);
        }else{
            cmd[0] = cmd[0]>'Z' ? 'A'+(cmd[0] - 'a') : cmd[0];
            cmd[1] = cmd[1]>'Z' ? 'A'+(cmd[1] - 'a') : cmd[1];
            if(
            !((cmd[0] >= 'A' && cmd[0] <= 'L' || cmd[0] >= 'W' && cmd[0] <= 'Z')
            && (cmd[1] >= 'A' && cmd[1] <= 'L' || cmd[1] >= 'W' && cmd[1] <= 'Z')
            )){
                puts("The command should contain the letters listed Above : 'A-L || W-Z'.");
                gets(cmd);
            }else{
                if(cmd[1]>='W'){
                    qq =  cmd[0]<='H'?GQS[cmd[0]-'A']:cmd[0]<='L'?HQS[cmd[0]-'I']:SQS[cmd[0]-'W'];
                    if(isEmpty(SQS[cmd[1]-'W']) && !isEmpty(qq)){
                        if(qq->data.nbr == 1){
                            if(fromTo(cmd[0]<='H'?&GQS[cmd[0]-'A']:cmd[0]<='L'?&HQS[cmd[0]-'I']:&SQS[cmd[0]-'W'],
                            &SQS[cmd[1]-'W'])){
                                puts("Operation went wrong1");
                                gets(cmd);
                            }
                        }else{
                            puts("Operation went wrong2");
                            gets(cmd);
                        }
                    }else{
                        if(fromTo1(cmd[0]<='H'?&GQS[cmd[0]-'A']:cmd[0]<='L'?&HQS[cmd[0]-'I']:&SQS[cmd[0]-'W'],
                            &SQS[cmd[1]-'W'])){
                                puts("Operation went wrong22");
                                gets(cmd);
                        }
                    }
                }else{
                    if(fromTo(cmd[0]<='H'?&GQS[cmd[0]-'A']:cmd[0]<='L'?&HQS[cmd[0]-'I']:&SQS[cmd[0]-'W'],
                        cmd[1]<='H'?&GQS[cmd[1]-'A']:cmd[1]<='L'?&HQS[cmd[1]-'I']:&SQS[cmd[1]-'W'])){
                        puts("Operation went wrong");
                        gets(cmd);
                    }
                }
            }
        }
        if(win()){
            puts("YOU WINNNNN!!!!!!!!!!!!!");
            gets(cmd);
        }
    }
    return 0;
}
