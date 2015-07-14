#include "programa.h"

#ifndef PROCESSO_H_   /* Include guard */
#define PROCESSO_H_

//imprime informação de um processo
int imprimeProc(Proc p);
//popup
char * sig_popup(Proc p,char *aux);
//comparacao de Proc
int procIgual(Proc a,Proc b);
//procura um processo em dada amostra
int encontraProcAmostra(Proc proc,Proc* a,int nproc);
int imprimeLista(Proc* lista,int N);
int imprimeAmostras(Proc** amostras, int N,int M);
int encontraProcAmostras(Proc p,Proc** amostras,int N, int M);
//add Processo À lista sem repetidos
Proc addProc(int j,int nproc,Proc* amostras,Proc* p,int tam);
//processos da lista
int procDaLista(int nproc,Proc* amostras,Proc* p,int tam);
int listaProcessos(int lim,int nproc,Proc** amostras,Proc* p,int tam);
//obter numero de avisos de um processo
void avisos(int tam,int* value,Proc* p,Proc** amostras,int lim,int nproc);
//avisarProcessos 
char** avisar(int tam,int *value,int aviso,int texto,int lim,int nproc,Proc** amostras,Proc* p,char** lista);
void comparaAmostras(User u,Proc** amostras,int texto,char*** lista);

void libertar(Proc* amostras,int max);
//clone de um processo
Proc copiaProc(Proc *listaMem,int i);
//contem processo p na lista l
int containsProc(Proc p, Proc* l,int max);

#endif 