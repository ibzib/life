#include "life.hpp"
#include <cmath>
#include <ctime>
#include <string>

void showUsage(char* program_call)
{
	printf("Format: %s height width [life-probability (0..1)]\n", program_call);
	printf("Example: %s 5 5 0.7\n", program_call);
}

Life generateRandomGame(int height, int width, float probability)
{
	Life game(height, width);

	srand(time(NULL));
	for (int row = 0; row < game.getHeight(); row++)
	{
		for (int col = 0; col < game.getWidth(); col++)
		{
			float random = (float)rand() / RAND_MAX;
			if (random < probability)
			{
				game.birthCell(row, col);
			}
		}
	}

	return game;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Invalid arguments\n");
		showUsage(argv[0]);
		return 1;
	}

	std::string flag(argv[1]);
	int argstart = flag=="-c" || flag=="-t" ? 1 : 0;
	int height = atoi(argv[argstart+1]);
	int width = atoi(argv[argstart+2]);
	if (height <= 0 || width <= 0)
	{
		printf("Error: Invalid dimensions.\n");
		showUsage(argv[0]);
		return 1;
	}

	float probability = 0.5;
	if (argc == 4)
	{
		probability = atof(argv[argstart+3]);
		if (probability <= 0 || probability >= 1)
		{
			printf("Error: Invalid probability.\n");
			showUsage(argv[0]);
			return 1;
		}
	}

	Life game = generateRandomGame(height, width, probability);
	if (flag == "-t")
	{
		Life::run(game, &Life::traffic, true);
	}
	else
	{
		Life::run(game, &Life::conway, true);
	}
	return 0;
}