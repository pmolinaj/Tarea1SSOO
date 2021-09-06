#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../file_manager/manager.h"

void signal_handlr(int signal, siginfo_t *info_signal, void *ucontext)
{
  int valor = info_signal->si_value.sival_int;
  printf("el valor recibido es: %d\n", valor);
}

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  //printf("Leyendo el archivo %s...\n", filename);
  //printf("- Lineas en archivo: %i\n", data_in->len);
  //printf("- Contenido del archivo:\n");
//
  //printf("\t- ");
  //for (int i = 0; i < 4; i++)
  //{
  //  printf("%s, ", data_in->lines[0][i]);
  //}
  //printf("\n");
//
  //printf("\t- ");
  //for (int i = 0; i < 5; i++)
  //{
  //  printf("%s, ", data_in->lines[1][i]);
  //}
  //printf("\n");

  int status;

  // Creamos al primer proceso hijo del proceso principal, que será la fábrica
  pid_t fabrica = fork();
  
  
  if (fabrica == 0)
  {   
      int x = atoi(data_in->lines[1][1]); //Cantidad de repartidores a crear
      int t = atoi(data_in->lines[1][0]); //tiempo que pasa entre la creación de c/repartidor
      printf("Hay que crear repartidores cada %d segundos\n", t);
      printf("Tengo que generar %d repartidores\n", x);
      connect_sigaction(SIGUSR1, signal_handlr);
      for(int i=0;i<3;i++) // Cambiar por i < x, para que se generen x repartidores.
      {
        if(fork() == 0)
        { sleep(t); //Con este sleep hacemos que se creen cada dos segundos los repartidores
          int x = i+1;
          int length = snprintf( NULL, 0, "%d", x );
          char* str = malloc( length + 1 );
          snprintf( str, length + 1, "%d", x );
          char *args[]={"./repartidor",str, NULL};
          execvp(args[0],args);
        }
        sleep(t); //Con este sleep también hacemos que se creen cada dos segundos los repartidores. (Con 2 sleep funciona, pero con uno no)
      }
      pid_t wpid;
      while ((wpid = wait(&status)) > 0); //Con esto nos aseguramos que el proceso Fábrica espera a todos sus hijos (Procesos de Repartidores) 
      printf("Proceso fabrica recién terminó");
  }

  else if (fabrica > 0)
  {
    
    //Creamos al segundo proceso hijo del proceso principal, que será el primer semáforo.
    pid_t semaforo_1 = fork();

    if (semaforo_1 == 0)
    { 
      int id_semaforo_1 = 1;
      int length_semaforo_1 = snprintf( NULL, 0, "%d", id_semaforo_1);
      char* str_semaforo_1 = malloc( length_semaforo_1 + 1 );
      snprintf( str_semaforo_1, length_semaforo_1 + 1, "%d", id_semaforo_1);

      int delay = atoi(data_in->lines[1][2]);
      int length = snprintf( NULL, 0, "%d", delay );
      char* str = malloc( length + 1 );
      snprintf( str, length + 1, "%d", delay );

      int length_fabrica = snprintf( NULL, 0, "%d", fabrica );
      char* str_fabrica = malloc( length_fabrica + 1 );
      snprintf( str_fabrica, length_fabrica + 1, "%d", fabrica );
      char *args[]={"./semaforo", str, str_fabrica, str_semaforo_1,  NULL};
      execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
      free(str);
      free(str_fabrica);
            
    }
    
    else if (semaforo_1 > 0)
    {
      printf("pid sem_1 %d\n", semaforo_1);
      //Creamos al tercer proceso hijo del proceso principal, que será el segundo semáforo.
      pid_t semaforo_2 = fork();

      if (semaforo_2 == 0)
      {
        int id_semaforo_2 = 2;
        int length_semaforo_2 = snprintf( NULL, 0, "%d", id_semaforo_2);
        char* str_semaforo_2 = malloc( length_semaforo_2 + 1 );
        snprintf( str_semaforo_2, length_semaforo_2 + 1, "%d", id_semaforo_2);

        int delay = atoi(data_in->lines[1][3]);
        int length = snprintf( NULL, 0, "%d", delay );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", delay );

        int length_fabrica = snprintf( NULL, 0, "%d", fabrica );
        char* str_fabrica = malloc( length_fabrica + 1 );
        snprintf( str_fabrica, length_fabrica + 1, "%d", fabrica );
        char *args[]={"./semaforo", str, str_fabrica, str_semaforo_2, NULL}; 
        execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
      }

      else if (semaforo_2 > 0)
      {
        printf("pid sem_2 %d\n", semaforo_2);
        //Creamos al cuarto proceso hijo del proceso principal, que será el tercer semáforo.
        pid_t semaforo_3 = fork();

        if (semaforo_3 == 0)
        { 
          int id_semaforo_3 = 3;
          int length_semaforo_3 = snprintf( NULL, 0, "%d", id_semaforo_3);
          char* str_semaforo_3 = malloc( length_semaforo_3 + 1 );
          snprintf( str_semaforo_3, length_semaforo_3 + 1, "%d", id_semaforo_3);      

          int delay = atoi(data_in->lines[1][4]);
          int length = snprintf( NULL, 0, "%d", delay );
          char* str = malloc( length + 1 );
          snprintf( str, length + 1, "%d", delay );

          int length_fabrica = snprintf( NULL, 0, "%d", fabrica );
          char* str_fabrica = malloc( length_fabrica + 1 );
          snprintf( str_fabrica, length_fabrica + 1, "%d", fabrica );
          char *args[]={"./semaforo", str, str_fabrica, str_semaforo_3, NULL};
          execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
        }

        else if (semaforo_3 > 0)
        {
          printf("pid sem_3 %d\n", semaforo_3);
          printf("Liberando memoria...\n");
          input_file_destroy(data_in);
        }
      }
    }
    waitpid(fabrica, &status, 0);
    //printf("Exit status: %d\n", WEXITSTATUS(status));
  }
}


