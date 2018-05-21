//Program designed to help game masters for Fantasy Flight's Star Wars table top role playing game.
//Lets the user access multiple saves, and allows them to create character profiles, including wounds, wound threshold, strain, strain threshold. It also allows the user to change the amount of wounds and strain the character has taken. 

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
//prototypes
void writeCharacters(string saveGame, char overWrite);
void loadCharacters(string saveGame, string nameofCharacters[20], int healthAndStrain[20][4], int &fileRows);
void updateHealthAndStrain(string saveGame, string nameOfCharacters[20], int healthAndStrain[20][4], int fileRows);

int main(int argc, char *argv[]) {
	
	char overWriteGame = 'N';
	char newOrExistingGame = 'N';
	char loadPrevious = 'Y';
	string saveGame = "";
	int whichSave = 0;
	string names[20] = {"","","","","","","","","","","","","","","","","","","",""};
	int woundsAndStrain[20][4];
	int totalRows = 0;
	int loadOrNew = 0;
	int menuChoice = 1;
	ifstream inFile;
	string save1 = "";
	string save2 = "";
	string save3 = "";
	
	//Determining whether file is there and is empty or not.
	inFile.open("saveGame1.txt");
	if (inFile.is_open())
	{
		getline(inFile, save1, '#');
		if (save1 != "")
		{
			save1 = "Save: ";
		}
		else 
		{
			save1 = "Empty: ";
		}
	}
	else 
	{
		save1 = "Empty: ";
	}
	inFile.close();
	inFile.open("saveGame2.txt");
		if (inFile.is_open())
		{
			getline(inFile, save2, '#');
			if (save2 != "")
			{
				save2 = "Save: ";
			}
			else 
			{
				save2 = "Empty: ";
			}
		}
		else 
			{
				save2 = "Empty: ";
			}
		inFile.close();
		inFile.open("saveGame3.txt");
			if (inFile.is_open())
			{
				getline(inFile, save3, '#');
				if (save3 != "")
				{
					save3 = "Save: ";
				}
				else 
				{
					save3 = "Empty: ";
				}
			}
			else 
				{
					save3 = "Empty: ";
				}
			inFile.close();
	
	//Opening menu to choose new game or load game.
	cout << "1) New Game" << endl << "2) Load Game" << endl << "Enter 1 or 2: ";
	cin >> loadOrNew;
	while (loadOrNew < 1 && loadOrNew > 2)
	{
		cout << endl << "Invalid Entry!" << endl << endl;
		cout << "1) New Game" << endl << "2) Load Game" << endl << "Enter 1 or 2: ";
			cin >> loadOrNew;
	}
	switch (loadOrNew)
	{
		case 1: //New Game
			cout << "Save Game: " << endl << save1 << "1" << endl << save2 << "2" << endl << save3 << "3" << endl << "Enter save: ";
				cin >> whichSave;
				switch (whichSave)
				{
					case 1:
						saveGame = "saveGame1";
						break;
					case 2:
						saveGame = "saveGame2";
						break;
					case 3:
						saveGame = "saveGame3";
						break;
				}
			overWriteGame = 'Y';
			break;
		case 2: //load game
			cout << "Save Game: " << endl << save1 << "1" << endl << save2 << "2" << endl << save3 << "3" << endl << "Selection: ";
				cin >> whichSave;
				switch (whichSave)
				{
					case 1:
						saveGame = "saveGame1";
						break;
					case 2:
						saveGame = "saveGame2";
						break;
					case 3:
						saveGame = "savegame3";
						break;
				}
				overWriteGame = 'N';
				loadCharacters(saveGame, names, woundsAndStrain, totalRows);
			break;
	}
	//Beginning of Main Menu
	while (menuChoice > 0)
	{
		cout << endl << endl << "Main Menu" << endl << "1) Add characters" << endl << "2) Change wounds and strain taken" << endl << "3) Display Characters with their wounds and strain" << endl << "Selection (0 to exit): ";
		cin >> menuChoice;
		while (menuChoice < 1 && menuChoice > 3)
		{
			cout << "Invalid Entry!" << endl << endl;
			cout << endl << endl << "Main Menu" << endl << "1) Add characters" << endl << "2) Change wounds and strain taken" << endl << "3) Display Characters with their wounds and strain" << endl << "Selection (0 to exit): ";
			cin >> menuChoice;
		}
		switch (menuChoice)
		{
			case 1:
				writeCharacters(saveGame, overWriteGame);
				break;
			case 2:
				updateHealthAndStrain(saveGame, names, woundsAndStrain, totalRows);
				break;
			case 3:
				loadCharacters(saveGame, names, woundsAndStrain, totalRows);
				break;
		}	
	}
}
//Function that updates the characters health and strain
void updateHealthAndStrain(string saveGame, string nameOfCharacters[20], int healthAndStrain[20][4], int fileRows)
{
	int characterNumber = 1;
	cout << endl << "Which character?" << endl;
	while (characterNumber > 0)
	{
		for (int sub = 1; sub < fileRows; sub += 1)
		{
			cout << sub << ") " << nameOfCharacters[sub] << endl;
		}
		cout << "Enter character number: ";
		cin >> characterNumber;
		if (characterNumber > 0 && characterNumber < fileRows)
		{
			cout << "Change wounds or strain? (W/S) ";
			char woundOrStrain = 'W';
			cin >> woundOrStrain;
			woundOrStrain = toupper(woundOrStrain);
			if (woundOrStrain == 'W')
			{
				cout << endl << "Wounds threshold: " << healthAndStrain[characterNumber][1] << endl;
				cout << "New wounds taken: ";
				cin >> healthAndStrain[characterNumber][0];
			}
			else if (woundOrStrain == 'S')
			{
				cout << endl << "Strain threshold: " << healthAndStrain[characterNumber][3] << endl;
				cout << "New strain taken: ";
				cin >> healthAndStrain[characterNumber][2];
			}
			else 
			{
				cout << "Error" << endl;
			}
		}
		else
		{
			cout << endl << "Invalid character number!" << endl;
		}
		cout << endl << "Change another character's wounds or strain? " << endl << "If no enter 0 or a negative number." << endl << endl;
	}
	ofstream outFile;
	outFile.open(saveGame + ".txt");
	if (outFile.is_open())
	{
		for (int sub = 1; sub < fileRows; sub += 1)
		{
			outFile << nameOfCharacters[sub] << "#";
			for (int column = 0; column <= 3; column += 1)
			{
				if (column < 3)
				outFile << healthAndStrain[sub][column] << "#";
				if (column == 3)
				outFile << healthAndStrain[sub][column] << endl;
			}
		}
	}
	outFile.close();
}
//Function that loads the characters from the txt file.
void loadCharacters(string saveGame, string nameofCharacters[20], int healthAndStrain[20][4], int &fileRows)
{
	ifstream inFile;
	int subscript = 0;
	string name[20] = {"","","","","","","","","","","","","","","","","","","",""};
	int healthNStrain[20][4];
	int column = 0;
	int row = 0;
	string temp = "";
	string empty = "";
	inFile.open(saveGame + ".txt");
	
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, empty);
			subscript += 1;
		}
		inFile.close();
		inFile.open(saveGame + ".txt");
		
		for (row = 1; row < subscript; row += 1)
		{
			getline(inFile, name[row], '#');
			cout << endl << name[row] << endl;
			for (column = 0; column <= 3; column += 1)
			{
				if (column < 3)
				{
					getline(inFile, temp, '#');
					healthNStrain[row][column] = static_cast<int>(stod(temp));
				}
				if (column == 3)
				{
					getline(inFile, temp, '\n');
					healthNStrain[row][column] = static_cast<int>(stod(temp));
				}
				{
					{
					switch (column)
						{
						case 0:
							cout << "   Wounds: " << healthNStrain[row][column] << endl << "   ";
							break;
						case 1:
							cout << "Wound Threshold: " << healthNStrain[row][column] << endl << "   ";
							break;
						case 2:
							cout << "Strain: " << healthNStrain[row][column] << endl << "   ";
							break;
						case 3:
							cout << "Strain Threshold: " << healthNStrain[row][column] << endl << "   ";
							break;
						}
					}
				}
			}
		}
		inFile.close();
	}
	std::copy(name, name+20, nameofCharacters);
	std::copy(&healthNStrain[0][0], &healthNStrain[0][0]+20*4, &healthAndStrain[0][0]);
	fileRows = subscript;
}
//Function that
void writeCharacters(string saveGame, char overWrite)
{
	char anotherCharacter = 'Y';
	string name = "";
	string wound = "";
	string wThreshold = "";
	string strain = "";
	string strainThreshold = "";
	ofstream outFile;
	
	if (overWrite == 'N')
		outFile.open(saveGame + ".txt", ios::app);
	else
		outFile.open(saveGame + ".txt");
	
	cout << "Enter player character? (Y/N): ";
	while (anotherCharacter == 'Y')
	{
		cin >> anotherCharacter;
		anotherCharacter = toupper(anotherCharacter);
		
		if (anotherCharacter == 'Y')
		{
			if (outFile.is_open())
			{
				cin.ignore();
				cout << "Character Name: ";
				getline(cin, name);
				cout << endl << name << "'s wounds taken: ";
				getline(cin, wound);
				cout << endl << name << "'s wound threshold: ";
				getline(cin, wThreshold);
				cout << endl << name << "'s strain taken: ";
				getline(cin, strain);
				cout << endl << name << "'s strain threshold: ";
				getline(cin, strainThreshold);
				outFile << name << "#" << wound << "#" << wThreshold << "#" << strain << "#" << strainThreshold << endl;
			}
		}
		cout << "Enter another player character? (Y/N)" << endl;
	}
	outFile.close();
}