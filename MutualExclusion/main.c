/*
 * Assignment 5: Mutual Exclusion with Bank Accounts
 * Author: Sinthuja Jeevarajhan
 * Professor: Anwar Haque
 * Date: November, 21, 2023
 * Purpose: Get hands-on experience in developing mutual exclusion/semaphore/critical section
techniques and algorithms.Gain experience with the C programming language from process/threads synchronization
perspective.
 */

//import required libraries
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

//initialize the 5 bank accounts to 0
int acc1 = 0;
int acc2 = 0;
int acc3 = 0;
int acc4 = 0;
int acc5 = 0;
//counters for the number of accounts and clients
int numAccounts=0;
int numClients=0;
//initialize the threads
pthread_mutex_t lock;
pthread_t depThread, withThread;
//flags to assist with counting unique number of clients
int acc1Flag=0, acc2Flag=0, acc3Flag=0, acc4Flag=0, acc5Flag=0;

//structure to hold transaction information to pass to functions with thread to add money to an account
struct TransactionArgs {
    int accountNum;
    int amount;
};

//deposit function, executed by a thread
//uses account number and amount variables stored in structure
void deposit(void *args) {
    struct TransactionArgs *transArgs = (struct TransactionArgs *)args;
    int accountNum = transArgs->accountNum;
    int amount = transArgs->amount;

    //lock for mutual exclusion
    pthread_mutex_lock(&lock);
    //use the account number to identify the account and deposit the specified amount
    //account flag is set to 1 to identify the correct number of unique clients
    switch (accountNum) {
        case 1:
            acc1 += amount;
            acc1Flag=1;
            break;
        case 2:
            acc2 += amount;
            acc2Flag=1;
            break;
        case 3:
            acc3 += amount;
            acc3Flag=1;
            break;
        case 4:
            acc4 += amount;
            acc4Flag=1;
            break;
        case 5:
            acc5 += amount;
            acc5Flag=1;
            break;

    }
    //exit the mutual exclusion - and unlock
    pthread_mutex_unlock(&lock);
}

//withdraw function, executed by a thread to subtract money from an account
//uses account number and amount variables stored in structure
void withdraw(void *args) {
    struct TransactionArgs *transactionArgs = (struct TransactionArgs *)args;
    int accountNum = transactionArgs->accountNum;
    int amount = transactionArgs->amount;

    //lock for mutual exclusion
    pthread_mutex_lock(&lock);

    //use the account number to identify the account and deposit the specified amount
    //if statement within each case implemented to ensure balance does not go below 0, if it does then discard transaction
    //account flag is set to 1 to identify the correct number of unique clients
    switch (accountNum) {
        case 1:
            if (acc1 - amount >= 0) {
                acc1 -= amount;
                acc1Flag=1;
            }
            break;
        case 2:
            if (acc2 - amount >= 0) {
                acc2 -= amount;
                acc2Flag=1;
            }
            break;
        case 3:
            if (acc3 - amount >= 0) {
                acc3 -= amount;
                acc3Flag=1;
            }
            break;
        case 4:
            if (acc4 - amount >= 0) {
                acc4 -= amount;
                acc4Flag=1;
            }
            break;
        case 5:
            if (acc5 - amount >= 0) {
                acc5 -= amount;
                acc5Flag=1;
            }
            break;
    }
    pthread_mutex_unlock(&lock);
}

