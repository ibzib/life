#include <vector>
#include "life.hpp"
using namespace std;

vector<vector<int>> countAliveNeighbors(const Life& game)
{
    auto counts = vector<vector<int>>(game.getHeight(), vector<int>(game.getWidth(), 0));
    for (int row = 0; row < game.getHeight(); row++)
    {
        for (int col = 0; col < game.getWidth(); col++)
        {
            for (int drow = -1; drow <= 1; drow++)
            {
                for (int dcol = -1; dcol <= 1; dcol++)
                {
                    if (drow == 0 && dcol == 0)
                        continue;

                    int nbr_row = row + drow;
                    int nbr_col = col + dcol;
                    if (!game.inBounds(nbr_row, nbr_col))
                        continue;

                    if (game.isCellAlive(nbr_row, nbr_col))
                        counts.at(row).at(col)++;
                }
            }
        }
    }
    return counts;
}

int conway(Life& game)
{	
    int changes = 0;
    auto counts = countAliveNeighbors(game);
    for (int row = 0; row < game.getHeight(); row++)
    {
        for (int col = 0; col < game.getWidth(); col++)
        {
            if (game.isCellAlive(row, col))
            {
                if (counts.at(row).at(col) >= 4 || counts.at(row).at(col) <= 1)
                {
                    game.killCell(row, col);
                    changes++;
                }
            }
            else
            {
                if (counts.at(row).at(col) == 3)
                {
                    game.birthCell(row, col);
                    changes++;
                }
            }
        }
    }

    return changes;
}