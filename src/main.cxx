#include "gamespace.h"

enum options {newgame, continuegame, quit, wrong};

options menu(char *menuList);
bool hasWon(gamespace &game);
void displayGame(gamespace &game);
char *topCard(stacks stack, char *str, gamespace &game);
int getNum(char *string);
options process(char *string);
bool sure();
void stackAll(gamespace &game);
const char homeMenu[] = "Home Menu Loaded:\n\n   >Start New Game\n   >Exit Program\n\n";
const char optionsMenu[] = "Options Menu Loaded:\n\n   >Start New Game\n   >Continue The Current Game\n   >Exit The Current Game\n\n";
const char fileName[] = "C:\\CommandLineSolitaire.dat";

int main()
{
	cout << "Welcome To Command Line Solitaire Version 1.1\n\n";
	
	options result = wrong;
	gamespace game;

	for (;;)
	{
		result = menu((char *)homeMenu);
		
		switch (result)
		{
		case newgame:
			cout << "\nStarting New Game. Please Wait\n";
			game.resetCards();
			game.shuffleDeal();

			game.flip();

			try
			{
				if (hasWon(game))
				{
					cout << "Congratulations!\nYou Won!\n\n";
					continue;
				}
				else
				{
					cout << "Sorry You Lost\nBetter Luck Next Time\n\n";
					continue;
				}
			}
			catch (char *ex)
			{
				if (!(strcmp(ex, "Quit!"))) return 0;
				else return 1;
			}
			break;
		case continuegame:
			cout << "There Is No Game To Continue\n";
			break;
		case quit:
			goto exit;
			break;
		case wrong:
			break;
		}
	}
	
exit:

	return 0;

}

options menu(char *menuList)
{
	char input[80];

	for(;;)
	{
		cout << menuList;
		cout << "   Please Enter Your Next Action:";
		cin.getline(input, sizeof input);

		if (process(input) == wrong) cout << "\nUnkown Command Entered. Please Try Again";
		else return (process(input));

		cout << "\n";	
	}
}

