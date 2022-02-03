#include "Cards.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
    Card* c1 = new BombCard();
    Card* c2 = new BlockadeCard();
    Card* c3 = new AirliftCard();
    Card* c4 = new DiplomacyCard();
    Card* c5 = new Card(*c4); //Testing copy constuctor

    cout << "BLAH" << endl;
    std::vector<Card*> cards = std::vector<Card*>(); //Adding cards to a vector to pass in to Deck.
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
  
    Deck* deck = new Deck(cards);
    Hand* hand = new Hand(); //Creating a new empty hand

    //Print out all cards: Print statement shows correct card type
    cout << *c1 << endl;
    cout << *c2 << endl;
    cout << *c3 << endl;
    cout << *c4 << endl;
    cout << *c5 << endl;

    cout << *deck << endl; //Print out deck
   
    hand->addCard(deck->draw()); //Add a card to the Hand by drawing one from the Deck
    
    //Print out new status of deck and hand
    cout << *deck << endl;
   
    cout << *hand << endl;
    
    //Draw the rest of the cards from the deck (random order):
    while (!deck->isEmpty()) {
        hand->addCard(deck->draw());
    }

    //Print out new status of deck and hand
    cout << *deck << endl;

    cout << *hand << endl;

    //Put the card back on the deck

    deck->returnToDeck(hand->returnCardToDeck(0));

    cout << *deck << endl;
    cout << *hand << endl;

    delete(c1);
    delete(c2);
    delete(c3);
    delete(c4);
    delete(c5);
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