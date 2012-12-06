#include "Player.h"

namespace ft {

Player::Player(const string& name) :
  _name(name)
{
}

void Player::AcceptCard(card_ptr_t card) {
  _hand.push_back(card);
}

void Player::ClearHand() {
  _hand.clear();
}

const card_list_t& Player::Hand() const {
  return _hand;
}

int Player::HandCount() {
  return _hand.size();
}

std::string Player::Name() const {
  return _name;
}


}
