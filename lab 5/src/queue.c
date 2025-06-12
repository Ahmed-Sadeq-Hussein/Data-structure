// AHMED HUSSEIN 2025
#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 20

// Complete the minheap structure definition
struct minheap {
    struct task **elements;  // Array of task pointers
    int size;               // Current number of elements
    int capacity;           // Maximum capacity of the heap
};

// Helper function to swap two tasks
static void swap(struct task **a, struct task **b) {
    struct task *temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to maintain heap property from bottom to top
static void heapify_up(struct minheap *h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (h->elements[index]->pages < h->elements[parent]->pages) {
            swap(&h->elements[index], &h->elements[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Helper function to maintain heap property from top to bottom
static void heapify_down(struct minheap *h, int index) {
    int left, right, smallest;
    
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < h->size && h->elements[left]->pages < h->elements[smallest]->pages) {
            smallest = left;
        }

        if (right < h->size && h->elements[right]->pages < h->elements[smallest]->pages) {
            smallest = right;
        }

        if (smallest != index) {
            swap(&h->elements[index], &h->elements[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// Create an empty binary heap
struct minheap *create_heap() {
    struct minheap *h = (struct minheap *)malloc(sizeof(struct minheap));
    if (h == NULL) {
        return NULL;
    }

    h->elements = (struct task **)malloc(INITIAL_CAPACITY * sizeof(struct task *));
    if (h->elements == NULL) {
        free(h);
        return NULL;
    }

    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    return h;
}

// Insert an element into the heap
int insert_heap(struct minheap *h, struct task *t) {
    if (h == NULL || t == NULL) {
        return 0;
    }

    // Resize if needed
    if (h->size == h->capacity) {
        int new_capacity = h->capacity * 2;
        struct task **new_elements = (struct task **)realloc(h->elements, new_capacity * sizeof(struct task *));
        if (new_elements == NULL) {
            return 0;
        }
        h->elements = new_elements;
        h->capacity = new_capacity;
    }

    // Add the new element at the end
    h->elements[h->size] = t;
    h->size++;

    // Maintain heap property
    heapify_up(h, h->size - 1);
    return 1;
}

// Delete the minimum element from the heap
int delete_heap(struct minheap *h) {
    if (h == NULL || h->size == 0) {
        return 0;
    }

    // Replace root with last element
    h->size--;
    h->elements[0] = h->elements[h->size];

    // Maintain heap property
    heapify_down(h, 0);
    return 1;
}

// Find the minimum value in the heap
struct task *findmin(struct minheap *h) {
    if (h == NULL || h->size == 0) {
        return NULL;
    }
    return h->elements[0];
}

// Destroy the heap and release memory
void destroy_heap(struct minheap *h) {
    if (h == NULL) {
        return;
    }

    // Note: We don't free the tasks here since they might be used elsewhere
    // The lab description suggests the printer will free completed tasks
    free(h->elements);
    free(h);
}

// Display the heap contents
void display_heap(struct minheap *h) {
    if (h == NULL) {
        printf("Heap is NULL\n");
        return;
    }

    printf("Heap contents (size=%d, capacity=%d):\n", h->size, h->capacity);
    for (int i = 0; i < h->size; i++) {
        printf("[%d] pages=%d\n", i, h->elements[i]->pages);
    }
}

// Check if the heap is empty
int is_empty(struct minheap *h) {
    if (h == NULL) {
        return 1;
    }
    return (h->size == 0) ? 1 : 0;
}