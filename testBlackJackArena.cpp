#include <iostream>
#include <vector>

#include "CardDeck.h"
#include "Player.h"
#include "BlackJackArena.h"

using namespace ft;

int main() {
  std::cout << "Testing BlackJackArena class" << std::endl;

  boost::shared_ptr<BlackJackArena> arena(new BlackJackArena());


  arena->StartGame();



  return 0;

  //unreachable code

  boost::shared_ptr<Player> player(new Player("sean"));

  carddeck_ptr_t cd(new CardDeck());

  std::cout << "current player is " << player->Name() << std::endl;

  cd->Shuffle();

  std::cout << "test deal first card..." << std::endl;
  boost::shared_ptr<Card> pCard = cd->GetNext();
  pCard->Print();
  player->AcceptCard(pCard);
  pCard = cd->GetNext();
  pCard->Print();

  player->AcceptCard(pCard);

  std::cout << "**********************************************" << std::endl;
  const card_list_t& player_hand = player->Hand();
  std::cout << "Printing " << player->Name() << "'s hand:" << std::endl;
  for(card_list_cit_t cit = player_hand.begin(); cit != player_hand.end(); cit++) {
    (*cit)->Print();
  }
  std::cout << "**********************************************" << std::endl;

  vector<int> values;
  int valCount = arena->getValue(player->Hand(), values);

  for(vector<int>::iterator it = values.begin(); it != values.end(); it++) {
    std::cout << "value calced: " << *it << std::endl;
  }


  return 0;
}
