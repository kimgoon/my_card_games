#include "Dealer.h"

namespace ft {

Dealer::Dealer() :
  _deck(new CardDeck())
{
}

void Dealer::ShuffleDeck() {
  _deck->Shuffle();
}

card_ptr_t Dealer::DealNextCard() {
  return _deck->GetNext();
}

void Dealer::AcceptCard(card_ptr_t card) {
  _hand.push_back(card);
}

void Dealer::ClearHand() {
  _hand.clear();
}

const card_list_t& Dealer::Hand() const {
  return _hand;
}

int Dealer::HandCount() {
  return _hand.size();
}


} //namespace ft

