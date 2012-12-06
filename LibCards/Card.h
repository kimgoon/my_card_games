/* Purpose: Declares the base Card class
 * Author: ft
 *
 *
 */
#pragma once

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>


namespace ft{

//fwd declaration
class Card;

//typedefs
typedef boost::shared_ptr<Card> card_ptr_t;
typedef std::vector<card_ptr_t> card_list_t;
typedef card_list_t::iterator card_list_it_t;
typedef card_list_t::const_iterator card_list_cit_t;

class Card {
public:
  enum card_suit_t {
    Suit_Min = 0,
    Suit_Clover = Suit_Min,
    Suit_Diamond,
    Suit_Heart,
    Suit_Spade,
    Suit_Max = Suit_Spade
  };
  static const char* CARD_SUITS[];

  enum card_value_t {
    Value_Min = 0,
    Value_Two = Value_Min,
    Value_Three,
    Value_Four,
    Value_Five,
    Value_Six,
    Value_Seven,
    Value_Eight,
    Value_Nine,
    Value_Ten,
    Value_Jack,
    Value_Queen,
    Value_King,
    Value_Ace,
    Value_Max = Value_Ace
  };
  static const char* CARD_VALUES[];

  Card() {
  }
  Card(card_suit_t suit, card_value_t value) :
    _suit(suit),
    _value(value)
  {
  }
  Card(const Card& card) {
  }
  Card& operator=(const Card& rhs) {
    return *this;
  }

  card_suit_t Suit() const {
    return _suit;
  }
  card_value_t Value() const {
    return _value;
  }
  void Print() const {
    std::cout << "Card is a " << CARD_VALUES[_value] << " of "
      << CARD_SUITS[_suit] << std::endl;
  }

private:
  card_suit_t _suit;
  card_value_t _value;
};

} //namespace ft
