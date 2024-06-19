#ifndef HANDBEST_H
#define HANDBEST_H
#include "cardsCategory.h"
#include <vector>

struct handBest{
    cardsCategory category;
    std::vector<int> handValue;
};

#endif // HANDBEST_H
