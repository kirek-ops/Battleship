#include <iostream>
#include <vector>
#include <algorithm>
#include "Game_Class/battleship.h"

const std::pair <int, int> EMPTY_CELL = {-1, -1};

bool check_ship (std::vector <std::pair <int, int>> ship) {
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

    return ok_hor || ok_ver;
}

int main () {
    sf::RenderWindow window (sf::VideoMode(BOARD_SIZE * CELL_SIZE * 2, BOARD_SIZE * CELL_SIZE + 100), "Battleship Game");
    BattleShipGame game;

    while (window.isOpen()) {
        while (game.getGameStatus() == GameStatus::Arranging) {
            std::vector <int> ships_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
            std::vector <std::vector <std::pair <int, int>>> ships;
            for (int i = 0; i < ships_sizes.size(); ++i) {
                int size = ships_sizes[i];
                std::vector <std::pair <int, int>> ship;
                while (true) {
                    auto cell = game.handleInput(window);
                    while (cell == EMPTY_CELL) {
                        cell = game.handleInput(window);
                        game.render(window);
                    }
                    std::cout << cell.first << " " << cell.second << std::endl;
                    if (cell.first >= 0 && cell.second >= 0) {
                        ship.push_back(cell);
                    }  
                    else {
                        cell.first = -cell.first;
                        cell.second = -cell.second;
                        auto it = find(ship.begin(), ship.end(), cell);
                        ship.erase(it, it + 1);
                    }

                    if (ship.size() == size) {
                        if (check_ship(ship)) {
                            std::cout << "okay!" << std::endl;
                            ships.push_back(ship);
                            break;
                        }
                    }
                }
            }
            game.setPlayersShips(ships);
            game.generateComputerShips();
            game.setGameStatus(GameStatus::Playing);
        }
        game.handleInput(window);
        game.update();
        game.render(window);
    }
    return 0;
}
