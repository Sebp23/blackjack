#include <logic.hpp>


class Card {
  public:
    int cardValue;

    Card(int value) {
      cardValue = value;
    }

};

struct Deck {

  std::vector<Card> *cardDeck = new std::vector<Card>();
  
  Deck() {
    
    int numberOfCardType = 0;
    int cardValue = 1;

    while(cardDeck->size() < 52) {
      
      if (cardValue == 10) {
        numberOfCardType = 0;
      }

      if (numberOfCardType == 4) {
        
        cardValue++;
        numberOfCardType = 0;
      }

      cardDeck->push_back(Card(cardValue));

      numberOfCardType++;
      
    }
  }

  ~Deck() {
    
  }

  void ShuffleDeck() {

    // get a time-based seed for the random shuffling of the card deck
    auto seedForRandom = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(cardDeck->begin(), cardDeck->end(), std::default_random_engine(seedForRandom));
  }

  Card Deal() {

    Card cardToDeal = cardDeck->back();
    cardDeck->pop_back();
    
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
  
  int CheckDealerCards(std::vector<Card> m_dealerHand) {
    
    int sumOfCards = 0;

    for (auto it = m_dealerHand.begin(); it != m_dealerHand.end(); it++) {
      sumOfCards += it->cardValue;
    }

    return sumOfCards;
  }

  int DealerHit(int m_dealerSum, Deck deckToBeDealt) {
    
    int currentDealerSum = m_dealerSum;

    //currentPlayerSum = CheckPlayerCards(currentPlayerHand) + deckToBeDealt.cardDeck->back().cardValue;
    currentDealerSum += deckToBeDealt.cardDeck->back().cardValue;
    //std::cout << "Card being dealt for Hit: " << deckToBeDealt.cardDeck->back().cardValue << std::endl;
    deckToBeDealt.cardDeck->pop_back();

    return currentDealerSum;
  }
};

struct Player {

  std::vector<Card> playerHand;

  Player(Deck deckToBeDealt) {
    for (auto i = 0; i < 2; i++) {
      playerHand.push_back(deckToBeDealt.Deal());
    }
  }

  int CheckPlayerCards(std::vector<Card> m_playerHand) {
    
    int sumOfCards = 0;

    for (auto it = m_playerHand.begin(); it != m_playerHand.end(); it++) {
      sumOfCards += it->cardValue;
    }

    return sumOfCards;
  }

  int PlayerHit(int m_playerSum, Deck deckToBeDealt) {
    
    int currentPlayerSum = m_playerSum;

    //currentPlayerSum = CheckPlayerCards(currentPlayerHand) + deckToBeDealt.cardDeck->back().cardValue;
    currentPlayerSum += deckToBeDealt.cardDeck->back().cardValue;
    //std::cout << "Card being dealt for Hit: " << deckToBeDealt.cardDeck->back().cardValue << std::endl;
    deckToBeDealt.cardDeck->pop_back();

    return currentPlayerSum;
  }
};

GameOutcome Game() {

  bool playerTurn = true;
  bool dealerTurn = false;


  Deck *test = new Deck();
  test->ShuffleDeck();

  Dealer dealer = Dealer(*test);
  for (auto it = dealer.dealerHand.begin(); it != dealer.dealerHand.end(); it++) {
    //std::cout << "Dealer Hand: " << it->cardValue << std::endl;
  }

  //std::cout << "Sum of Dealers Cards: " << dealer.CheckDealerCards(dealer.dealerHand) << std::endl;
  
  Player player = Player(*test);
  for (auto it = player.playerHand.begin(); it != player.playerHand.end(); it++) {
    //std::cout << "Player Hand: " << it->cardValue << std::endl;
  }

  int playerSum = player.CheckPlayerCards(player.playerHand);
  int dealerSum = dealer.CheckDealerCards(dealer.dealerHand);

  while(playerTurn) {

    //check to see if player got dealt a 10 and an ace, since this would change the ace's value to 11
    if (playerSum == 11 && (player.playerHand[0].cardValue == 1 || player.playerHand[1].cardValue == 1)) {
      //std::cout << "Player got Blackjack!" << std::endl;

      return WIN;
    }

    if (playerSum == 21) {
      //std::cout << "Player got Blackjack!" << std::endl;

      return WIN;
    }
    else if (playerSum > 21) {
      //std::cout << "Player went bust with: " << playerSum << std::endl;

      return LOSE;
    }
    else if (playerSum < 17) {
      // std::cout << "Sum of Players Cards: " << playerSum << std::endl;
      // std::cout << "Player is Hitting..." << std::endl;

      playerSum = player.PlayerHit(playerSum, *test);
    }
    else if (playerSum >= 17) {
      // std::cout << "Sum of Players Cards: " << playerSum << std::endl;
      // std::cout << "Player is Staying..." << std::endl;
      // std::cout << "Final sum of Players Cards: " << playerSum << std::endl;
      
      playerTurn = false;
      dealerTurn = true;

    }

  }

  while(dealerTurn) {
    //check to see if dealer got dealt a 10 and an ace, since this would change the ace's value to 11
    if (dealerSum == 11 && (dealer.dealerHand[0].cardValue == 1 || dealer.dealerHand[1].cardValue == 1)) {
      //std::cout << "Dealer got Blackjack!" << std::endl;

      return LOSE;
    }

    if (dealerSum == 21) {
      //std::cout << "Dealer got Blackjack!" << std::endl;

      return LOSE;
    }
    else if (dealerSum > 21) {
      // std::cout << "Dealer went bust with: " << dealerSum << std::endl;

      return WIN;
    }
    else if (dealerSum < 17) {
      // std::cout << "Sum of Dealers Cards: " << dealerSum << std::endl;
      // std::cout << "Dealer is Hitting..." << std::endl;

      dealerSum = dealer.DealerHit(dealerSum, *test);
    }
    else if (dealerSum >= 17 && dealerSum < 21) {
      // std::cout << "Sum of Dealers Cards: " << dealerSum << std::endl;
      // std::cout << "Dealer is Staying..." << std::endl;
      // std::cout << "Final sum of Dealers Cards: " << dealerSum << std::endl;

      if (playerSum <= dealerSum) { 
        return LOSE;
      }
      else if (playerSum > dealerSum && playerSum < 21) {
        return WIN;
      }
      
      dealerTurn = false;

    }
  }

  return LOSE;
}

std::string GameResult(GameOutcome win) {
  
  std::string result;

  if (win) {

    result = "Player Wins!";
  }
  else if (!win) {
    result = "House Wins!";
  }

  return result;
}

struct PlayGame {
  
  int amountOfPlays;

  PlayGame(int m_amountOfPlays) {
    amountOfPlays = m_amountOfPlays;
  }

  void PlayTheGame() {
    for(int i = 0; i < amountOfPlays; i++){
        std::cout << GameResult(Game()) << std::endl;
    }
  }
};


int main() {  
  PlayGame game = PlayGame(100);
  game.PlayTheGame();
}
