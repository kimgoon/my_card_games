#include "CardDeck.h"
namespace ft {

  namespace {
    const int CARDS_PER_DECK = 52;


  }

CardDeck::CardDeck(int numberOfDecks) :
  _current_pos(0),
  _numberOfDecks(numberOfDecks)
{
  for(int i = 0; i < _numberOfDecks; i++) {
    for(int suit = Card::Suit_Min; suit <= Card::Suit_Max; suit++) {
      for(int val = Card::Value_Min; val <= Card::Value_Max; val++) {
        card_ptr_t card_ptr(new Card(static_cast<Card::card_suit_t>(suit),
              static_cast<Card::card_value_t>(val)));
        _cards.push_back(card_ptr);
      }
    }
  }
}

void CardDeck::Shuffle() {
  _current_pos=0;
  srand(unsigned(time(NULL)));
  std::random_shuffle(_cards.begin(),_cards.end());
};

void CardDeck::PrintOutAll() {
  for(int i = 0; i < CARDS_PER_DECK*_numberOfDecks; i++) {
    _cards[i]->Print();
  }
}

boost::shared_ptr<Card> CardDeck::GetNext() {
  return _cards[_current_pos++];
}

} //namespace ft

