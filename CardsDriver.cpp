#include "Cards.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
    Card* c1 = new Card();
   
    Card* c2 = new BombCard();
    Card* c3 = new BlockadeCard();
    Card* c4 = new AirliftCard();
    Card* c5 = new DiplomacyCard();
    Card* c6 = new Card(*c5);

    std::vector<Card*> cards = std::vector<Card*>();
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
    cards.push_back(c6);
  
    Deck* deck = new Deck(cards);
    Hand* hand = new Hand();

    cout << *c1 << endl;
    cout << *c2 << endl;
    cout << *c3 << endl;
    cout << *c4 << endl;
    cout << *c5 << endl;
    cout << *c6 << endl;

    cout << *deck << endl;
    hand->addCard(deck->draw());
    /*hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());*/
    cout << *deck << endl;
   
    cout << *hand << endl;

    deck->returnToDeck(hand->returnCardToDeck(0));

    cout << *deck << endl;
    cout << *hand << endl;

    delete(c1);
    delete(c2);
    delete(c3);
    delete(c4);
    delete(c5);
    delete(c6);
    delete(deck);
    delete(hand);

   /* c1 = NULL;
    c2 = NULL;
    c3 = NULL;
    c4 = NULL;
    c5 = NULL;
    c6 = NULL;
    deck = NULL;
    hand = NULL;*/
    return 0;
}