
#include <iostream>
#include <string>

#include "Cards.h"
#include "Player.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Map.h"

using std::cout;
using std::endl;
using std::string;

void cardsDriver();
void gameEngineDriver();
void map_picker();

int main()
{
	gameEngineDriver();
	return 0;
}

void cardsDriver() {
	Card* c1 = new BombCard();
	Card* c2 = new BlockadeCard();
	Card* c3 = new AirliftCard();
	Card* c4 = new DiplomacyCard();
	Card* c5 = c4->clone(); //Testing copy constuctor through the clone method

	std::vector<Card*> cards = std::vector<Card*>(); //Adding cards to a vector to pass in to Deck.
	cards.push_back(c1);
	cards.push_back(c2);
	cards.push_back(c3);
	cards.push_back(c4);
	cards.push_back(c5);

	Deck* deck = new Deck(cards);
	string name = "TestPlayer";
	Player* player = new Player(name, vector<Territory*>(), new Hand(), new OrdersList());
	Hand* hand = player->getHand(); //Creating a new empty hand

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

	//Play the card and put it back on the deck
	cout << "Below is the execution of the play() method of Card, which takes that card out of the hand it came from and puts it in the specified deck:" << endl;
	while (hand->size() > 0) {
		Card* temp = hand->getCard(0); //Get first card in the hand
		//Call play method from the card, taking that card from the hand it came from and placing it in the deck. Returning an order of the right type.
		Order* order = temp->play(hand, deck);
		if (order != NULL) {
			player->issueOrder(order); //Add order to the orderslist
		}
	}

	cout << "Executing all orders:" << endl;
	OrdersList* ordersList = player->getOrdersList();
	for (int i = 0; i < ordersList->size(); i++)
		ordersList->getOrder(i)->execute(); //Prints out the order


	cout << *deck << endl;
	cout << *hand << endl;

	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete c5;
	delete player; //Should internally call the destructor of the hand and orderslist
	delete deck;


	c1 = NULL;
	c2 = NULL;
	c3 = NULL;
	c4 = NULL;
	c5 = NULL;
	deck = NULL;
	hand = NULL;
	player = NULL;
	ordersList = NULL;
}

void playerDriver() {
	cout << "Demonstration of Player class:" << endl;

	Territory* territory1 = new Territory();
	Territory* territory2 = new Territory();

	vector<Territory*> territories = { territory1, territory2 };
	Hand* hand = new Hand();

	OrdersList* listOfOrders = new OrdersList();
	string name = "PlayerName";
	Player* p = new Player(name, territories, hand, listOfOrders);
	p->issueOrder();
	cout << *p << endl;
	p->toDefend();
	p->toAttack();

	delete(p);
	p = NULL;
}

void gameEngineDriver() {
	string command;
	GameEngine* myGame;
	myGame = new GameEngine();
	while (myGame->getStatus() == true) {
		myGame->getCurrentState()->toString();
		cout << endl;
		//test the stream insertion operator for Game States
		myGame->getCurrentState()->commandMessage();
		cout << endl;
		cout << "Please enter a command:";
		cin >> command;
		myGame->transit(command);
		cout << endl << "_____________________________________" << endl;
		cout << endl;
	}
	delete myGame;
}

