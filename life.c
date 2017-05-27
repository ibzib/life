#include <stdio.h>
#include <stdlib.h>

#define N 4
#define DEAD 0
#define LIVE 1
int grid[N][N];
int live_cells;
void print();
void clear();
void kill(int i, int j);
void birth(int i, int j);
void initialize();
int isAlive(int i, int j);
int getNeighbor(int i, int j, int dx, int dy);
void countLiveNeighbors(int counts[N][N]);
int iterate();
void simulate(int periods);

void print()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", isAlive(i, j));
		}
		printf("\n");
	}
}

void clear()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			kill(i, j);
		}
	}
	live_cells = 0;
}

void kill(int i, int j)
{
	grid[i][j] = DEAD;
	live_cells--;
}

void birth(int i, int j)
{
	grid[i][j] = LIVE;
	live_cells++;
}

void initialize()
{
	clear();
	birth(0, 2);
	birth(1, 0);
	birth(1, 2);
	birth(2, 1);
	birth(2, 2);
}

int isAlive(int i, int j)
{
	return grid[i][j] == LIVE;
}

int getNeighbor(int i, int j, int dx, int dy)
{
	int ni = i + dx;
	int nj = j + dy;
	if (ni < 0 || ni >= N || nj < 0 || nj >= N)
	{
		// out of bounds
		return DEAD;
	}
	else
	{
		return isAlive(ni, nj);
	}
}

void countLiveNeighbors(int counts[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0)
						continue;
					counts[i][j] += getNeighbor(i, j, dx, dy);
				}
			}
		}
	}
}

int iterate()
{
	int counts[N][N];
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			counts[x][y] = 0;
		}
	}
	countLiveNeighbors(counts);
	
	int changes = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int count = counts[i][j];
			// printf("%d\n", count);
			if (isAlive(i, j))
			{
				if (count >= 4 || count <= 1)
				{
					kill(i, j);
					changes++;
				}
			}
			else
			{
				if (count == 3)
				{
					birth(i, j);
					changes++;
				}
			}
		}
	}
	return changes;
}

void simulate(int periods)
{
	for (int p = 0; p < periods; p++)
	{
		print();
		printf("\n");
		iterate();
	}
}

void extinction()
{
	int iterations = 0;
	while (live_cells > 0)
	{
		print();
		// printf("\n");
		if (iterate() == 0)
		{
			printf("Equilibrium reached.\n");
			break;
		}
		iterations++;
		getchar();
	}
	printf("Simulation ended after %d generations.\n", iterations);
}

int main()
{
	//printf("Enter dimensions of board:\n");
	//scanf("%d\n", &N);
	initialize();
	//simulate(5);
	extinction();
	return 0;
}
