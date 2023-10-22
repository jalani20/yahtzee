

 //Juan Alanis

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//#################################################################################################

class Dice
{
private:
	int value;

public:
	// Randomly assigns a value between from 1 to 6 to the dice.
	void roll();
	int reveal() { return value; }

	// The autograder will set the values directly instead of calling roll() to avoid randomness!
	void setValue(int value) { this->value = value; }
};

void Dice::roll()
{
	value = rand() % 6 + 1;
}

//#################################################################################################

const int HAND_SIZE = 5;

class Hand
{
public:
	// Display the value of the five dice
	void show();

	// rolls the dice minus the dice the player chose to keep
	void play();
	// returns the dice
	Dice *getDice(int diceNum);

	// selection is the string of dice numbers that the player wants to keep.
	// For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
	void setSelection(string selection);

	Hand();

private:
	vector<Dice> dices;
	string diceSelection;
};

// default constructor
Hand::Hand()
{
	// Create the five dices and roll the            m
	for (int i = 0; i < 5; i++)
	{
		Dice die;
		die.roll();
		dices.push_back(die);
	}
}

void Hand::show()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Dice " << i << ": " << dices.at(i).reveal() << endl;
	}
}

void Hand::setSelection(string selection)
{
	diceSelection = selection;
}

void Hand::play()
{
	//  Go through the five dices and check to see if it's index matches the user selection
	for (int i = 0; i < 5; i++)
	{
		bool shouldRoll = true;
		for (int j = 0; j < diceSelection.size(); j++)
		{
			if (i + 1 == diceSelection[j] - 48)
			{
				shouldRoll = false;
				break;
			}
		}

		if (shouldRoll)
		{
			dices.at(i).roll();
		}
	}
}

// returns dice (getDice function)
// find the dice that corresponds to the index at the vector and return the memory address of the value
Dice *Hand::getDice(int diceNum)
{
	return &dices.at(diceNum);
}
//######################################################################

// List of rows in the board

const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE = 13;

class Game
{

public:
	// calcScore returns a score of a hand (5 dice) for given row in the board.
	// Note the rows are indexed from zero.
	// For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
	int calcScore(Hand *hand, int row);

	// Display the board
	void show();

	// Returns the score of the upper part of the board
	int getUpperScore();

	// Returns the score of the lower part of the board
	int getLowerScore();

	// Returns the bonus points
	int getBonusScore();

	// Returns the total score
	int getTotalScore();

	// Play a hand based on the selected row
	// This should call calcScore to get the score for the row. Then it should save the score in the rowPlayed variable using the row as the index
	void play(Hand *hand, int row);

	// Check to see if a row has been played or not (returns true if a row has been played)
	bool isPlayed(int row);

	// Check to see if all rows haven been played or not (returns true if all rows have been played)
	bool isFinished();

private:
	int rowPlayed[13] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // If the value is no longer -1, then that means we have played that row
};
// displays the board of the game
void Game::show()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		switch (i)
		{
		case 0:
			cout << "1. Ones:            ";
			break;
		case 1:
			cout << "2. Twos:            ";
			break;
		case 2:
			cout << "3. Threes:          ";
			break;
		case 3:
			cout << "4. Fours:           ";
			break;
		case 4:
			cout << "5. Fives:           ";
			break;
		case 5:
			cout << "6. Sixes:           ";
			break;
		case 6:
			cout << "7. Three of a kind: ";
			break;
		case 7:
			cout << "8. Four of a kind:  ";
			break;
		case 8:
			cout << "9. Full House:      ";
			break;
		case 9:
			cout << "10. Small straight: ";
			break;
		case 10:
			cout << "11. Large straight: ";
			break;
		case 11:
			cout << "12. Chance:         ";
			break;
		default:
			cout << "13. Yahtzee:        ";
		}

		if (rowPlayed[i] == -1)
			cout << 0 << endl;
		else
			cout << rowPlayed[i] << endl;

		if (i == 7)
		{
			cout << "Sum:                " << getUpperScore() << endl;
			cout << "Bonus:              " << getBonusScore() << endl;
		}
		else if (i == 12)
		{
			cout << "Total:              " << getTotalScore() << endl;
		}
	}
	// cout << "1. Ones:            " << rowPlayed[0] << endl;
	// cout << "2. Twos:            " << rowPlayed[1] << endl;
	// cout << "3. Threes:          " << rowPlayed[2] << endl;
	// cout << "4. Fours:           " << rowPlayed[3] << endl;
	// cout << "5. Fives:           " << rowPlayed[4] << endl;
	// cout << "6. Sixes:           " << rowPlayed[5] << endl;
	// cout << "Sum:                " << getUpperScore() << endl;
	// cout << "Bonus:              " << getBonusScore() << endl;
	// cout << "7. Three of a kind: " << rowPlayed[6] << endl;
	// cout << "8. Four of a kind:  " << rowPlayed[7] << endl;
	// cout << "9. Full house:      " << rowPlayed[8] << endl;
	// cout << "10. Small straight: " << rowPlayed[9] << endl;
	// cout << "11. Large straight: " << rowPlayed[10] << endl;
	// cout << "12. Chance:         " << rowPlayed[11] << endl;
	// cout << "13. Yahtzee :       " << rowPlayed[12] << endl;
	// cout << "Total:              " << getTotalScore() << endl;
}

