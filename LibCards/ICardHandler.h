#pragma once

#include "Card.h"

namespace ft {

class ICardHandler {
  public:
    virtual void AcceptCard(card_ptr_t card)=0;
    virtual void ClearHand()=0;
    virtual const card_list_t& Hand() const =0;
    virtual int HandCount()=0;
    virtual ~ICardHandler(){}
};

} //namespace ft
