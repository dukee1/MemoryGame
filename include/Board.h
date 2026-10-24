#ifndef MEMORYGAME_BOARD_H
#define MEMORYGAME_BOARD_H

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
    void setupCardPositions(float startX, float startY, float cardSize, float padding);

    void render(sf::RenderWindow& window, const sf::Font& font);
    Card* getCardAtPosition(sf::Vector2f mousePos);

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif //MEMORYGAME_BOARD_H