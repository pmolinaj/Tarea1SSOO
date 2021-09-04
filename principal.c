#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>




int main(int argc, const char **argv)
{
  // Creamos al primer proceso hijo del proceso principal, que será la fábrica
  pid_t fabrica = fork();
  
  if (fabrica == 0)
  {   
      
      void sig_handler(int signum){
      int repartidores = 10;
      repartidores -= 1;
      printf("\n", repartidors)
      }
      signal(SIGALRM,sig_handler); // Register signal handler 
      alarm(2);  // Scheduled alarm after 2 seconds
      
      pid_t id_padre = getppid();


      printf("soy el proceso fábrica, siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);


  }

  else if (fabrica > 0)
  {
    pid_t id_padre = getpid();
    printf("Soy el proceso principal y mi PID es: %d\n", id_padre);


    //Creamos al segundo proceso hijo del proceso principal, que será el primer semáforo.
    pid_t semaforo_1 = fork();

    if (semaforo_1 == 0)
    { pid_t id_padre = getppid();
      printf("soy el proceso semáforo (1), siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
    }
    
    else if (semaforo_1 > 0)
    {
      //Creamos al tercer proceso hijo del proceso principal, que será el segundo semáforo.
      pid_t semaforo_2 = fork();

      if (semaforo_2 == 0)
      { pid_t id_padre = getppid();
        printf("soy el proceso semáforo (2), siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
      }

      else if (semaforo_2 > 0)
      {
        //Creamos al cuarto proceso hijo del proceso principal, que será el tercer semáforo.
        pid_t semaforo_3 = fork();

        if (semaforo_3 == 0)
        { pid_t id_padre = getppid();
          printf("soy el proceso semáforo (3), siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
        }

      }


    }
  

  }
  
  } 
