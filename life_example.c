#include "life.h"
#include <math.h>
#include <time.h>

void show_usage(char* program_call)
{
		printf("Format: %s width height [life-probability]\n", program_call);
		printf("Example: %s 5 5 0.7\n", program_call);
}

int main(int argc, char** argv)
{
	if (argc != 3 && argc != 4)
	{
		printf("Invalid arguments\n");
		show_usage(argv[0]);
		return -1;
	}
	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	if (width <= 0 || height <= 0)
	{
		printf("Error: Invalid dimensions.\n");
		show_usage(argv[0]);
		return -1;
	}

	float probability = 0.5;
	if (argc == 4)
	{
		probability = atof(argv[3]);
		if (probability <= 0)
		{
			printf("Error: Invalid probability.\n");
			show_usage(argv[0]);
			return -1;
		}
	}
	
	grid* game = new_game(width, height);

	srand(time(NULL));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float random = (float)rand() / RAND_MAX;
			if (random < probability)
			{
				birth(game, i, j);
			}
		}
	}

	extinction(game);
	delete_game(game);
	return 0;
}

