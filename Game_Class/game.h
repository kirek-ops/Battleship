enum class GameStatus {
    Arranging,
    Playing,
    Ended
};

class Game {
    private:
        GameStatus status;
    public:
        Game ();
        void set (const GameStatus &_status);
        GameStatus get ();
};