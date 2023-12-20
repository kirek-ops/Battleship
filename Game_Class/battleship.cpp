#include "battleship.h"
#include <assert.h>
#include <iostream>
#include <random>
#include <ctime>

const bool DEBUG_MODE = 1;
int dx[8] = {1, 1, -1, -1, 0, 0, 1, -1};
int dy[8] = {1, -1, 1, -1, 1, -1, 0, 0};

bool valid (int x, int y) {
    return x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE;
}

BattleShipGame::BattleShipGame () {
    this->player = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
    this->computer = std::vector <std::vector <Cell>> (BOARD_SIZE, std::vector <Cell> (BOARD_SIZE));
    this->gameStatus = GameStatus();
}

std::tuple <int, int, bool> BattleShipGame::handleInput (sf::RenderWindow &window) {
    sf::Event event;
    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x / CELL_SIZE;
                int mouseY = event.mouseButton.y / CELL_SIZE;
                
                if (mouseX >= BOARD_SIZE && mouseY < BOARD_SIZE) {
                    Cell cell = this->computer[mouseX - BOARD_SIZE][mouseY];
                    if (cell.get() == CellStatus::Ship) {
                        this->computer[mouseX - BOARD_SIZE][mouseY].set(CellStatus::Hit);
                        return {mouseX - BOARD_SIZE, mouseY, 1};
                    }
                    if (cell.get() == CellStatus::Empty) {
                        this->computer[mouseX - BOARD_SIZE][mouseY].set(CellStatus::Miss);
                        return {mouseX - BOARD_SIZE, mouseY, 0};
                    }
                }
            }
        }
    }
    return {-1, -1, 1};
}

void BattleShipGame::render (sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

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
                    cellRect.setFillColor(sf::Color::Cyan);
                    break;
                case CellStatus::Hit:
                    cellRect.setFillColor(sf::Color::Red);
                    break;
                case CellStatus::Miss:
                    cellRect.setFillColor(sf::Color::Green);
                    break;
                case CellStatus::Ship:
                    cellRect.setFillColor(sf::Color (128, 128, 128));
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
                    cellRect.setFillColor(sf::Color::Cyan);
                    break;
                case CellStatus::Hit:
                    cellRect.setFillColor(sf::Color::Red);
                    break;
                case CellStatus::Miss:
                    cellRect.setFillColor(sf::Color::Green);
                    break;
                case CellStatus::Ship:
                    if (DEBUG_MODE) {
                        cellRect.setFillColor(sf::Color (128, 128, 128));
                    }
                    else {
                        cellRect.setFillColor(sf::Color::Cyan);
                    }
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
        separatorBoarder.setFillColor(sf::Color::Black);

        window.draw(separatorBoarder);
    }

    // Labels on the bottom
    if (getGameStatus() == GameStatus::Ended) {
        sf::Font font;
        font.loadFromFile("Game_Class/Arial.ttf");
        sf::Text label;
        if (this->winner == 0) {
            std::string lab = "Winner is COMPUTER! AHAHAH LOSSSER";
            label = sf::Text(lab, font, 24);
            label.setPosition(BOARD_SIZE * CELL_SIZE - 100, BOARD_SIZE * CELL_SIZE + 10); 
        }
        else {
            std::string lab = "Winner is YOU!!";
            label = sf::Text(lab, font, 24);
            label.setPosition(BOARD_SIZE * CELL_SIZE - 50, BOARD_SIZE * CELL_SIZE + 10); 
        }
        label.setFillColor(sf::Color::White);
        window.draw(label);
    }

    window.display();
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

void BattleShipGame::update () {
    if (isGameOver(this->computer)) {
        setGameStatus(GameStatus::Ended); 
        this->winner = 1;
    }
    if (isGameOver(this->player)) {
        setGameStatus(GameStatus::Ended); 
        this->winner = 0;
    }

    for (const auto &i : this->playerShips) {
        bool ok = 1;
        for (const auto &[x, y] : i) {
            ok &= (this->player[x][y].get() == CellStatus::Hit);
        }
        if (ok) {
            for (const auto &[x, y] : i) {
                for (int j = 0; j < 8; ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    if (valid(nx, ny) && this->player[nx][ny].get() != CellStatus::Hit) {
                        this->player[nx][ny].set(CellStatus::Miss);
                    }
                }
            }
            
        }
    }
    for (const auto &i : this->computerShips) {
        bool ok = 1;
        for (const auto &[x, y] : i) {
            ok &= (this->computer[x][y].get() == CellStatus::Hit);
        }
        if (ok) {
            for (const auto &[x, y] : i) {
                for (int j = 0; j < 8; ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    if (valid(nx, ny) && this->computer[nx][ny].get() != CellStatus::Hit) {
                        this->computer[nx][ny].set(CellStatus::Miss);
                    }
                }
            }
            
        }
    }
}

GameStatus BattleShipGame::getGameStatus () {
    return this->gameStatus;
}

void BattleShipGame::setGameStatus (const GameStatus &_status) {
    this->gameStatus = _status;
}

void BattleShipGame::setPlayersShips (const std::vector <std::vector <std::pair <int, int>>> &ships) {
    this->playerShips = ships;
    
}

int count_around (int x, int y, const std::vector <std::vector <Cell>> &board) {
    int cnt = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (valid(nx, ny)) {
            cnt += (board[nx][ny].get() == CellStatus::Ship);
        }
    }
    return cnt;
}

void BattleShipGame::generateShips (const std::string &who) {
    std::vector <int> ships_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    std::vector <std::vector <std::pair <int, int>>> ships;
    std::mt19937 rng (time(0));

    auto board = (who == "player" ? this->player : this->computer);

    for (const int &size : ships_sizes) {
        std::vector <std::pair <int, int>> ship;
        while (true) {
            int x = rng() % BOARD_SIZE;
            int y = rng() % BOARD_SIZE;
            if (x + size - 1 < BOARD_SIZE) {
                bool ok = 0;
                ok |= (count_around(x, y, board) != 0);
                for (int i = 1; i < size; ++i) {
                    ok |= (count_around(x + i, y, board) != 0);
                } 
                if (!ok) {
                    for (int j = 0; j < size; ++j) {
                        ship.push_back({x + j, y});
                        board[x + j][y].set(CellStatus::Ship);
                    }
                    ships.push_back(ship);
                    break;
                }
            }
            else if (y + size - 1 < BOARD_SIZE) {
                bool ok = 0;
                ok |= (count_around(x, y, board) != 0);
                for (int i = 1; i < size; ++i) {
                    ok |= (count_around(x, y + i, board) != 0);
                } 
                if (!ok) {
                    for (int j = 0; j < size; ++j) {
                        ship.push_back({x, y + j});
                        board[x][y + j].set(CellStatus::Ship);
                    }
                    ships.push_back(ship);
                    break;
                }
            }
        }
    }

    if (who == "player") {
        player = board;
        playerShips = ships;
    }
    else {
        computer = board;
        computerShips = ships;
    }
}

bool BattleShipGame::stupidComputerMove () {
    std::mt19937 rng (time(0));
    while (true) {
        int x = rng() % BOARD_SIZE;
        int y = rng() % BOARD_SIZE;
        if (this->player[x][y].get() == CellStatus::Miss ||
            this->player[x][y].get() == CellStatus::Hit) {
            continue;
        }
        if (this->player[x][y].get() == CellStatus::Ship) {
            this->player[x][y].set(CellStatus::Hit);
            return 1;
        }   
        if (this->player[x][y].get() == CellStatus::Empty) {
            this->player[x][y].set(CellStatus::Miss);
            return 0;
        }
    }
}