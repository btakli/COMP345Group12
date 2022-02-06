#include "Cards.h"
#include <iostream>
#include <string>
using std::string;
using std::vector;

std::ostream& operator<<(std::ostream& strm, const Card& card)
{
	return strm << "Card of Type: " << card.getType();
}

std::ostream& operator<<(std::ostream& strm, const Deck& deck)
{
	strm << "This deck contains the following cards:" << std::endl;
	for (int i = 0; i < deck._cards->size(); i++)
		strm << '\t' << *(deck._cards->at(i)) << std::endl;
	return strm;
}

std::ostream& operator<<(std::ostream& strm, const Hand& hand)
{
	strm << "This hand contains the following cards:" << std::endl;
	for (int i = 0; i < hand._cards->size(); i++)
		strm << '\t' << *(hand._cards->at(i)) << std::endl;
	return strm;
}

Card::Card() : _type(new string("DEFAULT CARD"))
{
}

Card::Card(string type)
{
	this->_type = new string(type);
}


Card::Card(const Card& otherCard)
{
	this->_type = new string(*(otherCard._type));
}

Card::~Card()
{
	delete(_type);
}

Card& Card::operator=(const Card& rightSide)
{
	this->_type = new string(*(rightSide._type));
	return *this;
}

Card* Card::clone() const 
{
	return new Card(*this);
}

string Card::getType() const
{
	return *(_type);
}

Order* Card::play()
{
	return new Order();
}



BombCard::BombCard() : Card("bomb")
{

}

BombCard::BombCard(const BombCard& otherCard) : Card(otherCard)
{
}

BombCard::~BombCard()
{

}

BombCard& BombCard::operator=(const BombCard& rightSide)
{
	Card::operator=(rightSide);
	//TODO add other necessary items if need be.
	return *this;
}

Bomb* BombCard::play()
{
	return new Bomb();
}

BombCard* BombCard::clone() const
{
	return new BombCard(*this);
}

BlockadeCard::BlockadeCard() : Card("blockade")
{
}

BlockadeCard::BlockadeCard(const BlockadeCard& otherCard) : Card(otherCard)
{
}

BlockadeCard::~BlockadeCard()
{
}

BlockadeCard& BlockadeCard::operator=(const BlockadeCard& rightSide)
{
	Card::operator=(rightSide);
	//TODO add other necessary items if need be.
	return *this;
}

Blockade* BlockadeCard::play()
{
	return new Blockade();
}

BlockadeCard* BlockadeCard::clone() const
{
	return new BlockadeCard(*this);
}

AirliftCard::AirliftCard() : Card("airlift")
{
}

AirliftCard::AirliftCard(const AirliftCard& otherCard) : Card(otherCard)
{
}

AirliftCard::~AirliftCard()
{
}

AirliftCard& AirliftCard::operator=(const AirliftCard& rightSide)
{
	Card::operator=(rightSide);
	//TODO add other necessary items if need be.
	return *this;
}

Airlift* AirliftCard::play()
{
	return new Airlift();
}

AirliftCard* AirliftCard::clone() const
{
	return new AirliftCard(*this);
}

DiplomacyCard::DiplomacyCard() : Card("diplomacy")
{
}

DiplomacyCard::DiplomacyCard(const DiplomacyCard& otherCard) : Card(otherCard)
{
}

DiplomacyCard::~DiplomacyCard()
{
}

DiplomacyCard& DiplomacyCard::operator=(const DiplomacyCard& rightSide)
{
	Card::operator=(rightSide);
	//TODO add other necessary items if need be.
	return *this;
}

Negotiate* DiplomacyCard::play()
{
	return new Negotiate();
}

DiplomacyCard* DiplomacyCard::clone() const
{
	return new DiplomacyCard(*this);
}

Deck::Deck()
{
	_cards = new vector<Card*>();
}

