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

std::vector<std::vector<int>> countAliveNeighbors(const Life& game)
{
    std::vector<std::vector<int>> counts = std::vector<std::vector<int>>(game.getHeight(), std::vector<int>(game.getWidth(), 0));
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
    std::vector<std::vector<int>> counts = countAliveNeighbors(game);
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

int traffic(Life& game)
{
    
    return 0;
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
        Life::run(game, &traffic, true);
    }
    else
    {
        Life::run(game, &conway, true);
    }
    return 0;
}