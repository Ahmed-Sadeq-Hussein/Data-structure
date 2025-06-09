//Queue
// Ahmed Hussein 2025.
#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h> 


// Creates an empty queue
struct queue* create_queue() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    if (q == NULL) {
        return NULL; // Return NULL if allocation failed
    }
    q->front = q->rear = NULL; // Initialize both front and rear to NULL
    return q;
}

// Adds a task to the rear of the queue
void enqueue(struct queue *q, struct task *t) {
    if (q == NULL || t == NULL) return; // Safety check

    // Create new node
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) return; // Alloc failed

    newNode->data = t;
    newNode->next = NULL;

    // If queue is empty, new node is both front and rear
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    // Add the new node at the end and update rear
    q->rear->next = newNode;
    q->rear = newNode;
}

// Removes a task from the front of the queue
struct task* dequeue(struct queue *q) {
    if (q == NULL || q->front == NULL) {
        return NULL; // Queue is empty or invalid
    }

    // Store previous front and move front one node ahead
    struct node* temp = q->front;
    struct task* task = temp->data;
    
    q->front = q->front->next;

    // If front becomes NULL, then rear should also be NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp); // Free the dequeued node
    return task;
}

// Displays all tasks in the queue
void display_queue(struct queue *q) {
    if (q == NULL || q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue contents:\n");
    struct node* current = q->front;
    while (current != NULL) {
        printf("  Task: timestamp=%d, pages=%d\n", 
               current->data->time_stamp, 
               current->data->pages);
        current = current->next;
    }
}

// Checks if the queue is empty
int is_empty(struct queue *q) {
    if (q == NULL) return 1; // Consider NULL queue as empty
    return (q->front == NULL);
}