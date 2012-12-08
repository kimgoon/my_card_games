#pragma once


namespace ft {

class BlackJackStatUtil {
public:
  BlackJackStatUtil(int numDecks = 1) :
    _numDecks(numDeck)
  {
  }

  double GetBlackJackPercentage();
  double GetBustPercentage();


  private:
    int _numDecks;

};

}
