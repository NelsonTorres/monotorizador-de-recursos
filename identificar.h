#include "programa.h"
#include "processo.h"



#ifndef IDENTIFICAR_H_   /* Include guard */
#define IDENTIFICAR_H_


extern int ficheirocpu;
extern int ficheiromem;
//escrever para o GUI
void escreveParaGui(User u);
int killing(char* str);
void incCpu(int s);
void incMem(int s);
void auxiliarCliente(User u);
//obter os grupos de um user
Luser obterPermissoes(char* nome);
//adiciona à lista e arranca o auxiliar de cliente
void juntarLista(Luser novo,Luser* ultimonodo);
//identificar
int identificar(Luser *ultimonodo);

#endif 