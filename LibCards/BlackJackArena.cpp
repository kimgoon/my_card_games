#include "BlackJackArena.h"

namespace ft {

BlackJackArena::BlackJackArena() :
  _player(new Player("sean")),
  _dealer(new Dealer()) {
}

bool BlackJackArena::StartGame() {
  cout << "BlackJackArena::StartGame game is starting..." << endl;
  startRound();
  return true;
}

void BlackJackArena::startRound() {

  vector<int> values;
  //reset the deck
  reset();

  //deal cards

  //start with player
  _player->AcceptCard(_dealer->DealNextCard());

  //dealer card
  _dealer->AcceptCard(_dealer->DealNextCard());

  //player card
  _player->AcceptCard(_dealer->DealNextCard());

  //dealer card
  _dealer->AcceptCard(_dealer->DealNextCard());

  //show dealer's hand
  cout << "Dealer is showing a:" << endl;
  _dealer->Hand()[0]->Print();


  //show player's hand
  char i = 'q';
  do {
    cout << "Your hand is...." << endl;
    const card_list_t& playersHand = _player->Hand();
    for(card_list_cit_t it = playersHand.begin(); it != playersHand.end(); it++) {
      (*it)->Print();
    }

    getValue(playersHand, values);
    for(vector<int>::iterator it = values.begin(); it == values.end(); it++) {
      cout << " value: " << *it << ", ";
    }
    cout << endl << "h/H for hit; q/Q for break" << endl;
    //(loop)get player input
    cin >> i;
    if(i == 'h' || i == 'H') {
      cout << "Player hit" << endl;
      _player->AcceptCard(_dealer->DealNextCard());
    }
    else {
      cout << "Player says hold..." << endl;
      break;
    }

  }
  while(i != 'q');


  //when done dealer gets cards

  //add dealer logic


  //declare winner

  //start over?

  cout << "Do you want another round?" << endl;

}
#define DBG
int BlackJackArena::getValue(const card_list_t& cards, vector<int>& values) {
  int numAces = 0;
  int handVal = 0;
  card_list_cit_t cit = cards.begin();
  values.clear();

#ifdef DBG
  std::cout << "BlackJackArena::getValue begin debug print for hand:" << std::endl;
#endif

  for(; cit != cards.end(); cit++) {
    Card::card_value_t val = (*cit)->Value();
    if(val == Card::Value_Ace)
      ++numAces;
    else if(val >= Card::Value_Ten)
      handVal += 10;
    else
      handVal += (int)val + 2;

#ifdef DBG
    (*cit)->Print();
    std::cout << "current hand value:" << handVal << std::endl;
    if(numAces > 0) {
      std::cout << " w/ ace count: " << numAces << std::endl;
    }
#endif
  }

#ifdef DBG
  std::cout << "BlackJackArena::getValue end debug print for hand" << std::endl;
#endif

  if(numAces == 0) {
    values.push_back(handVal);
  }
  else {
    int totVal = handVal + numAces;
    if(totVal <= 21) {
      values.push_back(totVal);
      totVal = handVal + numAces + 10;
      if(totVal <= 21) {
        values.push_back(totVal);
      }
    }
  }
  return values.size();
}

void BlackJackArena::declareWinner() {
}

void BlackJackArena::reset() {
  _player->ClearHand();
  _dealer->ClearHand();
  _dealer->ShuffleDeck();
}





}


