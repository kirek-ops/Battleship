#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

const int BOARD_SIZE = 10;
const int CELL_SIZE = 40;

enum class CellStatus {
    Empty, 
    Ship,
    Hit,
    Miss
};

struct Cell {
    CellStatus status;
};

class BattleShipGame {
    private:
        std::vector <std::vector <Cell>> player;
        std::vector <std::vector <Cell>> computer;

    public:
        BattleShipGame ();

};