#include "life.h"
#include <math.h>
#include <time.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Invalid arguments\n");
		printf("Format: %s [width] [height]\n", argv[0]);
		return -1;
	}
	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	
	grid* game = new_game(width, height);
/*
	birth(game, 0, 2);
	birth(game, 1, 0);
	birth(game, 1, 2);
	birth(game, 2, 1);
	birth(game, 2, 2);
*/
	srand(time(NULL));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rand() % 2 == 0)
			{
				birth(game, i, j);
			}
		}
	}

	extinction(game);
	delete_game(game);
	return 0;
}

