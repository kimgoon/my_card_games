/* Purpose: Declares the CardDeck class
 * Author: ft
 *
 */

#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include "Card.h"

using namespace std;

namespace ft {
class CardDeck;

typedef boost::shared_ptr<CardDeck> carddeck_ptr_t;

class CardDeck {
public:
  CardDeck(int numberOfDecks = 1);
  void Shuffle();
  void PrintOutAll();
  card_ptr_t GetNext();

private:
  card_list_t _cards;
  int _current_pos;
  int _numberOfDecks;
};

}
