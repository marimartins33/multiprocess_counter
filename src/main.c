#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_PROCESSOS 4


	
 
int i = 0;

int flag;
int *contador;
int *l;


unsigned long long int entrada[100];   
  
  


/*funcao que realiza a leitura dos numeros a serem analisados*/
void ler_vetor (void){
 
  char fim;
  
  /* Aloca memoria para o vetor entrada*/
      	

  do {
      scanf("%llu%c", &entrada[i], &fim);
      i++;
    } while(fim != '\n');

    

	
}	
	
	
void calculo_primo(unsigned long long int primos){
 
 
  unsigned long long int div = 0;

 
  for (unsigned long long int k = 1; k <= primos; k++) {
    if (primos % k== 0) { 
     div++;
    }
  }
    
  if (div == 2){
  *contador = *contador+1;
   }
 
 *l = *l -1;
	//printf("primo %llu \ncontador %d \nl %d \n",primos,*contador,*l);
}
 
int main() {
  
   ler_vetor();

    /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

/*cria memoria compartilhada para o vetor entrada*/
 unsigned long long int *primo;
  primo = (unsigned long long int*) mmap(NULL, sizeof(unsigned long long int)*i,protection, visibility, 0, 0);


/* Cria memoria compartilhada para a variavel contador*/
    	
    contador = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  
  /*cria memoaria compartilahda para ponteiro l*/
   
  l = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);

  *l = i; 
       
 /*cria os processos*/ 
  pid_t filho[N_PROCESSOS];
  //printf("criei processos \n");

  /*cria processos filhos*/
 while (*l > 0){ 
   int n;
   if (*l>4){
     n=4;
 
     }
     else{
       n =*l;
     }
      
    //printf("l antes %d \n",*l);
    for (int j=0; j<n; j++) {
      filho[j] = fork();
      //printf("criei processos filhos \n");
               
      if (filho[j] == 0) {
        *primo = entrada[(*l-1)];
     	 calculo_primo(*primo);
        exit(0);
      }
           
    }  

   /*espera processos acabar de terminar*/
  for (int j=0; j<n; j++) {
    waitpid(filho[j], NULL, 0);
  }

   
  }
  /*informa quantidade de primos*/
  printf("%d\n", *contador);
  return 0;

}
