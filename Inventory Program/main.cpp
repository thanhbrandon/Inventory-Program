#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Function prototype
bool reRun();
void readItems(fstream&);
void addItem(fstream&, string);
void editItem(fstream&, int);

int main() {
	
	fstream dataFile;
	bool programOn = true; // Keeps program running
	do {
		bool mainMenuOn = true; // Keeps program

		do {
			system("CLS"); // Clears console
			// Creates main menu
			cout << "What would you like to do?\n\n";
			cout << "1) View/Edit existing inventory items\n";
			cout << "2) Add new item\n";
			cout << "3) Exit program\n\n";
			cout << "Enter your selection: ";

			// Initializes variables to be used in menu
			int selection;
			cin >> selection;
			switch (selection) {
			case 1:
				readItems(dataFile); // Prints file contents
				int selectedLine;
				char yOn;
				cout << "Do you want to edit a line (Y/N)? "; // Asks user if they want to edit file
				cin >> yOn;
				if (toupper(yOn) == 'Y') {
					cout << "What line do you want to edit? ";
					cin >> selectedLine;
					editItem(dataFile, selectedLine); // Edits item info
				}
				break;
			case 2:
				addItem(dataFile, "inventory.txt"); // Adds item to end of textfile
				break;
			case 3:
				mainMenuOn = false; // Ends current program
				break;
			}
		} while (mainMenuOn == true);
		programOn = reRun(); // Asks user if they want to rerun the program
	} while (programOn == true);
	
	return 0;
}

bool reRun()
{
	bool result; 	// true to end program, false to run again
	char runAgain;	// prompt for re-running program

	// prompt to run program again
	cout << "\n\nWould you like to run program again (Y/N) ? ";
	cin >> runAgain;

	// validate input for Y, y, N, or n
	while (toupper(runAgain) != 'Y' && toupper(runAgain) != 'N')
	{
		cout << "\n **  Invalid entry  **  Please enter 'Y' or 'N'\n\n";
		cout << "Would you like to run program again (Y/N) ? ";
		cin.ignore();  // clear keybard cache
		cin >> runAgain;
	}

	if (toupper(runAgain) == 'Y')
	{
		result = true;
		system("CLS"); // Clears console
	}
	else
		result = false;

	return result;
}

void readItems(fstream &file) {
	file.open("inventory.txt", ios::in);
	string line;
	int count = 0;
	// Outputs header
	cout << left << endl;;
	cout << setw(30 )<< "Project Description";
	cout << setw(30) << "Quantity on hand";
	cout << setw(30) << "Wholesale Cost";
	cout << setw(30) << "Retail Cost";
	cout << setw(30) << "Date Added to Inventory\n";
	cout << setfill('-') << setw(144) << "\n" << endl << setfill(' ');
	// While loop to print file contents
	while (file >> line) {
		cout << setw(30) << line;
		count++;
		if (count == 5) {
			cout << endl;
			count = 0;
		}
	}
	cout << endl;
	file.close(); // Close the file
}

void addItem(fstream& file, string filename) {
	file.open(filename, ios::app); // Opens file
	
	// Variables to hold info
	string stringTemp;
	int intTemp = -1;
	double doubleTemp = -1.00;
	
	// Asks user for item information
	cout << left;
	cout << "What is the Item Description?: ";
	cin >> stringTemp;
	file  << stringTemp << "\t";
	do {
		cout << "What is the Quantity on Hand? (Enter a number greater than 0): ";
		cin >> intTemp;
	} while (intTemp < 0);
	file  << intTemp << "\t";
	do {
		cout << "What is the Wholesale Cost? (Enter a number greater than 0): ";
		cin >> doubleTemp;
	} while (doubleTemp < 0);
	file << fixed << setprecision(2);
	file << doubleTemp << "\t";
	do {
		cout << "What is the Retail Cost? (Enter a number greater than 0): ";
		cin >> doubleTemp;
	} while (doubleTemp < 0);
	file << fixed << setprecision(2);
	file << doubleTemp << "\t";

	int month = 0;
	int day = 0;
	int year = 0;

	do {
		cout << "What is the Month Added to Inventory? (Enter number between 1-12): ";
		cin >> month;
	} while (month < 1 || month > 12);
	do {
		cout << "What is the Day Added to Inventory? (Enter number between 1-31): ";
		cin >> day;
	} while (day < 1 || day > 31);
	do {
		cout << "What is the Year Added to Inventory? (Enter a year greater than 1900): ";
		cin >> year;
	} while (year < 1900);
	file << month << "/" << day << "/" << year << "\n";
	file.close(); // Close the file
}

void editItem(fstream& file, int selectedLine) {
	file.open("inventory.txt", ios::in); // Opens inventory file to read
	fstream outFile;
	outFile.open("tempFile.txt", ios::out); // Opens tempFile to write
	int count = 0;
	string line;
	selectedLine *= 5;
	selectedLine -= 5;
	selectedLine++;
	int endOfLine = selectedLine + 4;
	while (file >> line) {
		count++;
		if (count == selectedLine) { //When line user wants to edit is reach, it asks for new information
			string stringTemp;
			int intTemp = -1;
			double doubleTemp = -1.00;

			cout << left;
			cout << "What is the Item Description?: ";
			cin >> stringTemp;
			outFile << stringTemp << "\t";
			do {
				cout << "What is the Quantity on Hand? (Enter a number greater than 0): ";
				cin >> intTemp;
			} while (intTemp < 0);
			outFile << intTemp << "\t";
			do {
				cout << "What is the Wholesale Cost? (Enter a number greater than 0): ";
				cin >> doubleTemp;
			} while (doubleTemp < 0);
			outFile << fixed << setprecision(2);
			outFile << doubleTemp << "\t";
			do {
				cout << "What is the Retail Cost? (Enter a number greater than 0): ";
				cin >> doubleTemp;
			} while (doubleTemp < 0);
			outFile << fixed << setprecision(2);
			outFile << doubleTemp << "\t";

			int month = 0;
			int day = 0;
			int year = 0;

			do {
				cout << "What is the Month Added to Inventory? (Enter number between 1-12): ";
				cin >> month;
			} while (month < 1 || month > 12);
			do {
				cout << "What is the Day Added to Inventory? (Enter number between 1-31): ";
				cin >> day;
			} while (day < 1 || day > 31);
			do {
				cout << "What is the Year Added to Inventory? (Enter a year greater than 1900): ";
				cin >> year;
			} while (year < 1900);
			outFile << month << "/" << day << "/" << year << "\n";
		}
		else if (count == selectedLine + 1 && selectedLine != endOfLine){ // Skips info of deleted items
			selectedLine++;
		}
		else {
			outFile << line << "\t"; // Adds old file info into new one
		}
	}
	file.close(); // Close the file
	outFile.close(); // Close the file
	file.open("inventory.txt", ios::out);
	outFile.open("tempFile.txt", ios::in);
	count = 0;
	while (outFile >> line) { // While loops overwrites old file with tempFile
		file << line << "\t";
		count++;
		if (count == 5) {
			file << endl;
			count = 0;
		}
	}

	file.close(); // Close the file
	outFile.close(); // Close the file
}
