#include "BlackJackArena.h"

namespace ft {

namespace {
const std::string& PLAYER_ACTION_MSG = "Player turn: (t/T to HIT; d/D to HOLD)";

}

BlackJackArena::BlackJackArena() :
  _player(new Player("sean")),
  _dealer(new Dealer()) {
}

bool BlackJackArena::StartGame() {
  cout << "BlackJackArena::StartGame game is starting..." << endl;

  bool anotherRound = false;
  do {
    cout
      << "************************** BEGIN ROUND ********************************\n"
      << "***********************************************************************\n"
      << endl;
    startRound();
    cout
      << "**************************** END ROUND ********************************\n"
      << "***********************************************************************\n"
      << endl;

    cout << "Play another round? " << endl;
    char input;
  cin >> input;
  if(input == 'y' || input == 'Y')
    anotherRound = true;
  else
    anotherRound = false;
  } while(anotherRound == true) ;
  return true;
}

void BlackJackArena::startRound() {


  vector<int> values;
  bool anotherRound = false;

  //reset the deck
  reset();
  values.clear();

  bool player_busted = false;

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

  char i = 'q';
  int player_hand_val = 0;
  do {
    //show player's hand
    cout << "******************** PLAYER HAND BEGIN **********************" << endl;
    const card_list_t& playersHand = _player->Hand();
    for(card_list_cit_t it = playersHand.begin(); it != playersHand.end(); it++) {
      (*it)->Print();
    }
    cout << "********************* PLAYER HAND END ***********************" << endl;

    getValue(playersHand, values);
    for(vector<int>::iterator it = values.begin(); it != values.end(); it++) {
      cout << " value: " << *it << ", ";
      if(it == values.begin() && *it > 21) {
        player_hand_val = *it;
        player_busted = true;
      }
    }
    cout << endl;

    if(player_busted == true) {
      cout << "Player busted with value: " << player_hand_val << endl;
      break;
    }

    //(loop)get player input
    bool unknownInput = true;
    for(;;) {
      i = _player->GetPlayerAction(PLAYER_ACTION_MSG);

      if(i == 't' || i == 'T') {
        unknownInput = false;
        cout << "Player HIT" << endl;
        _player->AcceptCard(_dealer->DealNextCard());
      }
      else if(i == 'd' || i == 'D') {
        cout << "Player says HOLD..." << endl;
        unknownInput = false;
      }

      if(unknownInput == false)
        break;
    }
  }
  while(i != 'd' && i != 'D');

  if(player_busted == true) {
    return;
  }

  player_hand_val = values[0];
  cout << "The value or your hand is: " << player_hand_val << endl;

  //when done dealer gets cards
  //add dealer logic
  int dealer_hand_val = 0;
  cout << "Dealer will try to hit soft 17" << endl;
  for(;;) {
    bool tgtHitOrBust = false;
    const card_list_t& dealersHand = _dealer->Hand();
    //show dealer's hand
    cout << "******************** DEALER HAND BEGIN **********************" << endl;
    for(card_list_cit_t it = dealersHand.begin(); it != dealersHand.end(); it++) {
      (*it)->Print();
    }
    cout << "********************* DEALER HAND END ***********************" << endl;
    getValue(dealersHand, values);

    for(vector<int>::iterator it = values.begin(); it != values.end(); it++) {
      cout << "value: " << *it << ", ";
      if(it == values.begin() && *it >= 17) {
        tgtHitOrBust = true;
        dealer_hand_val = *it;
        break;
      }
    }
    cout << endl;

    if(tgtHitOrBust == true)
      break;

    card_ptr_t dealer_next_card = _dealer->DealNextCard();
    cout << "Dealer draws another card...";
    dealer_next_card->Print();
    _dealer->AcceptCard(dealer_next_card);
  }

  //declare winner
  if(dealer_hand_val > 21) {
    cout << "Dealer busted, player wins" << endl;
  }
  else if(dealer_hand_val < player_hand_val) {
    cout << "Player wins with " << player_hand_val << " against dealer's "
      << dealer_hand_val << endl;
  }
  else if(dealer_hand_val > player_hand_val) {
    cout << "Player loses with " << player_hand_val << " against dealer's "
      << dealer_hand_val << endl;
  }
  else {
    cout << "PUSH!!!" << endl;
  }

  cout
    << "/**************************** END ROUND ********************************\n"
    << "/***********************************************************************\n"
    << endl;
}

//#define DBG
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
    values.push_back(totVal);
    totVal = handVal + numAces + 10;
    values.push_back(totVal);
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

} //namespace ft


