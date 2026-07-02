#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro definnitions
// #define MAP(X, Y) map[Y * map->x_size + X]

// makro na vypocet indexu na zaklade indexu s pomocou wrappingu:
#define coords(X, Y) [((Y + map->y_size) % map->y_size) * map->x_size + ((X + map->x_size) % map->x_size)]


// struct definitions
typedef struct Map_Struct {
    char* map;
    int size;
    int x_size;
    int y_size;
} Map;


// functions
void map_setup(Map* map, int x, int y) {
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
            if (map->map coords(x,y) == '1') {
                printf("\033[47m..\033[0m");
            } else {
                printf("\033[40m  \033[0m");
            }

        }
        printf("\n");
    }
}

void calc_next_gen(Map* map, char* rulestring) {
    char* nextgen = malloc(sizeof(char) * map->x_size * map->y_size);
    int live_count, dead_count;

    char temp[32];
    strcpy(temp, rulestring);
    char* birth = strtok(temp, "/") + 1;
    char* survive = strtok(NULL, "/") + 1;

    for (int y = 0; y < map->y_size; y++) {
        for (int x = 0; x < map->x_size; x++) {
            live_count = 0;
            dead_count = 0;
            // pre kazdu bunku skontrolujeme jej susedov
            for (int relative_x = -1; relative_x <= 1; relative_x++) {
                for (int relative_y = -1; relative_y <= 1; relative_y++) {
                    if (relative_x != 0 || relative_y != 0) {
                        if (map->map coords(x + relative_x, y + relative_y) == '1') {
                            live_count++;
                        }
                    }
                }
            }
            if (map->map coords(x, y) == '0') {
                if (strchr(birth, live_count+'0' ) != NULL) {
                    nextgen coords(x,y) = '1';
                } else {
                    nextgen coords(x,y) = '0';
                }
            } else {
                if (strchr(survive, live_count+'0' ) != NULL) {
                    nextgen coords(x,y) = '1';
                } else {
                    nextgen coords(x,y) = '0';
                }
            }
        }
    }
    for (int i = 0; i < map->size; i++) {
        map->map[i] = nextgen[i];
    }
    free(nextgen);
}

int main(void)
{
    char* rulestring = "B3/S23";
    // map setup
    Map GoL_map;
    int x = 25, y = 25;
    map_setup(&GoL_map,x,y);
    calc_next_gen(&GoL_map,rulestring);

    map_print(&GoL_map);

    system("pause");
    return 1;
}