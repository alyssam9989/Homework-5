#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

enum SkillLevel { BEGINNER = 1, AMATEUR, PRO };

struct BakingSession {
	string recipe;
	int quantity;
	double costEach;
	double total;
	SkillLevel skill;
};

// Function prototypes
void showBanner();
void setConsoleColor();
void resetConsoleColor();
string getRecipeName();
int getPositiveInt(string message);
double getPositiveDouble(string message);
double calculateTotalCost(int quantity, double costPerDessert);
void showMenu();
void saveReport(BakingSession sessions[], int count);
void viewReport();
void showRecommendation(const BakingSession& session);
SkillLevel getSkillLevel();

int main() {
	const int MAX_SESSIONS = 10;

	BakingSession sessionList[MAX_SESSIONS];
	int sessionCount = 0;
	int choice;

	setConsoleColor();
	showBanner();

	do {
		showMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			cin.ignore();
			sessionList[sessionCount].recipe = getRecipeName();
			sessionList[sessionCount].quantity = getPositiveInt("Enter quantity: ");
			sessionList[sessionCount].costEach = getPositiveDouble("Enter cost per dessert: ");
			sessionList[sessionCount].total =
				calculateTotalCost(
					sessionList[sessionCount].quantity,
					sessionList[sessionCount].costEach
				);
			sessionCount++;
			break;

		case 2:
			saveReport(sessionList, sessionCount);
			viewReport();
			break;

		case 3:
			if (sessionCount > 0)
				sessionList[sessionCount - 1].skill = getSkillLevel();
			break;

		case 4:
			if (sessionCount > 0)
				showRecommendation(sessionList[sessionCount - 1]);
			break;
		}
	} while (choice != 5);

	resetConsoleColor();
	return 0;
}

/* ================= IMPLEMENTATIONS ================= */

void setConsoleColor() {
	system("color 1");
}

void resetConsoleColor() {
	system("color 07");
}

void showBanner() {
	cout << "=============================\n";
	cout << " Baking Cost Calculator\n";
	cout << "=============================\n";
}

string getRecipeName() {
	string name;
	cout << "Enter recipe name: ";
	getline(cin, name);
	return name;
}

int getPositiveInt(string message) {
	int value;
	cout << message;
	cin >> value;
	return value;
}

double getPositiveDouble(string message) {
	double value;
	cout << message;
	cin >> value;
	return value;
}

double calculateTotalCost(int quantity, double costPerDessert) {
	return quantity * costPerDessert;
}

void showMenu() {
	cout << "\n1. Add Session\n";
	cout << "2. View Report\n";
	cout << "3. Set Skill Level\n";
	cout << "4. Recommendation\n";
	cout << "5. Quit\n";
	cout << "Choice: ";
}

SkillLevel getSkillLevel() {
	int choice;
	cout << "1.Beginner 2.Amateur 3.Pro: ";
	cin >> choice;
	return static_cast<SkillLevel>(choice);
}

void saveReport(BakingSession sessions[], int count) {
	ofstream file("report.txt");
	for (int i = 0; i < count; i++) {
		file << sessions[i].recipe << " "
			<< sessions[i].quantity << " "
			<< sessions[i].total << endl;
	}
}

void viewReport() {
	ifstream file("report.txt");
	string line;
	while (getline(file, line))
		cout << line << endl;
}

void showRecommendation(const BakingSession& session) {
	if (session.total > 50)
		cout << "Consider buying in bulk.\n";
	else
		cout << "Good cost efficiency.\n";
}