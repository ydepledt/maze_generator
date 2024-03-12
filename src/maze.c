#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

Maze *create_maze(int width, int height) {
    // Allocate memory for maze struct
    Maze *maze = malloc(sizeof(Maze));
    if (maze == NULL) {
        return NULL; // Memory allocation failed
    }

    maze->width = width;
    maze->height = height;

    // Allocate memory for predecessors array-like structure
    maze->predecessors = (int*)malloc(height * width * sizeof(int));
    if (maze->predecessors == NULL) {
        free(maze); // Free previously allocated memory
        return NULL; // Memory allocation failed
    }

    // Initialize predecessors (assuming all predecessors initially have value -1)
    for (int i = 0; i < height * width; i++) {
        maze->predecessors[i] = -1;
    }

    return maze;
}

void destroy_maze(Maze *maze) {
    free(maze->predecessors);
    free(maze);
}

void print_maze(Maze *maze) {

    int width = maze->width;
    int height = maze->height;

    for (int i = 0; i < 2 * width + 1; i++) {
        printf("#"); // Top border
    }

    printf("\n");

    for (int i = 0; i < 2 * (height - 1) + 1; i++) {

        printf("#"); // Left border

        for (int j = 0; j < 2 * (width - 1) + 1; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                printf("\033[7m \033[m"); // Node
            }

            else if (i % 2 != 0 && j % 2 != 0)
            {
                printf("#");
            }

            else {
                if (maze->predecessors[(i / 2) * width + ((j + 1) / 2)] == (i / 2) * width + (j / 2)) {
                    printf("\033[47;30m-\033[0m");
                }

                else if (maze->predecessors[((i + 1) / 2) * width + (j / 2)] == (i / 2) * width + (j / 2)) {
                    printf("\033[47;30m|\033[0m");
                }

                else {
                    printf("#");
                }
            }
        }
        printf("#\n"); // Right border
    }

    for (int i = 0; i < 2 * width + 1; i++) {
        printf("#"); // Bottom border
    }

    printf("\n");

}

void generate_image(Maze *maze, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    int width = maze->width;
    int height = maze->height;

    // Write a ppm file
    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", 2 * width + 1, 2 * height + 1);

    for (int i = 0; i < 2 * width + 1; i++) {
        fprintf(file, "1 "); // Top border
    }

    fprintf(file, "\n");

    for (int i = 0; i < 2 * (height - 1) + 1; i++) {

        fprintf(file, "1 "); // Left border

        for (int j = 0; j < 2 * (width - 1) + 1; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                fprintf(file, "0 ");
            }

            else if (i % 2 != 0 && j % 2 != 0) {
                fprintf(file, "1 ");
            }

            else {
                if (maze->predecessors[(i / 2) * width + ((j + 1) / 2)] == (i / 2) * width + (j / 2)) {
                    fprintf(file, "0 ");
                }

                else if (maze->predecessors[((i + 1) / 2) * width + (j / 2)] == (i / 2) * width + (j / 2)) {
                    fprintf(file, "0 ");
                }

                else {
                    fprintf(file, "1 ");
                }
            }
        }
        
        fprintf(file, "1 \n");
    }

    for (int i = 0; i < 2 * width + 1; i++) {
        fprintf(file, "1 "); // Bottom border
    }

    fprintf(file, "\n");
}
