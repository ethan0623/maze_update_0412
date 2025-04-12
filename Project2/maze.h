#ifndef maze_H
#define maze_H
#include <stack>
#include <vector>
#include <utility>


struct Cell {
    bool isWall=true;
    bool isVisited=false;
};
// 定義邊的結構
struct Edge {
    int x1, y1; // 邊的兩端點坐標
    int x2, y2; // 邊的另一端坐標
};
class Maze {
public:
    //vector<vector<Cell>> cells;
    int width, height,begin_x, begin_y, finish_x, finish_y;

   

    // 參數化構造函數，可進行初始化
    Maze(int w, int h);
    int getBeginX() const;
    int getBeginY() const;
    int getFinishX() const;
    int getFinishY() const;
    void display(sf::RenderWindow& window, int player_x, int player_y);
    bool player_move(int& player_x, int& player_y, int new_player_x, int new_player_y);
    bool DFS(std::pair<int, int>& node, int start_x, int start_y, sf::RenderWindow& window, std::vector<std::pair<int, int>>& path);
    void generateMaze();
    void drawCell(sf::RenderWindow& window, int x, int y, sf::Color color);

};

#endif // maze_H
