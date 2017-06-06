#include "life.hpp"

Life::Life(int height, int width)
{
	assert(height > 0 && width > 0);
	m_height = height;
	m_width = width;
	m_alive_cell_count = 0;
	m_cells = (Status**)malloc(height * sizeof(Status*));
	for (int row = 0; row < m_height; row++)
	{
		m_cells[row] = (Status*)malloc(m_width * sizeof(Status));
		for (int col = 0; col < m_width; col++)
		{
			m_cells[row][col] = Status::dead;
		}
	}
}

Life::~Life()
{
	for (int row = 0; row < m_height; row++)
	{
		free(m_cells[row]);
	}
	free(m_cells);
}

bool const Life::inBounds(int row, int col)
{
	return row >= 0 && row < m_height && col >= 0 && col < m_width;
}

void const Life::print()
{
	const char dead_symbol = '.';
	const char alive_symbol = '#';
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			char symbol = isCellAlive(row, col) ? alive_symbol : dead_symbol;
			printf("%c ", symbol);
		}
		printf("\n");
	}
}

void Life::clear()
{
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			killCell(row, col);
		}
	}
}

void Life::killCell(int row, int col)
{
	assert(inBounds(row, col));
	if (isCellAlive(row, col))
	{
		m_cells[row][col] = Status::dead;
		m_alive_cell_count--;
	}
}

void Life::birthCell(int row, int col)
{
	assert(inBounds(row, col));
	if (!isCellAlive(row, col))
	{
		m_cells[row][col] = Status::alive;
		m_alive_cell_count++;
	}
}

bool const Life::isCellAlive(int row, int col)
{
	assert(inBounds(row, col));
	return m_cells[row][col] == Status::alive;
}

int const Life::countAliveNeighbors(int row, int col)
{
	int count = 0;
	for (int drow = -1; drow <= 1; drow++)
	{
		for (int dcol = -1; dcol <= 1; dcol++)
		{
			if (drow == 0 && dcol == 0)
				continue;

			int nbr_row = row + drow;
			int nbr_col = col + dcol;
			if (!inBounds(nbr_row, nbr_col))
				continue;

			if (isCellAlive(nbr_row, nbr_col))
				count++;
		}
	}
	return count;
}

int Life::iterate()
{	
	int changes = 0;
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			int count = countAliveNeighbors(row, col);
			
			if (isCellAlive(row, col))
			{
				if (count >= 4 || count <= 1)
				{
					killCell(row, col);
					changes++;
				}
			}
			else
			{
				if (count == 3)
				{
					birthCell(row, col);
					changes++;
				}
			}
		}
	}

	return changes;
}

void Life::simulate(int periods)
{
	for (int p = 0; p < periods; p++)
	{
		print();
		printf("\n");
		iterate();
	}
}

void Life::extinction()
{
	int iterations = 0;
	for (;;)
	{
		print();
		if (m_alive_cell_count == 0)
		{
			printf("No live cells remaining.\n");
			break;
		}
		if (iterate() == 0)
		{
			printf("Equilibrium reached.\n");
			break;
		}
		iterations++;
		while (getchar() != '\n');
	}
	printf("Simulation ended after %d generations.\n", iterations);
}