#ifndef PEXESO_GAME_H
#define PEXESO_GAME_H

#include "Board.h"

class Game {
private:
    Board board;
    int turns;
    int pairsFound;
    int totalPairs;

    void clearScreen() const;
    void pause(int seconds) const;
    void processTurn();

public:
    Game(int rows, int cols);

    void run();
};

#endif //PEXESO_GAME_H