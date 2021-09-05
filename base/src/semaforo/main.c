#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i y el PID de mi papá es: %d\n", getpid(), getppid());
}
