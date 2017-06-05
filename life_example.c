#include "life.h"
#include <math.h>
#include <time.h>

void showUsage(char* program_call)
{
	printf("Format: %s width height [life-probability]\n", program_call);
	printf("Example: %s 5 5 0.7\n", program_call);
}

grid* generateRandomGame(int width, int height, float probability)
{
	grid* game = newGame(width, height);

	srand(time(NULL));
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			float random = (float)rand() / RAND_MAX;
			if (random < probability)
			{
				birth(game, row, col);
			}
		}
	}

	return game;
}

int main(int argc, char** argv)
{
	if (argc != 3 && argc != 4)
	{
		printf("Invalid arguments\n");
		showUsage(argv[0]);
		return -1;
	}
	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	if (width <= 0 || height <= 0)
	{
		printf("Error: Invalid dimensions.\n");
		showUsage(argv[0]);
		return -1;
	}

	float probability = 0.5;
	if (argc == 4)
	{
		probability = atof(argv[3]);
		if (probability <= 0)
		{
			printf("Error: Invalid probability.\n");
			showUsage(argv[0]);
			return -1;
		}
	}
	
	grid* game = generateRandomGame(width, height, probability);
	extinction(game);
	deleteGame(game);
	return 0;
}

