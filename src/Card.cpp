#include "Card.h"

//Initializing card symbol and state
Card::Card(char sym) : symbol(sym), revealed(false), matched(false) {}

char Card::getSymbol() const {
    return symbol;
}

bool Card::isRevealed() const {
    return revealed;
}

bool Card::isMatched() const {
    return matched;
}

void Card::flip() {
    revealed = true;
}

void Card::hide() {
    revealed = false;
}

void Card::setMatched(bool state) {
    matched = state;
}

//Returns symbol if revealed or matched, otherwise returns *
char Card::getDisplayChar() const {
    if (revealed || matched) {
        return symbol;
    }
    return '*';
}