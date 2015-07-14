/*um processo em abuso, só avisa o utilizador uma vez,
enquanto estiver a abusar*/

/*problema: como distinguir comandos iguais da mesma janela mas por chamadas diferentes??*/

		//quantar quantas vezes o mesmo pid aparece, 
		//falta verificar que o processo é outro e
		// não diferentes mas com o mesmo pid

#include "identificar.h"
#include "ciclo.h"
/*
semid=semget(key,nsems,IPC_CREAT|0666);
  if (semid<0) 
  { 
  perror("Semaphore creation failed ");
  }
*/

int ficheirocpu=0;
int ficheiromem=0;
Luser *inicio=NULL;
int main(int argc, char** argv){
	Luser *fim=NULL;
	Luser l=NULL;

	iniciarLuser(&l);
	inicio=&l;

	fim=&l;

	signal(SIGALRM,arrancaCiclo);
	identificar(fim);

	return(1);
	}
	
	
