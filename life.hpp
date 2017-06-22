#include <cstdio>
#include <cstdlib>
#include <vector>

class Life {
public:
    Life(int height, int width);
    ~Life();
    int m_alive_cell_count;
    size_t const getHeight();
    size_t const getWidth();
    void const print();
    void clear();
    void killCell(int row, int col);
    void birthCell(int row, int col);
    bool const isCellAlive(int row, int col);
    std::vector<std::vector<int>> const countAliveNeighbors();
    static void run(Life& game, int (*rulefunction)(Life&), bool pause);
private:
    enum class Status { dead, alive };
    std::vector<std::vector<Status>> m_cells;
    bool const inBounds(int row, int col);
};