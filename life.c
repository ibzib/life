#include "life.h"

struct grid
{
	int width;
	int height;
	int** cells;
	int** nbr_counts;
	int live_cells;
};

void clear2dArray(int** array, int width, int height)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			array[row][col] = 0;
		}
	}
}

void free2dArray(int** array, int length)
{
	for (int i = 0; i < length; i++)
	{
		free(array[i]);
	}
	free(array);
	array = NULL;
}

void deleteGame(grid* game)
{
	free2dArray(game->cells, game->height);
	free2dArray(game->nbr_counts, game->height);
	free(game);
	game = NULL;
}

void print(grid* game)
{
	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			char c = isAlive(game, row, col) ? LIVE_CHAR : DEAD_CHAR;
			printf("%c ", c);
		}
		printf("\n");
	}
}

void clear(grid* game)
{
	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			kill(game, row, col);
		}
	}
}

void kill(grid* game, int row, int col)
{
	if (game->cells[row][col] == LIVE)
	{
		game->cells[row][col] = DEAD;
		game->live_cells--;
	}
}

void birth(grid* game, int row, int col)
{
	if (game->cells[row][col] == DEAD)
	{
		game->cells[row][col] = LIVE;
		game->live_cells++;
	}
}

grid* newGame(int width, int height)
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

int isAlive(grid* game, int row, int col)
{
	return game->cells[row][col] == LIVE;
}

int getNeighbor(grid* game, int row, int col, int drow, int dcol)
{
	int nbr_row = row + drow;
	int nbr_col = col + dcol;
	if (nbr_row < 0 || nbr_row >= game->height || nbr_col < 0 || nbr_col >= game->width)
	{
		// out of bounds
		return DEAD;
	}
	else
	{
		return isAlive(game, nbr_row, nbr_col);
	}
}

void countLiveNeighbors(grid* game)
{
	clear2dArray(game->nbr_counts, game->width, game->height);

	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			if (isAlive(game, row, col))
			{
				int drow = row > 0 ? -1 : 0;
				for ( ; drow <= 1 && row + drow < game->height; drow++)
				{
					int dcol = col > 0 ? -1 : 0;
					for ( ; dcol <= 1 && col + dcol < game->width; dcol++)
					{
						if (drow == 0 && dcol == 0)
						{
							continue;
						}
						game->nbr_counts[row+drow][col+dcol]++;
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
	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			int count = game->nbr_counts[row][col];
			
			if (isAlive(game, row, col))
			{
				if (count >= 4 || count <= 1)
				{
					kill(game, row, col);
					changes++;
				}
			}
			else
			{
				if (count == 3)
				{
					birth(game, row, col);
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
