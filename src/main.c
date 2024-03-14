#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loader.h"
#include "maze.h"
#include "prim.h"

int main() {
    Map *map_ter = load_map("data/map_4_5_1024.txt");
    Maze *maze_ter = create_maze(4, 5);
    print_map(map_ter);


    prim(map_ter, maze_ter);
    print_maze(maze_ter);

    generate_image(maze_ter, "maze_ter.pbm", 2);

    destroy_map(map_ter);
    destroy_maze(maze_ter);

    return 0;
}
