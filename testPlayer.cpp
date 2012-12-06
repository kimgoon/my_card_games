#include <iostream>

#include "CardDeck.h"
#include "Player.h"

using namespace ft;

int main() {
  std::cout << "Testing Player class" << std::endl;

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

  const card_list_t& player_hand = player->Hand();
  std::cout << "Printing " << player->Name() << "'s hand:" << std::endl;
  for(card_list_cit_t cit = player_hand.begin(); cit != player_hand.end(); cit++) {
    (*cit)->Print();
  }

  player->ClearHand();
  std::cout << "Printing " << player->Name() << "'s hand:" << std::endl;
  for(card_list_cit_t cit = player_hand.begin(); cit != player_hand.end(); cit++) {
    (*cit)->Print();
  }

  return 0;
}
