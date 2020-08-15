#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_PROCESSOS 4

/*variaveis globais*/
unsigned long int *entrada;	
 
int i = 0;
int k =0;
int flag;


  
  


/*funcao que realiza a leitura dos numeros a serem analisados*/
void ler_vetor (void){
 
  char fim;

  do {
      scanf("%ld%c", &entrada[i], &fim);
      i++;
    } while(fim != '\n');

      
}

void calculo_primo (int primos){
 
 


  int div = 0;
 
 
  for (k = 1; k <= primos; k++) {
    if (primos % k== 0) { 
     div++;
    }
  }
    
  if (div == 2){
   flag = 1;
    }
  else{
   ;
	}
}


 
int main() {

  /*aloca memoria para o vetor entrada*/
  entrada = (unsigned long int*) malloc (sizeof(unsigned long int)*100);

  
   
 /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

/*cria memoria compartilhada para o vetor entrada*/
 int *primo;
  primo = (int*) mmap(NULL, sizeof(int)*i,protection, visibility, 0, 0);


/* Cria memoria compartilhada para a variavel contador*/
    int *contador;	
    contador = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  
  /*cria memoaria compartilahda para ponteiro l*/
  int *l;
  l = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  
  *l = i;  
  *primo = entrada[*l];
  
  
 /*cria os processos*/ 
  pid_t filho[N_PROCESSOS];
  
  ler_vetor();

  
/*cria processos filhos*/
  for (int j=0; j<N_PROCESSOS; j++) {
    filho[j] = fork();

sleep(1); 
    
    while (*l >= 0){


      if (j == 0) {
      calculo_primo(*primo);
      if (flag==1){
       *contador = *contador+1;
       }
      *l = *l -1;
      
      
      
      }


      else if (j == 1) {
      /*executa no processo filho 1*/
      calculo_primo(*primo);
       if (flag==1){
       *contador = *contador+1;
       }
      *l = *l -1;
      
      
      }

      else if (j== 2) {
      /*executa no processo filho 2*/
      calculo_primo(*primo);
       if (flag==1){
       *contador = *contador+1;
       }
      *l = *l -1;
      
      
      }

      else if (j== 3) {
      /*executa no processo filho 3*/
      
      calculo_primo(*primo);
       if (flag==1){
       *contador = *contador+1;
       }
      *l = *l -1;
      
      }
    }  




    exit(0);
  }

  /*espera processos acabar de terminar*/
  for (int j=0; j<N_PROCESSOS; j++) {
    waitpid(filho[j], NULL, 0);
  }
  
  

/*informa quantidade de primos*/
  printf("%d\n", *contador);
  return 0;

}
