#include "card.h"

Card::Card(){}
Card::Card(int v, int s)
{
    this->value = v;
    this->suit = s;
}
int Card::getValue() const  {
    return value;
}
int Card::getSuit(){
    return suit;
}

QString Card::getName(){
    QString suitName;
    QString valueName;

    switch(suit) {
    case 1:
        suitName = "clubs";
        break;
    case 2:
        suitName = "diamonds";
        break;
    case 3:
        suitName = "hearts";
        break;
    case 4:
        suitName = "spades";
        break;
    default:
        suitName = "unknown";
        break;
    }

    if (value >= 2 && value <= 10) {
        valueName = QString::number(value);
    } else {
        switch(value) {
        case 11:
            valueName = "jack";
            break;
        case 12:
            valueName = "queen";
            break;
        case 13:
            valueName = "king";
            break;
        case 14:
            valueName = "ace";
            break;
        default:
            valueName = "unknown";
            break;
        }
    }

    return valueName + "_of_" + suitName;
}
