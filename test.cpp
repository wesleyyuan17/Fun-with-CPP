#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int factorial(int n) {
	int f = 1;
	for (int i = n; i > 0; i--) {
		f *= i;
	}
	return(f);
}

int main() {

	string input;
	int n;

	cout << "Input Number. \n";
	getline(cin, input);
	stringstream(input) >> n;

	cout << n << "!: " << factorial(n) << endl;
	return 0;
}