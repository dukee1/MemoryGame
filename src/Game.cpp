#include "Game.h"
#include <iostream>
#include <string>

Game::Game(int rows, int cols)
    : window(sf::VideoMode(800, 600), "MemoryGame", sf::Style::Titlebar | sf::Style::Close),
      board(rows, cols),
      firstSelected(nullptr),
      secondSelected(nullptr),
      waitingForMismatchHide(false),
      turns(0),
      pairsFound(0),
      totalPairs((rows * cols) / 2) {

    //Load bundled font first, then fall back to system fonts
    if (!font.loadFromFile("assets/DejaVuSans.ttf") &&
        !font.loadFromFile(std::string(ASSETS_DIR) + "/DejaVuSans.ttf") &&
        !font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf") &&
        !font.loadFromFile("C:/Windows/Fonts/arial.ttf") &&
        !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Warning: Could not load any font!\n";
    }

    //Position cards in window
    board.setupCardPositions(200.0f, 100.0f, 80.0f, 15.0f);
}

void Game::handleCardClick(Card* clickedCard) {
    if (!clickedCard || clickedCard->isMatched() || clickedCard->isRevealed() || waitingForMismatchHide) {
        return;
    }

    clickedCard->flip();

    if (!firstSelected) {
        firstSelected = clickedCard;
    } else if (!secondSelected && clickedCard != firstSelected) {
        secondSelected = clickedCard;
        turns++;

        if (firstSelected->getSymbol() == secondSelected->getSymbol()) {
            firstSelected->setMatched(true);
            secondSelected->setMatched(true);
            firstSelected = nullptr;
            secondSelected = nullptr;
            pairsFound++;
        } else {
            waitingForMismatchHide = true;
            mismatchClock.restart();
        }
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handleCardClick(board.getCardAtPosition(mousePos));
        }
    }
}

void Game::update() {
    //If cards didn't match, wait 1 second before flipping back
    if (waitingForMismatchHide && mismatchClock.getElapsedTime().asSeconds() >= 1.0f) {
        if (firstSelected && secondSelected) {
            firstSelected->hide();
            secondSelected->hide();
        }
        firstSelected = nullptr;
        secondSelected = nullptr;
        waitingForMismatchHide = false;
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 45)); //Dark background

    //Render Board
    board.render(window, font);

    //Render Turn Counter
    sf::Text hudText;
    hudText.setFont(font);
    hudText.setString("Turns: " + std::to_string(turns));
    hudText.setCharacterSize(24);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition(20.0f, 20.0f);
    window.draw(hudText);

    //Render WON Message
    if (pairsFound == totalPairs) {
        sf::Text winText;
        winText.setFont(font);
        winText.setString("YOU WON IN " + std::to_string(turns) + " TURNS!");
        winText.setCharacterSize(32);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(220.0f, 520.0f);
        window.draw(winText);
    }

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}