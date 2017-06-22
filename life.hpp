#include <cstdio>
#include <cstdlib>
#include <vector>

class Life {
public:
    Life(int height, int width);
    ~Life();
    int m_alive_cell_count;
    size_t getHeight() const;
    size_t getWidth() const;
    void print() const;
    void clear();
    void killCell(int row, int col);
    void birthCell(int row, int col);
    void movecell(int drow, int dcol);
    bool inBounds(int row, int col) const;
    bool isCellAlive(int row, int col) const;
    static void run(Life& game, int (*rulefunction)(Life&), bool pause);
private:
    enum class Status { dead, alive };
    std::vector<std::vector<Status>> m_cells;
};