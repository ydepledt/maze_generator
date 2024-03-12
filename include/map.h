#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

// Structure for edges
typedef struct {
    int down;   // Cost of edge going down
    int right;  // Cost of edge going right
} Edges;

// Structure for map
typedef struct {
    int height;         // Height of the map
    int width;          // Width of the map
    Edges *edges;       // Pointer to edges array
} Map;

// Function prototypes
Map *create_map(int height, int width);
Map *create_map_weighted(int height, int width, int *down, int *right);
void destroy_map(Map *map);
void print_map(Map *map);

bool validate_input(Map *map, int row, int col);
void change_edge_down_right(Map *map, int row, int col, int down, int right);
void change_edge_down(Map *map, int row, int col, int down);
void change_edge_right(Map *map, int row, int col, int right);

#endif /* MAP_H */