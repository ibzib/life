#include <stdio.h>
#include <stdlib.h>

#define DEAD 0
#define LIVE 1
#define DEAD_CHAR '.'
#define LIVE_CHAR '#'
struct grid;
typedef struct grid grid;
void print(grid* game);
void clear(grid* game);
void kill(grid* game, int i, int j);
void birth(grid* game, int i, int j);
grid* new_game(int width, int height);
int isAlive(grid* game, int i, int j);
void delete_game(grid* game);
int getNeighbor(grid* game, int i, int j, int dx, int dy);
int** countLiveNeighbors(grid* game);
int iterate(grid* game);
void simulate(grid* game, int periods);
void extinction(grid* game);
