#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loader.h"

int main() {
    Map *map = create_map(3, 3);

    int down[]  = {1, 2, 3, 8, 9};
    int right[] = {4, 5, 6};

    int down_size = sizeof(down) / sizeof(down[0]);
    int right_size = sizeof(right) / sizeof(right[0]);

    Map *map_bis = create_map_weighted(3, 3, down_size, right_size, down, right);

    Map *map_ter = load_map("map.txt");

    print_map(map, 10);
    print_map(map_bis, 10);
    print_map(map_ter, 10);


    destroy_map(map);
    destroy_map(map_bis);
    destroy_map(map_ter);

    return 0;
}
