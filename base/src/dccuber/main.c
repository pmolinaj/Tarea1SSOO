#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");

  int status;

  // Creamos al primer proceso hijo del proceso principal, que será la fábrica
  pid_t fabrica = fork();
  
  
  if (fabrica == 0)
  {   
      pid_t id_padre = getppid();
      printf("soy el proceso fábrica, siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
  }

  else if (fabrica > 0)
  {
    //Creamos al segundo proceso hijo del proceso principal, que será el primer semáforo.
    pid_t semaforo_1 = fork();

    if (semaforo_1 == 0)
    { pid_t id_padre = getppid();
      printf("soy el proceso semáforo (1), siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
      char *args[]={"./semaforo",NULL};
      execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
      
    }
    
    else if (semaforo_1 > 0)
    {
      printf("%d\n", semaforo_1);
      //Creamos al tercer proceso hijo del proceso principal, que será el segundo semáforo.
      pid_t semaforo_2 = fork();

      if (semaforo_2 == 0)
      { pid_t id_padre = getppid();
        printf("soy el proceso semáforo (2), siempre retorno PID cero, pero el id de mi papá es: %d\n", id_padre);
        char *args[]={"./semaforo",NULL};
        execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
      }

      else if (semaforo_2 > 0)
      {
        //Creamos al cuarto proceso hijo del proceso principal, que será el tercer semáforo.
        pid_t semaforo_3 = fork();

        if (semaforo_3 == 0)
        { //pid_t id_padre = getppid();
          char *args[]={"./semaforo",NULL};
          execvp(args[0],args); //Con esto mandamos el proceso al archivo semaforo/main.c
        }

        else if (semaforo_3 > 0)
        {
          printf("Liberando memoria...\n");
          input_file_destroy(data_in);
        }
      }
    }
    waitpid(fabrica, &status, 0);
    //printf("Exit status: %d\n", WEXITSTATUS(status));
  }
  //printf("Liberando memoria...\n");
  //input_file_destroy(data_in);
}


