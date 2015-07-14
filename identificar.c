#include "identificar.h"

//escrever para o GUI
void escreveParaGui(User u){
	char **linhas = (char**)malloc(sizeof(char*)*(u->nproc+1));
	int n=u->iterado%u->nAmostras,i;
	if(u->amostrasAmbos && u->amostrasAmbos[n])comparaAmostras(u,u->amostrasAmbos,2,&linhas);
	printf("Ambos:\n");
	for(i=0;i<u->nproc && linhas[i];i++)printf("%s\n",linhas[i]);
	comparaAmostras(u,u->amostrasMem,1,&linhas);
	printf("Memoria:\n");
	for(i=0;i<u->nproc && linhas[i];i++)printf("%s\n",linhas[i]);
	comparaAmostras(u,u->amostrasCpu,0,&linhas);
	printf("CPU:\n");
	for(i=0;i<u->nproc && linhas[i];i++)printf("%s\n",linhas[i]);
	}
int killing(char* str){
	int i=0,pid;
	char *pidc, *decisao,*regime;
	pidc=strtok(str,"$");
	decisao=strtok(NULL,"$");
	regime=strtok(NULL,"$");

	pid=atoi(pidc);
	if(strcmp(decisao,"matar")==0){
		printf("matando --%s - %s\n",decisao,pidc );
		kill(SIGTERM,pid);
	} else if(strcmp(decisao,"parar")==0){
		kill(SIGSTOP,pid);
	}

	}
void incCpu(int s){ficheirocpu=1;}
void incMem(int s){ficheiromem=1;}
void auxiliarCliente(User u){

	int ambos=0;
	signal(SIGUSR1,incCpu);
	signal(SIGUSR2,incMem);
	if(fork()==0){
		killing(u->id);
		exit(0);
	}
	while(1){
		if(ficheirocpu){
			cpuDoUser(&u);
			ficheirocpu=0;
			ambos++;
			}
		if(ficheiromem){
			memoriaDoUser(&u);
			ficheiromem=0;
			ambos++;
			}
		if(ambos>2){
			removeRepUser(&u);
			ambos=0;
			escreveParaGui(u);
			
			u->iterado++;
			if(u->iterado>u->nAmostras){
				libertar(u->amostrasAmbos[u->iterado%u->nAmostras],u->nproc);
				libertar(u->amostrasCpu[u->iterado%u->nAmostras],u->nproc);
				libertar(u->amostrasMem[u->iterado%u->nAmostras],u->nproc);
				}
			}
		pause();
		}
	}
//obter os grupos de um user
Luser obterPermissoes(char* nome){
	
	char buf[500],*dados;
	printf("%s\n",nome );
	int c=0,i=0,n=0;
	
	Luser aux;iniciarLuser(&aux);
	User u;iniciarUser(&u);
	aux->u=u;
	aux->prox=NULL;
	u->id=strtok(nome,"\0");

	strcpy(buf,"groups ");
	strcat(buf,nome);
	FILE* fd=popen(buf,"r");
	
	n=fscanf(fd,"%s",buf);
	while(n==1){
		c++;
		buf[0]='\0';
		n=fscanf(fd,"%s",buf);
		}
	u->groupTam=c;
	u->groups = (char**)malloc(sizeof(char*)*c);
	i=0;
	strcpy(buf,"groups ");
	strcat(buf,nome);
	fd=popen(buf,"r");
	
	while(i<c){
		n=fscanf(fd,"%s",buf);
		if(n!=1)perror("descritor de ficheiro, erro");	
		u->groups[i]=(char*)malloc(sizeof(char)*500);
		strcpy(u->groups[i],buf);
		i++;
		}
	return aux;
	} 
//adiciona à lista e arranca o auxiliar de cliente
void juntarLista(Luser novo,Luser* ultimonodo){
	int pid;
	if(!novo)exit(0);
	pid=fork();
	if(pid==0){
		auxiliarCliente(novo->u);
		exit(0);
	}
	novo->pid=pid;
	if(!ultimonodo){
		(*ultimonodo)=novo;
		}
	else{
		(*ultimonodo)->prox=novo;
		(ultimonodo)=&(*ultimonodo)->prox;
		}
	}	
//identificar
int identificar(Luser *ultimonodo){
	char buf[500],lerc[500],wrc[500];
	char* s;
	int file;
	int r=0,ler=0;
	Luser u;
	mkfifo("id.txt",0666);

	while(1){
		u=NULL;
		file=open("id.txt",O_RDONLY);
		r=0;
		r=read(file,buf,500);
		if(r){
			s=strtok(buf,"$");
			if(strcmp(s,"id")==0){
				s=strtok(NULL,"\n");
				strcpy(lerc,s);
				strcat(lerc,"toM");
				mkfifo(lerc,0666);
				strcpy(wrc,"toM");
				strcat(wrc,s);
				mkfifo(wrc,0666);
				u=obterPermissoes(s);
				juntarLista(u,ultimonodo);
				}
			}
		}
	return 0;
	}


