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
#include "ICardHandler.h"

using namespace std;


namespace ft {

class BlackJackArena {
public:
  BlackJackArena();
  bool StartGame();

  int getValue(const card_list_t& cards, vector<int>& values);

private:
  //typedefs
  typedef typename std::vector<boost::shared_ptr<ICardHandler> > cardhandler_list_t;
  typedef typename cardhandler_list_t::iterator cardhander_list_it_t;

  //members
  boost::shared_ptr<Player> _player;
  boost::shared_ptr<Dealer> _dealer;
  cardhandler_list_t _cardHandlers;

  //methods
  void startRound();
  void startInitialDeal();
  void declareWinner();
  void reset();
  void printRoundResults(int32_t player_hand_val, int32_t dealer_hand_val);
  void printHand(const std::string& name, const card_list_t hand);

};


} //namespace ft


