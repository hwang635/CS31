#include <iostream>
using namespace std;

/* 1a. Should print out 30 20 10, each on a new line
int main() {
	int arr[3] = { 5, 10, 15 };
	int* ptr = arr; //int* means address of some int, address of int = address of a[0]
	
	*ptr = 30; //*ptr means value that ptr points to, value at (address ptr = address of a[0]) = 30
	*(ptr+1) = 20; //compiler automatically makes this +1 address spot, value @ address of a[1] = 20
	ptr += 2; //ptr += 2 = address of a[2]
	ptr[0] = 10; //value at a[2] = 10

	ptr -= 2; //ptr - 2 = address of a[0]
	while (ptr <= arr+2) { //while address of ptr <= address of a[0+2] = a[2]
		cout << *ptr << endl;
		ptr++;
	}

} */

/* 1b. Should find max item in array, set pToMax to point to max to find its location
void findMax(int arr[], int n, int*& pToMax) { //reference to a pointer (can't do int&* p, that is pointer to ref)
	if (n <= 0)
		return;      // no items, no maximum!

	pToMax = arr;
	
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > * pToMax)
			pToMax = arr + i;
	}
}

int main() {
	int nums[4] = { 5, 3, 15, 6 };
	int* ptr;

	findMax(nums, 4, ptr);
	cout << "The maximum is at address " << ptr << endl;
	cout << "It's at position " << ptr - nums << endl;
	cout << "Its value is " << *ptr << endl;
} */

/* 1c.
void computeCube(int n, int* ncubed) {
	*ncubed = n * n * n; //gets value at the address ncubed points to
}

int main() {
	int ptr;
	computeCube(5, &ptr); //ref to int ptr
	cout << "Five cubed is " << ptr << endl;
} */

/*1d. Return true if two C strings are equal
bool strequal(const char str1[], const char str2[]) {
	while (*str1 != 0 && *str2 != 0) //Checks the char value at str1, str2 is not the null char (in ASCII, 0 = \0)
	{
		if (*str1 != *str2)  //Compares the value at address str1 and str2
			return false;
		//array name str1 is pointer to const array str1[], str1[] array items can't be changed but pointer to constant can't be changed
		//Pointer arithmetic: pointers can do ++, --, +, -
		str1++; //Address is incremented to address of next item in array
		str2++;
	}
	return *str1 == *str2;   //Are the last letters the same? Ended at same time?
}

int main() {
	char a[15] = "Chen";
	char b[15] = "Chen";

	if (strequal(a, b))
		cout << "They're the same person!\n";
	else
		cout << "They're different people." << endl;
} */

/* 1e.
#include <iostream>
using namespace std;

int* nochange(int* p)
{
	return p;
}

//usu anArray "dies" at end of function b/c no way to access it, but since the function returns a pointer
//the pointer still accesses it but values are uninitialised outside the function??
int* getPtrToArray(int& m)
{
	int anArray[100];
	for (int j = 0; j < 100; j++)
		anArray[j] = 100 - j;
	m = 100;
	return nochange(anArray);
}

void f()
{
	int junk[100];
	for (int k = 0; k < 100; k++)
		junk[k] = 123400000 + k;
	junk[50]++;
	/*int* ptr = &junk[0];
	for (int i = 0; i < 3; i++)
		cout << ptr[i] << ' ';
	for (int i = 100 - 3; i < 100; i++)
		cout << ptr[i] << ' ';
	cout << "end of f" << endl; 
}

int main()
{	
	int n;
	//name of array = same as pointer to address of array[0], pointer to address array[0] same as name of array?
	int* ptr = getPtrToArray(n);
	f(); //Does nothing
	for (int i = 0; i < 3; i++)
		cout << ptr[i] << ' '; //ptr[i] = the items at addresses of the array ptr points to, values are unitialised at the spots
	for (int i = n - 3; i < n; i++)
		cout << ptr[i] << ' ';
	cout << endl;
} */

