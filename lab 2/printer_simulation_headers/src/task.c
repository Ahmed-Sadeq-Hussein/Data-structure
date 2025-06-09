//Task 
// Ahmed Hussein 2025.

#include "../include/task.h"
#include <stdlib.h> // For malloc

// Creates a new print task
// Parameters:
//   ct - current time (in seconds) when the task is created
// Returns:
//   Pointer to the newly created task
struct task* create_task(int ct) {
    // Allocate memory for the new task
    struct task* new_task = (struct task*)malloc(sizeof(struct task));
    
    // Check if memory allocation succeeded
    if (new_task == NULL) {
        return NULL; // Return NULL if allocation failed
    }
    
    // Initialize the task fields
    new_task->time_stamp = ct; // Set creation timestamp
    new_task->pages = 0;       // Initialize pages (will be set later)
    
    return new_task;
}