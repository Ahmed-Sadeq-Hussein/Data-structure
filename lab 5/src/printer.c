// AHMED HUSSEIN 2025
#include "../include/printer.h"
#include <stdio.h>
#include <stdlib.h>

// Perform one second of printing
void tick(struct printer *p) {
    if (p == NULL || p->current_task == NULL) {
        return;
    }
    
    // Only subtract time if there's time remaining
    if (p->time_remaining > 0) {
        p->time_remaining--;
    }
    
    // Check if task is completed
    if (p->time_remaining == 0) {
        free(p->current_task);
        p->current_task = NULL;
    }
}

// Check if printer is busy
int is_busy(struct printer *p) {
    if (p == NULL) {
        return 0;
    }
    return (p->current_task != NULL) ? 1 : 0;
}

// Start the next printing task
void start_next_task(struct printer *p, struct task *t) {
    if (p == NULL || t == NULL) {
        return;
    }
    
    p->current_task = t;
    // Calculate time remaining: pages * (60 seconds / page_rate)
    p->time_remaining = t->pages * (60 / p->page_rate);
}

// Display the printer's current status
void display_printer_status(struct printer *p) {
    if (p == NULL) {
        printf("Printer status: Invalid printer\n");
        return;
    }
    
    if (!is_busy(p)) {
        printf("Printer status: Idle\n");
    } else {
        printf("Printer status: Busy, %d seconds remaining\n", p->time_remaining);
    }
}

// Optional: Initialization function (not in interface but useful)
struct printer* create_printer(int page_rate) {
    struct printer *p = (struct printer*)malloc(sizeof(struct printer));
    if (p != NULL) {
        p->page_rate = page_rate;
        p->current_task = NULL;
        p->time_remaining = 0;
    }
    return p;
}

// Optional: Cleanup function (not in interface but useful)
void destroy_printer(struct printer *p) {
    if (p != NULL) {
        if (p->current_task != NULL) {
            free(p->current_task);
        }
        free(p);
    }
}