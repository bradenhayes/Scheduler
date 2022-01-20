#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#define MEMORY 1000
#define MAXCHAR 1000
//INITILIZING TASK STATES
enum task_state
{

    UNDEFINED,

    READY,

    RUNNING,

	TERMINATED,

    TASK_WAITING

};
//creating the structure thats usesd by the .c file
typedef struct PCB
{
    int pid;
    int arrivalTime;
    int totalCPUTime;
    int priority;
    int ioFrequency;
    int ioDuration;
    bool wait;
    int turnaroundTime;
    int waitingTime;
    enum task_state state;
	int memoryNeeded;
} PCB;
//CREATING NODE
typedef struct node
{
    PCB *data;
    struct node *next;

} node;
//CREATING QUEUE
typedef struct queue
{

    int count;
    node *front;
    node *rear;
} queue;

#endif
