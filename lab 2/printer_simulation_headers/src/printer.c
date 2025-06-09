#include "../include/printer.h"
#include <stdio.h> 
#include <stdlib.h>

// Performs one second of printing
void tick(struct printer *p) {
    if (p == NULL || p->current_task == NULL) return;

    //Only dec
    if (p->time_remaining > 0) {
        p->time_remaining--;
    }

    //Check if task is completed
    if (p->time_remaining == 0) {
        free(p->current_task); // Free the completed task
        p->current_task = NULL;
    }
}

// Checks if printer is busy
int is_busy(struct printer *p) {
    if (p == NULL) return 0;
    return (p->current_task != NULL && p->time_remaining > 0);
}

// Starts the next printing task
void start_next_task(struct printer *p, struct task *t) {
    if (p == NULL || t == NULL) return;

    //Calculate time required for this task (pages * (60/page_rate) seconds)
    p->time_remaining = (t->pages * 60) / p->page_rate;
    
    // Handle case where pages is less than page_rate (minimum 1 second)
    if (p->time_remaining == 0 && t->pages > 0) {
        p->time_remaining = 1;
    }
    
    p->current_task = t;
}

//Displays the printer's current status

void display_printer_status(struct printer *p) {
    if (p == NULL) {
        printf("Printer: Invalid printer\n");
        return;
    }

    if (is_busy(p)) {
        printf("Printer: Busy (%d seconds remaining)\n", p->time_remaining);
    } else {
        printf("Printer: Idle\n");
    }
}

//  initialization function 
struct printer* create_printer(int page_rate) {
    struct printer* p = (struct printer*)malloc(sizeof(struct printer));
    if (p == NULL) return NULL;
    
    p->page_rate = page_rate;
    p->current_task = NULL;
    p->time_remaining = 0;
    
    return p;
}