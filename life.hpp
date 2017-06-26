#include <cstdio>
#include <cstdlib>
#include <vector>
#include <curses.h>

class Life {
public:
    Life(int height, int width);
    ~Life();
    int getLiveCellCount() const;
    size_t getHeight() const;
    size_t getWidth() const;
    void print() const;
    void clear();
    void killCell(int row, int col);
    void birthCell(int row, int col);
    bool inBounds(int row, int col) const;
    bool inBounds(std::pair<int,int> coorpair) const;
    bool isCellAlive(int row, int col) const;
    bool isCellAlive(std::pair<int,int> coorpair) const;
    static void run(Life& game, int (*rulefunction)(Life&), bool pause);
private:
    int m_alive_cell_count;
    enum class Status { dead, alive };
    std::vector<std::vector<Status>> m_cells;
};
