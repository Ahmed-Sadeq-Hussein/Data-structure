//the interface for the priority queue ADT based on min binary heap,
//and binary heap is implemented using array.
//Written by He Tan, Feb 2022
#include "task.h"

#ifndef QUEUE_H_ /* Include guard */
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

//an incomplete declaration for a min binary heap
//complete this in .c file.
struct minheap;

//create an empty binary heap
struct minheap *create_heap();

//insert an element
//parameters: h, the pointer points to the heap.
//            t, the task to be inserted into the queue
//return:  0, the heap is full.
//		     1, the element is inserted.
int insert_heap(struct minheap *h, struct task *t);

//delete an element
//parameters: h, the pointer points to the heap.
//return: 0, the heap is empty.
//		    1, the element is deleted.
int delete_heap(struct minheap *h);

//find the minimun value in a heap
//parameters: h, the pointer points to the heap.
//return: the printing task which has the smallest number of pages
struct task *findmin(struct minheap *h);

//destroy a heap and release the space allocated to the heap
//parameters: h, the pointer points to the heap.
void destroy_heap(struct minheap *h);

//prints the heap represented in the array
//parameters: h, the pointer points to the heap.
void display_heap(struct minheap *h);

//check whether the queue is empty
//parameters: *q, the pointer that points to the queue
//returns: 1 (true) or 0 (false)
int is_empty(struct minheap *h);


#endif
