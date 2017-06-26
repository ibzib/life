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

void Life::print() const
{
    const static char dead_symbol = '.';
    const static char alive_symbol = '#';
    const static char y_border = '|';
    const static char x_border = '=';

    erase();
    for (int col = 0; col < getWidth()+2; col++)
    {
        addch(x_border);
    }
    addch('\n');
    for (int row = 0; row < getHeight(); row++)
    {
        addch(y_border);
        for (int col = 0; col < getWidth(); col++)
        {
            char symbol = isCellAlive(row, col) ? alive_symbol : dead_symbol;
            addch(symbol);
        }
        addch(y_border);
        addch('\n');
    }
    for (int col = 0; col < getWidth()+2; col++)
    {
        addch(x_border);
    }
    addch('\n');
}

void Life::run(Life& game, int (*rulefunction)(Life&), bool pause)
{
    initscr();
    noecho();

    if (game.getHeight() > LINES-3 || game.getWidth() > COLS-3)
    {
        endwin();
        printf("Error: not enough space in console to render game size %zu x %zu\n", game.getWidth(), game.getHeight());
        return;
    }

    int generations = 1;
    for (;;)
    {
        game.print();
        if (game.getLiveCellCount() == 0)
        {
            printw("No live cells remaining.\n");
            break;
        }
        int changes = rulefunction(game);
        if (changes == 0)
        {
            printw("Equilibrium reached.\n");
            break;
        }
        generations++;

        if (pause)
        {
            for (;;)
            {
                char c = getch();
                if (c == '\n')
                {
                    break;
                }
                else if (c == 'q')
                {
                    endwin();
                    return;
                }
            }
        }
    }

    attron(A_BOLD);
    printw("Simulation ended after %d generations.\n", generations);
    attroff(A_BOLD);
    printw("Press 'q' to quit...");
    while (getch() != 'q');
    endwin();
}