Deck::Deck(vector<Card*> listOfCards)
{
	_cards = new vector<Card*>();
	for (int i = 0; i < listOfCards.size(); i++) //Making a deep copy of the list
	{
		Card* cardToCopy = listOfCards[i];
		//Call the clone() method of the card in order to get the constructor of the right member in the polymorphic hierarchy
		_cards->push_back(cardToCopy->clone());
	}
}

Deck::Deck(const Deck& otherDeck) : Deck(*otherDeck._cards) //Since the only thing we need to copy is _cards, get the other deck's cards!
{
}

Deck::~Deck()
{
	//Delete all current cards and clear the vector.
	for (int i = 0; i < _cards->size(); i++)
		delete(_cards->at(i));
	_cards->clear();
	delete(_cards);
}

Deck& Deck::operator=(const Deck& rightSide)
{
	//Delete all current cards and clear the vector.
	for (int i = 0; i < _cards->size(); i++)
		delete(_cards->at(i));
	_cards->clear();
	vector<Card*> otherVector = *(rightSide._cards);
	for (int i = 0; i < otherVector.size(); i++) //Making a deep copy of the list
	{
		
		Card cardToCopy = *(otherVector[i]);
		//Call clone in order to get the right constructor called in the polymorphic hierarchy
		_cards->push_back(cardToCopy.clone());
	}
	return *this;
}

vector<Card*> Deck::getCards()
{
	return *_cards;
}

Card* Deck::draw()
{
	//If the deck is not empty
	if (_cards->size() != 0) {
		srand(clock()); //Generate a random number, use clock as the seed
		int randomIndex = rand() % _cards->size(); //Generate a random index to ge the card from
		Card* card = _cards->at(randomIndex); //Since we have a pointer to a vector, we can use at() to get the item we want
		_cards->erase(_cards->begin() + randomIndex); //remove the card from the deck (need to use begin(), so that random index is an offset from that.
		return card;
	}
	else {
		std::cout << "The Deck is Empty";
		return nullptr;
	}

}

void Deck::returnToDeck(Card* card)
{
	_cards->push_back(card);
}

bool Deck::isEmpty()
{
	return _cards->size() == 0;
}

Hand::Hand(): _cards(new vector<Card*>())
{
}

Hand::Hand(const Hand& otherHand)
{
	_cards = new vector<Card*>();
	for (int i = 0; i < otherHand._cards->size(); i++) //Making a deep copy of the list
	{
		Card* cardToCopy = otherHand._cards->at(i); //dereferencing it
		//Using clone in order to get the right polymorphic copy constructor called
		_cards->push_back(cardToCopy->clone());
	}
}

Hand::~Hand()
{
	//Delete all current cards and clear the vector.
	for (int i = 0; i < _cards->size(); i++)
		delete(_cards->at(i));
	_cards->clear();
	delete(_cards);
}

Hand& Hand::operator=(const Hand& rightSide)
{
	//Delete all current cards and clear the vector.
	for (int i = 0; i < _cards->size(); i++)
		delete(_cards->at(i));
	_cards->clear();

	vector<Card*> otherVector = *(rightSide._cards);
	for (int i = 0; i < otherVector.size(); i++) //Making a deep copy of the list
	{

		Card* cardToCopy = otherVector[i];
		//Calling clone in order to get the right polymorphic copy constructor called
		_cards->push_back(cardToCopy->clone());
	}
	return *this;
}

void Hand::addCard(Card* card)
{
	_cards->push_back(card);
}

vector<Card*> Hand::getCards()
{
	return *_cards;
}

int Hand::size()
{
	return _cards->size();
}

Card* Hand::getCard(int index)
{
	return _cards->at(index);
}

Card* Hand::returnCardToDeck(int index)
{
	Card* card = _cards->at(index);
	_cards->erase(_cards->begin() + index); //remove card from the vector
	return card;
}

Order* Hand::playAndReturnToDeck(int index, Deck* deck)
{
	Card* card = getCard(index); //Get the card
	Order* order = card->play(); //Set the order as the one returned by the play method.
	deck->returnToDeck(returnCardToDeck(index)); //Return the card to the deck and remove it from your hand.
	return order; 
}

