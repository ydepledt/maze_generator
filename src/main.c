#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loader.h"
#include "maze.h"

int main() {
    Map *map = create_map(3, 3);

    int down[]  = {1, 2, 3, 8, 99, -1, -4, -88, -99};
    int right[] = {4, 5, 6, -10, -2, -9, -26, -42, 78};

    int down_size = sizeof(down) / sizeof(down[0]);
    int right_size = sizeof(right) / sizeof(right[0]);

    Map *map_bis = create_map_weighted(3, 3, down_size, right_size, down, right);

    print_map(map, 10);
    print_map(map_bis, 10);

    Neighbors *neighbors = find_neighbors_row_col(map_bis, 0, 1);

    printf("Number of neighbors: %d\n", neighbors->nb);
    for (int i = 0; i < 4; i++) {
        printf("Neighbor: %d, Cost: %d\n", neighbors->neighbors[i], neighbors->costs[i]);
    }

    Maze *maze = create_maze(3, 3);

    maze->predecessors[1] = 0;
    maze->predecessors[2] = 1;
    maze->predecessors[5] = 2;
    maze->predecessors[8] = 5;
    maze->predecessors[3] = 0;

    print_maze(maze);
    generate_image(maze, "maze.pbm");

    destroy_map(map);
    destroy_map(map_bis);
    free(neighbors);
    destroy_maze(maze);


    return 0;
}
