#ifndef MEMORYGAME_GAME_H
#define MEMORYGAME_GAME_H

#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    Board board;

    Card* firstSelected;
    Card* secondSelected;
    bool waitingForMismatchHide;
    sf::Clock mismatchClock;

    int turns;
    int pairsFound;
    int totalPairs;

    void processEvents();
    void update();
    void render();
    void handleCardClick(Card* clickedCard);

public:
    Game(int rows, int cols);
    void run();
};

#endif //MEMORYGAME_GAME_H