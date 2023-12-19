#include "cell.h"

Cell::Cell () {
    this->status = CellStatus::Empty;
}

void Cell::set (const CellStatus &_status) {
    this->status = _status;
}

CellStatus Cell::get () const {
    return this->status;
}