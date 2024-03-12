#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"

Map *create_map(int width, int height) {
    // Allocate memory for map struct
    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        return NULL; // Memory allocation failed
    }

    map->width = width;
    map->height = height;

    // Allocate memory for edges array-like structure
    map->edges = (Edges*)malloc(height * width * sizeof(Edges));
    if (map->edges == NULL) {
        free(map); // Free previously allocated memory
        return NULL; // Memory allocation failed
    }

    // Initialize edges (assuming all edges initially have cost 0)
    for (int i = 0; i < height * width; i++) {
        map->edges[i].down = 0;
        map->edges[i].right = 0;
    }

    return map;
}

Map *create_map_weighted(int width, int height, int *down, int *right) {
    // Allocate memory for map struct
    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        return NULL; // Memory allocation failed
    }

    map->width = width;
    map->height = height;

    // Allocate memory for edges array-like structure
    map->edges = (Edges*)malloc(height * width * sizeof(Edges));
    if (map->edges == NULL) {
        free(map); // Free previously allocated memory
        return NULL; // Memory allocation failed
    }

    // Check if down and right arrays are not NULL
    if (down == NULL || right == NULL) {
        free(map->edges); // Free previously allocated memory
        free(map); // Free previously allocated memory
        printf("Down and right arrays cannot be NULL.\n");
        return NULL; // Memory allocation failed
    }
    // Check if down and right len are not greater than height * width
    else if (sizeof(down) / sizeof(down[0]) > height * width || sizeof(right) / sizeof(right[0]) > height * width) {
        free(map->edges); // Free previously allocated memory
        free(map); // Free previously allocated memory
        printf("Down and right arrays cannot be greater than %d.\n", height * width);
        return NULL; // Memory allocation failed
    }

    
    // Initialize edges with down and right arrays and 0 after the arrays
    for (int i = 0; i < height * width; i++) {
        map->edges[i].down = down[i];
        map->edges[i].right = right[i];
    }

    return map;
}

void destroy_map(Map *map) {
    if (map != NULL) {
        if (map->edges != NULL) {
            free(map->edges);
        }
        free(map);
    }
}

void print_map(Map* map) {
    if (map == NULL) {
        printf("Map is not initialized.\n");
        return;
    }
    else if (map->edges == NULL) {
        printf("Map edges are not initialized.\n");
        return;
    }

    printf("Map:\n");
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("(%d, %d)\t", map->edges[i * map->width + j].down, map->edges[i * map->width + j].right);
        }
        printf("\n");
    }
}

bool validate_input(Map *map, int row, int col) {
    if (map == NULL) {
        printf("Map is not initialized.\n");
        return false;
    }
    else if (map->edges == NULL) {
        printf("Map edges are not initialized.\n");
        return false;
    }
    else if (row < 0 || row >= map->height) {
        printf("Invalid row index.\n");
        printf("Please select a row between 0 and %d.\n", map->height - 1);
        return false;
    }
    else if (col < 0 || col >= map->width) {
        printf("Invalid column index.\n");
        printf("Please select a column between 0 and %d.\n", map->width - 1);
        return false;
    }
    return true;
}

void change_edge_down_right(Map *map, int row, int col, int down, int right) {
    if (!validate_input(map, row, col)) {
        return;
    }

    map->edges[row * map->width + col].down = down;
    map->edges[row * map->width + col].right = right;
}

void change_edge_down(Map *map, int row, int col, int down) {
    if (!validate_input(map, row, col)) {
        return;
    }

    map->edges[row * map->width + col].down = down;
}

void change_edge_right(Map *map, int row, int col, int right) {
    if (!validate_input(map, row, col)) {
        return;
    }

    map->edges[row * map->width + col].right = right;
}

