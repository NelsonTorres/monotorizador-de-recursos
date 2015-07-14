#include "processo.h"

//imprime informação de um processo
int imprimeProc(Proc p){
	if(p==NULL){printf(" Proc: NULL\n");return 1;}
	printf("%s ",p->nome);
	printf("%d ",p->pid );
	printf("%f ",p->mem );
	printf("%s ",p->user );
	printf("%f;\n",p->cpu );
	return 0;}
//popup
char * sig_popup(Proc p,char *aux){
	sprintf(aux,"%d$%s$%f$%f$%s\n",p->pid,p->nome,p->cpu,p->mem,p->user);
	return aux;
	}
//comparacao de Proc
int procIgual(Proc a,Proc b){
	if(!a)return 0;
	if(!b)return 0;
	
	if (a->pid==b->pid && strcmp(a->nome,b->nome)==0){
		return  1;
	}

	return 0;
	}	
//procura um processo em dada amostra
int encontraProcAmostra(Proc proc,Proc* a,int nproc){
	int i=0;
	if(nproc==0)return 0;
	
	while(i<nproc){
		if(!a[i])return 0;
		if(procIgual(a[i],proc))return 1;

		i++;
	}
	return 0;
	}
int imprimeLista(Proc* lista,int N){
	int i=0;
	while(i<N && lista[i]){
		imprimeProc(lista[i]);
		i++;
	}
	return i;}
int imprimeAmostras(Proc** amostras, int N,int M){
	int i=0;
		while(i<N){
			printf("lista %d:\n",i);
			imprimeLista(amostras[i],M);
			printf("\n");
			i++;
		}
		return i;}
int encontraProcAmostras(Proc p,Proc** amostras,int N, int M){
	int i,aux;
	int accum=0;
	aux=0;

	
	for(i=0;i<N;i++){					
			accum+=encontraProcAmostra(p,amostras[i],M);
	}
	return 	accum;
	}
//add Processo À lista sem repetidos
Proc addProc(int j,int nproc,Proc* amostras,Proc* p,int tam){
	if(!amostras[j])return NULL;
	if(!encontraProcAmostra(amostras[j],p,tam))return amostras[j];
	return NULL;
	}
//processos da lista
int procDaLista(int nproc,Proc* amostras,Proc* p,int tam){
	int j;
	Proc paux=NULL;
	for(j=0;j<nproc;j++){
		paux=addProc(j,nproc,amostras,p,tam);
		if(paux){
			p[tam++]=paux;
			}
		}
	return tam;
	}
int listaProcessos(int lim,int nproc,Proc** amostras,Proc* p,int tam){
	int i;
	for(i=0;i<lim;i++){
		tam=procDaLista(nproc,amostras[i],p,tam);
	}
	return tam;
	}
//obter numero de avisos de um processo
void avisos(int tam,int* value,Proc* p,Proc** amostras,int lim,int nproc){
	int i;
	for(i=0;i<tam;i++){
		value[i]=encontraProcAmostras(p[i],amostras,lim,nproc);
		}
	}
//avisarProcessos 
char** avisar(int tam,int *value,int aviso,int texto,int lim,int nproc,Proc** amostras,Proc* p,char** lista){
	int k,tams=0,i;
	char *buf;
	for(k=0;k<tam;k++){
		if(value[k]>=aviso ){
			if(texto==2){
				lista[tams]=(char*)malloc(sizeof(char)*500);
				sig_popup(p[k],lista[tams]);
				tams++;
			}
			else if(p[k]->ambos!=1){
				lista[tams]=(char*)malloc(sizeof(char)*500);
				sig_popup(p[k],lista[tams]);
				tams++;
				}
			}
		}


		lista[tams]=NULL;
	return lista;
	}
void comparaAmostras(User u,Proc** amostras,int texto,char*** lista){
	int i,j,k,warn=0,lim=u->iterado;
	int tam=0;
	Proc p[u->nAmostras*u->nproc];
	int value[u->nAmostras*u->nproc];

	if(u->iterado>u->nAmostras)lim=u->nAmostras;
	tam=listaProcessos(lim,u->nproc,amostras,p,tam);
	avisos(tam,value,p,amostras,lim,u->nproc);
	avisar(tam,value,u->aviso,texto,lim,u->nproc,amostras,p,*lista);	

	}

void libertar(Proc* amostras,int max){
	int i;
	for(i=0;i<max && amostras[i];i++){
		free(amostras[i]);
		amostras[i]=NULL;
		}
	}
//clone de um processo
Proc copiaProc(Proc *listaMem,int i){
	Proc p= (Proc)malloc(sizeof(proc));
	p->pid=listaMem[i]->pid;
	p->nome=listaMem[i]->nome;
	p->cpu=listaMem[i]->cpu;
	p->user=listaMem[i]->user;
	p->mem=listaMem[i]->mem;
	p->ambos = listaMem[i]->ambos; 
	return p;
	}
//contem processo p na lista l
int containsProc(Proc p, Proc* l,int max){
	int i=0,r=-1;
	for(i=0;i<max && l[i];i++){
		if(procIgual(p,l[i]))r=i;
	}
	return r;
	}
//adaptar a lista para os processos que gastem tanto  memória a mais como cpu
