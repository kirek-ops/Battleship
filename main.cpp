#include <iostream>
#include <vector>
#include "Game_Class/battleship.h"

int main () {
    sf::RenderWindow window (sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "Battleship Game");
    BattleShipGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.update();
        game.render(window);
    }
    return 0;
}
