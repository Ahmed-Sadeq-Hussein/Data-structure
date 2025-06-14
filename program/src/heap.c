//AHMED HUSSEIN 2025
#include <stdio.h>
#include <stdlib.h>
#include "../include/heap.h"


// Create a new min heap node
struct minHeapNode* new_min_heap_node(int n, int dist) {
    struct minHeapNode* node = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed for heap node\n");
        exit(EXIT_FAILURE);
    }
    node->graph_node_id = n;
    node->dist = dist;
    return node;
}

// Create an empty min heap
struct minheap* create_heap(int m) {
    struct minheap* h = (struct minheap*)malloc(sizeof(struct minheap));
    if (h == NULL) {
        fprintf(stderr, "Memory allocation failed for heap\n");
        exit(EXIT_FAILURE);
    }
    
    h->max_size = m;
    h->cur_size = 0;
    h->pos = (int*)malloc(m * sizeof(int));
    h->array = (struct minHeapNode**)malloc(m * sizeof(struct minHeapNode*));
    
    if (h->pos == NULL || h->array == NULL) {
        fprintf(stderr, "Memory allocation failed for heap arrays\n");
        free(h->pos);
        free(h->array);
        free(h);
        exit(EXIT_FAILURE);
    }
    
    return h;
}

// Helper function to swap two heap nodes
void swap_nodes(struct minHeapNode** a, struct minHeapNode** b) {
    struct minHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify at a given index
void min_heapify(struct minheap* h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->cur_size && h->array[left]->dist < h->array[smallest]->dist) {
        smallest = left;
    }

    if (right < h->cur_size && h->array[right]->dist < h->array[smallest]->dist) {
        smallest = right;
    }

    if (smallest != idx) {
        // Update positions
        h->pos[h->array[smallest]->graph_node_id] = idx;
        h->pos[h->array[idx]->graph_node_id] = smallest;
        
        // Swap nodes
        swap_nodes(&h->array[smallest], &h->array[idx]);
        
        min_heapify(h, smallest);
    }
}

// Insert a node into the heap
int insert_heap(struct minheap* h, struct minHeapNode* n) {
    if (h->cur_size == h->max_size) {
        return 0; // Heap is full
    }

    // Insert at the end
    int i = h->cur_size;
    h->array[i] = n;
    h->pos[n->graph_node_id] = i;
    h->cur_size++;

    // Fix the heap property if violated
    while (i != 0 && h->array[(i - 1) / 2]->dist > h->array[i]->dist) {
        // Update positions
        h->pos[h->array[i]->graph_node_id] = (i - 1) / 2;
        h->pos[h->array[(i - 1) / 2]->graph_node_id] = i;
        
        // Swap nodes
        swap_nodes(&h->array[i], &h->array[(i - 1) / 2]);
        
        i = (i - 1) / 2;
    }

    return 1;
}

// Delete the minimum element from the heap
int delete_heap(struct minheap* h) {
    if (h->cur_size == 0) {
        return 0; // Heap is empty
    }

    // Store the root node
    struct minHeapNode* root = h->array[0];

    // Replace root with last node
    h->array[0] = h->array[h->cur_size - 1];
    h->pos[h->array[0]->graph_node_id] = 0;
    h->pos[root->graph_node_id] = -1; // Mark as removed
    h->cur_size--;

    // Heapify the root
    min_heapify(h, 0);

    free(root);
    return 1;
}

// Decrease key value of a given node
void decreaseKey(struct minheap* h, int n, int dist) {
    // Get position of node in heap
    int i = h->pos[n];
    
    // Update distance value
    h->array[i]->dist = dist;

    // Fix the heap property if violated
    while (i != 0 && h->array[(i - 1) / 2]->dist > h->array[i]->dist) {
        // Update positions
        h->pos[h->array[i]->graph_node_id] = (i - 1) / 2;
        h->pos[h->array[(i - 1) / 2]->graph_node_id] = i;
        
        // Swap nodes
        swap_nodes(&h->array[i], &h->array[(i - 1) / 2]);
        
        i = (i - 1) / 2;
    }
}

// Find the minimum element in the heap
struct minHeapNode* findmin(struct minheap* h) {
    if (h->cur_size == 0) {
        return NULL;
    }
    return h->array[0];
}

// Destroy the heap and free memory
void destroy_heap(struct minheap* h) {
    if (h == NULL) return;
    
    // Free all heap nodes
    for (int i = 0; i < h->cur_size; i++) {
        free(h->array[i]);
    }
    
    free(h->array);
    free(h->pos);
    free(h);
}

// Display the heap
void display_heap(struct minheap* h) {
    printf("Heap contents:\n");
    for (int i = 0; i < h->cur_size; i++) {
        printf("Node %d: distance %d\n", h->array[i]->graph_node_id, h->array[i]->dist);
    }
}

// Check if heap is empty
int is_empty(struct minheap* h) {
    return h->cur_size == 0;
}

// Extract minimum node from heap (for Dijkstra's algorithm)
struct minHeapNode* extract_min(struct minheap* h) {
    if (is_empty(h)) {
        return NULL;
    }

    // Store the root node
    struct minHeapNode* root = h->array[0];

    // Replace root with last node
    h->array[0] = h->array[h->cur_size - 1];
    h->pos[h->array[0]->graph_node_id] = 0;
    h->pos[root->graph_node_id] = -1; // Mark as removed
    h->cur_size--;

    // Heapify the root
    min_heapify(h, 0);

    return root;
}