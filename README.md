# Advanced-C 🖥️
🚀 Dive into my advanced C projects, showcasing key OS concepts like process management, synchronization, memory management, and system calls! 💻 These projects bring to life essential OS fundamentals with hands-on implementations, including inter-process communication and file systems. Perfect for sharpening OS skills! 🔧 Below are the details of each project with their core features and functionality. 🚀


1. Sum of Natural Number Calculator ➕
   
Description:
This program calculates the sums of natural numbers from 1 to N and from 1 to M using two separate processes. It then forks additional child processes to compute the sums concurrently using external programs.

🔑 Key Features:

Process Management: Utilizes the fork() system call to create child processes.
Inter-Process Communication: Parent waits for child processes to complete using wait().
External Program Execution: Child processes execute external programs using execl() to calculate the sums.
Input Validation: Ensures proper input arguments, preventing errors and unexpected behavior.

2. Bi-directional Communication between Parent and Child Processes using Pipe 📬
3. 
Description:
This project demonstrates bi-directional communication using pipes, where the parent and child processes communicate to calculate the sum of natural numbers. The task is split among child processes, each responsible for calculating a partial sum.

🔑 Key Features:

Forking Processes: Forks multiple child processes for parallel computation.
Pipe Communication: Uses pipes to send partial sums to the parent for aggregation.
Parallel Processing: Computes partial sums concurrently to enhance performance.
Dynamic Task Distribution: Tasks are split based on user input.

3. Shortest Job First (SJF) CPU Scheduling Algorithm ⏱️
   
Description:
The program implements the Shortest Job First (SJF) CPU scheduling algorithm, which selects the process with the shortest burst time for execution. It reads input from a file containing multiple test cases and simulates the scheduling of processes.

🔑 Key Features:

SJF Scheduling: Selects the process with the shortest burst time.
Process Metrics Calculation: Computes turnaround time and waiting time.
Test Case Support: Handles multiple test cases and computes performance metrics.
Queue Data Structures: Uses queues to manage processes in the scheduling algorithm.

4. Threading Functions for Shared Data Access 🧵
   
Description:
This project demonstrates multithreading in C using POSIX threads (pthreads). Threads access and update shared data in a global array, performing various tasks like summation, checking for even/odd numbers, multiplication, and reversing numbers.

🔑 Key Features:

Multithreading: Enhances performance by running tasks concurrently.
Shared Data Access: Uses a global array shared by threads.
Thread Operations: Includes summation, even/odd check, multiplication, and reversal.
Thread Synchronization: Ensures correct execution order using pthread_join.

5. Bank Account Mutual Exclusion Program 💳
   
Description:
This program simulates bank transactions (deposits and withdrawals) using threads and mutexes for mutual exclusion. It ensures that only one thread can modify a bank account at a time, preventing data corruption during concurrent transactions.

🔑 Key Features:

Account Balances & Transactions: Handles multiple bank accounts and transactions.
Thread Synchronization with Mutex: Prevents data corruption with mutex locks.
Dynamic Thread Creation: Creates a thread for each deposit or withdrawal.
Error Handling & File I/O: Reads transaction details from an input file.
Unique Client Tracking: Tracks the number of unique clients interacting with accounts.


🛠️ Technologies Used:

C Programming 🖥️
POSIX Threads (pthread) 🧵
System Calls 🔧
Mutexes & Semaphores 🔒
Inter-Process Communication (IPC) 📡
Linux OS 🐧

🚀 Learning Outcomes:

Multithreading: Created and managed multiple threads to improve performance.
Synchronization: Applied synchronization techniques to avoid data race conditions.
Process Management: Worked with fork(), execl(), and pipes for process management and communication.
Scheduling Algorithms: Implemented CPU scheduling algorithms like Shortest Job First (SJF).
Real-World Applications: Simulated real-world applications such as banking and process scheduling.
