C Program: Sum of Natural Number Calculator

📜 Description

This C program demonstrates advanced process management by utilizing fork() and execl() system calls. The program calculates the sums of natural numbers from 1 to N and from 1 to M using two separate processes. It goes a step further by forking additional child processes to execute external programs, computing the sums concurrently.

🖥️ Key Features

Process Management: Utilizes the fork() system call to create child processes.
Inter-Process Communication: The parent process waits for child processes to complete using wait().
External Program Execution: Child processes execute external programs using execl() to compute the sums.
Input Validation: The program ensures proper input arguments, preventing errors and unexpected behavior.

⚙️ How It Works

Parent Process:

The parent process forks child_1, which then forks child_1.1 and child_1.2 to calculate the sums in parallel.
The parent waits for child_1 to complete before forking child_2.
child_2 executes an external program to calculate the sum from 1 to M.
Child Process 1 (child_1):

This process creates two child processes: child_1.1 and child_1.2.
Each child executes an external program to compute the sum for N and M, respectively.
Child Process 2 (child_2):

This process executes an external program to calculate the sum from 1 to M using execl().

🚀 Usage Instructions

Command Line Arguments:

N: The upper limit for the first sum of natural numbers.
M: The upper limit for the second sum of natural numbers.
external_program1: The first external program to compute the sum from 1 to N.
external_program2: The second external program to compute the sum from 1 to M.
Example Command: ./assignment1.out 12 5 "Sudipto" ./external_program1.out ./external_program2.out

📂 Files Included

assignment1.c: The core C program that demonstrates process forking, inter-process communication, and external program execution.
external_program1.out: An external program that calculates the sum of numbers from 1 to N.
external_program2.out: An external program that calculates the sum of numbers from 1 to M.

🛠️ Prerequisites

A C compiler such as GCC.
Proper permissions to execute the external programs on your system.
