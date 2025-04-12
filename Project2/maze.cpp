#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include <chrono>
#include <windows.h>
#include <psapi.h>  // 包含 GetProcessMemoryInfo
#include "maze.h"

using namespace std;
//using namespace std::chrono;
//extern int i;

extern vector<vector<Cell>> cells;
int main() {
    int i;
 
    std::cout << "Before memory usage tracking:" << endl;

    // 獲取內存資訊
    HANDLE hProcess = GetCurrentProcess(); // 獲取當前進程的句柄
    PROCESS_MEMORY_COUNTERS pmc;

    // 獲取內存資訊
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        std::cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB" << endl;
        std::cout << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
        std::cout << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB" << endl;
        std::cout << "Peak Pagefile Usage: " << pmc.PeakPagefileUsage / 1024 << " KB" << endl;
    }
    else {
        cerr << "Error in GetProcessMemoryInfo()" << endl;
    }

    //auto start = high_resolution_clock::now();

    //sf::VideoMode videoMode(width, height); 拿來設定 windows 的長寬
    int count = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Visualization");
    Maze maze(40, 30); // 40x30 的迷宮
    int height = 40, width = 30;
  
    int player_x = maze.getBeginX(), player_y = maze.getBeginY(); // 玩家初始位置
    int final_x = maze.getFinishX(), final_y = maze.getFinishY();
 
    std::pair<int, int> node;
    //while (!maze.DFS(player_x, player_y)) {
    //    Maze maze(40, 30);
    //    player_x = maze.getBeginX(), player_y = maze.getBeginY();
    //    count++;
    //}
    //cout << "迷宮生成了幾次才成功：" << count << endl;
    //do {
    //    maze.generateMaze();
    //    count++;
    //    if (count == 10) {
    //        cout << "成功10次"<<endl;
    //        break;
    //    }
    //} while (maze.DFS(player_x, player_y, window));
    maze.generateMaze();
    maze.display(window, player_x, player_y);
    //window.display();
    
    
    
    //bool canMove = true; // 標記是否可以移動
    //const float moveDelay = 0.15f; // 移動延遲時間（秒）
    //sf::Clock moveClock; // 用於計時
    vector<pair<int, int>> path;
    //window.display();
    if (maze.DFS(node,player_x, player_y, window,path)) { // 啟動 DFS
        std::cout << "Found a path to the finish!" << std::endl;
       for (const auto& visitedNode : path) {
            std::cout << "Visited: (" << visitedNode.first << ", " << visitedNode.second << ")" << std::endl;
            maze.drawCell(window, visitedNode.first, visitedNode.second, sf::Color::Blue); // 绘制路径
            //sf::sleep(sf::milliseconds(100)); // 控制移動速度
            //window.display();
            count++;
       }
       window.display();
       cout << "走" << count << "步才到"  ;
    }
    else {
        std::cout << "No path to the finish." << std::endl;
    }

    while (window.isOpen()) {
        //用於表示各種事件（如鍵盤、滑鼠、窗口狀態等）
        sf::Event event;
        // 處理事件
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // 正確處理窗口關閉事件
            }
        }
       
        //player_x = ans[i].first;
        //player_y = ans[i].second;
        
        



        

        //if (canMove) { // 僅在可以移動時檢查按鍵
        //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        //        maze.player_move(player_x, player_y, player_x - 1, player_y); // 上
        //        canMove = false;
        //        moveClock.restart(); // 重置計時器
        //    }
        //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //        maze.player_move(player_x, player_y, player_x + 1, player_y); // 下
        //        canMove = false;
        //        moveClock.restart(); // 重置計時器
        //    }
        //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //        maze.player_move(player_x, player_y, player_x, player_y - 1); // 左
        //        canMove = false;
        //        moveClock.restart(); // 重置計時器
        //    }
        //    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //        maze.player_move(player_x, player_y, player_x, player_y + 1); // 右
        //        canMove = false;
        //        moveClock.restart(); // 重置計時器
        //    }
        //}

         //檢查是否超過移動延遲
        // moveClock.getElapsedTime() 會自動返回所經的時間
        //.asSeconds() 將經過的時間轉換為以秒為單位的浮點數
        //if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
        //    canMove = true; // 重新允許移動
        //}

        //window.clear();
        //maze.display(window, player_x, player_y); // 繪製迷宮並顯示玩家位置
        //window.display();
        
    }
    
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Execution time: " << duration.count() << " microseconds" << endl;
 
    std::cout << "\nAfter memory usage tracking:" << endl;

    // 再次獲取內存資訊
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        std::cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB" << endl;
        std::cout << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
        std::cout << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB" << endl;
        std::cout << "Peak Pagefile Usage: " << pmc.PeakPagefileUsage / 1024 << " KB" << endl;
    }
    else {
        cerr << "Error in GetProcessMemoryInfo()" << endl;
    }
    return 0;
}