int main() {
    FILE *fp;
    //initialize array to hold each line from the file
    char line[100];

    //hard code the file name
    fp = fopen("assignment_5_input.txt", "r");
    //if error with the file return and output this error message
    if (fp == NULL) {
        printf("Input file cannot be found");
        return 0;
    }
    //while there is still lines to read in the file
    while (fgets(line, sizeof(line), fp)) {

        //store the first segment of the line seperated with a space
        char *str = strtok(line, " ");
        if (str == NULL) {
            continue; // Skip empty lines
        }
        //store the account and account number parsed from the file
        char account = str[0];
        int accountNum = atoi(&str[1]); // Convert the character to integer

        //get the next segment in the line
        str = strtok(NULL, " ");

        int str_count = 0;

        while (str != NULL && str[0] != ' ') {
            //if the line starts with an A it's to initialize the account balance
            if (account == 'A') {
                numAccounts++; //increase the number of accounts
                //if updating balance
                if (strcmp(str, "balance") == 0) {
                    // check account number and update the approproiate balance
                    //update the account flag to count the correct unique number of clients
                    str = strtok(NULL, " ");
                    int balanceAmount = atoi(str); //convert the balance to an int
                    if (accountNum == 1) {
                        acc1=balanceAmount;
                        acc1Flag=1;
                    }
                    if (accountNum == 2) {
                        acc2=balanceAmount;
                        acc2Flag=1;
                    }
                    if (accountNum == 3) {
                        acc3=balanceAmount;
                        acc3Flag=1;
                    }
                    if (accountNum == 4) {
                        acc4=balanceAmount;
                        acc4Flag=1;
                    }
                    if (accountNum == 5) {
                        acc5=balanceAmount;
                        acc5Flag=1;
                    }
                }
                //if start of line is c == client transaction
            } else if (account == 'C') {
                //if depositing call the deposit function with the deposit thread
                if (strcmp(str, "deposit") == 0) {
                    // Handle deposit transactions
                    str = strtok(NULL, " ");
                    char custAccount = str[0];
                    //store the customer account number
                    int custNum = atoi(&str[1]);
                    //convert the deposit amount to an integer
                    str = strtok(NULL, " ");
                    int depBalanceAmount = atoi(str);

                    //store the customer account number and deposit amount in the strucuture variables
                    struct TransactionArgs *transactionArgs = malloc(sizeof(struct TransactionArgs));
                    transactionArgs->accountNum = custNum;
                    transactionArgs->amount = depBalanceAmount;

                    // Create a new thread for deposit
                    pthread_create(&depThread, NULL, deposit, transactionArgs);
                    //join to avoid race condition
                    pthread_join(depThread, NULL);
                   //if client wants to withdraw
                } else if (strcmp(str, "withdraw") == 0) {
                    // convert the customer number to an integer
                    str = strtok(NULL, " ");
                    char custAccount = str[0];
                    int custNum = atoi(&str[1]);

                    //convert the withdraw amount to an integer
                    str = strtok(NULL, " ");
                    int withBalanceAmount = atoi(str);
                    //store the customer account number and withdrawl amount in the structure
                    struct TransactionArgs *transactionArgs = malloc(sizeof(struct TransactionArgs));
                    transactionArgs->accountNum = custNum;
                    transactionArgs->amount = withBalanceAmount;

                    // Create a new thread for withdraw
                    pthread_create(&withThread, NULL, withdraw, transactionArgs);
                    //join the thread for immediate execution
                    pthread_join(withThread, NULL);


                }

            }
            // Update str to progress through the string
            str = strtok(NULL, " ");
            str_count++;
        }
    }
    //check the flags to calculate the number of unique clients
    if (acc1Flag== 1) {
        numClients++;
    }
    if (acc2Flag== 1) {
        numClients++;
    }
    if (acc3Flag== 1) {
        numClients++;
    }
    if (acc4Flag== 1) {
        numClients++;
    }
    if (acc5Flag== 1) {
        numClients++;
    }
    //print the number of accounts and clients and account balance to the screen
    printf("No. of Accounts: %d", numAccounts);
    printf("\nNo. of Clients: %d", numClients);
    printf("\nA1 Balance %d", acc1);
    printf("\nA2 Balance %d", acc2);
    printf("\nA3 Balance %d", acc3);
    printf("\nA4 Balance %d", acc4);
    printf("\nA5 Balance %d", acc5);



    fclose(fp);
    return 0;
}
