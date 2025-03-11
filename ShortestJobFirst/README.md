C Program: Shortest Job First (SJF) CPU Scheduling Algorithm

📜 Description

This C program implements the Shortest Job First (SJF) CPU scheduling algorithm, a non-preemptive scheduling method that selects the process with the shortest burst time for execution next. It reads input from a file containing multiple test cases with process names, arrival times, and burst times, and simulates the scheduling of processes based on the SJF algorithm.

The program calculates key performance metrics such as the turnaround time (TAT) and waiting time (WT) for each process and then computes the average TAT and WT across all processes in a given test case.

🖥️ Key Features

Shortest Job First (SJF) Scheduling: Selects the process with the shortest burst time to execute next.
Process Metrics Calculation: Computes and displays the turnaround time and waiting time for each process.
Average Calculations: Calculates and displays the average turnaround time and average waiting time for all processes in a test case.
Test Case Support: Handles multiple test cases provided in a text file.
Queue Data Structures: Uses queues to manage arriving and ready processes in the scheduling algorithm.

🚀 How It Works

Input Format: The program reads from an input file named sjf_input.txt. Each test case contains several lines of process data formatted as:

For each test case, processes are read and stored in an arrival queue.
Processes are scheduled based on the Shortest Job First algorithm, where the process with the shortest burst time is selected for execution next.
The program outputs the state of the CPU at each time unit, showing which process is being executed.

Metrics:

Turnaround Time (TAT): The total time taken from arrival to completion of a process (TAT = Wait Time + Burst Time).
Waiting Time (WT): The total time a process spends waiting in the ready queue before being executed.
Average Calculations: After scheduling all processes, the program calculates and prints the average turnaround time and average waiting time for the test case.

Program Output:

The program outputs the status of each process at each time unit, including which process is executing and whether any new processes have arrived.
At the end of each test case, it outputs the average turnaround time and average waiting time.

🚀 Usage Instructions

Input File Format:

The input file (sjf_input.txt) contains multiple test cases. Each test case is a series of process entries, where each entry has:
process_name (e.g., "P1", "P2")
arrival_time (the time the process arrives)
burst_time (the time the process needs to complete execution)


📂 Files Included

sjf_scheduling.c: The main C program that implements the SJF CPU scheduling algorithm.
sjf_input.txt: The input file containing multiple test cases, each with a series of processes defined by their name, arrival time, and burst time.

🛠️ Prerequisites

A C compiler that supports the C Standard Library (such as GCC).
Basic knowledge of CPU scheduling algorithms (especially Shortest Job First).
