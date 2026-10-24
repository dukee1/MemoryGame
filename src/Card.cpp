#include "Card.h"

Card::Card(char sym) : symbol(sym), revealed(false), matched(false) {
    shape.setFillColor(sf::Color(70, 130, 180)); // Steel Blue for hidden cards
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.0f);
}

char Card::getSymbol() const { return symbol; }
bool Card::isRevealed() const { return revealed; }
bool Card::isMatched() const { return matched; }

void Card::flip() {
    revealed = true;
    shape.setFillColor(sf::Color(220, 220, 220)); // Light Gray when open
}

void Card::hide() {
    revealed = false;
    shape.setFillColor(sf::Color(70, 130, 180));
}

void Card::setMatched(bool state) {
    matched = state;
    if (matched) {
        shape.setFillColor(sf::Color(60, 179, 113)); // Medium Sea Green when matched
    }
}

void Card::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Card::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
}

bool Card::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Card::render(sf::RenderWindow& window, const sf::Font& font) const {
    window.draw(shape);

    if (revealed || matched) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::string(1, symbol));
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);

        //Center text on the card
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        sf::Vector2f cardPos = shape.getPosition();
        sf::Vector2f cardSize = shape.getSize();
        text.setPosition(cardPos.x + cardSize.x / 2.0f, cardPos.y + cardSize.y / 2.0f);

        window.draw(text);
    }
}