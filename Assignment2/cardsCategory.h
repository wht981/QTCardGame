#ifndef CARDSCATEGORY_H
#define CARDSCATEGORY_H

enum class cardsCategory{
    high, // Highest Card, all cards are different for both players
    pair, // One Pair, a single matched pair of the same value
    twop, // Two Pair, two separate matched pairs of different values
    trio, // Three of A Kind, three cards with the same value
    strt, // Straight, all cards are in numerical order, regardless suit
    flsh, // Flush, all cards are the same suit
    full, // Full houses, three of one the same value and two of another
    four, // Four of A king, four cards with same value
    stfl, // Straight flush, flush and straight at the same time
};

#endif // CARDSCATEGORY_H
