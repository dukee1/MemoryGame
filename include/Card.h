#ifndef MEMORYGAME_CARD_H
#define MEMORYGAME_CARD_H

#include <SFML/Graphics.hpp>

class Card {
private:
    char symbol;
    bool revealed;
    bool matched;
    sf::RectangleShape shape;

public:
    explicit Card(char sym = ' ');

    char getSymbol() const;
    bool isRevealed() const;
    bool isMatched() const;

    void flip();
    void hide();
    void setMatched(bool state);

    void setPosition(float x, float y);
    void setSize(float width, float height);
    bool contains(sf::Vector2f point) const;
    void render(sf::RenderWindow& window, const sf::Font& font) const;
};

#endif //MEMORYGAME_CARD_H