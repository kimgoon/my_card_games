/* Purpose: Dealer class manages the deck and 
 *
 */
#pragma once

#include "CardDeck.h"
#include "ICardHandler.h"

namespace ft {

class Dealer : public ICardHandler {
public:
  Dealer();
  void ShuffleDeck();
  card_ptr_t DealNextCard();
  //implement ICardHandler
  void AcceptCard(card_ptr_t card);
  void ClearHand();
  const card_list_t& Hand() const;
  int HandCount();

private:
  carddeck_ptr_t _deck;
  card_list_t _hand;
};

}


