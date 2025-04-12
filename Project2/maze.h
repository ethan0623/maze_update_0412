#ifndef maze_H
#define maze_H
#include <stack>
#include <vector>
#include <utility>


struct Cell {
    bool isWall=true;
    bool isVisited=false;
};
// �w�q�䪺���c
struct Edge {
    int x1, y1; // �䪺����I����
    int x2, y2; // �䪺�t�@�ݧ���
};
class Maze {
public:
    //vector<vector<Cell>> cells;
    int width, height,begin_x, begin_y, finish_x, finish_y;

   

    // �ѼƤƺc�y��ơA�i�i���l��
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
