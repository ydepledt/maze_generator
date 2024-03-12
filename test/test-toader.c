#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "map.h"
#include "loader.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Print an error message
        fprintf(stderr, "Error: Please provide a file or 'ALL' as an argument.\n");
        
        // Exit the program with a non-zero status code
        exit(EXIT_FAILURE);
    }

    // Test all maps present in the data folder
    if (strcmp(argv[1], "ALL") == 0) {
        DIR *dir;
        struct dirent *ent;

        printf("Loading all maps in the data folder...\n");

        if ((dir = opendir("data")) != NULL) {
            // Loop through all files in the data folder
            while ((ent = readdir(dir)) != NULL) {
                // Skip the current directory and the parent directory
                if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                    continue;

                printf("Loading map: \"%s\"...\n", ent->d_name);
                // Check if the file ends with ".txt"
                if (strstr(ent->d_name, ".txt") == NULL)
                    continue;

                char filepath[300];
                snprintf(filepath, sizeof(filepath), "data/%s", ent->d_name);

                // Load and print each map
                Map *map = load_map(filepath);

                if (map == NULL) {
                    // Print an error message
                    fprintf(stderr, "Error: Could not load map %s.\n", ent->d_name);
                } else {
                    print_map(map, 10);
                    destroy_map(map);
                    printf("\n");
                }
            }

            closedir(dir);

        } 
        
        else {
            // Print an error message
            perror("Error: Unable to open directory");
            exit(EXIT_FAILURE);
        }
    } 
    
    else {
        Map *map = load_map(argv[1]);
        if (map == NULL) {
            // Print an error message
            fprintf(stderr, "Error: Could not load map.\n");
            
            // Exit the program with a non-zero status code
            exit(EXIT_FAILURE);
        }

        print_map(map, 10);

        destroy_map(map);
    }

    return 0;
}