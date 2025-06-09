//the interface for the FIFO queue ADT
//Written by He Tan, Feb 2022
#include "task.h"

#ifndef QUEUE_H_ /* Include guard */
#define QUEUE_H_

//a linked list node to store a queue entry
struct node {
    //each queue entry is a printing task
	struct task *data;
	struct node *next;
};

//declare queue
struct queue {
	struct node *front, *rear;
};

//create a queue
//return the pointer that points to the queue 
struct queue* create_queue();


//add a task into the queue 
//parameters:
//  *q, the pointer that points to queue 
//  *t, the pointer that points to the printing task
void enqueue(struct queue *q, struct task *t);


//delete a task from the queue 
//parameters:
//  *q, the pointer that points to the queue 
//return the dequeued task
struct task* dequeue(struct queue *q);

//display all the tasks in the queue 
//parameters:
//  *q, the pointer that points to the queue 
void display_queue(struct queue *q);

//check whether the queue is empty
//parameters:
//  *q, the pointer that points to the queue 
//return 1 (true) or 0 (false)
int is_empty(struct queue *q);


#endif
