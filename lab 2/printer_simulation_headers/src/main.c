#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.c"
#include "task.c"
#include "printer.c"

#define SIMULATION_TIME 10    // Total simulation time in seconds (as per lab example)
#define TASK_IN_N_SECOND 2   // Average one task every N seconds (N=2 from lab)
#define MAX_PAGES 5          // Maximum pages per task (M=5 from lab)
#define PAGES_PER_MINUTE 60  // Printer speed (P=60 from lab)

// Function prototypes
void simulate_second(struct printer *printer, struct queue *q, int current_second);
void print_simulation_header();

int main() {
    //Initialize random number generator. May luck be with you
    srand(time(NULL));

    print_simulation_header();

    //Initialize printer 
    struct printer printer = {
        .page_rate = PAGES_PER_MINUTE,
        .current_task = NULL,
        .time_remaining = 0
    };

    //Create queue
    struct queue *q = create_queue();
    if (q == NULL) {
        fprintf(stderr, "Failed to create queue\n");
        return 1;
    }

    //Run sim
    for (int second = 1; second <= SIMULATION_TIME; second++) {
        simulate_second(&printer, q, second);
        printf("\n ~~~~Running printing simulation ~~~~ \n");
    }

    //  Cleanup 
    while (!is_empty(q)) {
        struct task *t = dequeue(q);
        printf("## Cleaning task queue ##\n ");
        free(t);
    }
    free(q);

    //Free task if printer was busy when sim finished
    if (printer.current_task != NULL) {
        free(printer.current_task);
    }

    return 0;
}

void print_simulation_header() {
    printf("=== Printer Simulation ===\n");
    printf("Parameters:\n");
    printf("- Duration: %d seconds\n", SIMULATION_TIME);
    printf("- Tasks arrive every %d seconds on average\n", TASK_IN_N_SECOND);
    printf("- Pages per task: 1-%d\n", MAX_PAGES);
    printf("- Printer speed: %d pages/minute\n\n", PAGES_PER_MINUTE);
}

void simulate_second(struct printer *printer, struct queue *q, int current_second) {
    //Check if a new task should be generated
    if ((rand() % TASK_IN_N_SECOND) == 0) {
        struct task *new_task = create_task(current_second);
        if (new_task != NULL) {
            new_task->pages = 1 + (rand() % MAX_PAGES);
            enqueue(q, new_task);
            printf("[Second %02d] New task: %d pages\n", 
                   current_second, new_task->pages);
        }
    }

    //If printer is idle and tasks are waiting
    if (!is_busy(printer) && !is_empty(q)) {
        struct task *next_task = dequeue(q);
        start_next_task(printer, next_task);
        printf("[Second %02d] Started printing: %d pages (%d seconds)\n",
               current_second, 
               next_task->pages,
               printer->time_remaining);
    }

    //Process current print task
    if (is_busy(printer)) {
        tick(printer);
        if (!is_busy(printer)) {
            printf("[Second %02d] Finished printing\n", current_second);
        }
    }
}