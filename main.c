#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro definnitions
// #define MAP(X, Y) map[Y * map->x_size + X]

// makro na vypocet indexu na zaklade indexu s pomocou wrappingu:
#define MAP(X, Y) map[((Y + map->y_size) % map->y_size) * map->x_size + ((X + map->x_size) % map->x_size)]


// struct definitions
typedef struct Map_Struct {
    char* map;
    int size;
    int x_size;
    int y_size;
} Map;


// functions
void map_setup(Map* map, char* next_gen, int x, int y) {
    next_gen = malloc(sizeof(char) * x * y);
    map->map = malloc(sizeof(*map->map) * x * y);
    map->size = x * y;
    map->x_size = x;
    map->y_size = y;
    for (int i = 0; i < map->size; i++) {
        map->map[i] = '0';
        if (i % 2 == 1) {  // delete later
            map->map[i] = '1';
        }
    }
}

void map_print(Map* map) {
    for (int y = 0; y < map->y_size; y++) {
        for (int x = 0; x < map->x_size; x++) {
            if (map->MAP(x,y) == '1') {
                printf("\033[47m..\033[0m");
            } else {
                printf("\033[40m  \033[0m");
            }

        }
        printf("\n");
    }
}

void calc_next_gen(Map* map, char* next_gen, char* rulestring) {
    for (int i = 0; i < map->size; i++) {
        // TODO
    }
}

int main(void)
{

    // map setup
    Map GoL_map;
    char* next_gen;
    int x = 25, y = 25;
    map_setup(&GoL_map,next_gen,x,y);


    map_print(&GoL_map);

    system("pause");
    free(next_gen);
    return 1;
}