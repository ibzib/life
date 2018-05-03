#include "life.hpp"
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

extern int conway(Life& game);

void showUsage(char* program_call)
{
    printf("Format: %s width height [life-probability (0..1)]\n", program_call);
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
    int width = argc >= 2 ? atoi(argv[1]) : 10;
    int height = argc >= 3 ? atoi(argv[2]) : 10;
    if (height <= 0 || width <= 0)
    {
        printf("error: invalid dimensions.\n");
        showUsage(argv[0]);
        return 1;
    }

    float probability = 0.5;
    if (argc >= 4)
    {
        probability = atof(argv[4]);
        if (probability <= 0 || probability >= 1)
        {
            printf("Error: Invalid probability.\n");
            showUsage(argv[0]);
            return 1;
        }
    }

    Life game = generateRandomGame(height, width, probability);
    Life::run(game, &conway, true);
    return 0;
}
