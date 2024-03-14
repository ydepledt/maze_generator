#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "prim.h"
#include "maze.h"

int findMinCostNode(int* cheapest, bool* explored, int numVertices) {
    int minCost = INFINITY;
    int minCostNode = -1;
    
    for (int i = 0; i < numVertices; i++) {
        if (!explored[i] && cheapest[i] < minCost) {
            minCost = cheapest[i];
            minCostNode = i;
        }
    }
    
    return minCostNode;
}

void prim(Map *map, Maze *maze) {
    
    int numVertices = map->height * map->width;
    int *cheapest = malloc(numVertices * sizeof(int));
    bool *explored = malloc(numVertices * sizeof(bool));

    for (int i = 0; i < numVertices; i++) {
        cheapest[i] = INFINITY;
        explored[i] = false;
    }

    // print all cheapest and explored
    // for (int i = 0; i < numVertices; i++) {
    //     printf("cheapest[%d] = %d\n", i, cheapest[i]);
    //     printf("explored[%d] = %d\n", i, explored[i]);
    //     printf("predecessors[%d] = %d\n", i, maze->predecessors[i]);
    // }

    int start = 0;
    cheapest[start] = 0;

    // int t = 0;

    Neighbors *neighbors_struct = malloc(sizeof(Neighbors)); // Allocate memory for neighbors

    while (true) {
        int minCostNode = findMinCostNode(cheapest, explored, numVertices);
        if (minCostNode == -1) {
            break;
        }
        explored[minCostNode] = true;

        // printf("cheapest[%d] = %d\n", minCostNode, cheapest[minCostNode]);
        // printf("%d\n", t++);

        find_neighbors(map, neighbors_struct, minCostNode);

        for (int direction = BELOW; direction <= LEFT; direction++) {
            int neighbor = neighbors_struct->neighbors[direction];
            int cost = neighbors_struct->costs[direction];

            // printf("Node: %d, Neighbor: %d, Cost: %d\n", minCostNode, neighbor, cost);

            if (neighbor != -1 && !explored[neighbor] && cost < cheapest[neighbor]) {
                cheapest[neighbor] = cost;
                maze->predecessors[neighbor] = minCostNode;
            }
        }


    }

    free(neighbors_struct); // Free memory for neighbors
    free(cheapest);
    free(explored);
}