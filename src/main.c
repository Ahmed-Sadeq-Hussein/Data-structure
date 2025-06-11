// The main function for the program to find the shortest path between cities.
//
//Written by He Tan, March 2022
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"

//the number of nodes in the graph
#define GRAPH_NODE_N 7
#define INFINITY 9999


//the function that calculates the distances of shortest paths between cities
//parameters: source_node, the id of the source node
//            dist, the minimum distance
//            graph, the graph
void dijkstra(int source_node, int dist[], struct graph* graph);


int main(void)
{
    char *cities[GRAPH_NODE_N] = {"Jönköping", "Ulricehamn", "Värnamo", "Göteborg", "Helsingborg", "Ljungby", "Malmö"};

    struct graph* graph = createGraph(GRAPH_NODE_N);

    //0: Jönköping, 1: Ulricehamn, 2: Värnamo, 3: Göteborg, 4: Helsingborg, 5: Ljunby, 6: Malmö
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 0, 4);
    addEdge(graph, 3, 1, 15);
    addEdge(graph, 3, 5, 5);
    addEdge(graph, 3, 6, 23);
    addEdge(graph, 4, 1, 17);
    addEdge(graph, 4, 6, 11);
    addEdge(graph, 5, 2, 9);
    addEdge(graph, 5, 6, 13);

    //displayGraph(graph, cities);

    int source_node;
    printf("\n0: Jönköping, 1: Ulricehamn, 2: Värnamo, 3: Göteborg, 4: Helsingborg, 5: Ljunby, 6: Malmö");
    printf("\nEnter the city :  ");
    scanf("%d", &source_node);


    //store the minimun distance
    int dist[GRAPH_NODE_N];
    dijkstra(source_node, dist, graph);

    printf("\nThe distance of the shortest path for travelling from %s to ", cities[source_node]);
    for(int i=0; i<GRAPH_NODE_N; i++ ){

        if(dist[i] == INFINITY)
            printf("\n%s !!! no connection between these two cities", cities[i]);
        else printf("\n%s is %d", cities[i], dist[i]);
    }


    printf("\n");
    return 0;
}
