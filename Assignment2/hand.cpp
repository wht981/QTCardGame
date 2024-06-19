#include "hand.h"
#include "qdebug.h"
#include <algorithm>

Hand::Hand(): handCard(5){

}

void Hand::dealHand(Deck& deck){
    for(int i = 0; i < 5; i++){
        handCard[i] = deck.dealCard();
        qDebug() << handCard[i].getName();
    }

    sortGroup();
    qDebug() << "AfterSort";
    for(int i = 0; i < 5; i++){
        qDebug() << handCard[i].getName();
    }
}

void Hand::sortValue(){
    std::sort(handCard.begin(), handCard.end(), [](const Card& a, const Card& b) {
        return a.getValue() < b.getValue();
    });
    // if the sort result is {2,3,4,5,A}, rotate the A to the first
    if(handCard[0].getValue() == 2 &&
       handCard[1].getValue() == 3 &&
       handCard[2].getValue() == 4 &&
       handCard[3].getValue() == 5 &&
       handCard[4].getValue() == 14){
       std::rotate(handCard.rbegin(), handCard.rbegin() + 1, handCard.rend());
    }
}

std::vector<std::pair<int, int> > Hand::sortGroup() {
    sortValue();
    // logic of count the times of repeating, eg: {6, 6, 7, 7, 7} -> {{6,2}, {7,3}}; {6, 7, 7, 8, 8} ->{{6，1}，{7，2}，{8，2}}
    // the first value of the pair is the value, the second is the repeating times
    std::vector<std::pair<int, int>> repeatCount;
    repeatCount.push_back(std::make_pair(handCard[0].getValue(), 1));
    for (int i = 1; i < handCard.size(); i++) {
       if (handCard[i].getValue() == handCard[i - 1].getValue()) {
           repeatCount.back().second++;
       } else {
           repeatCount.push_back(std::make_pair(handCard[i].getValue(), 1));
       }
    }
    // possible combination {1,2,1,1}/{1,1,2,1}/{1,1,1,2}->{2,1,1,1}; {1,2,2}/{2,1,2}->{2,2,1}; {1,3,1}/{1，1，3}->{3,1,1}; {1,4}->{4,1}; {2,3}->{3,2}

    //{1,2,1,1}/{1,1,2,1}/{1,1,1,2}->{2,1,1,1}
    if(repeatCount.size() == 4){
       int pos = 0;
       for(int i = 0; i < repeatCount.size(); i++){
           if(repeatCount.at(i).second == 2){
               pos = i;
               break;
           }
       }
       if(pos != 0){
           std::rotate(handCard.begin(), handCard.begin()+pos, handCard.begin()+pos+2);
           std::rotate(repeatCount.begin(), repeatCount.begin()+pos, repeatCount.begin()+pos+1);
       }
    }
    // {1,2,2}->{2,2,1}
    if(repeatCount.at(0).second == 1 &&
        repeatCount.at(1).second == 2 &&
        repeatCount.at(2).second == 2){
       std::rotate(handCard.begin(), handCard.begin()+1, handCard.end());
       std::swap(repeatCount.at(0), repeatCount.at(1));
       std::swap(repeatCount.at(1), repeatCount.at(2));
    }
    // {2,1,2}
    if(repeatCount.at(0).second == 2 &&
        repeatCount.at(1).second == 1 &&
        repeatCount.at(2).second == 2){
       std::rotate(handCard.begin()+2, handCard.begin()+3, handCard.end());
       std::swap(repeatCount.at(1), repeatCount.at(2));
    }
    // {1,3,1}
    if(repeatCount.at(0).second == 1 &&
        repeatCount.at(1).second == 3 &&
        repeatCount.at(2).second == 1){
       std::rotate(handCard.begin(), handCard.begin()+1, handCard.end());
       std::swap(repeatCount.at(0), repeatCount.at(1));
    }
    // {1,1,3}
    if(repeatCount.at(0).second == 1 &&
        repeatCount.at(1).second == 1 &&
        repeatCount.at(2).second == 3){
       std::rotate(handCard.begin(), handCard.begin()+2, handCard.end());
       std::swap(repeatCount.at(0), repeatCount.at(2));
       std::swap(repeatCount.at(1), repeatCount.at(2));
    }
    // {1,4}
    if(repeatCount.at(0).second == 1 &&
        repeatCount.at(1).second == 4){
       std::rotate(handCard.begin(), handCard.begin()+1, handCard.end());
       std::swap(repeatCount.at(0), repeatCount.at(1));
    }
    // {2,3}
    if(repeatCount.at(0).second == 2 &&
        repeatCount.at(1).second == 3){
       std::rotate(handCard.begin(), handCard.begin()+2, handCard.end());
       std::swap(repeatCount.at(0), repeatCount.at(1));
    }
    return repeatCount;
}

