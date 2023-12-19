#include <iostream>
#include <vector>
#include <algorithm>
#include "Game_Class/battleship.h"

const std::pair <int, int> EMPTY_CELL = {-1, -1};

int main () {
    sf::RenderWindow window (sf::VideoMode(BOARD_SIZE * CELL_SIZE * 2, BOARD_SIZE * CELL_SIZE + 100), "Battleship Game");
    BattleShipGame game;

    while (window.isOpen()) {
        while (game.getGameStatus() == GameStatus::Arranging) {
            std::vector <int> ships_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
            std::vector <std::pair <int, int>> ship;
            for (int i = 0; i < ships_sizes.size(); ++i) {
                int size = ships_sizes[i];
                for (int iter = 0; iter < size; ++iter) {
                    auto cell = game.handleInput(window);
                    while (cell == EMPTY_CELL) {
                        cell = game.handleInput(window);
                        game.render(window);
                    }
                    
                    if (cell.first < 0 && cell.second < 0) {
                        cell.first = -cell.first;
                        cell.second = -cell.second;
                        auto iter = find(ship.begin(), ship.end(), cell);
                        ship.erase(iter, iter + 1);
                    }
                    else {
                        ship.push_back(cell);
                    }
                }
    
                sort(ship.begin(), ship.end());
                bool ok_hor = 1, ok_ver = 1;
                for (int i = 0; i + 1 < ship.size(); ++i) {
                    auto [x, y] = ship[i];
                    auto [nx, ny] = ship[i + 1]; 
                    ok_hor &= (x + 1 == nx && y == ny);
                    ok_ver &= (x == nx && y + 1 == ny);
                }

                ok_hor &= (ship.size() > 0);
                ok_ver &= (ship.size() > 0);

                if (ok_hor || ok_ver) {
                    std::cout << "Okay ship!" << std::endl;
                    ship.clear();
                }
                else {
                    --i;
                    std::cout << "Wrong!" << std::endl;
                }
            }
            game.setGameStatus(GameStatus::Playing);
        }
        game.handleInput(window);
        game.update();
        game.render(window);
    }
    return 0;
}
