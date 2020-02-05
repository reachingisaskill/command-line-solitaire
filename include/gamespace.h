#include "card.h"

enum stacks {pileOne, pileTwo, pileThree, pileFour, pileFive, pileSix, pileSeven, stackSpades, stackHearts, stackClubs, stackDiamonds, deckMain, deckDealt};

class gamespace
{
	int arraySize(stacks stack);
	void clearCards();
	void setUp();
	int dealNum;
	card *getStackFromEnum(stacks stack);
	card deck[53], spades[14], hearts[14], clubs[14], diamonds[14];
public:
	gamespace();
	card one[14], two[15], three[16], four[17], five[18], six[19], seven[20], dealt[25];
	card getCard(stacks location, int num, bool fromBottom = true);
	void resetCards();
	bool move(card *location, card *destination, int numCards, bool changeVisibility = false, bool isUser = false);
	bool deal();
	void shuffleDeal();
	bool stack(card *stack);
	void flip();
	void flip(card *stack);	
	bool fullStacks();
	int getDealNum() {return dealNum;}
	void setDealtNum(int newNum) {dealNum = newNum;}
	friend void stackAll(gamespace &game);
};

gamespace::gamespace()
{
	this->setUp();
}

card gamespace::getCard(stacks location, int num, bool fromBottom)
{
	if (num < 1) throw "Out Of Bounds Exception";
	if (num > arraySize(location)) throw "Out Of Bounds Exception";

	card result;
	card *stack = getStackFromEnum(location);

	if (fromBottom)
	{
		card *initLoc = stack;

		while(stack->getSuit() != empty) {stack++;}

		if (initLoc != stack) 
		{
			int i = 0;
			while (i < num)
			{
				stack--;
				i++;
				if (stack == initLoc) break;
			}

			if (i != num) throw "Out Of Bounds Exception";

			result = *stack;
		}
	}
	else
	{
		for (int i = 1; i < num; i++)
		{
			stack++;
		}

		result = *stack;
	}

	return result;
}

void gamespace::clearCards()
{
	card temp;

	for (int i = 0; i < 14; i++)
	{
		this->spades[i] = temp;
	}

	for (int i = 0; i < 14; i++)
	{
		this->hearts[i] = temp;
	}

	for (int i = 0; i < 14; i++)
	{
		this->clubs[i] = temp;
	}

	for (int i = 0; i < 14; i++)
	{
		this->diamonds[i] = temp;
	}

	for (int i = 0; i < 14; i++)
	{
		this->one[i] = temp;
	}

	for (int i = 0; i < 15; i++)
	{
		this->two[i] = temp;
	}

	for (int i = 0; i < 16; i++)
	{
		this->three[i] = temp;
	}

	for (int i = 0; i < 17; i++)
	{
		this->four[i] = temp;
	}

	for (int i = 0; i < 18; i++)
	{
		this->five[i] = temp;
	}

	for (int i = 0; i < 19; i++)
	{
		this->six[i] = temp;
	}

	for (int i = 0; i < 20; i++)
	{
		this->seven[i] = temp;
	}

	for (int i = 0; i < 25; i++)
	{
		this->dealt[i] = temp;
	}
}

void gamespace::setUp()
{
	this->dealNum = 3;

	int v = 1;
	int s = 0;
	int num = 0;

	for (; num < 52; num++)
	{
		suits t = (suits)s;

		card temp(v, t);

		this->deck[num] = temp;

		if (v == 13)
		{
			s++;
			v = 1;
		}
		else v++;
	};
}

void gamespace::resetCards()
{
	this->clearCards();
	this->setUp();
}

bool gamespace::move(card *location, card *destination, int numCards, bool changeVisibility, bool isUser)
{
	if (destination == location) return false;

	card *initloc = location;
	card *initdest = destination;

	while(location->getSuit() != empty) {location++;}

	for(int i = 0;;location--)
	{
		if (i == numCards) break;
		if (initloc == location)
		{
			numCards = i;
			break;
		}
		i++;
	};

	if (!(location->isVisible) && (isUser)) return false;

	while(destination->getSuit() != empty) {destination++;}

	if ((isUser) && (initdest != destination))
	{
		destination--;

		if (!(destination->isVisible)) return false;

		if ((destination->isRed()) == (location->isRed())) return false;

		if ((destination->getValue() - 1) != location->getValue()) return false;

		destination++;
	}

	card tmp;

	if (changeVisibility)
	{
		for (int i = 0; i <= numCards;i++)
		{
			tmp = *location;
			*location = *destination;
			tmp.isVisible = !(tmp.isVisible);
			*destination = tmp;

			location++;
			destination++;
		};
	}
	else
	{
		for (int i = 0; i < numCards;i++)
		{
			tmp = *location;
			*location = *destination;
			*destination = tmp;

			location++;
			destination++;
		};
	}

	return true;
}

