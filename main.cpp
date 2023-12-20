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

    game.generateShips("player");
    game.generateShips("computer");
    game.setGameStatus(GameStatus::Playing);

    while (window.isOpen()) {
        game.handleInput(window);
        game.update();
        game.render(window);
    }
    return 0;
}
