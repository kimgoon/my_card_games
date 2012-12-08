#include <stdint.h>
#include "BlackJackArena.h"


namespace ft {

namespace {
const std::string& PLAYER_ACTION_MSG = "Player turn: (t/T to HIT; d/D to HOLD)";
const int32_t INITIAL_CARD_DEAL_COUNT = 2;
const int32_t BUST_VALUE = 22;
const int32_t DEALER_SOFT_TGT = 17;

} //anonymous namespace

BlackJackArena::BlackJackArena() :
  _player(new Player("sean")),
  _dealer(new Dealer()) {

  _cardHandlers.push_back(_dealer);
  _cardHandlers.push_back(_player);
}


bool BlackJackArena::StartGame() {
  cout << "BlackJackArena::StartGame game is starting..." << endl;
  cout << "Dealer will try to hit soft " << DEALER_SOFT_TGT << endl;

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

void BlackJackArena::startInitialDeal() {
  std::cout << "Starting BlackJack Initial Deal" << endl;
  //reset the deck
  reset();
  for(int i = 0; i < INITIAL_CARD_DEAL_COUNT; i++) {
    for(cardhander_list_it_t it = _cardHandlers.begin(); it != _cardHandlers.end(); it++) {
      (*it)->AcceptCard(_dealer->DealNextCard());
    }
  }
}
void BlackJackArena::printHand(const std::string& name, const card_list_t hand) {
  cout << "******************** " << name << "'s HAND BEGIN **********************" << endl;
  for(card_list_cit_t it = hand.begin(); it != hand.end(); it++) {
    (*it)->Print();
  }
  cout << "********************* "<< name << "'s HAND END ***********************" << endl;

}

void BlackJackArena::startRound() {
  startInitialDeal();

  bool anotherRound = false;
  bool player_busted = false;

  //show dealer's hand
  cout << "Dealer is showing a:";
  _dealer->Hand()[0]->Print();
  cout << endl;

  char i = 'q';
  int32_t player_hand_val = 0;
  vector<int> values;
  do {
    //show player's hand
    printHand("sean", _player->Hand());

    getValue(_player->Hand(), values);
    for(vector<int>::iterator it = values.begin(); it != values.end(); it++) {
      cout << " value: " << *it << ", ";
      if(it == values.begin() && *it >= BUST_VALUE) {
        player_hand_val = *it;
        player_busted = true;
      }
    }
    cout << endl;

    if(player_busted == true)
      break;

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
      cout << endl << endl << endl << endl;

      if(unknownInput == false)
        break;
    }
  }
  while(i != 'd' && i != 'D');

  if(player_busted == true) {
    cout << "Player busted with value: " << player_hand_val << endl;
    return;
  }

  if(values.size() > 1 && values[1] < BUST_VALUE) {
    player_hand_val = values[1];
  }
  else
    player_hand_val = values[0];

  cout << "The value or your hand is: " << player_hand_val << endl;

  //start dealer logic
  int32_t dealer_hand_val = 0;
  for(;;) {
    bool tgtHitOrBust = false;
    //show dealer's hand
    printHand("dealer", _dealer->Hand());
    getValue(_dealer->Hand(), values);

    cout << "value: ";
    for(vector<int>::iterator it = values.begin(); it != values.end(); it++) {
      cout << *it << ", ";
      if(*it >= DEALER_SOFT_TGT) {
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

  printRoundResults(player_hand_val, dealer_hand_val);
}

void BlackJackArena::printRoundResults(int32_t player_hand_val, int32_t dealer_hand_val) {
  //declare winner
  cout << endl << "RESULT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  if(dealer_hand_val >= BUST_VALUE) {
    cout << "^^^^^^^^^^^^^^^^^ Dealer busted, player wins ^^^^^^^^^^^^^^^^" << endl;
  }
  else if(dealer_hand_val < player_hand_val) {
    cout << "^^^^^^^^^^^^^^^^^ Player wins ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    cout << "Player wins with " << player_hand_val << " against dealer's "
      << dealer_hand_val << endl;
  }
  else if(dealer_hand_val > player_hand_val) {
    cout << "^^^^^^^^^^^^^^^^^ Player loses  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    cout << "Player loses with " << player_hand_val << " against dealer's "
      << dealer_hand_val << endl;
  }
  else {
    cout << "^^^^^^^^^^^^^^^^^ PUSH^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    cout << "PUSH!!!" << endl;
  }
  cout << "RESULT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
}

int BlackJackArena::getValue(const card_list_t& cards, vector<int>& values) {
  int numAces = 0;
  int handVal = 0;
  card_list_cit_t cit = cards.begin();
  values.clear();

  for(; cit != cards.end(); cit++) {
    Card::card_value_t val = (*cit)->Value();
    if(val == Card::Value_Ace)
      ++numAces;
    else if(val >= Card::Value_Ten)
      handVal += 10;
    else
      handVal += (int)val + 2;
  }

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


