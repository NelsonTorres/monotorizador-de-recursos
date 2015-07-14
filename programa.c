#include "programa.h"

void iniciarLuser(Luser *l){
	*l= (Luser)malloc(sizeof(luser));
	}
void iniciarUser(User *l){
	*l= (User)malloc(sizeof(luser));
	}
//cria um novo processo
Proc iniciarProcesso(int pid, float cpu,char* user, float mem, char* nome, int modo){
	Proc p=(Proc)malloc(sizeof(proc));
	p->ambos=modo;
	p->pid=pid;
	p->cpu=cpu;
	p->mem=mem;
	p->user=(char*)malloc(sizeof(char)*strlen(user));
	strcpy(p->user,user);
	p->nome=(char*)malloc(sizeof(char)*strlen(nome));
	strcpy(p->nome,nome);
	return p;
	}

