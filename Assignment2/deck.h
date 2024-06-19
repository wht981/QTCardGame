#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>

class Deck
{
private:
    std::vector<Card> deck;
public:
    Deck();
    void createDeck();
    void exchangeCard(Card card);
    Card dealCard();
    int getCardsNum(){return deck.size();};
};

#endif // DECK_H
