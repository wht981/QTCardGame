#ifndef CARD_H
#define CARD_H
#include "QString"

class Card
{
private:
    int suit;
    int value;

public:
    Card();
    Card(int v, int s);
    int getValue() const;
    int getSuit();
    QString getName();
};

#endif // CARD_H
