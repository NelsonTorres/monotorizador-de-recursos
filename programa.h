#ifndef PROGRAMA_H_   
#define PROGRAMA_H_

#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h> 
#include <sys/socket.h>
#include <stdint.h>
#include <sys/mman.h>

typedef struct proc{
	int ambos;
	int pid;
	float cpu;
	float mem;
	char* user;
	char* nome; 
	}*Proc,proc;
typedef struct user{
	char* id;
	char** groups;
	int groupTam;
	int nproc;
	int nAmostras;
	int iterado;
	int aviso;

	Proc **amostrasMem;
	Proc **amostrasCpu;
	Proc **amostrasAmbos;

	struct user* prox;
	}*User,user;
typedef struct luser{
	int pid;
	User u;
	struct luser* prox;
	}*Luser,luser;

void iniciarLuser(Luser *l);
void iniciarUser(User *l);
//cria um novo processo
Proc iniciarProcesso(int pid, float cpu,char* user, float mem, char* nome, int modo);
#endif 