int Game::calcScore(Hand *hand, int row)
{
	int sum = 0;
	if (row >= 0 && row < 6)
	{
		for (int i = 0; i < 5; i++)
		{ // implement the getDice
			if (hand->getDice(i)->reveal() == row + 1)
			{
				sum += row + 1;
			}
		}
	}
	else if (row == 6)
	{

		// Each index represents the number of times we found this dice value
		// 1  2  3  4  5  6
		//[0, 0, 0, 0, 0, 0]

		int matchingDices[6] = {0};
		for (int i = 0; i < 5; i++)
		{
			matchingDices[hand->getDice(i)->reveal() - 1] += 1;
		}

		for (int i = 0; i < 6; i++)
		{
			if (matchingDices[i] == 3)
			{
				sum += hand->getDice(0)->reveal() + hand->getDice(1)->reveal() + hand->getDice(2)->reveal() + hand->getDice(3)->reveal() + hand->getDice(4)->reveal();
			}
		}
	}
	else if (row == 7)
	{
		int matchingDices[6] = {0};
		for (int i = 0; i < 5; i++)
		{
			matchingDices[hand->getDice(i)->reveal() - 1] += 1;
		}

		for (int i = 0; i < 6; i++)
		{
			if (matchingDices[i] == 4)
			{
				sum += hand->getDice(0)->reveal() + hand->getDice(1)->reveal() + hand->getDice(2)->reveal() + hand->getDice(3)->reveal() + hand->getDice(4)->reveal();
			}
		}
	}
	else if (row == 8)
	{
		int matchingDices[6] = {0};
		for (int i = 0; i < 5; i++)
		{
			matchingDices[hand->getDice(i)->reveal() - 1] += 1;
		}
		bool fullHouseWithYahtzee = false;
		bool threeOfKind = false;
		bool pair = false;

		for (int i = 0; i < 6; i++)
		{
			if (matchingDices[i] == 3)
			{
				threeOfKind = true;
			}
			if (matchingDices[i] == 2)
			{
				pair = true;
			}
			if (threeOfKind && pair)
			{
				sum += 25;
				break;
			}
		}
	}
	else if (row == 9)
	{
		// Sort the dices and then check to see if there are 4 in increasing order
		vector<int> sortedDices;
		for (int i = 0; i < 5; i++)
		{
			sortedDices.push_back(hand->getDice(i)->reveal());
		}

		sort(sortedDices.begin(), sortedDices.end());

		// We only check the first 2 numbers since there is only 3 possible options after
		for (int i = 0; i < 2; i++)
		{
			if ((sortedDices.at(i + 1) == sortedDices.at(i) + 1) && (sortedDices.at(i + 2) == sortedDices.at(i) + 2) && (sortedDices.at(i + 3) == sortedDices.at(i) + 3))
			{
				sum += 30;
				break;
			}
		}
	}
	else if (row == 10)
	{
		vector<int> sortedDices;
		for (int i = 0; i < 5; i++)
		{
			sortedDices.push_back(hand->getDice(i)->reveal());
		}

		sort(sortedDices.begin(), sortedDices.end());

		if ((sortedDices.at(1) == sortedDices.at(0) + 1) && (sortedDices.at(2) == sortedDices.at(0) + 2) && (sortedDices.at(3) == sortedDices.at(0) + 3) && (sortedDices.at(4) == sortedDices.at(0) + 4))
		{
			sum += 40;
			
		}
	}
	else if (row == 11)
	{
		sum += hand->getDice(0)->reveal() + hand->getDice(1)->reveal() + hand->getDice(2)->reveal() + hand->getDice(3)->reveal() + hand->getDice(4)->reveal();
	}
	else if (row == 12)
	{

		if (hand->getDice(0)->reveal() == hand->getDice(1)->reveal() && hand->getDice(0)->reveal() == hand->getDice(2)->reveal() && hand->getDice(0)->reveal() == hand->getDice(3)->reveal() && hand->getDice(0)->reveal() == hand->getDice(4)->reveal())
		{
			sum += 50;
		}
	}

	return sum;
}

