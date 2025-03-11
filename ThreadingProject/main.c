#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * Assignment 3
 * Professor: Anwar Haque
 * Due: October 24, 2023
 * Author: Sinthuja Jeevarajhan
 * Purpose of the assignment: Gain experience with threading functions, create multiple threads for different tasks and how they can access shared data
 */

//create global input array for threads to access and update
int input_array[3];

//sum function - summation, S = X + Y, and then the result S will be written to the input_array[2].
void *sum(void *thread_id) {

    //store x and why as integers from the array
    int x = input_array[0];
    int y = input_array[1];

    //output to the screen that x and y have been read, and state the associated thread ID
    printf("thread_1 (TID %ul) reads X = %d and Y = %d from input_array[]\n", ((unsigned long)pthread_self()), x, y);

    // Calculate the sum and store it in array[2]
    int sum = x + y;
    input_array[2] = sum;

    //output to the screen the sum with the associated thread ID
    printf("thread_1 (TID %ul) writes X+Y = %d to input_array[2]\n", ((unsigned long)pthread_self()), sum);

}

//even odd function - states whether an integer is even or odd
void *even_odd(void *thread_id) {

    //output to the screen that the sum has been read, and state the associated thread ID
    printf("thread_2 (TID %ul) reads %d from the input_array[2]\n", ((unsigned long)pthread_self()), input_array[2]);

    //if the integer divides evenly by 0 with no remainder then it is even number else odd, print to the screen to the screen whether its even or odd with the thread's ID
    if (input_array[2] % 2 == 0) {
        printf("thread_2 (TID %ul) identifies that %d is an even number\n", ((unsigned long)pthread_self()), input_array[2]);
    } else {
        printf("thread_2 (TID %ul) identifies that %d is an odd number\n", ((unsigned long)pthread_self()), input_array[2]);
    }


}

//multiplication - multiply two integers and generate the product and write to input_array[3]
void *multiplication(void *thread_id) {
    //store x and y from the input array
    int x = input_array[0];
    int y = input_array[1];

    // Calculate the product and store it in input_array[3]
    int product = x * y;
    input_array[3] = product;
    //output to the screen the product and state the according thread ID
    printf("thread_2 (TID %ul) reads X and Y from input_array[],writes X*Y = %d to input_array[3] \n", ((unsigned long)pthread_self()),
           product);

    return NULL;

}

//function to call the even and odd function and the multiplication function to allow thread 2 to execute two functions
void *even_oddAndMultiplication(void *thread_id) {
    even_odd(thread_id);
    multiplication(thread_id);
}

//reverse function - reverses the integer  and stores the reversed integer into input_array[3]
void *reverse_num(void *thread_id) {
    //store the integer value twice in two seperate variables x and y
    int x = input_array[3];
    int y = input_array[3];
    //store the original number which is unchanged throughout the function, to output later
    int reversed = 0;
    //output to the screen the original integer and the associated thread ID
    printf("thread_3 (TID %ul) reads %d from input_array[3]\n", ((unsigned long)pthread_self()), x);
    // Reverse the digits of x - found this function (next 3 lines) on the internet - used it to help me understand how to reverse an integer
    while (y > 0) {
        reversed = reversed * 10 + y % 10;
        y /= 10;
    }

    // Store the reversed number back in input_array[3]
    input_array[3] = reversed;
    //output to the screen the before and the after of reversing as well as the associated thread ID number
    printf("thread_3 (TID %ul) reverses the number from %d -> %d\n", ((unsigned long)pthread_self()), x, input_array[3]);

}

//get the input from the command line, formatted as the file name x y
int main(int argc, char **argv) {
    //initalize the three threads
    pthread_t thread_1, thread_2, thread_3;
    //convert the commmand line input to integers and store them as x and y accordingly
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);


    // input argument validation check, must input 3 values formatted as filename x y - 3 arguments total
    if (argc != 3) {
        printf("Invalid input argument. Usage:\n");
        printf("Must be formatted as: ./assignment3.out 21 3\n");
        exit(1);
    }
    //output the recieved x and y values with the parent process identifier
    printf("parent (PID %d) receives X=%d and Y=%d from the user\n", getpid(), x, y);
    //store the x and y values in the integer array
    input_array[0] = x;
    input_array[1] = y;
    //output to the screen that you wrote these values to the array, with the parent process identifier specified
    printf("parent (PID %d) writes X=%d and Y=%d to input_array[]\n", getpid(), x, y);

    //create the first thread to execute the sum function
    pthread_create(&thread_1, NULL, sum, NULL);
    //join the thread to ensure it executes immediatly after creation to prevent non determenistic output
    pthread_join(thread_1, NULL);
    //create the second thread to execute the evenodd/multiplication helper function
    pthread_create(&thread_2, NULL, even_oddAndMultiplication, NULL);
    //join the thread to ensure it executes immediatly after creation to prevent non determenistic output
    pthread_join(thread_2, NULL);
    //create the third thread to execute the reverse number function
    pthread_create(&thread_3, NULL, reverse_num, NULL);
    //join the thread to ensure it executes immediatly after creation to prevent non determenistic output
    pthread_join(thread_3, NULL);

    return 0;
}
