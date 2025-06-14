// AHMED HUSSEIN 2025
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printer.c"
#include "queue.c"
#include "task.c"

#define SIMULATION_TIME 10    // Total simulation time in seconds
#define TASK_IN_N_SECOND 2   // Average one task every N seconds
#define MAX_PAGES 5          // Maximum pages per task
#define PAGES_PER_MINUTE 60  // Printer speed

void simulate_second(struct printer *printer, struct minheap *queue, int current_second);

int main() {
    srand(time(NULL));
    
    // Create printer with given page rate
    struct printer *printer = (struct printer*)malloc(sizeof(struct printer));
    if (printer == NULL) {
        fprintf(stderr, "Failed to create printer\n");
        return 1;
    }
    printer->page_rate = PAGES_PER_MINUTE;
    printer->current_task = NULL;
    printer->time_remaining = 0;
    
    // Create priority queue for print tasks
    struct minheap *queue = create_heap();
    if (queue == NULL) {
        fprintf(stderr, "Failed to create queue\n");
        free(printer);
        return 1;
    }

    printf("Starting printer simulation for %d seconds...\n", SIMULATION_TIME);
    printf("Parameters: Task every %d sec, Max pages: %d, Printer speed: %d ppm\n\n",
           TASK_IN_N_SECOND, MAX_PAGES, PAGES_PER_MINUTE);

    // Main simulation loop
    for (int second = 1; second <= SIMULATION_TIME; second++) {
        printf("\nSIMULATION AT SECOND %d\n", second);
        simulate_second(printer, queue, second);
    }

    printf("\nSIMULATION ENDS\n");

    // Cleanup - free remaining tasks in queue
    while (!is_empty(queue)) {
        struct task *t = findmin(queue);
        delete_heap(queue);
        free(t);
    }
    destroy_heap(queue);
    
    // Free printer and any current task
    if (printer->current_task != NULL) {
        free(printer->current_task);
    }
    free(printer);

    return 0;
}

void simulate_second(struct printer *printer, struct minheap *queue, int current_second) {
    // Check if a new task should be created
    if ((rand() % TASK_IN_N_SECOND) == 0) {
        struct task *new_task = create_task(current_second);
        if (new_task != NULL) {
            new_task->pages = 1 + (rand() % MAX_PAGES);
            if (insert_heap(queue, new_task)) {
                printf("NEW TASK: %d pages (arrived at second %d)\n", 
                       new_task->pages, current_second);
            } else {
                free(new_task);
                printf("COULD NOT ADD TASK (QUEUE FULL)\n");
            }
        }
    }

    // Process current print task (if any)
    if (is_busy(printer)) {
        tick(printer);
        printf("PRINTER STATUS: BUSY (%d seconds remaining)\n", printer->time_remaining);
    } else {
        printf("PRINTER STATUS: IDLE\n");
    }

    // Start new task if printer is available
    if (!is_busy(printer) )
    {
        if (!is_empty(queue)) {
            struct task *next_task = findmin(queue);
            delete_heap(queue);
            start_next_task(printer, next_task);
            printf("STARTED PRINTING: %d page task (waited %d seconds)\n",
                   next_task->pages, current_second - next_task->time_stamp);
        }
    }

    // Display queue contents
    printf("TASKS IN QUEUE:\n");
    if (is_empty(queue)) {
        printf("  (empty)\n");
    } else {
        // Note: This displays the heap array order, not sorted order
        for (int i = 0; i < queue->size; i++) {
            printf("  [%d] %d pages (arrived at %d)%s\n",
                   i, queue->elements[i]->pages, 
                   queue->elements[i]->time_stamp,
                   (i == queue->size-1) ? "" : ",");
        }
    }
}