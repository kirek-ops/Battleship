enum class CellStatus {
    Empty, 
    Ship,
    Hit,
    Miss
}; 

class Cell {
    private:
        CellStatus status;
    public:
        Cell ();
        void set (const CellStatus &_status);
        CellStatus get () const;
};