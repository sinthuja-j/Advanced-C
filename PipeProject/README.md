C Program: Bi-directional Communication between Parent and Child Processes using Pipe

📜 Description

This C program demonstrates bi-directional communication between parent and child processes using pipes. The program divides the task of calculating the sum of natural numbers between multiple child processes, enabling parallel computation. The parent process communicates with child processes to collect and sum partial results, showcasing inter-process communication (IPC).

🖥️ Key Features

Forking Processes: The program forks multiple child processes based on the user-specified value (M), with each child responsible for calculating a partial sum.
Pipe Communication: Utilizes a pipe to send partial sums from child processes to the parent process for aggregation.
Parallel Processing: Child processes compute partial sums concurrently, enhancing performance and demonstrating process synchronization.
Dynamic Task Distribution: The task is dynamically split based on the value of M, with each child handling a portion of the total sum.

⚙️ How It Works

Parent Process:

The parent process forks child_1 and establishes a pipe for communication.
Child_1 then forks M child processes (i.e., child_1.1 through child_1.M).
Each child computes a partial sum and writes it to the pipe.
The parent process reads the partial sums from the pipe and computes the total sum.
Child Process:

Each child computes a partial sum by calculating the sum of a specific range of natural numbers.
After calculating the partial sum, each child writes the result to the pipe and exits.
Pipe Communication:

The parent reads from the pipe to accumulate the partial sums from all child processes, ensuring proper synchronization and data flow.

🚀 Usage Instructions

Command Line Arguments:

N: The upper limit of the range for the sum of natural numbers.
M: The number of child processes that will calculate partial sums.
Example Command: ./assignment2.out 12 5

📂 Files Included

assignment2.c: The core C program that demonstrates bi-directional communication using pipes, forking processes, and parallel computation.

🛠️ Prerequisites

A C compiler such as GCC.
Basic knowledge of process management and pipes in Unix-like systems.
