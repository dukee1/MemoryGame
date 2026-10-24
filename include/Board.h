#ifndef PEXESO_BOARD_H
#define PEXESO_BOARD_H

#include "Card.h"
#include <vector>

class Board {
private:
    int rows;
    int cols;
    std::vector<std::vector<Card>> grid;

public:
    Board(int r, int c);

    void initialize();
    void shuffle();
    void display() const;

    bool isValidCoordinate(int r, int c) const;
    Card& getCard(int r, int c);
    const Card& getCard(int r, int c) const;

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif //PEXESO_BOARD_H