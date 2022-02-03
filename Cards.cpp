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


Card::Card(Card& otherCard)
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

string Card::getType() const
{
	return *(_type);
}

BombCard::BombCard() : Card("bomb")
{

}

BombCard::BombCard(BombCard& otherCard) : Card(otherCard)
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

BlockadeCard::BlockadeCard() : Card("blockade")
{
}

BlockadeCard::BlockadeCard(BlockadeCard& otherCard) : Card(otherCard)
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

AirliftCard::AirliftCard() : Card("airlift")
{
}

AirliftCard::AirliftCard(AirliftCard& otherCard) : Card(otherCard)
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

DiplomacyCard::DiplomacyCard() : Card("diplomacy")
{
}

DiplomacyCard::DiplomacyCard(DiplomacyCard& otherCard) : Card(otherCard)
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

Deck::Deck()
{
	_cards = new vector<Card*>();
}

Deck::Deck(vector<Card*> listOfCards)
{
	_cards = new vector<Card*>();
	for (int i = 0; i < listOfCards.size(); i++) //Making a deep copy of the list
	{
		Card cardToCopy = *(listOfCards[i]); //dereferencing it
		_cards->push_back(new Card(cardToCopy));
	}
}

Deck::Deck(Deck& otherDeck) : Deck(*otherDeck._cards) //Since the only thing we need to copy is _cards, get the other deck's cards!
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
		_cards->push_back(new Card(cardToCopy));
	}
	return *this;
}

vector<Card*> Deck::getCards()
{
	return *_cards;
}

Card* Deck::draw()
{
	srand(clock()); //Generate a random number, use clock as the seed
	int randomIndex = rand() % _cards->size(); //Generate a random index to ge the card from
	Card* card = _cards->at(randomIndex); //Since we have a pointer to a vector, we can use at() to get the item we want
	_cards->erase(_cards->begin() + randomIndex); //remove the card from the deck (need to use begin(), so that random index is an offset from that.
	return card;
}

Hand::Hand(): _cards(new vector<Card*>())
{
}

Hand::Hand(Hand& otherHand)
{
	_cards = new vector<Card*>();
	for (int i = 0; i < otherHand._cards->size(); i++) //Making a deep copy of the list
	{
		Card cardToCopy = *(otherHand._cards->at(i)); //dereferencing it
		_cards->push_back(new Card(cardToCopy));
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

		Card cardToCopy = *(otherVector[i]);
		_cards->push_back(new Card(cardToCopy));
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

