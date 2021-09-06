#include <stdio.h>
#include <unistd.h>
#include "../file_manager/manager.h"
#include <stdlib.h>


void signal_handlr(int signum)
{
  printf("La señal es: %d\n", signum);
}

int main(int argc, char const *argv[])
{
  //int cambios = 0;
  int delay = atoi(argv[1]);
  int pid_fabrica = atoi(argv[2]);
  int id_semaforo = atoi(argv[3]);
  //int rojo = 0;
  //int verde = 1;
  printf("I'm the SEMAFORO process and my PID is: %i y el PID de mi papá es: %d y mi delay es: %d y el PID del proceso fábrica es: %d y el id del semaforo es: %d\n", getpid(), getppid(), delay, pid_fabrica, id_semaforo);
  //while (1){
   // sleep(delay);
    //send_signal_with_int(pid_fabrica, verde + id_semaforo);
    //send_signal_with_int(pid_fabrica, rojo + id_semaforo);
  //}


  //printf("%i\n", cambios);
}
