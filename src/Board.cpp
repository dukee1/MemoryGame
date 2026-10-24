#include "Board.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

Board::Board(int r, int c) : rows(r), cols(c) {
    initialize();
}

//Initialize board grid
void Board::initialize() {
    grid.assign(rows, std::vector<Card>(cols));
    int totalCards = rows * cols;
    int numPairs = totalCards / 2;

    std::vector<char> symbols;
    for (int i = 0; i < numPairs; ++i) {
        char sym = static_cast<char>('A' + i);
        symbols.push_back(sym);
        symbols.push_back(sym); //Add pair
    }

    //Fill grid sequentially with generated symbols
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = Card(symbols[index++]);
        }
    }

    shuffle();
}

//Randomly shuffle cards on the board
void Board::shuffle() {
    std::vector<Card> flatBoard;
    for (const auto& row : grid) {
        for (const auto& card : row) {
            flatBoard.push_back(card);
        }
    }

    //Seed random generator with current time
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(flatBoard.begin(), flatBoard.end(), std::default_random_engine(seed));

    //Repopulate grid with shuffled cards
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = flatBoard[index++];
        }
    }
}

//Render formatted board to standard output
void Board::display() const {
    std::cout << "\n   ";
    for (int c = 0; c < cols; ++c) {
        std::cout << c + 1 << " ";
    }
    std::cout << "\n  +" << std::string(cols * 2, '-') << "\n";

    for (int r = 0; r < rows; ++r) {
        std::cout << r + 1 << " |";
        for (int c = 0; c < cols; ++c) {
            std::cout << grid[r][c].getDisplayChar() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool Board::isValidCoordinate(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

Card& Board::getCard(int r, int c) {
    return grid[r][c];
}

const Card& Board::getCard(int r, int c) const {
    return grid[r][c];
}