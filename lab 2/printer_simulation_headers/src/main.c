//AHMED HUSSEIN 2025
#include "queue.c"
#include "task.c"
#include "printer.c"
#include <stdio.h>
#include <stdlib.h>
#include "../include/printer.h"
#include "../include/queue.h"
#include "../include/task.h"

#define SIMULATION_TIME 10    // Total simulation time in seconds
#define TASK_IN_N_SECOND 2   // Average one task every N seconds
#define MAX_PAGES 5          // Maximum pages per task
#define PAGES_PER_MINUTE 60  // Printer speed
//to print text
void simulate_second(struct printer *printer, struct queue *q, int current_second);

int main() {

    srand(time(NULL));
    


    struct printer *printer = create_printer(PAGES_PER_MINUTE);
    if (printer == NULL) {
        fprintf(stderr, "Failed to create printer\n");
        return 1;
    }


    struct queue *q = create_queue();
    if (q == NULL) {
        fprintf(stderr, "Failed to create queue\n");
        free(printer);
        return 1;
    }


    for (int second = 1; second <= SIMULATION_TIME; second++) {
        printf("\nSIMULATION AT SECOND %d\n", second);
        simulate_second(printer, q, second);
    }

    printf("\nSIMULATION ENDS\n");


    while (!is_empty(q)) {
        struct task *t = dequeue(q);
        free(t);
    }
    free(q);
    
    if (printer->current_task != NULL) {
        free(printer->current_task);
    }
    free(printer);

    return 0;
}

void simulate_second(struct printer *printer, struct queue *q, int current_second) {
    if ((rand() % TASK_IN_N_SECOND) == 0) {
        struct task *new_task = create_task(current_second);
        if (new_task != NULL) {
            new_task->pages = 1 + (rand() % MAX_PAGES);
            enqueue(q, new_task);
        }
    }


    if (is_busy(printer)) {
        tick(printer);
        printf("THE PRINTER IS BUSY\n");
        printf("%d seconds to complete the current task.\n", printer->time_remaining);
    } else {
        printf("THE PRINTER IS NO LONGER BUSY\n");
    }
    if (!is_busy(printer) && !is_empty(q)) {
        struct task *next_task = dequeue(q);
        start_next_task(printer, next_task);
    }

    // Display queue contents
    printf("TASKS IN QUEUE:\n");
    if (is_empty(q)) {
        printf("  (empty)\n");
    } else {
        struct node *current = q->front;
        while (current != NULL) {
            printf("  TASK [%d pages, arrives at second %d ]%s\n",
                   current->data->pages,
                   current->data->time_stamp,
                   current->next != NULL ? "," : "");
            current = current->next;
        }
    }
}