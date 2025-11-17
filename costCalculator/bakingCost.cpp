#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

void showBanner();
void setConsoleColor();
void resetConsoleColor();

string getRecipeName();
int getPositiveInt(string message);
double getPositiveDouble(string message);

double calculateTotalCost(int quantity, double costPerDessert);

void showMenu();
void saveReport(string recipe, int quantity, double cost, double totalCost);
void viewReport();
void showRecommendation(double totalCost, int quantity);

int main() {

	const int MAX_TITLE_WIDTH = 20;

	setConsoleColor();
	showBanner();
	resetConsoleColor();

	string recipeName;
	int numberOfDesserts = 0;
	double costPerDessert = 0.00;
	double totalCost = 0.00;
	int choice;

	do {
		showMenu();
		cin >> choice;

		while (cin.fail() || choice < 1 || choice > 4) {
			cin.clear(); 
			cin.ignore(1000, '\n');
			cout << "Invalid choice. Please enter 1-4: ";
			cin >> choice;
		}
	

	switch (choice) {
	
	case 1:
		cin.ignore();
		recipeName = getRecipeName();
		numberOfDesserts = getPositiveInt("Enter the quantity you plan to bake: ");
		costPerDessert = getPositiveDouble("Enter the cost per dessert ($): ");

		totalCost = calculateTotalCost(numberOfDesserts, costPerDessert);

		cout << "\n--- Summary ---\n";
		cout << fixed << setprecision(2);
		cout << left << setw(MAX_TITLE_WIDTH) << "Recipe Name: " << recipeName << endl;
		cout << left << setw(MAX_TITLE_WIDTH) << "Quantity: " << numberOfDesserts << endl;
		cout << left << setw(MAX_TITLE_WIDTH) << "Cost per dessert: " << "$" << costPerDessert << endl;
		cout << left << setw(MAX_TITLE_WIDTH) << "Total Cost: " << "$" << totalCost << endl;

		saveReport(recipeName, numberOfDesserts, costPerDessert, totalCost);
		break;

	case 2:
		viewReport();
		break;

	case 3:
		showRecommendation(totalCost, numberOfDesserts);
		break;

	case 4:
		cout << "Exiting program. Goodbye!\n";
		break;
	}

	} while (choice != 4);

	return 0;
 }

void setConsoleColor() {
	system("color B");
}

void resetConsoleColor() {
	system("color 07");
}

void showBanner() {
	cout << "===========================================\n";
	cout << "   Welcome to the Baking Cost Calculator   \n";
	cout << "===========================================\n";
}

string getRecipeName() {
	string name;
	do {
		cout << "Enter the name of your recipe: ";
		getline(cin, name);
		if (name == "")
			cout << "Recipe name cannot be empty.\n";
	} while (name == "");
	return name;
}

int getPositiveInt(string message) {
	int value;
	cout << message;
	cin >> value;
	while (cin.fail() || value <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Enter a positive number: ";
		cin >> value;
	}
	return value; 
}

double getPositiveDouble(string message) {
	double value;
	cout << message;
	cin >> value; 
	while (cin.fail() || value <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Enter a positive number: ";
		cin >> value;
	}
	return value;
}

double calculateTotalCost(int numberOfDesserts, double costPerDessert) {
	return numberOfDesserts * costPerDessert;
}

void showMenu() {
	cout << "\n--- Menu ---\n";
	cout << "1. Add a baking report\n";
	cout << "2. View baking report\n";
	cout << "3. Recommend baking level\n";
	cout << "4. Quit\n";
	cout << "Enter your choice: ";
}

void saveReport(string recipe, int numberOfDesserts, double costEach, double totalCost) {
	ofstream file("report.txt");

	if (!file) {
		cout << "ERROR: Could not open file.\n";
		return;
	}

	file << fixed << setprecision(2);
	file << "------ Baking Report ------\n";
	file << left << setw(20) << "Recipe Name: " << recipe << endl;
	file << left << setw(20) << "Quantity: " << numberOfDesserts << endl;
	file << left << setw(20) << "Individual Cost: $" << costEach << endl;
	file << left << setw(20) << "Total Cost: $" << totalCost << endl;

	cout << "Report saved to 'report.txt'.\n";
}

void viewReport() {
	ifstream file("report.txt");
	if (!file) {
		cout << "No report found. Please add a report first.\n";
		return;
	}

	string line;
	cout << "\n--- Viewing Report ---\n";
	while (getline(file, line)) {
		cout << line << endl;
	}
}

	void showRecommendation(double totalCost, int numberOfDesserts) {
		if (totalCost > 50 && numberOfDesserts >= 10) {
		cout << "Bake more to reduce cost per dessert.\n";
	}
	else if (totalCost <= 50 && numberOfDesserts >= 10) {
			cout << "You're baking efficiently!\n";
	}
	else {
			cout << "Keep baking and experimenting!\n";
	}
}
