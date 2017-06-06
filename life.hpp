#include <cstdio>
#include <cstdlib>
#include <cassert>

class Life {
public:
    Life(int height, int width);
    ~Life();
    int m_height;
    int m_width;
    int m_alive_cell_count;
    void const print();
    void clear();
    void killCell(int row, int col);
    void birthCell(int row, int col);
    bool const isCellAlive(int row, int col);
    int iterate();
    void simulate(int iterations); // runs the given number of iterations
    void extinction(); // lets user cycle through iterations until game ends
private:
    enum class Status { dead, alive };
    Status** m_cells; // points to an array of m_height arrays of m_width Statuses
    bool const inBounds(int row, int col);
    int const countAliveNeighbors(int row, int col);
};