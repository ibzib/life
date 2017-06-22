#include <vector>
#include "life.hpp"
using namespace std;

vector<vector<pair<int,int>>> getTrafficMoves(const Life& game)
{
    auto moves = vector<vector<pair<int,int>>>(game.getHeight(), vector<pair<int,int>>(game.getWidth()));
    for (int row = 0; row < game.getHeight(); row++)
    {
        for (int col = 0; col < game.getWidth(); col++)
        {
            if (!game.isCellAlive(row, col))
            {
                moves[row][col] = make_pair(row,col);
            }
            else
            {
                auto move = make_pair(row,col+1); // forward
                if (!game.inBounds(move) || !game.isCellAlive(move))
                {
                    moves[row][col] = move;
                    continue;
                }
                move = make_pair(row-1, col); // left
                if (game.inBounds(move) && !game.isCellAlive(move))
                {
                    moves[row][col] = move;
                    continue;
                }
                move = make_pair(row+1, col); // right
                if (game.inBounds(move) && !game.isCellAlive(move))
                {
                    moves[row][col] = move;
                    continue;
                }
                else
                {
                    move = make_pair(row, col); // stay
                    moves[row][col] = move;
                }
            }
        }
    }
    return moves;
}

int traffic(Life& game)
{
    int changes = 0;
    auto moves = getTrafficMoves(game);
    for (int row = 0; row < game.getHeight(); row++)
    {
        for (int col = 0; col < game.getWidth(); col++)
        {
            int nrow = moves[row][col].first;
            int ncol = moves[row][col].second;
            if (nrow==row && ncol==col)
            {
                continue;
            }
            else if (!game.inBounds(nrow, ncol))
            {
                game.killCell(row, col);
            }
            else if (game.isCellAlive(nrow, ncol))
            {
                // collision!
                game.killCell(row, col);
                game.killCell(nrow, ncol);
            }
            else
            {
                // move car
                game.killCell(row, col);
                game.birthCell(nrow, ncol);
            }
            changes++;
        }
    }
    return changes;
}