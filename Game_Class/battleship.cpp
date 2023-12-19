#include "battleship.h"
#include <assert.h>
#include <iostream>

BattleShipGame::BattleShipGame () {
    player = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
    computer = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
}

void BattleShipGame::handleInput (sf::RenderWindow &window) {
    sf::Event event;
    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x / CELL_SIZE;
                int mouseY = event.mouseButton.y / CELL_SIZE;

                player[mouseX][mouseY].set(CellStatus::Hit);
            }
        }
    }
}

void BattleShipGame::render (sf::RenderWindow &window) {
    window.clear(sf::Color::White);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            sf::RectangleShape cellRect (sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cellRect.setPosition(i * CELL_SIZE, j * CELL_SIZE);

            switch (player[i][j].get()) {
                case CellStatus::Empty:
                    cellRect.setFillColor(sf::Color::Blue);
                    break;
                case CellStatus::Hit:
                    cellRect.setFillColor(sf::Color::Red);
                    break;
                case CellStatus::Miss:
                    cellRect.setFillColor(sf::Color::Green);
                    break;
                case CellStatus::Ship:
                    cellRect.setFillColor(sf::Color::Red);
                    break;
                default:
                    assert(0);
            }
            window.draw(cellRect);
        }
    }

    window.display();
}

void BattleShipGame::update () {
    
}