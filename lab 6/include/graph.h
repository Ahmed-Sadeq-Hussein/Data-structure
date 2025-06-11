
#ifndef GRAPH_H_ /* Include guard */
#define GRAPH_H_


#include <stdio.h>


//declare a structure for adjacent node in a adjacent list
struct adjListNode
{
    //the id of the node in the graph
    int graph_node_id;
    //the weight of the edge from this node to another node.
    int weight;
    //pointer points to the next element in an adjacent list, i.e., an adjacent node to the head
    struct adjListNode *next;
};

//declear a structure to present an adjacency list 
//head is the pointer points to the first element in the list, i.e., a node in the graph.
struct adjList {
    struct adjListNode* head;
};

// declare a structure to represent a graph. 
// N is the number of nodes in graph.
// A graph is an array of adjacency lists.
struct graph {
    int N;
    struct adjList* array;
};


//create a graph
//parameters: int, the number of nodes in the graph 
//return: the pointer points to the graph
struct graph* createGraph(int);
//display an edge between the source node and the target node
//parameters: graph, the pointer points to the graph
//            cities, the cities referenced by the node id in the graph  
void displayGraph(struct graph*, char **cities);
//add an edge between the source node and the target node
//parameters: graph, the pointer points to the graph
//            source, the id of the source node
//            target, the id of the target nonde
//            weight, the weight of the edge
void addEdge(struct graph* graph, int source, int target, int weight);
//delete the edge between the source node and the target node
//parameters: graph, the pointer points to the graph
//            source, the id of the source node
//            target, the id of the target node
void deleteEdge(struct graph* graph, int source, int target);

#endif