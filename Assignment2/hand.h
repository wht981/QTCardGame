#ifndef HAND_H
#define HAND_H

#include "HandBest.h"
#include "deck.h"
#include <vector>
#include <QList>


class Hand
{
private:
    std::vector<Card> handCard;

public:
    Hand();
    void dealHand(Deck& deck);
    void sortValue();
    std::vector<std::pair<int, int>> sortGroup();
    struct handBest getBest();
    void swapCard(const QVector<int>& cardPos, Deck& deck);
    void swapCard(int pos, Deck &deck); //only swap one card;
    std::vector<Card> getHandCard();
    QString getHandName();
};

#endif // HAND_H

