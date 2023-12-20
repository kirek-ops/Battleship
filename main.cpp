#include <iostream>
#include <vector>
#include <algorithm>
#include "Game_Class/battleship.h"

const std::tuple <int, int, bool> EMPTY_CELL = {-1, -1, 1};

int main () {
    sf::RenderWindow window (sf::VideoMode(BOARD_SIZE * CELL_SIZE * 2, BOARD_SIZE * CELL_SIZE + 100), "Battleship Game");
    BattleShipGame game;

    game.generateShips("player");
    game.generateShips("computer");
    game.setGameStatus(GameStatus::Playing);
    game.render(window);

    while (window.isOpen()) {
        auto input = game.handleInput(window);
        while (true) {
            while (input == EMPTY_CELL) {
                input = game.handleInput(window);
                game.update();
                game.render(window);
            }
            if (std::get<2>(input) != 1) break;
            else input = EMPTY_CELL;
        }
        while (game.stupidComputerMove()) {
            game.update();
            game.render(window);
        }
        game.update();
        game.render(window);
        if (game.getGameStatus() == GameStatus::Ended) {
            // TODO: make a game restart
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    exit(0);
                }
            }
        }
    }
    return 0;
}