bool hasWon(gamespace &game)
{
	char input[80];

	for(;;)
	{
		displayGame(game);
		cout << "Enter Your Next Move:";
		cin.getline(input, sizeof input);
		cout << "\n";

		for(int i = 0; i < 80; i++)
		{
			if (!(input[i]))break;

			if ((input[i] >= 'A') && (input[i] <= 'Z')) input[i] += 32; 
		}

		char action[80];
		char arguments[3][30];

		int i = 0;

		for(; i < 80; i++)
		{
			if (!(input[i])){action[i] = '\0'; break;}
			if (input[i] == ';') {action[i] = '\0'; break;}

			action[i] = input[i];
		}

		i++;

		int j = 0;
		int k = 0;

		for (;(i < 80) && (j < 3); i++)
		{
			if (!(input[i])) {arguments[j][k] = '\0'; j++; break;}
			if (input[i] == ';')
			{
				arguments[j][k] = '\0';

				j++;				
				k = 0;
				continue;
			}

			arguments[j][k] = input[i];
			k++;
		}

		int argNum = j;

		bool errorFlag = false;

		
		if (!(strcmp(action, "move")))
		{
			card *location;
			card *destination;
			int numCards = 0;

			try
			{
				if ((argNum < 2) ||(argNum > 3)) throw "Incorrect Number Of Arguments";

				int i = 1;
				int j = 2;

				try
				{
					numCards = getNum(arguments[0]);
				}
				catch (char ex[])
				{
					throw ex;
				}
				if (numCards < 0)
				{
					numCards = 1;
					i--;
					j--;
				}
				if (numCards > 13)	throw "Incorrect Number Of Cards";


				if (!(strcmp(arguments[i], "one")))
				{
					location = &game.one[0];
				}
				else if (!(strcmp(arguments[i], "two")))
				{
					location = &game.two[0];
				}
				else if (!(strcmp(arguments[i], "three")))
				{
					location = &game.three[0];
				}
				else if (!(strcmp(arguments[i], "four")))
				{
					location = &game.four[0];
				}
				else if (!(strcmp(arguments[i], "five")))
				{
					location = &game.five[0];
				}
				else if (!(strcmp(arguments[i], "six")))
				{
					location = &game.six[0];
				}
				else if (!(strcmp(arguments[i], "seven")))
				{
					location = &game.seven[0];
				}
				else if (!(strcmp(arguments[i], "dealt")))
				{
					if (numCards !=1) throw "Can Only Move 1 Card From The Dealt Pile";
					location = &game.dealt[0];
				}
				else
				{
					throw "Incorrect Location";					
				}
				
				if (!(strcmp(arguments[j], "one")))
				{
					destination = &game.one[0];
				}
				else if (!(strcmp(arguments[j], "two")))
				{
					destination = &game.two[0];
				}
				else if (!(strcmp(arguments[j], "three")))
				{
					destination = &game.three[0];
				}
				else if (!(strcmp(arguments[j], "four")))
				{
					destination = &game.four[0];
				}
				else if (!(strcmp(arguments[j], "five")))
				{
					destination = &game.five[0];
				}
				else if (!(strcmp(arguments[j], "six")))
				{
					destination = &game.six[0];
				}
				else if (!(strcmp(arguments[j], "seven")))
				{
					destination = &game.seven[0];
				}
				else
				{
					throw "Incorrect Destination";					
				}				

				bool legal = game.move(location, destination, numCards, false, true);

				if (!legal)
				{
					throw "Illegal Move Attempted";
				}

			}
			catch (char ex[])
			{
				cout << "There Was An Error With The Argumnents Entered.\n";
				cout << ex;
				errorFlag = true;
			}
		}
		else if (!(strcmp(action, "flip")))
		{
			try
			{
				if (argNum != 1) throw "Incorrect Number Of Arguments";

				card *stack = 0;

				if (!(strcmp(arguments[0], "one")))
				{
					stack = &game.one[0];
				}
				else if (!(strcmp(arguments[0], "two")))
				{
					stack = &game.two[0];
				}
				else if (!(strcmp(arguments[0], "three")))
				{
					stack = &game.three[0];
				}
				else if (!(strcmp(arguments[0], "four")))
				{
					stack = &game.four[0];
				}
				else if (!(strcmp(arguments[0], "five")))
				{
					stack = &game.five[0];
				}
				else if (!(strcmp(arguments[0], "six")))
				{
					stack = &game.six[0];
				}
				else if (!(strcmp(arguments[0], "seven")))
				{
					stack = &game.seven[0];
				}
				else
				{
					throw "Incorrect Stack To Flip";					
				}

				game.flip(stack);
			}
			catch (char ex[])
			{
				cout << "There Was An Error With The Argumnents Entered.\n";
				cout << ex;
				errorFlag = true;
			}
		}
		else if (!(strcmp(action, "stack")))
		{
			try
			{
				if (argNum != 1) throw "Incorrect Number Of Arguments";

				card *stack = 0;

				if (!(strcmp(arguments[0], "one")))
				{
					stack = &game.one[0];
				}
				else if (!(strcmp(arguments[0], "two")))
				{
					stack = &game.two[0];
				}
				else if (!(strcmp(arguments[0], "three")))
				{
					stack = &game.three[0];
				}
				else if (!(strcmp(arguments[0], "four")))
				{
					stack = &game.four[0];
				}
				else if (!(strcmp(arguments[0], "five")))
				{
					stack = &game.five[0];
				}
				else if (!(strcmp(arguments[0], "six")))
				{
					stack = &game.six[0];
				}
				else if (!(strcmp(arguments[0], "seven")))
				{
					stack = &game.seven[0];
				}
				else if (!(strcmp(arguments[0], "dealt")))
				{
					stack = &game.dealt[0];
				}
				else if (!(strcmp(arguments[0], "all")))
				{
					stackAll(game);
					goto leaveNests;
				}
				else
				{
					throw "Unknown Pile Entered";					
				}

				bool go = game.stack(stack);

				if (!go) throw "Illegal Move Attempted";

			}
			catch (char ex[])
			{
				cout << "There Was An Error With The Argumnents Entered.\n";
				cout << ex;
				errorFlag = true;
			}
		}
		else if (!(strcmp(action, "deal")))
		{
			bool go = game.deal();
			if (!go)
			{
				cout << "No Cards Are Left To Deal";
				errorFlag = true;
			}
		}
		else if (!(strcmp(action, "menu")))
		{
			options result = wrong;
			result = menu((char *)optionsMenu);
			switch (result)
			{
			case newgame:
				game.resetCards();
				game.shuffleDeal();
				game.flip();
				continue;
				break;
			case continuegame:
				break;
			case quit:
				cout << "\nAre You Sure You Want To Quit The Current Game?:";
				if (sure()) return false;
				break;
			case wrong:
				break;
			}
		}
		else if (!(strcmp(action, "quit!")))
		{
			throw "Quit!";
		}
		else
		{
			cout << "Unknown Action Entered\n";
			cout << "Please Try Again";
			errorFlag = true;			
		}

		if (errorFlag)
		{
			cout << "\n";
			system("pause");
			cout << "\n";
		}
leaveNests:


		if (game.fullStacks())
		{
			displayGame(game);
			return true;
		}
	}
}

