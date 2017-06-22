#include "life.hpp"

Life::Life(int height, int width)
{
	m_cells = std::vector<std::vector<Status>>(height, std::vector<Status>(width, Status::dead));
	m_alive_cell_count = 0;
}

Life::~Life()
{
	
}

size_t const Life::getHeight()
{
	return m_cells.size();
}

size_t const Life::getWidth()
{
	return m_cells.at(0).size();
}

bool const Life::inBounds(int row, int col)
{
	return row >= 0 && row < getHeight() && col >= 0 && col < getWidth();
}

void const Life::print()
{
	const char dead_symbol = '.';
	const char alive_symbol = '#';
	for (int row = 0; row < getHeight(); row++)
	{
		for (int col = 0; col < getWidth(); col++)
		{
			char symbol = isCellAlive(row, col) ? alive_symbol : dead_symbol;
			printf("%c ", symbol);
		}
		printf("\n");
	}
}

void Life::clear()
{
	for (int row = 0; row < getHeight(); row++)
	{
		for (int col = 0; col < getWidth(); col++)
		{
			killCell(row, col);
		}
	}
}

void Life::killCell(int row, int col)
{
	if (isCellAlive(row, col))
	{
		m_cells.at(row).at(col) = Status::dead;
		m_alive_cell_count--;
	}
}

void Life::birthCell(int row, int col)
{
	if (!isCellAlive(row, col))
	{
		m_cells.at(row).at(col) = Status::alive;
		m_alive_cell_count++;
	}
}

bool const Life::isCellAlive(int row, int col)
{
	return m_cells.at(row).at(col) == Status::alive;
}

std::vector<std::vector<int>> const Life::countAliveNeighbors()
{
	std::vector<std::vector<int>> counts = std::vector<std::vector<int>>(getHeight(), std::vector<int>(getWidth(), 0));
	for (int row = 0; row < getHeight(); row++)
	{
		for (int col = 0; col < getWidth(); col++)
		{
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
						counts.at(row).at(col)++;
				}
			}
		}
	}
	return counts;
}

void Life::run(Life& game, int (*rulefunction)(Life&), bool pause)
{
	int generations = 1;
	for (;;)
	{
		game.print();
		if (game.m_alive_cell_count == 0)
		{
			printf("No live cells remaining.\n");
			break;
		}
		int changes = rulefunction(game);
		if (changes == 0)
		{
			printf("Equilibrium reached.\n");
			break;
		}

		generations++;
		if (pause)
			while (getchar() != '\n');
	}
	printf("Simulation ended after %d generations.\n", generations);
}