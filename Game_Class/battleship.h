#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "cell.h"
#include "game.h"

const int BOARD_SIZE = 10;
const int CELL_SIZE = 40;

class BattleShipGame {
    private:
        GameStatus gameStatus;
        std::vector <std::vector <Cell>> player;
        std::vector <std::vector <Cell>> computer;
    
        bool isGameOver (const std::vector <std::vector <Cell>> &board);

        int winner = -1;
        
    public:
        std::vector <std::vector <std::pair <int, int>>> playerShips;
        std::vector <std::vector <std::pair <int, int>>> computerShips;

        BattleShipGame ();
        std::tuple <int, int, bool> handleInput (sf::RenderWindow &window);
        void update ();
        bool stupidComputerMove ();
        void render (sf::RenderWindow &window);
        GameStatus getGameStatus ();
        void setGameStatus (const GameStatus &_status);
        void setPlayersShips (const std::vector <std::vector <std::pair <int, int>>> &ships);
        void generateShips (const std::string &who);
};