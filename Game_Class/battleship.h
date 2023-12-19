#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "cell.h"

const int BOARD_SIZE = 10;
const int CELL_SIZE = 40;

class BattleShipGame {
    private:
        std::vector <std::vector <Cell>> player;
        std::vector <std::vector <Cell>> computer;
        bool isGameOver (const std::vector <std::vector <Cell>> &board);

    public:
        BattleShipGame ();
        void handleInput (sf::RenderWindow &window);
        void update ();
        void render (sf::RenderWindow &window);
};