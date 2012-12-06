#include "CardDeck.h"
namespace ft {
CardDeck::CardDeck() :
  _current_pos(0)
{
  int count = 0;
  for(int suit = Card::Suit_Min; suit <= Card::Suit_Max; suit++) {
    for(int val = Card::Value_Min; val <= Card::Value_Max; val++) {
      card_ptr_t card_ptr(new Card(static_cast<Card::card_suit_t>(suit),
            static_cast<Card::card_value_t>(val)));
      _smart_cards.push_back(card_ptr);
    }
  }
}

void CardDeck::Shuffle() {
  _current_pos=0;
  srand(unsigned(time(NULL)));
  std::random_shuffle(_smart_cards.begin(),_smart_cards.end());
};

void CardDeck::PrintOutAll() {
  for(int i = 0; i < 52; i++) {
    _smart_cards[i]->Print();
  }
}

boost::shared_ptr<Card> CardDeck::GetNext() {
  return _smart_cards[_current_pos++];
}

}
