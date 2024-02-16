#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

//Namespace Access
using namespace std;

//Global Definitions
typedef int menuSize;
ifstream inFile;

//Constant Global Variables
const int MENU_SIZE = 100;			//Amount of items on the menu
const double TAX_RATE = 7.5 / 100;	//Tax rate

//Global Variables
char q;

//Struct Definition
struct menuItemType
{
	string menuItem;
	double menuPrice;
};

//Function Prototypes
void getData(menuItemType menu[], menuSize& counter);
void showMenu(menuItemType menu[], menuSize counter);
void printCheck(const menuItemType menu[], const int order[][2], int orderCount);
bool getSelection(char selection);
bool validateSelection(char selection);

int main()
{
	menuItemType menu[MENU_SIZE];	//Define menu variable of menuItemType struct
	menuSize counter = 0;			//Define and initialize counter to zero

	cout << "Anthony Cantu\t" << "L3-5\t" << "L3-5.exe" << endl;

	getData(menu, counter);		//Retrieve data from data file
	showMenu(menu, counter);	//Display menu

	cout << "Press any key to Exit.";
	cin.ignore(2, '\n');
	cin.get(q);
	return 0;
}

void getData(menuItemType menu[], menuSize& counter)
{
	inFile.open("L3-5Data.txt");	//Open file

	if (!inFile.is_open())			//If file cannot open, display error and terminate
	{
		cout << "Error: Unable to find the file required to process this application." << endl;
		cout << "Press any key to Exit.";
		cin.ignore(2, '\n');
		cin.get(q);
		exit(1);
	}
	
	//Read data from file and store into appropriate variables.
	getline(inFile, menu[counter].menuItem);
	while (!inFile.eof())
	{
		inFile >> menu[counter].menuPrice;
		inFile.ignore(25, '\n');
		inFile.clear();
		counter++;
		getline(inFile, menu[counter].menuItem);
	}

	inFile.close();	//Close file
}

void showMenu(menuItemType menu[], menuSize counter)
{
	char selection;				//Variable to store users selection
	int orderCount = 0;			//Variable to store the amount of orders placed
	int order[MENU_SIZE][2];	//Array to store what items were ordered and how many
	double totalCost = 0.00;	//Variable to store the total cost of items ordered
	bool validInput;			//Variable to check if users input was valid

	cout << right;
	cout << setfill(' ');
	cout << fixed << setprecision(2);
	cout << setw(9) << "" << "Welcome to Johnny's Resturant" << endl;
	cout << setw(9) << "" << "----Today's Menu----" << endl;
	for (int i = 0; i < counter; i++)
	{
		//Display menu to user
		cout << setw(9) << left << "" << i + 1 << ": " 
			 << setw(16) << left << menu[i].menuItem
			 << "$" << menu[i].menuPrice << endl;
	}

	cout << endl; //Line Break

	cout << "You can make up to 8 different selections" << endl;
	cout << "Do you want to make a selection Y/y (Yes), N/n (No): ";
	do
	{
		cin >> selection;
		if (validateSelection(selection))	//Check if input is valid
		{
			if (getSelection(selection))	//Get what selection was made
			{
				cout << endl; //Line Break
				for (int i = 0; i < 2; i++) //Ask user for input twice
				{
					do
					{
						if (!cin) //Clear input stream if cin is no longer valid
						{
							cin.clear();
							cin.ignore(200, '\n');
						}
						cout << (i == 0 ? "Enter item number: " : "How many orders: ");
						cin >> order[orderCount][i == 0 ? 0 : 1]; //Insert input into column 0 first loop, then column 1 second loop
						switch (i)
						{
						case 0:
							//Check if integer was entered and if its within range
							if (!cin || order[orderCount][i] < 1
								|| order[orderCount][i] > counter) 
							{
								cout << "Invalid entry! Please try again!" << endl;
								validInput = false;
								continue;
							}
							else
								validInput = true;
						case 1:
							//Only check if a integer was entered
							if (!cin) 
							{
								cout << "Invalid entry! Please try again!" << endl;
								validInput = false;
								continue;
							}
							else
								validInput = true;
						}
					} while (!validInput);
				}
			}
			else
				break; //Break from loop if selection was N/n
		}
		else
		{
			//Display error message and reprompt if user input was invalid
			cout << "Invalid selection! Please try again!" << endl
				<< "Do you want to make a selection Y/y (Yes), N/n (No): ";
			continue;
		}
		
		orderCount++;	//Add to number of items ordered
		if (orderCount == 8)
			break; //Break from loop if 8 orders have been placed

		cout << endl; //Line Break
		cout << "Select another item Y/y (Yes), N/n (No): ";
	} while (!getSelection(selection) || orderCount < 8);

	//End of menu selection
	cout << endl; //Line Break
	printCheck(menu, order, orderCount);
}

void printCheck(const menuItemType menu[], const int order[][2], int orderCount)
{
	double totalCost = 0.00;

	cout << setw(9) << "" << "Welcome to Johnny's Resturant" << endl;
	cout << setw(15) << "" << "Please pay cashier" << endl;
	for (int i = 0; i < orderCount; i++)
	{
		//Display all items ordered with total amount
		cout << setw(9) << left << "" << setw(2) << left << order[i][1]
			<< setw(16) << left << menu[order[i][0] - 1].menuItem
			<< "$" << (menu[order[i][0] - 1].menuPrice * order[i][1]) << endl;
		totalCost += (menu[order[i][0] - 1].menuPrice * order[i][1]);
	}
	cout << setw(12) << left << "" << "Tax"
		<< setw(13) << left << "" << "$" << totalCost * TAX_RATE << endl;
	cout << setw(12) << left << "" << "Amount Due"
		<< setw(6) << left << "" << "$" << totalCost + (totalCost * TAX_RATE) << endl;

	cout << endl; //Line Break
}

bool getSelection(char selection)	//Get users selection
{
	switch (selection)
	{
	case 'Y':
	case 'y':
		return true;
	case 'N':
	case 'n':
		return false;
	}
}

bool validateSelection(char selection)	//Validate user input a valid selection
{
	switch (selection)
	{
	case 'Y':
	case 'y':
	case 'N':
	case 'n':
		return true;
	default:
		return false;
	}
}