#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Author: Sinthuja Jeevarajhan (251241418)
// Professor: Anwar Haque
// Date: Sept 19, 2023
// Purpose: C program that calculates the sums of natural numbers from 1 to N and from 1 to M using two separate processes.

int main(int argc, char **argv)
{
    pid_t child1;
    int i;

    // input argument validation check
    if (argc !=6){
      printf("Invalid input argument. Usage:\n");
      printf("./assignment1.out 12 5 \"Sudipto\" ./external_program1.out ./external_program2.out\n");
      exit(1);
    }


    printf("\nparent(PID %d): process started\n\n", getpid());
    printf("parent(PID %d): forking child_1\n\n", getpid());
    child1 = fork(); // create process Child_1
    if (child1 < 0){
      printf("fork unsuccessful\n");
      exit(1);
    }

    if (child1 == 0){ // in process Child_1, report its process ID and its parent process ID
      printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
      printf("parent (PID %d)): waiting for child_1 (PID %d) to complete\n", getppid(), getpid());
    }

    // process parent would wait for all computation in process 1 complete
    // before starting process Child_2 and make external call from process Child 2
    if( child1 > 0 ){
	    wait(NULL);

      pid_t child2;
      printf("parent (PID %d): forking child_2\n", getpid());
      child2 = fork();
      if (child2 > 0){
        wait(NULL);
        printf("parent (PID %d): completed parent\n", getpid());
      }
      else { // child2 in action
        printf("parent (PID %d): fork successful for child_2 (PID %d)\n", getppid(), getpid());
        printf("child_2 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
        printf("child_2 (PID %d): calling an external program [%s]\n", getpid(), argv[5]);
        execl(argv[5], argv[3], NULL); // from process child_2 calling external program
      }


    } else {
 	  // Process Child_1 will create 2 additional children processes Child1_1 and Child1_2
      printf("child_1 (PID %d): process started from parent (PID %d)\n\n", getpid(), getppid());
      pid_t child1_1, child1_2;

      printf("child_1 (PID %d): forking child_1.1\n", getpid());
      child1_1 = fork(); // first create process Child1_1
      if (child1_1 > 0) {
    	   wait(NULL);
         printf("child_1 (PID %d): completed child_1.1\n\n", getpid());
      }

      if (child1_1 == 0) {
        printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
        printf("child_1.1 (PID %d): calling an external program [%s]\n", getpid(), argv[4]);
        execl(argv[4], argv[1], NULL); // call external program to compute value N
      }


      printf("child_1 (PID %d): forking child_1.2\n", getpid());
      child1_2 = fork(); // second create process Child1_2
      if (child1_2 > 0) {
        wait(NULL);
        printf("child_1 (PID %d): completed child_1.2\n\n", getpid());
      }
      if (child1_2 == 0) {
        printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
        printf("child_1.2 (PID %d): calling an external program [%s]\n", getpid(), argv[4]);
        execl(argv[4], argv[2], NULL); // call external program to compute value M
      }

 }

 return 0;
}
