#include "deck.h"
#include "qdebug.h"
#include <algorithm>
#include <random>
#include <array>

Deck::Deck()
{
    createDeck();
}

void Deck::createDeck() {
    // clear deck;
    deck.clear();

    for (int value = 2; value <= 14; ++value) {
        for (int suit = 1; suit <= 4; ++suit) { // 1 = clubs, 2 = diamonds, 3 = hearts, 4 = spades
            Card card(value, suit);
            deck.push_back(card);
        }
    }

    std::random_device rd;
    std::mt19937 engine(rd());
    std::shuffle(deck.begin(), deck.end(), engine);

    qDebug()<<"Deck created and shuffled";
}

void Deck::exchangeCard(Card card){
    int randomIndex = std::rand() % (deck.size() + 1);
    deck.insert(deck.begin()+randomIndex, card);
}

Card Deck::dealCard(){
    Card dealCard = deck.back();
    deck.pop_back();
    return dealCard;
}
