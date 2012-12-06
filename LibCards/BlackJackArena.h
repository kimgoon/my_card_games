/* Purpose: Defines the class BlackJackArena which has a Dealer and a player, manages
 * the rounds of the game and sets the rules of the game
 * Author:ft
 */
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Card.h"
#include "CardDeck.h"
#include "Player.h"
#include "Dealer.h"

using namespace std;


namespace ft {

class BlackJackArena {
public:
  BlackJackArena();
  bool StartGame();

int getValue(const card_list_t& cards, vector<int>& values);

private:
  boost::shared_ptr<Player> _player;
  boost::shared_ptr<Dealer> _dealer;

  //methods
  void startRound();
  void declareWinner();
  void reset();
};




} //namespace ft


