C Program: Threading Functions for Shared Data Access

📜 Description

This C program demonstrates multithreading in C using POSIX threads (pthreads). The program performs multiple tasks by creating threads that access and update shared data (stored in a global array). It showcases the creation of threads for different operations like summation, checking if a number is even or odd, performing multiplication, and reversing numbers.

🖥️ Key Features

Multithreading: The program uses multiple threads to perform different tasks concurrently, enhancing performance and demonstrating thread synchronization.
Shared Data Access: The program uses a global array that is shared between threads, allowing them to read and write values concurrently.
Thread Operations:
Summation: Calculates the sum of two numbers and stores the result.
Even/Odd Check: Determines if a number is even or odd.
Multiplication: Multiplies two numbers and stores the result.
Reversing a Number: Reverses the digits of a number.

🚀 How It Works
Main Function:


The user inputs two integers X and Y.
These values are stored in the input_array[] which is shared by all threads.
The main function creates three threads:
Thread 1 performs the summation of X and Y.
Thread 2 first checks if the result is even or odd, then performs the multiplication.
Thread 3 reverses the multiplication result.

Thread Operations:

Sum Function: Computes the sum of X and Y and stores it in input_array[2].
Even/Odd Function: Checks if the value stored in input_array[2] is even or odd.
Multiplication Function: Multiplies X and Y and stores the product in input_array[3].
Reverse Function: Reverses the digits of the number in input_array[3].

Thread Synchronization:

The main function uses pthread_join to ensure that the threads execute in the correct order, allowing for deterministic output.

🚀 Usage Instructions

Command Line Arguments:
X: The first integer input.
Y: The second integer input.
Example Command: ./assignment3.out 21 3

📂 Files Included

assignment3.c: The core C program that demonstrates multithreading with shared data access and different thread operations.

🛠️ Prerequisites

A C compiler that supports pthread (such as GCC).
Basic knowledge of multithreading and pthreads in Unix-like systems.
