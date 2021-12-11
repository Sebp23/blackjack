#include "utils.h"
#include "logic.cpp"

//TESTING STARTS HERE

class LastCardInDeckTestHarness : public AbstractTestHarness {
private:

  Deck *d = new Deck();
  Card c = d->Deal();

public:
  LastCardInDeckTestHarness() {
    register_test_func("Testing Deck",
                       [this]() -> void { assert_equal(10, c.cardValue); });
    CleanTestOne();
  }

  void CleanTestOne() {
    delete d;
  }
};

class FirstCardInDeckTestHarness : public AbstractTestHarness {
private:

  Deck *d1 = new Deck();
  Card c1 = d1->Deal();

public:
  FirstCardInDeckTestHarness() {
    register_test_func("Testing Deck",
                       [this]() -> void { assert_equal(1, d1->cardDeck->front().cardValue); });
    CleanTestTwo();
  }

  void CleanTestTwo() {
    delete d1;
  }
};

class StartingPlayerHandTestHarness : public AbstractTestHarness {
private:

  Deck *d2 = new Deck();
  Dealer dealer = Dealer(*d2);

public:
  StartingPlayerHandTestHarness() {
    register_test_func("Testing Number of Cards in Starting Hand",
                       [this]() -> void { assert_equal(2, (int)dealer.dealerHand.size()); });
    CleanTestThree();
  }

  void CleanTestThree() {
    delete d2;
  }
};

class GlobalTestManager : public TestManager {
public:
  GlobalTestManager() { 
      //this test works properly on its own
      add_test("Last Card in Deck Test", LastCardInDeckTestHarness());

      //this test changes the results of the previous test for some reason.
      add_test("Number of Cards In Dealer Start Hand", StartingPlayerHandTestHarness());

      //this test causes a seg fault
      add_test("First Card in Deck Test", FirstCardInDeckTestHarness());
    }
};

int main() {
    GlobalTestManager tr = GlobalTestManager();
    tr.execute();
}
