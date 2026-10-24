#include "Board.h"
#include <algorithm>
#include <random>
#include <chrono>

Board::Board(int r, int c) : rows(r), cols(c) {
    initialize();
}

void Board::initialize() {
    grid.assign(rows, std::vector<Card>(cols));
    int totalCards = rows * cols;
    int numPairs = totalCards / 2;

    std::vector<char> symbols;
    for (int i = 0; i < numPairs; ++i) {
        char sym = static_cast<char>('A' + i);
        symbols.push_back(sym);
        symbols.push_back(sym);
    }

    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = Card(symbols[index++]);
        }
    }

    shuffle();
}

void Board::shuffle() {
    std::vector<Card> flatBoard;
    for (const auto& row : grid) {
        for (const auto& card : row) {
            flatBoard.push_back(card);
        }
    }

    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(flatBoard.begin(), flatBoard.end(), std::default_random_engine(seed));

    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = flatBoard[index++];
        }
    }
}

void Board::setupCardPositions(float startX, float startY, float cardSize, float padding) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float x = startX + c * (cardSize + padding);
            float y = startY + r * (cardSize + padding);
            grid[r][c].setSize(cardSize, cardSize);
            grid[r][c].setPosition(x, y);
        }
    }
}

void Board::render(sf::RenderWindow& window, const sf::Font& font) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c].render(window, font);
        }
    }
}

Card* Board::getCardAtPosition(sf::Vector2f mousePos) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].contains(mousePos)) {
                return &grid[r][c];
            }
        }
    }
    return nullptr;
}