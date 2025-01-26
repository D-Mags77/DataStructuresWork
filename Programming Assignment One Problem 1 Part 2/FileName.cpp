//Simple exponential slope function to demonstrate recursion

#include <iostream>
using namespace std;



int calculateSquare(int x, int current = 0, int accumulator = 0) {
	if (current == abs(x)) {
		return accumulator;
	}
	return calculateSquare(x, current + 1, accumulator + abs(x));
}


int calculateYValue(int x) {

	int squareofX = calculateSquare(x);
	return squareofX + 7;

}


int main() {
	int x;
	cout << "Enter a value of x for the function y=x^2+7: ";
	cin >> x;

	int y = calculateYValue(x);

	cout << "y = " << x << "^2 + 7 = " << y << endl;

	return 0;

}