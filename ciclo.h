#include "programa.h"
#include "processo.h"

#ifndef CICLO_H_   /* Include guard */
#define CICLO_H_


//ciclo do programa principal
void ciclo(Luser *l);
//executa ciclo atraves de um processo filho
void arrancaCiclo();
void memoriaDoUser(User *u);
void detetaMemoria();
void cpuDoUser(User *u);
//detetar cpu
void detetaCpu();
void avisarUser(Luser *u, int p);
//adaptar a lista para os processos que gastem tanto  memória a mais como cpu
void removeRepUser(User* u);
int containsGroup(char* user,char** groups,int tam);

#endif 