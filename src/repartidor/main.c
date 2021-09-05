#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int n = atoi(argv[1]);
  int tiempo1 = 0;
  int tiempo2 = 0;
  int tiempo3 = 0;
  int tiempob = 0;  
  printf("I'm the REPARTIDOR process and my PID is: %i y el PID de mi papi es %i\n", getpid(), getppid());
  printf("repartidor numero %i\n", n);
}
