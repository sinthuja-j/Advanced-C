#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>


/*
 * Assignment2: Using pipe, for bi-directional programming between parent and child processes
 * Author: Sinthuja Jeevarajhan
 * Professor: Anwar Haque
 * Date: Thursday September 28, 2023
 */

//three functions provided by professor
int summation(int start, int end)
{
	int sum = 0;
	if (start < end)
	{
		sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
	}
	return sum;
}

int ith_part_start(int i, int N, int M)
{
	int part_size = N / M;
	int start = i * part_size;
	return start;
}
int ith_part_end(int i, int N, int M)
{
	int part_size = N / M;
	int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
	return end;
}

//main function, accepts command line argument values - file followed by two integer values to represent N and M
int main(int argc, char **argv)
{
    //port to read and write
    int port[2];

    //process for first child
    pid_t child_1;
    // converting M and N from char * to int
    int M = atoi(argv[2]);
    int N = atoi(argv[1]);

    // input argument validation check, must input 3 values formatted as such
    if (argc !=3){
        printf("Invalid input argument. Usage:\n");
        printf("Must be formatted as: ./assignment2.out 12 5\n");
        exit(1);
    }
    // Error handelling: pipe was unsuccessful, output this error
    if (pipe(port) < 0) {
        perror("pipe error");
        exit(0);
    }
    // Parent process has started, output PID
    printf("\nparent(PID %d): process started\n\n", getpid());
    // Forking first child
    printf("parent(PID %d): forking child_1\n\n", getpid());
    // Create first child process
    child_1 = fork();
    // Error handelling: Child fork process has failed
    if (child_1 < 0){
        printf("fork unsuccessful\n");
        exit(1);
    }

    //if child fork was successful, report its process ID and parent process ID
    if (child_1 == 0){
        printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
        printf("parent (PID %d)): waiting for child_1 (PID %d) to complete\n", getppid(), getpid());
    }

    //if child fork acting as parent, wait for process for child process to be completed
    if (child_1 > 0) {
        wait(NULL);
        printf("parent (PID %d): completed parent\n", getpid());
    } else {
        //child_1 process has started, reports it's process ID and parent process ID
        printf("child_1 (PID %d): process started from parent (PID %d)\n\n", getpid(), getppid());

        //output how many child processes will be created based on M value entered
        printf("child_1 (PID %d): forking child_1.1....child_1.%d\n", getpid(), M);

        // loop to create M child processes, stop when reaching M children
        for (int i=0; i<M; i++) {
            // create temp child and call the fork function
            pid_t tmpChild;
            tmpChild = fork();
            // increase the child number, to display in print statements
            int numChild = i+1;
            // if fork call successful print the according child number and its PID
            if (tmpChild == 0) {
                printf("child_1.%d (PID %d): fork() successful\n", numChild, getpid());

                //calculate the partial sum using the functions provided
                int start = ith_part_start(i, N, M);
                int end = ith_part_end(i, N, M);
                int partial_sum = summation(start, end);

                //output the partial sum calculated at each loop iteration, with the child number and PID
                printf("child_1.%d (PID %d): partial sum: [%d - %d] = %d\n", numChild, getpid(), start, end, partial_sum);
                // write the partial sum to the pipe
                write (port[1], &partial_sum, sizeof(int)); //or could be size of int

                // found this function on the internet, to call the exit function to ensure the child process doesn't continue iterating through the loop
                exit(0);
            }
        }

        // initialize the total sum
        int totalSum = 0;
        // read the partial sum from the pipe, and sum it to the total value for M total children
        for (int i =0; i<M; i++) {
            int partial_sum;
            read(port[0], &partial_sum, sizeof(int)); //ask when you read what second parameter should be
            totalSum+= partial_sum;
        }

        //output the total sum and output child_1 is completed
        printf("child_1 (PID %d): total sum= %d\n", getpid(), totalSum);
        printf("child_1 (PID %d): child_1 completed\n", getpid());

        //ensure that each parent process waits
        for (int i = 0; i < M; i++)
        {
            wait(NULL);
         }

        close(port[0]);
        close(port[1]);

    }

}
