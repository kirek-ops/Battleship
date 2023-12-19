#include "game.h"

Game::Game () {
    this->status = GameStatus::Arranging;
}

void Game::set (const GameStatus &_status) {
    this->status = _status;
}

GameStatus Game::get () {
    return this->status;
}