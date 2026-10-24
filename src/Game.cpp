#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <cstdlib>

Game::Game(int rows, int cols)
    : board(rows, cols), turns(0), pairsFound(0), totalPairs((rows * cols) / 2) {}

void Game::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Game::pause(int seconds) const {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

//Turn input and card matching logic
void Game::processTurn() {
    int r1, c1, r2, c2;

    while (true) {
        board.display();
        std::cout << "Enter row and column for FIRST card (e.g., 1 2): ";
        if (!(std::cin >> r1 >> c1)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter numbers.\n";
            continue;
        }

        --r1; --c1;

        if (!board.isValidCoordinate(r1, c1) || board.getCard(r1, c1).isMatched() || board.getCard(r1, c1).isRevealed()) {
            std::cout << "Invalid card selection. Try again.\n";
            continue;
        }
        break;
    }

    board.getCard(r1, c1).flip();
    board.display();

    while (true) {
        std::cout << "Enter row and column for SECOND card: ";
        if (!(std::cin >> r2 >> c2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter numbers.\n";
            continue;
        }

        --r2; --c2;

        if (!board.isValidCoordinate(r2, c2) || (r1 == r2 && c1 == c2) ||
            board.getCard(r2, c2).isMatched() || board.getCard(r2, c2).isRevealed()) {
            std::cout << "Invalid card selection. Try again.\n";
            continue;
        }
        break;
    }

    board.getCard(r2, c2).flip();
    board.display();
    turns++;

    //Check if matched
    if (board.getCard(r1, c1).getSymbol() == board.getCard(r2, c2).getSymbol()) {
        std::cout << "Match found!\n";
        board.getCard(r1, c1).setMatched(true);
        board.getCard(r2, c2).setMatched(true);
        pairsFound++;
        pause(1);
    } else {
        std::cout << "No match. Hiding cards...\n";
        pause(2);
        board.getCard(r1, c1).hide();
        board.getCard(r2, c2).hide();
    }
    clearScreen();
}

//Main interactive game loop
void Game::run() {
    int choice = 0;
    while (choice != 2) {
        clearScreen();
        std::cout << "PEXESO GAME\n";
        std::cout << "1. Play Game\n";
        std::cout << "2. Exit\n";
        std::cout << "Select an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            turns = 0;
            pairsFound = 0;
            board.initialize();
            clearScreen();

            while (pairsFound < totalPairs) {
                processTurn();
            }

            clearScreen();
            std::cout << "Congratulations! You won in " << turns << " turns.\n";
            std::cout << "Press Enter to return to menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}