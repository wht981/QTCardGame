#include "player.h"

Player::Player()
{

}

int Player::swapCardStrategy(Hand hand){
    std::pair<int, int> maxSuitCount = {0, 0}; // the number of the most same suit

    std::vector<std::pair<int, int>> suitCount = {
        {1, 0}, // count of suit club
        {2, 0}, // count of suit diamonds
        {3, 0}, // count of suit hearts
        {4, 0}  // count of suit spades
    };

    for(int i = 0; i < hand.getHandCard().size(); i++){
        int suit = hand.getHandCard().at(i).getSuit();
        suitCount.at(suit - 1).second++; // 1 = clubs, 2 = diamonds, 3 = hearts, 4 = spades, so the count at (suit - 1) ++；
    }

    for (const auto& pair : suitCount) {
        if(pair.second > maxSuitCount.second){
            maxSuitCount = pair;
        }
    }


    // if the category is high and

    switch (hand.getBest().category) { 
    case cardsCategory::high:
        if(maxSuitCount.second == 3 || maxSuitCount.second == 4){
            for(int i = 0; i < hand.getHandCard().size(); i++){
                if(hand.getHandCard().at(i).getSuit() != maxSuitCount.first){
                    return i; // return the smaller card when maxSuitCount is 3 (since the card is from small to big)
                }
            }
        }else{
            return 0; // if no maxSuitCount is smaller than 3, return the smallest card pos to change
        }
    case cardsCategory::pair:
        if(maxSuitCount.second == 4){ // the one of the pair has a different suit which make it not a flush, take a chance to get the flush, the chance is 1-(3/4）^3 = 0.578
            if(hand.getHandCard().at(0).getSuit() ==  maxSuitCount.first){
                return 1;
            }else{
                return 0;
            }
        }else{
            return 2; // if the possibility of swap to a flush is small, return the smaller card pos except the pair;
        }
    case cardsCategory::twop:
        return 4; // the category is good, and the maxSuitCount cannot be large than 3, so it is better to swap the single card;
    case cardsCategory::trio:
        return 3; // the category is good, and the maxSuitCount cannot be large than 3, so it is better to swap the smaller single card;
    case cardsCategory::strt:
        return -1; // no need to swap any card because it will break the category;
    case cardsCategory::flsh:
        return -1; // no need to swap any card;
    case cardsCategory::full:
        return -1; // no need to swap any card;
    case cardsCategory::four:
        if(hand.getHandCard().at(4).getValue() < 8){
            return 4;
        }
    case cardsCategory::stfl:
        return -1;
    }

}
