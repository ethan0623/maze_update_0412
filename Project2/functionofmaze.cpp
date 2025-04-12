#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
#include "maze.h"
using namespace std;

vector<vector<Cell>> cells;

int i;

    // 參數化構造函數，可進行初始化
Maze::Maze(int w, int h) : width(w), height(h) {

    //height 指的是迷宮的列數，vector<Cell>(width) 指的是每一列都有 width 個 Cell
    cells.resize(height, vector<Cell>(width));

    //srand 的 source code => void srand(unsigned int seed);
    //time(0) 的類型為 time_t，所以要先透過 static_cast<unsigned int>(time(0)) 轉成 unsigned int
    srand(static_cast<unsigned int>(time(0)));

    // 隨機生成迷宮


    // 設定起點和終點
    // 起點
    begin_x = 1 + 2 * (rand() % ((height - 1) / 2));
    begin_y = 1 + 2 * (rand() % ((width - 1) / 2));
    cells[begin_x][begin_y].isVisited = true;
    // 終點
    // 確保起點與終點不在同一個位置
    do {
        finish_x = 1+2*(rand()%((height-1)/2));
        finish_y = 1 + 2 * (rand() % ((width - 1) / 2));
    } while (begin_x == finish_x && begin_y == finish_y);
    
    //test
    cells[begin_x][begin_y].isWall = false;
    cells[finish_x][finish_y].isWall = false;
}
    int Maze::getBeginX() const { return begin_x; }
    int Maze::getBeginY() const { return begin_y; }
    int Maze::getFinishX() const { return finish_x; }
    int Maze::getFinishY() const { return finish_y; }

    void Maze::generateMaze() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i % 2 == 1 && j % 2 == 1) {
                    cells[i][j].isWall = false;
                }
            }
        }
        vector<pair<int, int>> walls;
        if (begin_x > 1) {
            walls.push_back({ begin_x - 1,begin_y });
        }
        if (begin_x < height - 2) {
            walls.push_back({ begin_x + 1,begin_y });
        }
        if (begin_y > 1) {
            walls.push_back({ begin_x,begin_y - 1 });
        }
        if (begin_y < width - 2) {
            walls.push_back({ begin_x,begin_y + 1 });
        }
        while (!walls.empty()) {
            int count_visited = 0;
            int index = rand() % (walls.size());
            int row = walls[index].first;
            int col = walls[index].second;
            if (row > 1 && cells[row - 1][col].isVisited) {
                count_visited++;
            }
            if (row < height-2 && cells[row + 1][col].isVisited) {
                count_visited++;
            }
            if (col > 1 && cells[row][col - 1].isVisited) {
                count_visited++;
            }
            if (col < width - 2 && cells[row][col + 1].isVisited) {
                count_visited++;
            }

            if (count_visited == 1) {
                cells[row][col].isWall = false;
                cells[row][col].isVisited = true;

                if (row > 1) {
                    walls.push_back({ row - 1,col });
                }
                if (row < height - 2) {
                    walls.push_back({ row + 1,col });
                }
                if (col > 1) {
                    walls.push_back({ row,col - 1 });
                }
                if (col < width - 2) {
                    walls.push_back({ row,col + 1 });
                }
            }
            walls.erase(walls.begin() + index);
        }

    }
    // 顯示迷宮
    // sf::RenderWindow& window 是 SFML 的窗口對象的引用，用於進行所有的繪圖操作
    void Maze::display(sf::RenderWindow& window, int player_x, int player_y) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                //創建一個長方形，大小為 20x20 像素，即為每個迷宮單元格的大小
                sf::RectangleShape rect(sf::Vector2f(20, 20));
                //將長方形放置在窗口中的正確位置
                rect.setPosition(j * 20, i * 20);
                // 這個判斷式是用來將牆壁畫成黑色的
                rect.setFillColor(cells[i][j].isWall ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
            }
        }
        //繪製終點位置
        sf::RectangleShape finish(sf::Vector2f(15, 15));
        finish.setFillColor(sf::Color::Green);
        finish.setPosition(finish_y * 20 + 5, finish_x * 20 + 5);
        window.draw(finish);

        // 繪製玩家位置
        sf::CircleShape player(5); // 半徑為 10 的圓形，表示玩家
        player.setFillColor(sf::Color::Red); // 玩家顏色
        player.setPosition(player_y * 20 + 5, player_x * 20 + 5); // 計算玩家位置，顯示在格子中央
        window.draw(player); // 繪製玩家

    }

    bool Maze::player_move(int& player_x, int& player_y, int new_player_x, int new_player_y) {
        // 檢查新位置是否有效
        if (new_player_x < 0 || new_player_x >= height || new_player_y < 0 || new_player_y >= width || cells[new_player_x][new_player_y].isWall) {
            cout << "無法移動，碰到牆壁！" << endl;
            return false;
        }

        // 更新玩家位置
        player_x = new_player_x;
        player_y = new_player_y;
        cells[player_x][player_y].isVisited = true; // 標記為已訪問

        // 檢查是否到達終點
        if (player_x == finish_x && player_y == finish_y) {
            cout << "恭喜你成功到達終點！" << endl;
            return true;
        }
        return false;
    }

    bool Maze::DFS(pair<int, int>& node, int start_x, int start_y, sf::RenderWindow& window, vector<pair<int, int>>& path) {
        stack<pair<int, int>> s;
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        s.push({ start_x, start_y });

        while (!s.empty()) {
            node = s.top();
            s.pop();
            if (visited[node.first][node.second]) {
                continue;
            }

            visited[node.first][node.second] = true;
            path.push_back(node); // 将访问的节点存储到路径中

            // 绘制路径（可以注释掉，如果你想动态显示）
            // drawCell(window, node.first, node.second, sf::Color::Blue);

            if (node.first == finish_x && node.second == finish_y) {
                return true; // 找到终点，返回 true
            }

            vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
            for (const pair<int, int>& dir : directions) {
                int newX = node.first + dir.first;
                int newY = node.second + dir.second;
                if (newX >= 0 && newX < height && newY >= 0 && newY < width &&
                    !visited[newX][newY] && !cells[newX][newY].isWall) {
                    s.push({ newX, newY });
                }
            }
        }
        return false; // 未找到路径
    }

    void Maze::drawCell(sf::RenderWindow& window, int x, int y, sf::Color color) {
        sf::RectangleShape cell(sf::Vector2f(5, 5)); // 每個格子的大小
        cell.setPosition(5+y * 20, 5+x * 20); // 設置格子的位置
        cell.setFillColor(color); // 設置顏色
        window.draw(cell); // 在視窗中繪製格子
    }



