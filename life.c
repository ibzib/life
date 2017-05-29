#include "life.h"

struct grid
{
	int width;
	int height;
	int** cells;
	int** nbr_counts;
	int live_cells;
};

void free_2d_array(int** array, int length)
{
	for (int i = 0; i < length; i++)
	{
		free(array[i]);
	}
	free(array);
	array = NULL;
}

void delete_game(grid* game)
{
	free_2d_array(game->cells, game->height);
	free_2d_array(game->nbr_counts, game->height);
	free(game);
	game = NULL;
}

void print(grid* game)
{
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			char c = isAlive(game, i, j) ? LIVE_CHAR : DEAD_CHAR;
			printf("%c ", c);
		}
		printf("\n");
	}
}

void clear(grid* game)
{
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			kill(game, i, j);
		}
	}
}

void kill(grid* game, int i, int j)
{
	if (game->cells[i][j] == LIVE)
	{
		game->cells[i][j] = DEAD;
		game->live_cells--;
	}
}

void birth(grid* game, int i, int j)
{
	if (game->cells[i][j] == DEAD)
	{
		game->cells[i][j] = LIVE;
		game->live_cells++;
	}
}

grid* new_game(int width, int height)
{
	grid* game = malloc(sizeof(grid));
	game->width = width;
	game->height = height;
	game->cells = malloc(height * sizeof(int*));
	game->nbr_counts = malloc(height * sizeof(int*));
	for (int row = 0; row < height; row++)
	{
		game->cells[row] = malloc(width * sizeof(int));
		game->nbr_counts[row] = malloc(width * sizeof(int));
		for (int col = 0; col < width; col++)
		{
			game->cells[row][col] = 0;
			game->nbr_counts[row][col] = 0;
		}
	}
	game->live_cells = 0;
	return game;
}

int isAlive(grid* game, int i, int j)
{
	return game->cells[i][j] == LIVE;
}

int getNeighbor(grid* game, int i, int j, int dx, int dy)
{
	int ni = i + dx;
	int nj = j + dy;
	if (ni < 0 || ni >= game->height || nj < 0 || nj >= game->width)
	{
		// out of bounds
		return DEAD;
	}
	else
	{
		return isAlive(game, ni, nj);
	}
}

void countLiveNeighbors(grid* game)
{
	for (int x = 0; x < game->height; x++)
	{
		for (int y = 0; y < game->width; y++)
		{
			game->nbr_counts[x][y] = 0;
		}
	}

	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			if (isAlive(game, i, j))
			{
				int dx = i > 0 ? -1 : 0;
				for ( ; dx <= 1 && i + dx < game->height; dx++)
				{
					int dy = j > 0 ? -1 : 0;
					for ( ; dy <= 1 && j + dy < game->width; dy++)
					{
						if (dx == 0 && dy == 0)
						{
							continue;
						}
						game->nbr_counts[i+dx][j+dy]++;
					}
				}
			}
		}
	}
/*
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			printf("%d ", counts[i][j]);
		}
		printf("\n");
	}
*/
}

int iterate(grid* game)
{
	countLiveNeighbors(game);
	
	int changes = 0;
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			int count = game->nbr_counts[i][j];
			
			if (isAlive(game, i, j))
			{
				if (count >= 4 || count <= 1)
				{
					kill(game, i, j);
					changes++;
				}
			}
			else
			{
				if (count == 3)
				{
					birth(game, i, j);
					changes++;
				}
			}
		}
	}

	return changes;
}

void simulate(grid* game, int periods)
{
	for (int p = 0; p < periods; p++)
	{
		print(game);
		printf("\n");
		iterate(game);
	}
}

void extinction(grid* game)
{
	int iterations = 0;
	for (;;)
	{
		print(game);
		if (game->live_cells == 0)
		{
			printf("No live cells remaining.\n");
			break;
		}
		if (iterate(game) == 0)
		{
			printf("Equilibrium reached.\n");
			break;
		}
		iterations++;
		while (getchar() != '\n');
	}
	printf("Simulation ended after %d generations.\n", iterations);
}
