
//AHMED HUSSEIN 2025
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

// Create a graph with N vertices
struct graph* createGraph(int N) {
    // Allocate memory for graph structure
    struct graph* graph = (struct graph*)malloc(sizeof(struct graph));
    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed for graph\n");
        exit(EXIT_FAILURE);
    }
    
    graph->N = N;
    
    // Allocate memory for array of adjacency lists
    graph->array = (struct adjList*)malloc(N * sizeof(struct adjList));
    if (graph->array == NULL) {
        fprintf(stderr, "Memory allocation failed for adjacency list array\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    
    // Initialize each adjacency list as empty
    for (int i = 0; i < N; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Add an edge from source to target with given weight
void addEdge(struct graph* graph, int source, int target, int weight) {
    // Validate input parameters
    if (graph == NULL || source < 0 || source >= graph->N || target < 0 || target >= graph->N) {
        fprintf(stderr, "Invalid parameters in addEdge\n");
        return;
    }
    
    // Create new node for adjacency list
    struct adjListNode* newNode = (struct adjListNode*)malloc(sizeof(struct adjListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for new edge\n");
        return;
    }
    
    newNode->graph_node_id = target;
    newNode->weight = weight;
    
    // Add to front of source's adjacency list (more efficient)
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
}

// Delete the edge from source to target
void deleteEdge(struct graph* graph, int source, int target) {
    // Validate input parameters
    if (graph == NULL || source < 0 || source >= graph->N || target < 0 || target >= graph->N) {
        fprintf(stderr, "Invalid parameters in deleteEdge\n");
        return;
    }
    
    struct adjListNode* current = graph->array[source].head;
    struct adjListNode* prev = NULL;
    
    // Search for target in source's adjacency list
    while (current != NULL && current->graph_node_id != target) {
        prev = current;
        current = current->next;
    }
    
    // If found, remove it
    if (current != NULL) {
        if (prev == NULL) {
            // Edge was at head of list
            graph->array[source].head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    }
}

// Display the graph with city names
void displayGraph(struct graph* graph, char **cities) {
    if (graph == NULL || cities == NULL) {
        fprintf(stderr, "Invalid parameters in displayGraph\n");
        return;
    }
    
    for (int i = 0; i < graph->N; i++) {
        printf("%s: ", cities[i]);
        struct adjListNode* current = graph->array[i].head;
        
        while (current != NULL) {
            printf("-> %s (%d) ", cities[current->graph_node_id], current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

// Free all memory allocated for the graph
void freeGraph(struct graph* graph) {
    if (graph == NULL) return;
    
    // Free each adjacency list
    for (int i = 0; i < graph->N; i++) {
        struct adjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct adjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    // Free the array and the graph structure
    free(graph->array);
    free(graph);
}