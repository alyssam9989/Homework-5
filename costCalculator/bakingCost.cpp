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
void saveReport(string recipe[], int qty[], double costEach[], double totals[], int count);
void viewReport();
void showRecommendation(double totalCost, int quantity);

enum SkillLevel { BEGINNER = 1, AMATEUR, PRO };

SkillLevel getSkillLevel();

int main() {

	const int MAX_SESSIONS = 10;
	string recipes[MAX_SESSIONS];
	int quantities[MAX_SESSIONS];
	double costs[MAX_SESSIONS];
	double totals[MAX_SESSIONS];
	int sessionCount = 0;

	setConsoleColor();
	showBanner();
	resetConsoleColor();

	int choice;

	do {
		showMenu();
		cin >> choice;

		while (cin.fail() || choice < 1 || choice > 5) {
			cin.clear(); 
			cin.ignore(1000, '\n');
			cout << "Invalid choice. Please enter 1-5: ";
			cin >> choice;
		}
	

	switch (choice) {
	
	case 1:
		cin.ignore();
		recipes[sessionCount] = getRecipeName();
		quantities[sessionCount] = getPositiveInt("Enter the quantity you plan to bake: ");
		costs[sessionCount] = getPositiveDouble("Enter the cost per dessert ($): ");

		totals[sessionCount] = calculateTotalCost(quantities[sessionCount], costs[sessionCount]);

		cout << "\n--- Summary ---\n";
		cout << fixed << setprecision(2);
		cout << left << setw(22) << "Recipe Name: " << recipes[sessionCount] << endl;
		cout << left << setw(22) << "Quantity: " << quantities[sessionCount] << endl;
		cout << left << setw(22) << "Cost per dessert: " << "$" << costs[sessionCount] << endl;
		cout << left << setw(22) << "Total Cost: " << "$" << totals[sessionCount] << endl;

		sessionCount++;

		break;

	case 2:
		saveReport(recipes, quantities, costs, totals, sessionCount);
		viewReport();
		break;

	case 3:
		if (sessionCount == 0) {
			cout << "Add a session first.\n";
			break;
		}

		{
			SkillLevel level = getSkillLevel();

			switch (level) {
			case BEGINNER: 
				cout << "Beginner tip: Start with cookies or cupcakes.\n";
				break;

			case AMATEUR: 
				cout << "Amateur tip: Try pastries or layered cakes!\n";
				break;

			case PRO:
				cout << "Experiment with artisan breads.\n";
				break;
			}
		}

		if (totals[sessionCount - 1] > 40 && quantities[sessionCount - 1] > 12) {
			cout << "You're baking a lot, consider purchasing ingredients in bulk!\n";
		}
		else if (totals[sessionCount - 1] < 20 && quantities[sessionCount - 1] >= 5) {
			cout << "Great efficiency! Keep it up!\n";
		}

		break;

	case 4:
		if (sessionCount == 0) {
			cout << "Add a session first.\n";
			break;
		}
		showRecommendation(totals[sessionCount - 1], quantities[sessionCount - 1]);
		break;

	case 5:
		cout << "Goodbye\n";
		break; 
	}

	} while (choice != 5);

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
	cout << "1. Add a Baking Session\n";
	cout << "2. View Baking Report\n";
	cout << "3. Get Skill Level Advice\n";
	cout << "4. Cost Efficiency Recommendation\n";
	cout << "5. Quit\n";
	cout << "Enter your choice: ";
}

SkillLevel getSkillLevel() {
	int choice;
	cout << "\nChoose skill level:\n";
	cout << "1. Beginner\n";
	cout << "2. Amateur\n";
	cout << "3. Pro\n";
	cout << "Enter choice: ";
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > 3) {
		cin.clear();
		cin.ignore(1000, 'n');
		cout << "Invalid. Enter 1-3: ";
		cin >> choice;
	}
	return static_cast<SkillLevel>(choice);
}

void saveReport(string recipes[], int qty[], double costEach[], double totals[], int count) {
	ofstream file("report.txt");

	if (!file) {
		cout << "ERROR: Could not open file.\n";
		return;
	}

	file << fixed << setprecision(2);
	file << "------ Baking Report ------\n";

	for (int i = 0; i < count; i++) {
		file << left << setw(20) << "Recipe: " << recipes[i] << endl;
		file << left << setw(20) << "Quantity: " << qty[i] << endl;
		file << left << setw(20) << "Individual Cost: $" << costEach[i] << endl;
		file << left << setw(20) << "Total Cost: $" << totals[i] << endl;
	}

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