bool gamespace::deal()
{
	bool flag = false;
	card *location = 0;

retry:

	location = &deck[0];

	int i = 0;
	while (location->getSuit() != empty)
	{
		location++;
		i++;
	}

	if ((i < dealNum) && (i != 0))
	{		
		for (int j = 0; j < i; j++)
		{
			move(deck,dealt, 1, true);
			return true;
		}
	}
	else if (i != 0)
	{
		for (int j = 0; j < dealNum; j++) move(deck, dealt, 1, true);
		return true;
	}

	if (flag) return false;

	for (int j = 0; j < 25;j++)
	{
		if (!(move(dealt, deck, 1, true))) break;
	}

	flag = true;
	goto retry;
}

void gamespace::shuffleDeal()
{	
	card temp;
	int r = 0;

	for (int i = 0; i < 52; i++)
	{
		r = (rand() %52);

		if (r == i) continue;

		temp = deck[i];
		deck[i] = deck[r];
		deck[r] = temp;
	};

	move(deck, seven, 7);
	move(deck, six, 6);
	move(deck, five, 5);
	move(deck, four, 4);
	move(deck, three, 3);
	move(deck, two, 2);
	move(deck, one, 1);
	
}
bool gamespace::stack(card *stack)
{
	card *initpos = stack;

	while (stack->getSuit() != empty) {stack++;}

	if (initpos == stack) return false;

	stack--;

	card *dest = 0;

	switch (stack->getSuit())
	{
	case spade:
		dest = &this->spades[0];
		break;
	case heart:
		dest = &this->hearts[0];
		break;
	case club:
		dest = &this->clubs[0];
		break;
	case diamond:
		dest = &this->diamonds[0];
		break;
	}

	int i = 1;

	while (dest->getSuit() != empty)
	{
		dest++;
		i++;
	}
	
	if (stack->getValue() != i) return false;
	else
	{
		if (move(stack, dest, 1)) return true;
		else return false;
	}
}

void gamespace::flip()
{
	flip(this->seven);
	flip(this->six);
	flip(this->five);
	flip(this->four);
	flip(this->three);
	flip(this->two);
	flip(this->one);
}

void gamespace::flip(card *stack)
{
	card *initloc = stack;

	while (stack->getSuit() != empty) {stack ++;}

	if (initloc == stack) return;

	stack--;
	stack->isVisible = true;
}

bool gamespace::fullStacks()
{
	card *Card = &this->spades[0];
	int num = 0;

	while (Card->getSuit() != empty) {Card++;}
	Card--;

	if (Card->getValue() == 13) num++;

	Card = &this->hearts[0];

	while (Card->getSuit() != empty) {Card++;}
	Card--;

	if (Card->getValue() == 13) num++;

	Card = &this->clubs[0];

	while (Card->getSuit() != empty) {Card++;}
	Card--;

	if (Card->getValue() == 13) num++;

	Card = &this->diamonds[0];

	while (Card->getSuit() != empty) {Card++;}
	Card--;

	if (Card->getValue() == 13) num++;

	if (num == 4) return true;
	else return false;
}

card *gamespace::getStackFromEnum(stacks stack)
{
	switch (stack)
	{
	case pileOne:
		return &this->one[0];
		break;
	case pileTwo:
		return &this->two[0];
		break;
	case pileThree:
		return &this->three[0];
		break;
	case pileFour:
		return &this->four[0];
		break;
	case pileFive:
		return &this->five[0];
		break;
	case pileSix:
		return &this->six[0];
		break;
	case pileSeven:
		return &this->seven[0];
		break;
	case stackSpades:
		return &this->spades[0];
		break;
	case stackHearts:
		return &this->hearts[0];
		break;
	case stackClubs:
		return &this->clubs[0];
		break;
	case stackDiamonds:
		return &this->diamonds[0];
		break;
	case deckMain:
		return &this->deck[0];
		break;
	case deckDealt:
		return &this->dealt[0];
		break;
	default:
		throw "Fuck Off!";
	}
}


int gamespace::arraySize(stacks stack)
{
	switch (stack)
	{
	case pileOne:
		return 14;
		break;
	case pileTwo:
		return 15;
		break;
	case pileThree:
		return 16;
		break;
	case pileFour:
		return 17;
		break;
	case pileFive:
		return 18;
		break;
	case pileSix:
		return 19;
		break;
	case pileSeven:
		return 20;
		break;
	case stackSpades:
		return 14;
		break;
	case stackHearts:
		return 14;
		break;
	case stackClubs:
		return 14;
		break;
	case stackDiamonds:
		return 14;
		break;
	case deckMain:
		return 53;
		break;
	case deckDealt:
		return 25;
		break;
	default:
		throw "Fuck Off!";
	}
}
