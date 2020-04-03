#include <iostream>
using namespace std;


//Recursive fibonacci seq function, returns nth fib #
int fib(int n) {
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

void returnImmed() {
	return;
}

void f1() {
	returnImmed();

	cout << "code past returnImmed" << endl; //this is called
}

//Returns 2^x
int powerOfTwo(int x) {
	if (x == 1)
		return 2;

	return 2 * powerOfTwo(x - 1);
}

//Find sum of array
int sumArray(int arr[], int size) {
	if (size == 0)
		return 0;

	return arr[0] + sumArray(arr + 1, size - 1);
}

int main()
{
	cout << powerOfTwo(5) << endl;
	int arr[3] = { 1, 2, 3 };
	cout << sumArray(arr, 2) << endl;

	struct Test {
		int value = 5;
	};

	Test* pointerArrTest = new Test[5];
	delete[] pointerArrTest;
	cerr << "delete once" << endl;
	pointerArrTest = nullptr; //OK! do this, don't delete 2x or problems
	delete[] pointerArrTest;
	cerr << "delete twice" << endl;


	/*int arr[3] = { 1, 2, 3 };
	cout << *arr << endl;
	//arr++; not allowed
	cout << *arr << endl; */

	/*const char* str = "C+ B+ B- A C A- A C- B+ D B";
	int count = 0;
	const char* p;
	for (p = str; *p != '\0' && count < 6; p++)
		if (*p == ' ')
			count++; //count = 6 (space after A-), p point to A (char after the space)
	for (; *p != '\0' && *p != ' '; p++)
		cout << *p; //next char is space, so prints out A
	cout << '\n'; */


	//cout << char(65) << endl; //ASCII A = 65

	/*int i = 4; //Test for loop condition
	for (int j = i-1; j>-1; j--) {
		cout << "i = " << i << " j = " << j << endl;
	} */

	//cout << fib(5) << endl;
}