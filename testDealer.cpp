#include <iostream>
#include "CardDeck.h"

using namespace ft;

int main() {
  std::cout << "Testing CardDeck class" << std::endl;

  boost::shared_ptr<CardDeck> cd(new CardDeck());

  cd->Shuffle();

  std::cout << "test deal first card..." << std::endl;
  boost::shared_ptr<Card> pCard = cd->GetNext();
  pCard->Print();
  std::cout << "test deal second card..." << std::endl;
  pCard = cd->GetNext();
  pCard->Print();
  std::cout << "test deal third card..." << std::endl;
  pCard = cd->GetNext();
  pCard->Print();
  std::cout << "test deal fourth card..." << std::endl;
  pCard = cd->GetNext();
  pCard->Print();
  std::cout << "test deal five card..." << std::endl;
  pCard = cd->GetNext();
  pCard->Print();
  std::cout << "test deal six card..." << std::endl;
  pCard = cd->GetNext();
  pCard->Print();
  return 0;
}
