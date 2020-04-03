#include <iostream>
#include <string>
using namespace std;

int main() {
	if ("Help" > "help")
		cout << "uppercase >>";
	else
		cout << "...";

	char arr[3] = { 1, 0, 1 };
	if (arr[0] == 1)
		cout << "=1" << endl;
	else
		cout << "NO!" << endl;
}