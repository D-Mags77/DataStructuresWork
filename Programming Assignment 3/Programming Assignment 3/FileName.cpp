#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {

	int NumberOfQueries = 105;


	unordered_map<string, string> PhoneBook;

	string Query;
	string Number;
	string Name;

	for (int i = 0; i < NumberOfQueries; i++) {  

		cout << "Enter your action: add del find" << endl;
		cin >> Query;

		if (Query == "add") {
			

			cout << "You would like to add a name into the query. Enter it in the format number followed by name" << endl;
			cin >> Number;
			cin >> Name;

			PhoneBook[Number] = Name;
		}

		else if (Query == "del") {

			cout << "Enter the number that you would like to delete" << endl;
			cin >> Number;

			PhoneBook.erase(Number);
		}

		else if (Query == "find") {
			cout << "Enter the number you would like to find and I will give you the name of that person's number" << endl;
			cin >> Number;

			if (PhoneBook.find(Number) != PhoneBook.end()) {
				cout << PhoneBook[Number] << endl;
			}
			else {
				cout << "Not found" << endl;
			}
		}


	}


	return 0;
}