void displayGame(gamespace &game)
{
	char string[5] = "";
	cout << "\nLast Dealt: |" << topCard(deckDealt, string, game);
	cout <<  "|		Current Stacks: |"<< topCard(stackSpades, string, game);
	cout << "| |" << topCard(stackHearts, string, game);
	cout << "| |" << topCard(stackClubs, string, game);
	cout << "| |" << topCard(stackDiamonds, string, game) << "|\n";
	cout << "Playng Field:\n\n";
	cout << " one     two     three   four    five    six    seven\n";

	char value[4];

	card tmp;

	for (int i = 1; i <= 20; i++)
	{
		if (i < 14)
		{
			tmp = game.getCard(pileOne, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";

		if (i < 15)
		{
			tmp = game.getCard(pileTwo, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";


		if (i < 16)
		{
			tmp = game.getCard(pileThree, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";

		if (i < 17)
		{
			tmp = game.getCard(pileFour, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";

		if (i < 18)
		{
			tmp = game.getCard(pileFive, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";
		
		if (i < 19)
		{
			tmp = game.getCard(pileSix, i, false);

			if (tmp.getSuit() == empty) cout << "        ";
			else if (!(tmp.isVisible)) cout << "|   |   ";
			else
			{
				cout << "|";
				tmp.dumpValue(value);
				cout << value;
				cout << "|   ";
			}
		}
		else cout << "      ";

		tmp = game.getCard(pileSeven, i, false);

		if (tmp.getSuit() == empty) cout << "        \n";
		else if (!(tmp.isVisible)) cout << "|   |\n";
		else
		{
			cout << "|";
			tmp.dumpValue(value);
			cout << value;
			cout << "|\n";
		}
	}	

}

char *topCard(stacks stack, char *str, gamespace &game)
{
	card tmp = game.getCard(stack, 1);

	tmp.dumpValue(str);		

	return str;
}

int getNum(char *string)
{
	char *initloc = string;

	while (*string != '\0') {string++;}

	if (initloc == string) throw "No Number Was Entered";

	int num = 0;
	int i = 1;
	do
	{
		string--;

		if ((*string < '0') || (*string > '9'))
		{
			num = -10;
			break;
		}

		num += (i * ((int)(*string) - 48));
		i *= 10;
	}
	while (string != initloc);

	return num;
}

options process(char *string)
{
	int i = 0;
	while (*string != '\0')
	{
		if ((*string >= 'A') && (*string <='Z'))
		{
			*string += 32;
		}
		string++;
		i++;
	}

	for (;i > 0; i--) {string--;}

	if (!(strcmp(string, "new"))) return newgame;
	else if (*string == 'n') return newgame;
	else if (!(strcmp(string, "continue"))) return continuegame;
	else if (!(strcmp(string, "quit"))) return quit;
	else if (!(strcmp(string, "exit"))) return quit;
	else if (*string == 'q') return quit;

	return wrong;
}

bool sure()
{
	char input[80];

	for (;;)
	{
		cin.getline(input, sizeof input);

		switch (input[0])
		{
		case 'y':
		case 'Y':
			return true;
		case 'n':
		case 'N':
			return false;
		default:
			cout << "\n\nUnknown Answer. Try Again:";
		}
	}

}

void stackAll(gamespace &game)
{
	bool moves = true;
	while (moves)
	{
		moves = false;
		
		if (game.stack(game.one)) moves = true;
		if (game.stack(game.two)) moves = true;
		if (game.stack(game.three)) moves = true;
		if (game.stack(game.four)) moves = true;
		if (game.stack(game.five)) moves = true;
		if (game.stack(game.six)) moves = true;
		if (game.stack(game.seven)) moves = true;
	}
}