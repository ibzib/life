#include "life.hpp"

Life::Life(int height, int width)
{
    m_cells = std::vector<std::vector<Status>>(height, std::vector<Status>(width, Status::dead));
    m_alive_cell_count = 0;
}

Life::~Life()
{
    
}

int Life::getLiveCellCount() const
{
    return m_alive_cell_count;
}

size_t Life::getHeight() const
{
    return m_cells.size();
}

size_t Life::getWidth() const
{
    return m_cells.at(0).size();
}

bool Life::inBounds(int row, int col) const
{
    return row >= 0 && row < getHeight() && col >= 0 && col < getWidth();
}

bool Life::inBounds(std::pair<int,int> coorpair) const
{
    return inBounds(coorpair.first, coorpair.second);
}

void Life::print(bool border) const
{
    char dead_symbol = '.';
    char alive_symbol = '#';
    char y_border = '|';
    char x_border = '-';
    if (border)
    {
        for (int col = 0; col < getWidth()+2; col++)
        {
            printf("%c", x_border);
        }
        printf("\n");
    }
    for (int row = 0; row < getHeight(); row++)
    {
        if (border) printf("%c", y_border);
        for (int col = 0; col < getWidth(); col++)
        {
            char symbol = isCellAlive(row, col) ? alive_symbol : dead_symbol;
            printf("%c", symbol);
        }
        if (border) printf("%c", y_border);
        printf("\n");
    }
    if (border)
    {
        for (int col = 0; col < getWidth()+2; col++)
        {
            printf("%c", x_border);
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

bool Life::isCellAlive(int row, int col) const
{
    return m_cells.at(row).at(col) == Status::alive;
}

bool Life::isCellAlive(std::pair<int,int> coorpair) const
{
    return isCellAlive(coorpair.first, coorpair.second);
}

void Life::run(Life& game, int (*rulefunction)(Life&), bool pause)
{
    int generations = 1;
    for (;;)
    {
        game.print(true);
        if (game.getLiveCellCount() == 0)
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