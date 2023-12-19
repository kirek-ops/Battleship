#include "battleship.h"
#include <assert.h>
#include <iostream>

BattleShipGame::BattleShipGame () {
    this->player = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
    this->computer = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
    this->gameStatus = GameStatus();
}

std::pair <int, int> BattleShipGame::handleInput (sf::RenderWindow &window) {
    sf::Event event;
    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x / CELL_SIZE;
                int mouseY = event.mouseButton.y / CELL_SIZE;

                if (this->gameStatus == GameStatus::Arranging) {
                    if (mouseX < BOARD_SIZE && mouseY < BOARD_SIZE) {
                        this->player[mouseX][mouseY].set(CellStatus::Ship);
                        return {mouseX, mouseY};
                    }
                }
            }
        }
    }
    return {-1, -1};
}

void BattleShipGame::render (sf::RenderWindow &window) {
    window.clear(sf::Color::White);

    // Draw Player's board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            sf::RectangleShape cellRect (sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cellRect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            
            sf::RectangleShape boarderRect (sf::Vector2f(CELL_SIZE, CELL_SIZE));
            boarderRect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            boarderRect.setFillColor(sf::Color::Transparent);
            boarderRect.setOutlineColor(sf::Color::Black);
            boarderRect.setOutlineThickness(4);

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
            window.draw(boarderRect);
        }
    }

    // Draw Computer's board
    for (int i = BOARD_SIZE; i < BOARD_SIZE * 2; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            sf::RectangleShape cellRect (sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cellRect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            
            sf::RectangleShape boarderRect (sf::Vector2f(CELL_SIZE, CELL_SIZE));
            boarderRect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            boarderRect.setFillColor(sf::Color::Transparent);
            boarderRect.setOutlineColor(sf::Color::Black);
            boarderRect.setOutlineThickness(4);

            switch (computer[i - BOARD_SIZE][j].get()) {
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
            window.draw(boarderRect);
        }
    }

    // Draw separator
    for (int i = BOARD_SIZE - 1, j = 0; j < BOARD_SIZE; ++j) {
        sf::RectangleShape separatorBoarder (sf::Vector2f(8, CELL_SIZE));
        separatorBoarder.setPosition(i * CELL_SIZE + CELL_SIZE - 4, j * CELL_SIZE);
        separatorBoarder.setFillColor(sf::Color::White);

        window.draw(separatorBoarder);
    }

    window.display();
}

void BattleShipGame::update () {
    
}

bool BattleShipGame::isGameOver (const std::vector <std::vector <Cell>> &board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j].get() == CellStatus::Ship) {
                return false;
            }
        }
    }
    return true;
}

GameStatus BattleShipGame::getGameStatus () {
    return this->gameStatus;
}

void BattleShipGame::setGameStatus (const GameStatus &_status) {
    this->gameStatus = _status;
}
