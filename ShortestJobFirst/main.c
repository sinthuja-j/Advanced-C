/*
 * Assignment 4: SJF Scheduling
 * Professor: Anwar Haque
 * Author: Sinthuja Jeevarajhan
 * Date: November 7th 2023
 * Purpose: To understand CPU scheduling algorithim and design a scheduling proccess that follows the shortest job first procedure
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create a structure to hold all the attributes of the process
struct process {
    char *pName;
    int artTime;
    int burstTime;
    int waitTime;
    int progress;
};
typedef struct process process;
//structure to store a node in the queue
struct node {
    struct process *data;
    struct node *next;
};
typedef struct node node;

//structure of a queue
struct queue {
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;

//creating queue
queue *create_queue() {
    queue *q = malloc(sizeof(queue));
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;

    return q;
}
//function to check if a queue is empty
int isempty(queue *q) { return (q->rear == NULL); }

//function to initialize a proccess
process *create_process(char *pName, int artTime, int burstTime) {
    process *p = malloc(sizeof(process));
    p->pName = pName;
    p->artTime = artTime;
    p->burstTime = burstTime;
    p->waitTime = 0;
    p->progress = 0;

    return p;
}
//function to add a process to the head of the queue
void enqueue(queue *q, process *data) {
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
    if (!isempty(q)) {
        q->rear->next = tmp;
        q->rear = tmp;
    } else {
        q->front = tmp;
        q->rear = tmp;
    }
    q->count++;
}

//function to remove a proccess from the end of a queue
process *dequeue(queue *q) {
    if (q->count == 0) {
        return NULL;
    }

    node *tmp;
    process *data = q->front->data;
    tmp = q->front;

    if (q->count == 1) {
        free(tmp);
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
        free(tmp);
    }

    q->count--;
    return (data);
}

int main() {
    //hard coded file name
    const char *filename = "sjf_input.txt";
    FILE *file = fopen(filename, "r");
    //array to hold each line from the file
    char line[256];
    //variable to store the test case #
    int test_num = 0;

    //initialize ready and arrival queue
    queue *arrival_q = create_queue();
    queue *ready_q = create_queue();

    //while file is not empty
    while (fgets(line, sizeof(line), file)) {
        //increase the test case number to represent the line in the file
        test_num++;
        char *test = line;

        //intialize calculation times and process count
        float avgTaTime = 0.0;
        float avgWaitTime = 0.0;
        int process_count = 0;

        // Remove trailing newline character
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = 0;

        //print the test case number
        printf("Test case #%d: %s\n", test_num, test);

        char *token = strtok(test, " ");
        // loop through the string to extract all other tokens
        while (token != NULL) {
            //convert the proccess name to a char array
            char *process_name = token;
            //convert the burst and arrival time to integers
            int arrival_time = atoi(strtok(NULL, " "));
            int burst_time = atoi(strtok(NULL, " "));

            // printf("Process Created: %s, %d, %d\n", process_name, arrival_time, burst_time);
            process *p = create_process(process_name, arrival_time, burst_time);
            enqueue(arrival_q, p);

            //proccess the space at the end
            token = strtok(NULL, " ");
        }

        //store the proccess count in the arrival queue attribute
        process_count = arrival_q->count;


        int t = 0;
        int tSpent = 0;
        process *curr = NULL;
        process *next = dequeue(arrival_q);

        //print the number of proccesses and indicate the scheduling started
        printf("Number of Processes: %d\n", process_count);
        printf("Process Scheduling Started:\n");

        //read until the ready and the  arrival queue is empty
        while (!isempty(ready_q) || !isempty(arrival_q) || curr != NULL) {
            printf("CPU Time %d: ", t);

            while (next != NULL && next->artTime == t) {
                printf("[%s Arrived] ", next->pName);

                //when a proccess arrives add it to the queue
                enqueue(ready_q, next);
                next = dequeue(arrival_q);
            }

            //when proccess is ready to be served, remove it from the ready queue
            if (curr == NULL && !isempty(ready_q)) {
                curr = dequeue(ready_q);
                curr->waitTime += t - curr->artTime;
            }

            if (curr != NULL) {
                curr->progress++;
                tSpent++;
                printf("%s [%d/%d]\n", curr->pName, curr->progress, curr->burstTime);

                if (curr->progress == curr->burstTime) {
                    int taTime = curr->waitTime + curr->burstTime;
                    printf("Process %s completed with Turn Around Time: %d, Waiting "
                           "Time: %d\n",
                           curr->pName, taTime, curr->waitTime);
                    //accumulate total times for calculations
                    avgTaTime += taTime;
                    avgWaitTime += curr->waitTime;
                    //free node space
                    free(curr);
                    curr = NULL;
                    //reset time spent for each proccess
                    tSpent = 0;
                }
            } else {
                printf("None\n");
            }

            t++;
        }

        //calculate average turn around time and waiting time
        avgTaTime /= process_count;
        avgWaitTime /= process_count;

        printf("Process scheduling completed with Avg Turn Around Time: %.2f, Avg "
               "Waiting Time: %.2f\n\n",
               avgTaTime, avgWaitTime);
    }

    //free up the space and close the files
    free(arrival_q);
    free(ready_q);
    fclose(file);

    return 0;
}