/*2.
int main() {
	double* cat; //Declare pointer variable cat that can point to variable of type double
	double mouse[5]; //Declare mouse to be 5 element array of doubles
	cat = mouse + 4; //Make cat point to the last element of mouse
	*cat = 25; //Make the double cat points to equal 25, using * operator
	*(mouse + 3) = 54; //Set the fourth element of mouse array to 54 without using the pointer or []
	cat -= 3; //Move cat back by three doubles (cat now = address of mouse[1], second element)
	cat[1] = 27; //Set the third element at mouse[2] equal to 27 using [] and not mouse
	cat[0] = 42; //Set the double cat points to = 42 using [], without using mouse or *
	bool b = (*cat == *(cat + 1)); //True if double cat points to = double immediately following, using *
	bool d = (cat[0] == mouse[0]); //True if cat points to double at start of mouse array, using ==
} */

/* 3a.
/*double mean(const double* scores, int numScores)
{
	const double* ptr = scores;
	double tot = 0;
	while (ptr != scores + numScores)
	{
		tot += *ptr;
		ptr++;
	}
	return tot / numScores;
} 

double mean(const double* scores, int numScores) {
	double tot = 0;
	for (int i = 0; i < numScores; i++)
		tot += *(scores + i);
	return tot / numScores;
}

int main() {
	double arr[3] = { 1.0, 2.0, 3.0 };
	cout << mean(arr, 3) << endl;
} */


/*3b. and 3c.

//Looks through str for chr, if chr is found returns pointer into str where chr was first found
//If chr not found, returns nullptr
/*const char* findTheChar(const char str[], char chr) { //Original
	for (int k = 0; str[k] != 0; k++)
		if (str[k] == chr)
			return &str[k];

	return nullptr;
}

/*const char* findTheChar(const char* str, char chr) { //3b. Rewritten w/ no []
	for (int k = 0; *(str + k) != 0; k++)
		if (*(str + k) == chr)
			return (str + k);
	return nullptr;
}

const char* findTheChar(const char* str, char chr) { //3c. Rewritten w/ no [], only local var are parameters
	while (*str != 0) {
		if (*str == chr)
			return str;
		str++;
	}
	return nullptr;
}
int main() {
	const char str[] = "hello";
	cout << findTheChar(str, 'l') << endl;
}*/

/* 4.
int* maxwell(int* a, int* b) {
	if (*a > * b)
		return a;
	else
		return b;
}

void swap1(int* a, int* b) {//Parameters are references to pointers
	int* temp = a;
	a = b;
	b = temp; //Swaps the addresses of the two pointers, not allowed ==> can't swap addresses of items in array
}

void swap2(int* a, int* b) {//Swaps values at position array[0] and array[2]
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int array[6] = { 5, 3, 4, 17, 22, 19 };
	int* ptr = maxwell(array, &array[2]);
	*ptr = -1;
	ptr += 2;
	ptr[1] = 9;
	*(array + 1) = 79; //array now = -1, 79, 4, 9, 22, 19

	cout << &array[5] - ptr << endl;
	//cout << &array[0] << endl;
	swap1(&array[0], &array[1]);
	//cout << &array[0] << endl; //They are unchanged
	swap2(array, &array[2]);

	for (int i = 0; i < 6; i++)
		cout << array[i] << endl;
} */
 
//6.
//Function accepts one char pointer as only parameter, parameter is Cstring, returns no value
//Removes upper/lowercase s, max 1 local variable + local var must be pointer
void removeS(char* ptr) {
	while (*ptr != 0) { //Stops if finds null char at end of Cstring
		if (*ptr == 's' || *ptr == 'S') {
			char* temp = ptr;
			while (*temp != 0) { //Moves all char s and after forward by one
				*temp = *(temp + 1);
				temp++;
			}
			ptr--; //To check in cas there are two s in a row
		}
		ptr++;
	}
	*(ptr + 1) = '\0';
}

int main() {
	char msg[50] = "She'll be a massless princes.";
	removeS(msg);
	cout << msg;  // prints   he'll be a male prince.
}
