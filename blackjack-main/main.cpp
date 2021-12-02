#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Card {
  public:
    int cardValue;

    Card(int value) {
      cardValue = value;
    }

};

struct Deck {

  std::vector<Card> cardDeck = std::vector<Card>();
  
  Deck() {
    
    int numberOfCardType = 0;
    int cardValue = 1;

    while(cardDeck.size() < 52) {
      
      if (cardValue == 10) {
        numberOfCardType = 0;
      }

      if (numberOfCardType == 4) {
        
        cardValue++;
        numberOfCardType = 0;
      }

      cardDeck.push_back(Card(cardValue));

      numberOfCardType++;
      
    }

    cardDeck = ShuffleDeck(cardDeck);
  }

  std::vector<Card> ShuffleDeck(std::vector<Card> deckToBeShuffled) {

    // get a time-based seed for the random shuffling of the card deck
    auto seedForRandom = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(deckToBeShuffled.begin(), deckToBeShuffled.end(), std::default_random_engine(seedForRandom));

    std::vector<Card> shuffledDeck = deckToBeShuffled;

    return shuffledDeck;
  }

  Card Deal() {

    Card cardToDeal = cardDeck.back();
    cardDeck.erase(cardDeck.end()-1);
    
    return std::move(cardToDeal);
  }
};

struct Dealer {

  std::vector<Card> dealerHand;

  Dealer(Deck deckToBeDealt) {
    for (auto i = 0; i < 2; i++) {
      dealerHand.push_back(deckToBeDealt.Deal());
    }
  }
};

struct Player {

  std::vector<Card> playerHand;

  Player(Deck deckToBeDealt) {
    for (auto i = 0; i < 2; i++) {
      playerHand.push_back(deckToBeDealt.Deal());
    }
  }
};


int main() {  
  
  Deck test = Deck();

  for (auto it = test.cardDeck.begin(); it != test.cardDeck.end(); it++) {
    std::cout << "Current Deck: " << it->cardValue << std::endl;
  }

  Dealer dealer = Dealer(test);
  for (auto it = dealer.dealerHand.begin(); it != dealer.dealerHand.end(); it++) {
    std::cout << "Dealer Hand: " << it->cardValue << std::endl;
  }
  
  for (auto it = test.cardDeck.begin(); it != test.cardDeck.end(); it++) {
    std::cout << "Current Deck: " << it->cardValue << std::endl;
  }

  // Player player = Player(test);
  // for (auto it = player.playerHand.begin(); it != player.playerHand.end(); it++) {
  //   std::cout << "Player Hand: " << it->cardValue << std::endl;
  // }

}
