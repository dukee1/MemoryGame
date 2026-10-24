#ifndef PEXESO_CARD_H
#define PEXESO_CARD_H

class Card {
private:
    char symbol;
    bool revealed;
    bool matched;

public:
    explicit Card(char sym = ' ');

    char getSymbol() const;
    bool isRevealed() const;
    bool isMatched() const;

    void flip();
    void hide();
    void setMatched(bool state);

    char getDisplayChar() const;
};

#endif //PEXESO_CARD_H