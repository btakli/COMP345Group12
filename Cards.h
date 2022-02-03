#pragma once
#include <iostream>
#include <string>
#include<vector>

class Card {
public:
	Card();
	Card(std::string type);
	Card(Card& otherCard); //Copy constructor
	~Card(); //Destructor

	Card& operator = (const Card& rightSide); //assignment operator

	std::string getType() const;
	//Order play() Play the card and return an order TODO!!!

private:
	std::string* _type; //The card type
};

std::ostream& operator<<(std::ostream& strm, const Card& card); //stream insertion operator overload for Card

class BombCard : public Card {
public:
	BombCard();
	BombCard(BombCard& otherCard); //Copy constructor
	~BombCard();  //Destructor
	BombCard& operator = (const BombCard& rightSide); //assignment operator

};

class BlockadeCard : public Card {
public:
	BlockadeCard();
	BlockadeCard(BlockadeCard& otherCard); //Copy constructor
	~BlockadeCard(); //Destructor
	BlockadeCard& operator = (const BlockadeCard& rightSide); //assignment operator

};

class AirliftCard : public Card {
public:
	AirliftCard();
	AirliftCard(AirliftCard& otherCard); //Copy constructor
	~AirliftCard(); //Destructor
	AirliftCard& operator = (const AirliftCard& rightSide); //assignment operator

};

class DiplomacyCard : public Card {
public:
	DiplomacyCard();
	DiplomacyCard(DiplomacyCard& otherCard); //Copy constructor
	~DiplomacyCard(); //Destructor
	DiplomacyCard& operator = (const DiplomacyCard& rightSide); //assignment operator

};

class Deck {
public:
	Deck();
	Deck(std::vector<Card*> listOfCards); //Set up the deck with a predefined list of cards;
	Deck(Deck& otherDeck); //Copy constructor
	~Deck(); //Destructor
	Deck& operator = (const Deck& rightSide); //assignment operator

	std::vector<Card*> getCards(); //Gets the list of cards in the deck

	Card* draw(); //Returns a reference to a random card and removes it from the deck.
	void returnToDeck(Card* card);
private:
	std::vector<Card*>* _cards; //The list of cards
	friend std::ostream& operator<<(std::ostream& strm, const Deck& deck); //stream insertion operator overload for Deck


};


class Hand {
public:
	Hand();
	Hand(Hand& otherHand); //Copy constructor
	~Hand(); //Destructor
	Hand& operator = (const Hand& rightSide); //assignment operator
	void addCard(Card* card); //add a card to you hand
	std::vector<Card*> getCards(); //gets all cards in the hand
	Card* returnCardToDeck(int index); //Return the card pointer and remove it from _cards based on passed in indes

private:
	std::vector<Card*>* _cards;
	friend std::ostream& operator<<(std::ostream& strm, const Hand& hand); //stream insertion operator overload for Hand

};
