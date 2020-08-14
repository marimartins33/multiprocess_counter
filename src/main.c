#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_PROCESSOS 4

/*variaveis globais*/
unsigned long int *entrada;	
int *contador;	 
int i =0;
int k =0;



/*funcao que realiza a leitura dos numeros a serem analisados*/
void ler_vetor (void){
 
  char fim;

  do {
      scanf("%ld%c", &entrada[i], &fim);
      i++;
    } while(fim != '\n');

      
}

void primo (void){
  int primo;
  primo = entrada[i];


  int div = 0;
  
 
  for (k = 1; k <= primo; k++) {
    if (primo % k == 0) { 
     div++;
    }
  }
    
  if (div == 2)
    *contador = *contador+1;
  else
   ;

}


 
int main() {
  /*aloca memoria para o vetor entrada*/
  entrada = (unsigned long int*) malloc (sizeof(unsigned long int)*100);
 /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

/*cria memoria compartilhada para o vetor entrada*/
 entrada = (unsigned long int*) mmap(NULL, sizeof(unsigned long int)*i,protection, visibility, 0, 0);


/* Cria memoria compartilhada para a variavel contador*/

    contador = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  /*cria os processos*/
  pid_t filho[N_PROCESSOS];
  
  ler_vetor();

  
/*cria processos filhos*/
  for (int j=0; j<N_PROCESSOS; j++) {
    filho[j] = fork();

    
    while (i >= 0){


      if (filho[j] == 0) {
      primo();
      i = i -1;
      
      
      
      }


      else if (filho[j] == 1) {
      /*executa no processo filho 1*/
      primo();
      i = i -1;
      
      
      }

      else if (filho[j] == 2) {
      /*executa no processo filho 2*/
      primo();
      i = i -1;
      
      
      }

      else if (filho[j] == 3) {
      /*executa no processo filho 3*/
      
      primo();
      i = i -1;
      
      }
    }  




    exit(0);
  }

  /*espera processos acabar de terminar*/
  for (int j=0; j<N_PROCESSOS; j++) {
    waitpid(filho[j], NULL, 0);
  }

/*informa quantidade de primos*/
  printf("Quantidade de numeros primos: *c=%d\n", *contador);
  return 0;

}
