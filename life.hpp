#include <cstdio>
#include <cstdlib>
#include <cassert>

class Life {
public:
    Life(int width, int height);
    ~Life();
    int m_width;
    int m_height;
    int m_alive_cell_count;
    void const print();
    void clear();
    void killCell(int row, int col);
    void birthCell(int row, int col);
    bool const isCellAlive(int row, int col);
    int iterate();
    void simulate(int periods);
    void extinction();
private:
    enum class Status { dead, alive };
    Status** m_cells; // points to an array of m_height arrays of m_width Statuses
    bool const inBounds(int row, int col);
    int const countAliveNeighbors(int row, int col);
};