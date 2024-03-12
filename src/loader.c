#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "loader.h"

Map *load_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Print an error message
        fprintf(stderr, "Error: Could not open file.\n");
        
        // Exit the program with a non-zero status code
        exit(EXIT_FAILURE);
    }

    int width, height;
    fscanf(file, "%d %d", &width, &height);

    int *down = malloc(height * width * sizeof(int));
    int *right = malloc(height * width * sizeof(int));

    for (int i = 0; i < height * width; i++) {
        fscanf(file, "%d %d", &down[i], &right[i]);
    }

    Map *map = create_map_weighted(width, height, height * width, height * width, down, right);
    if (map == NULL) {
        free(down);
        free(right);
        fclose(file);
        return NULL; // Map creation failed
    }

    free(down);
    free(right);
    fclose(file);
    
    return map;
}