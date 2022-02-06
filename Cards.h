#pragma once
#include <iostream>
#include <string>
#include<vector>
#include "Orders.h"

//Base class for all cards
class Card {
public:
	//Copy constructor
	Card();
	//Constructor taking in a string which sets the type, used by the others.
	Card(std::string type);
	//Copy constructor
	Card(const Card& otherCard);
	//Destructor, VIRTUAL DUE TO INHERITANCE STRUCTURE AND USE OF POINTERS/POLYMORPHISM https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~Card();
	//assignment operator
	virtual Card& operator = (const Card& rightSide);
	//Clone function, crucial for polymorphic calls to the copy constructor.
	virtual Card* clone() const;
	//Get the type of the card as a string
	std::string getType() const;
	//Play the card and return an order.
	virtual Order* play(); 

private:
	//The card type
	std::string* _type;
};
//stream insertion operator overload for Card
std::ostream& operator<<(std::ostream& strm, const Card& card);

class BombCard : public Card {
public:
	//Default constructor
	BombCard();
	//Copy constructor
	BombCard(const BombCard& otherCard);
	//Destructor, VIRTUAL DUE TO INHERITANCE STRUCTURE AND USE OF POINTERS/POLYMORPHISM https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~BombCard();
	//assignment operator
	virtual BombCard& operator = (const BombCard& rightSide);
	//Play the card and return a Bomb order.
	Bomb* play(); 
	//Clone function, crucial for polymorphic calls to the copy constructor.
	virtual BombCard* clone() const;
};

class BlockadeCard : public Card {
public:
	//Default Constructor
	BlockadeCard();
	//Copy constructor
	BlockadeCard(const BlockadeCard& otherCard);
	//Destructor, VIRTUAL DUE TO INHERITANCE STRUCTURE AND USE OF POINTERS/POLYMORPHISM https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~BlockadeCard();
	//assignment operator
	virtual BlockadeCard& operator = (const BlockadeCard& rightSide);
	//Play the card and return a Blockade order.
	Blockade* play(); 
	//Clone function, crucial for polymorphic calls to the copy constructor.
	virtual BlockadeCard* clone() const;
};

class AirliftCard : public Card {
public:
	//Default Constructor
	AirliftCard();
	//Copy constructor
	AirliftCard(const AirliftCard& otherCard);
	//Destructor, VIRTUAL DUE TO INHERITANCE STRUCTURE AND USE OF POINTERS/POLYMORPHISM https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~AirliftCard();
	//assignment operator
	virtual AirliftCard& operator = (const AirliftCard& rightSide);
	//Play the card and return an Airlift order.
	Airlift* play();
	//Clone function, crucial for polymorphic calls to the copy constructor.
	virtual AirliftCard* clone() const;
};

class DiplomacyCard : public Card {
public:
	//Default constructor
	DiplomacyCard();
	//Copy constructor
	DiplomacyCard(const DiplomacyCard& otherCard);
	//Destructor, VIRTUAL DUE TO INHERITANCE STRUCTURE AND USE OF POINTERS/POLYMORPHISM https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~DiplomacyCard();
	//assignment operator
	virtual DiplomacyCard& operator = (const DiplomacyCard& rightSide);
	//Play the card and return a Negotiate order.
	Negotiate* play();
	//Clone function, crucial for polymorphic calls to the copy constructor.
	virtual DiplomacyCard *clone() const;
};

class Deck {
public:
	//Default constructor
	Deck();
	//Set up the deck with a predefined list of cards
	Deck(std::vector<Card*> listOfCards);
	//Copy constructor
	Deck(const Deck& otherDeck);
	//Destructor
	~Deck();
	//assignment operator
	Deck& operator = (const Deck& rightSide);

	//Gets the list of cards in the deck
	std::vector<Card*> getCards();

	//Returns a reference to a random card and removes it from the deck.
	Card* draw();
	//Return a card to the deck, adding it to the _cards list.
	void returnToDeck(Card* card);
	//Return if the internal list of cards is empty. Wrapper method
	bool isEmpty(); 
private:
	//The list of cards
	std::vector<Card*>* _cards;
	//stream insertion operator overload for Deck
	friend std::ostream& operator<<(std::ostream& strm, const Deck& deck);


};


class Hand {
public:
	//Default constructor
	Hand();
	//Copy constructor
	Hand(const Hand& otherHand);
	//Destructor
	~Hand();
	//assignment operator
	Hand& operator = (const Hand& rightSide);
	//add a card to your hand
	void addCard(Card* card); 
	//gets all cards in the hand
	std::vector<Card*> getCards();
	//Return the size of the hand.
	int size();
	//Get a card at a specific index in the hand
	Card* getCard(int index); 
	//Return the card pointer and remove it from _cards based on passed in index
	Card* returnCardToDeck(int index);
	//Play a card and return it to the passed in deck. Returns an Order.
	Order* playAndReturnToDeck(int index, Deck* deck);
private:
	std::vector<Card*>* _cards;
	//stream insertion operator overload for Hand
	friend std::ostream& operator<<(std::ostream& strm, const Hand& hand);

};
