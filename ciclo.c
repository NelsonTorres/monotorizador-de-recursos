#include "ciclo.h"

extern Luser *inicio;
void memoriaDoUser(User *u){
	int processo=0,n=0,pid;
	float cpu,mem;
	char user[500],nome[500];
	User l=*u;
	FILE* file=fopen("mem.txt","r");
	n=fscanf(file,"%s %d %f %f %s",user,&pid,&cpu,&mem,nome);
	while(n==5 && mem>1 && processo<l->nproc){		
		if(containsGroup(user,l->groups,l->groupTam)){
			l->amostrasMem[l->iterado%l->nAmostras][processo]=iniciarProcesso(pid,cpu,user,mem,nome,0);
			processo++;
		}
		n=fscanf(file,"%s %d %f %f %s\n",user,&pid,&cpu,&mem,nome);	
		}
	l->amostrasMem[l->iterado%l->nAmostras][processo]=NULL;
	}
void detetaMemoria(){	
	int pid=0,i,n=0,processo;
	float cpu=0,mem=0;
	char user[500],nome[500],buf[500];
	Proc* lista;
	FILE* file;
	Luser aux=*inicio;
	FILE* copia = fopen("memoria.txt", "ab+");
	file=popen("ps -e -o user,pid,pcpu,pmem,ucmd --sort '-%mem'","r");
	if(!file)printf("error\n");
	for(i=0;i<5;i++){
		n=fscanf(file,"%s",buf);
		}
	n=0;
	processo=0;

	while(file){
		fread(buf,500,1,file);
		fwrite(buf,500,1,copia);
		}
	fclose(file);
	}
void cpuDoUser(User *u){
	int processo=0,pid,n;
	float cpu,mem;
	char user[500],nome[500],buf[500];
	User l= *u; 
	FILE* file=fopen("cpu.txt","r");
	n=fscanf(file,"%s %d %f %f %s %s %s %s %s %s %s",user,&pid,&cpu,&mem,buf,buf,buf,buf,buf,buf,nome);	
	while(n==11 && cpu>10 && processo<l->nproc){	
		if(containsGroup(user,l->groups,l->groupTam)){
			l->amostrasCpu[l->iterado%l->nAmostras][processo]=iniciarProcesso(pid,cpu,user,mem,nome,1);
			processo++;
			}
		pid=cpu=0;
		n=fscanf(file,"%s %d %f %f %s %s %s %s %s %s %s",user,&pid,&cpu,&mem,buf,buf,buf,buf,buf,buf,nome);	
		}
	if(processo< l->nproc)l->amostrasCpu[l->iterado%l->nAmostras][processo]=NULL;
	}
//detetar cpu
void detetaCpu(){	
	int pid=0,i,n,processo;
	float cpu=0,mem=0;
	char user[500],nome[500],buf[500];
	Proc* lista;
	FILE* file;

	remove("cpu.txt");
	FILE* copia = fopen("cpu.txt", "ab+");	
	file=popen("ps aux --sort '-%cpu'","r");
	if(!file)printf("error\n");


	for(i=0;i<11;i++){
		n=fscanf(file,"%s",buf);
		}
	n=0;
	processo=0;
	
	while(file){
		fread(buf,500,1,file);
		fwrite(buf,500,1,copia);
	}
	fclose(file);
	}
//ciclo do programa principal
void ciclo(Luser *l){
	int fd[2],n=0;
	FILE* file;
	int r,killer,gui,i,aviso=2,max=10,pid,nAmostras=10,amostra=0,processo,iterado=0;
	float cpu;
	char buf[500];
	
	detetaMemoria();
	avisarUser(l,SIGUSR2);
		
	detetaCpu();
	avisarUser(l,SIGUSR1);
	//removeRep(l);


	}
//executa ciclo atraves de um processo filho
void arrancaCiclo(){
	alarm(5);
	ciclo(inicio);
	}

	void avisarUser(Luser *u, int p){
	Luser aux=*u;
	while(aux)kill(aux->pid,SIGUSR2);
	}
int containsGroup(char* user,char** groups,int tam){
	int i;
	for(i=0;i<tam;i++){
		if(strcmp(groups[i],user)==0)return 1;
		}
	return 0;
	}
void removeRepUser(User* u){
	int i;
	int f;
	int tam=0;
	User l =*u;
	for(i=0;i<l->nproc && l->amostrasMem[l->iterado%l->nAmostras][i];i++){
		f=-1;
		f=containsProc(l->amostrasMem[l->iterado%l->nAmostras][i],l->amostrasCpu[l->iterado%l->nAmostras],l->nproc);
		if(f>=0){
			l->amostrasAmbos[l->iterado][tam++]=copiaProc(l->amostrasMem[l->iterado%l->nAmostras],i);
			l->amostrasMem[l->iterado%l->nAmostras][i]->ambos=1;
			l->amostrasCpu[l->iterado%l->nAmostras][i]->ambos=1;
			}
		}
	
	}