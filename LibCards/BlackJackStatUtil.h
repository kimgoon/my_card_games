#pragma once
#include "Card.h"


namespace ft {

class BlackJackStatUtil {
public:
  BlackJackStatUtil(int numDecks = 1) :
    _numDecks(numDecks)
  {
  }

  double GetBustPercentage(card_list_t dealerHand, card_list_t playerHand);
  double GetBlackJackPercentage();


  private:
    int _numDecks;

};

}