void Game::play(Hand *hand, int row)
{
	int sum = calcScore(hand, row);
	rowPlayed[row] = sum;
}

int Game::getUpperScore()
{
	int score = 0;

	for (int i = 0; i < 6; i++)
	{
		if (rowPlayed[i] != -1)
		{
			score += rowPlayed[i];
		}
	}
	return score;
}

int Game::getLowerScore()
{
	int score = 0;
	for (int i = 6; i < BOARD_SIZE; i++)
	{
		if (rowPlayed[i] != -1)
		{
			score += rowPlayed[i];
		}
	}
	return score;
}

int Game::getBonusScore()
{
	if (getUpperScore() >= 60)
	{
		return 30;
	}
	return 0;
}

int Game::getTotalScore()
{
	return getUpperScore() + getLowerScore() + getBonusScore();
}
// if false -> the row hasn't been played
bool Game::isPlayed(int row)
{
	if (rowPlayed[row] != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// if false -> at least one of the rows hasn't been played
// the issue here is that sometimes i can pick a combo even with the wrong hand
bool Game::isFinished()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (!isPlayed(i))
		{
			return false;
		}
	}
	return true;
}

//#######################################################################################

// The run function is the main loop of your program

void run()
{
	Game game;

	// Create the hand
	Hand *hand = new Hand();

	// hand->getDice(0)->setValue(1);
	// hand->getDice(1)->setValue(2);
	// hand->getDice(2)->setValue(3);
	// hand->getDice(3)->setValue(4);
	// hand->getDice(4)->setValue(5);

	while (!game.isFinished())
	{

		// Show the dices after the first roll
		hand->show();

		int rollCount = 1;
		string userInput = "";

		cout << "Keep Dice (s to stop rolling): ";
		cin >> userInput;

		// Ask the user to select dices to keep
		while (userInput != "s" && rollCount < 3)
		{
			// Set the selection the user inputs and then play the dice
			hand->setSelection(userInput);
			hand->play();

			// Print the dice values
			hand->show();
			rollCount++;

			cout << "Keep Dice (s to stop rolling): ";
			cin >> userInput;
		}

		game.show();

		// Ask user which combination they want to play
		int selectCombo;
		cout << "Select a combination to play: ";
		cin >> selectCombo;

		switch (selectCombo)
		{
			// calling play() instead of calcScore
		case 1:
			game.play(hand, ONES);
			break;
		case 2:
			game.play(hand, TWOS);
			break;
		case 3:
			game.play(hand, THREES);
			break;
		case 4:
			game.play(hand, FOURS);
			break;
		case 5:
			game.play(hand, FIVES);
			break;
		case 6:
			game.play(hand, SIXES);
			break;
		case 7:
			game.play(hand, THREE_OF_KIND);
			break;
		case 8:
			game.play(hand, FOUR_OF_KIND);
			break;
		case 9:
			game.play(hand, FULL_HOUSE);
			break;
		case 10:
			game.play(hand, SMALL_STRAIGHT);
			break;
		case 11:
			game.play(hand, LARGE_STRAIGHT);
			break;
		case 12:
			game.play(hand, CHANCE);
			break;
		default:
			game.play(hand, YAHTZEE);
		}

		// Show the game options
		game.show();
	}

	// Print the game board one last time to show the final score
	game.show();
}

// For these types of programs there exists many combinations that you might have missed.
// The best way to check them all is to write test cases for your program.
// Here I give you an example of checking large straight. You can design your own test cases for different parts.
/**
void test_case() {
	Game game;
	Hand* hand = new Hand();
	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(5);

	bool check1 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check1 = false;
	}
	if (check1) {
		cout << "check 1 passed\n";
	}

	hand->getDice(0)->setValue(2);
	hand->getDice(1)->setValue(6);
	hand->getDice(2)->setValue(4);
	hand->getDice(3)->setValue(3);
	hand->getDice(4)->setValue(5);

	bool check2 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check2 = false;
	}

	if (check2) {
		cout << "check 2 passed\n";
	}

	hand->getDice(0)->setValue(3);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(5);
	hand->getDice(3)->setValue(6);
	hand->getDice(4)->setValue(3);

	bool check3 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check3 = false;
	}

	if (check3) {
		cout << "check 3 passed\n";
	}

	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(6);

	bool check4 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check4 = false;
	}

	if (check4) {
		cout << "check 4 passed\n";
	}


}
**/
// THE AUTOGRADER WILL REPLACE THE MAIN FUNCTION.
// DO NOT ADD ANY LOGIC OF YOUR PROGRAM HERE.
int main()
{

	srand(time(0));
	run();
	//test_case();

	return 0;
}