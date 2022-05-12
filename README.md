# Banker-s-algorithm
An example of the Banker's algorithm

Here is a sample run:

input text:

1, 5, 2, 0

0, 0, 1, 2,   0, 0, 1, 2

1, 0, 0, 0,   1, 7, 5, 0

1, 3, 5, 4,   2, 3, 5, 6

0, 6, 3, 2,   0, 6, 5, 2

0, 0, 1, 4,   0, 6, 5, 6


output:

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
