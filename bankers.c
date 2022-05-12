#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUMBER_OF_CUSTOMERS 5   //number of customers set to the number of maxtrix rows
#define NUMBER_OF_RESOURCES 4   //number of resources set to the number of matrix columns

int available[NUMBER_OF_RESOURCES];                         //the available amount of each resource
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];      //the maximum demand of each customer
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];   //the amount currently allocated to each customer
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];         //the remaining need of each customer

int finish[NUMBER_OF_CUSTOMERS];    //1/0 if the process has finished

pthread_mutex_t mutex;

int request_resources(int customer_num)
{
    int safe = 1;   //determines if the request is safe
    int temp = 0;
    pthread_mutex_lock(&mutex);
    printf("customer %d is requesting resources\n", customer_num);
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        temp = available[i] - need[customer_num][i];
        if(temp < 0)
        {
            safe = 0;
            printf("    requesting %d of resource type %d, it has %d available\n",need[customer_num][i], i , available[i]);
            break;
        }
        printf("    requesting %d of resource type %d, it has %d available\n",need[customer_num][i], i , available[i]);
    }
    pthread_mutex_unlock(&mutex);
    //if the request is safe return 0 else -1
    if(safe)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int release_resources(int customer_num)
{
    pthread_mutex_lock(&mutex);
    printf("customer %d has finished and released resources\n", customer_num);
    int temp;
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        temp = (available[i] + allocation[customer_num][i]);
        printf("    type %d     %d -> %d\n", i, available[i], temp);
        available[i] = temp;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void* customer(void* args)
{
    int customerID = *(int*)args;   //thread #
    int requestStatus = -1;         //request status = -1 for fail, 0 for success 
    int count = 0;                  

    finish[customerID] = 0;

    requestStatus = request_resources(customerID);
    while(requestStatus == -1 || count > NUMBER_OF_CUSTOMERS)
    {
        printf("customer %d request failed\n", customerID);
        sleep(rand()%10 / 9); //waits a random amount before asking again
        requestStatus = request_resources(customerID);
        count++;
    }

    if(count > NUMBER_OF_CUSTOMERS)
    {
        finish[customerID] = 0;
    }
    else
    {
        release_resources(customerID);
        finish[customerID] = 1;
    }
}   

void fileinput()
{
    char str[10];
    int num;
    FILE * fpointer = fopen("input.txt", "r");
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        fscanf(fpointer, "%s", str);
        available[i] = atoi(str);
    }
    for(int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
    {
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            fscanf(fpointer, "%s", str);
            allocation[j][i] = atoi(str);
        }
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            fscanf(fpointer, "%s", str);
            maximum[j][i] = atoi(str);
        }
    }
}

void needinit() //initializes need array with the values derived from max and alloc
{
    for(int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
    {
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            need[j][i] = maximum[j][i] - allocation[j][i];        
        }
    }
}

int main(int argc, char* argv[])
{
    fileinput();    //initilizes the arrays with a file input
    needinit();     //initilizes the need array

    int a = 0;
    int finished = 1;

    pthread_mutex_init(&mutex, NULL);

    pthread_t customerThread[NUMBER_OF_CUSTOMERS];
    for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&customerThread[i], NULL, &customer, a);
        printf("thread %d is starting up\n", i);
    }

    for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        pthread_join(customerThread[i], NULL);
    }

    for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        if(finish[i] == 0)
        {
            finished = 0;
        }
    }

    if(finished)
    {
        printf("all threads have finished\nbankers algorithm is a success\n");
    }
    else
    {
        printf("thread(s) have failed to finish\nbankers algorithm has failed\n");
    }

    pthread_mutex_destroy(&mutex);
    system("pause");
    return 0;
}

/*--------------input.txt-------------
1, 5, 2, 0
0, 0, 1, 2,   0, 0, 1, 2
1, 0, 0, 0,   1, 7, 5, 0
1, 3, 5, 4,   2, 3, 5, 6
0, 6, 3, 2,   0, 6, 5, 2
0, 0, 1, 4,   0, 6, 5, 6

  --------------output----------------

osc@ubuntu:~/final-src-osc10e/ch3$ ./bankers
thread 0 is starting up
thread 1 is starting up
thread 2 is starting up
thread 3 is starting up
thread 4 is starting up
customer 4 is requesting resources
    requesting 0 of resource type 0, it has 1 available
    requesting 6 of resource type 1, it has 5 available
customer 4 request failed
customer 3 is requesting resources
    requesting 0 of resource type 0, it has 1 available
    requesting 0 of resource type 1, it has 5 available
    requesting 2 of resource type 2, it has 2 available
    requesting 0 of resource type 3, it has 0 available
customer 3 has finished and released resources
    type 0     1 -> 1
    type 1     5 -> 11
    type 2     2 -> 5
    type 3     0 -> 2
customer 4 is requesting resources
    requesting 0 of resource type 0, it has 1 available
    requesting 6 of resource type 1, it has 11 available
    requesting 4 of resource type 2, it has 5 available
    requesting 2 of resource type 3, it has 2 available
customer 4 has finished and released resources
    type 0     1 -> 1
    type 1     11 -> 11
    type 2     5 -> 6
    type 3     2 -> 6
customer 2 is requesting resources
    requesting 1 of resource type 0, it has 1 available
    requesting 0 of resource type 1, it has 11 available
    requesting 0 of resource type 2, it has 6 available
    requesting 2 of resource type 3, it has 6 available
customer 2 has finished and released resources
    type 0     1 -> 2
    type 1     11 -> 14
    type 2     6 -> 11
    type 3     6 -> 10
customer 1 is requesting resources
    requesting 0 of resource type 0, it has 2 available
    requesting 7 of resource type 1, it has 14 available
    requesting 5 of resource type 2, it has 11 available
    requesting 0 of resource type 3, it has 10 available
customer 1 has finished and released resources
    type 0     2 -> 3
    type 1     14 -> 14
    type 2     11 -> 11
    type 3     10 -> 10
customer 0 is requesting resources
    requesting 0 of resource type 0, it has 3 available
    requesting 0 of resource type 1, it has 14 available
    requesting 0 of resource type 2, it has 11 available
    requesting 0 of resource type 3, it has 10 available
customer 0 has finished and released resources
    type 0     3 -> 3
    type 1     14 -> 14
    type 2     11 -> 12
    type 3     10 -> 12
all threads have finished
bankers algorithm is a success
osc@ubuntu:~/final-src-osc10e/ch3$ */