struct handBest Hand::getBest(){
    handBest handBest;
    std::vector<std::pair<int, int>> cardStruct = sortGroup();
    //are the suits the same
    int firstSuit = handCard[0].getSuit();
    int isFlush = 1;
    for(int i = 1; i < handCard.size(); i++){
       if(firstSuit != handCard[i].getSuit()){
           isFlush = 0;
           break;
       }
    }
    //are the cards straight
    int isStraight = 1;
    for(int i = 0; i<handCard.size()-1; i++){
       if(handCard[i].getValue() != handCard[i+1].getValue()-1){
           isStraight = 0;
           break;
       }
    }
    //special case: {A, 2, 3, 4, 5}
    if(handCard[0].getValue() == 14 &&
       handCard[1].getValue() == 2 &&
       handCard[2].getValue() == 3 &&
       handCard[3].getValue() == 4 &&
       handCard[4].getValue() == 5){
       isStraight = 1;
    }
    // the cards in hand form a High, put the largest value the left
    if(!isFlush && !isStraight && cardStruct.size() == 5){
       handBest.category = cardsCategory::high;
       for(int i = 0; i < handCard.size(); i++){
           handBest.handValue.push_back(cardStruct.at(4-i).first);
       }
       return handBest;
    }
    // the cards in hand form a pair, the handBest.handValue will become {pairValue, sumOfFollow}
    if(cardStruct.size() == 4){
       handBest.category = cardsCategory::pair;
       handBest.handValue.push_back(cardStruct.at(0).first);
       int sum = 0; // the sum of the following cards
       for(int i = 2; i < cardStruct.size(); i++){
           sum = sum + cardStruct.at(i).first;
       }
       handBest.handValue.push_back(sum);
       return handBest;
    }
    // the cards in hand form two pair, the handBest.handValue will become {pair2Value, pair1Value, follow}, the higher pair put in the first
    if(cardStruct.size() == 3 && cardStruct.at(0).second == 2){
       handBest.category = cardsCategory::twop;
       handBest.handValue.push_back(cardStruct.at(1).first); // the higher pair at first
       handBest.handValue.push_back(cardStruct.at(0).first);
       handBest.handValue.push_back(cardStruct.at(2).first);
       return handBest;
    }
    // the cards in hand form Three of A kind, only need to put in the value of the three
    if(cardStruct.size() == 3 && cardStruct.at(0).second == 3){
       handBest.category = cardsCategory::trio;
       handBest.handValue.push_back(cardStruct.at(0).first);
       return handBest;
    }
    // the cards in hand form a Straight, the largest value will be push into the handvalue
    if(!isFlush && isStraight){
       handBest.category = cardsCategory::strt;
       if(cardStruct.at(0).first == 14){
           handBest.handValue.push_back(14);
       }else{
           handBest.handValue.push_back(cardStruct.at(4).first);
       }
       return handBest;
    }
    // the cards in hand form a Flush, the sum of the card will be push into the handValue
    if(isFlush && !isStraight){
       handBest.category = cardsCategory::flsh;
       int sum = 0;
       for(int i = 0; i < cardStruct.size(); i++){
           sum = sum + cardStruct.at(i).first;
       }
       handBest.handValue.push_back(sum);
       return handBest;
    }
    // the cards in hand form a Full Houses,
    if(cardStruct.size() == 2 && cardStruct.at(0).second == 3){
       handBest.category = cardsCategory::full;
       handBest.handValue.push_back(cardStruct.at(0).first);
       handBest.handValue.push_back(cardStruct.at(1).first);
       return handBest;
    }
    // the cards in hand form a Four of A king, the cardStruct will be {{fourValue, 4}, {fourValue2, 1}}
    if(cardStruct.size() == 2 && cardStruct.at(0).second == 4){
       handBest.category = cardsCategory::four;
       handBest.handValue.push_back(cardStruct.at(0).first);
       handBest.handValue.push_back(cardStruct.at(1).first);
       return handBest;
    }
    // the cards in hand form a Straight Flush,
    if(isFlush && isStraight){
       handBest.category = cardsCategory::stfl;
       if(cardStruct.at(0).first == 14){
           handBest.handValue.push_back(14);
       }else{
           handBest.handValue.push_back(cardStruct.at(4).first);
       }
       return handBest;
    }
    return handBest;
}

void Hand::swapCard(const QVector<int> &cardPos, Deck &deck){
    std::vector<Card> newCard(cardPos.size());
    //firstly deal all cards, then exchange.
    for(int i = 0; i < cardPos.size(); i++){
        newCard[i] = deck.dealCard();
    }
    for(int i = 0; i < cardPos.size(); i++){
        deck.exchangeCard(handCard[cardPos.at(i)]);
        handCard[cardPos.at(i)] = newCard[i];
    }
    sortGroup();
}

void Hand::swapCard(int pos, Deck &deck){
    if(pos == -1){
        return;
        qDebug() << "no need to swap card";
    }
    Card newCard = deck.dealCard();
    deck.exchangeCard(handCard[pos]);
    handCard[pos] = newCard;
    sortGroup();
}

std::vector<Card> Hand::getHandCard(){
    return handCard;
}

QString Hand::getHandName() {
    switch (this->getBest().category) {
    case cardsCategory::high:
        return "Highest Card";
    case cardsCategory::pair:
        return "One Pair";
    case cardsCategory::twop:
        return "Two Pair";
    case cardsCategory::trio:
        return "Three of A Kind";
    case cardsCategory::strt:
        return "Straight";
    case cardsCategory::flsh:
        return "Flush";
    case cardsCategory::full:
        return "Full House";
    case cardsCategory::four:
        return "Four of A Kind";
    case cardsCategory::stfl:
        return "Straight Flush";
    default:
        return "Unknown";
    }
}
