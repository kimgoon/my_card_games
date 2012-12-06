/* Purpose: Defines the class Player, who has a hand and manages the next move
 * Author:ft
 */
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "ICardHandler.h"
#include "Card.h"

using namespace std;

namespace ft {
class Player;

typedef boost::shared_ptr<Player> player_ptr_t;

class Player : public ICardHandler {
  public:
    Player(const string& name);

    //implement ICardHandler
    void AcceptCard(card_ptr_t card);
    void ClearHand();
    const card_list_t& Hand() const;
    int HandCount();

    //Player properties
    std::string Name() const;

  private:
    std::string _name;
    card_list_t _hand;
};

} //namespace ft

