#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main() {
    Map *map = create_map(3, 3);
    if (map == NULL) {
        printf("Map creation failed.\n");
        return 1;
    }

    print_map(map);

    change_edge_down_right(map, 0, 0, 1, 2);
    change_edge_down_right(map, 0, 1, 3, 4);

    print_map(map);

    destroy_map(map);

    return 0;
}
