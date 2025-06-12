// AHMED HUSSEIN 2025
#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>


// Create a new printing task
struct task* create_task(int ct) {
    struct task* new_task = (struct task*)malloc(sizeof(struct task));
    if (new_task == NULL) {
        return NULL;  
    }
    new_task->time_stamp = ct;
    new_task->pages = 0;  
    
    return new_task;
}
