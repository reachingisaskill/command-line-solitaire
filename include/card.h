#include "standard.h"


class card
{
	int value;
	suits suit;
public:
	card(int Value, suits Suit);
	card();
	void dumpValue(char *str);	
	int getValue() {return value;}
	bool isVisible;
	suits getSuit(){return suit;}
	bool isRed();
};

card::card(int Value, suits Suit)
{
	this->value = Value;
	this->suit = Suit;
	this->isVisible = false;
}

card::card()
{
	this->value = 100;
	this->suit = empty;
	this->isVisible = false;
}

void card::dumpValue(char *str)
{
	switch (this->getValue())
	{
	case 1:
		*str = ' ';
		str++;
		*str = 'A';
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		*str = ' ';
		str++;
		*str = (char)(this->getValue() + 48);
		break;
	case 10:
		*str = '1';
		str++;
		*str = '0';
		break;
	case 11:
		*str = ' ';
		str++;
		*str = 'J';
		break;
	case 12:
		*str = ' ';
		str++;
		*str = 'Q';
		break;
	case 13:
		*str = ' ';
		str++;
		*str = 'K';
		break;
	}

	str++;

	switch (this->getSuit())
	{
	case spade:
		*str = 'S';
		break;
	case heart:
		*str = 'H';
		break;
	case club:
		*str = 'C';
		break;
	case diamond:
		*str = 'D';
		break;
	default:
		str--;
		for (int i = 0; i < 3; i++)
		{
			*str = ' ';
			str++;
		}
		*str = '\0';
		return;
		break;
	}

	str++;
	*str = '\0';	
}

bool card::isRed()
{
	if ((suit == heart) || (suit == diamond)) return true;
	else return false;
}
