// Examples of pass by value reference and pointers in C++
#include <iostream>

using namespace std;


void passbyValueExample(int num) {

	num += 500;
	cout << "Inside Pass By Value, Modified Value = " << num << endl;

}

void passbyReferenceExample(int &num2) {
	num2 += 100;
	cout << "Inside Pass By Reference, Modified Value = " << num2 << endl;
}

void passbyPointerExample(int  *num3) {
	*num3 += 10;
	cout << "Inside Pass Bt Pointer, Modified Value = " << *num3 << endl;
}

int main() {
	int a = 5;
	int b = 5;
	int c = 5;


	passbyValueExample(a);
	cout << "After Pass By Value, Orginal Value = " << a << endl;

	passbyReferenceExample(b);
	cout << "After Pass By Value, Orginal Value = " << b << endl;

	passbyPointerExample(&c);
	cout << "After Pass By Value, Orginal Value = " << c << endl;



	return 0;
}