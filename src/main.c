#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loader.h"
#include "maze.h"
#include "prim.h"

int main() {
    Map *map_ter = load_map("data/map_10_8_42.txt");
    Maze *maze_ter = create_maze(10, 8);
    print_map(map_ter);


    prim(map_ter, maze_ter);
    print_maze(maze_ter);

    generate_image(maze_ter, "maze_ter.pbm", 10);

    destroy_map(map_ter);
    destroy_maze(maze_ter);

    return 0;
}
