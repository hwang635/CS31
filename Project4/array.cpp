#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void print(string arr[], int size);

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main() {
	//Testing appendToAll
	/*string people[5] = { "donald", "lindsey", "fiona", "rudy", "mick" };
	print(people, 5);
	cerr << appendToAll(people, 5, "!!!") << endl;
	print(people, 5);

	//Testing lookup
	string officeholders[5] = { "donald", "lindsey", "mike", "adam", "nancy" };
	cerr << lookup(officeholders, -1, "donald");
	cerr << lookup(officeholders, 5, "adam");

	//Testing positionOfMax (uppercase > lowercase)
	string persons[7] = { "donald", "lindsey", "rudy", "Rudy", "rudy", "adam", "z" };
	string cat[3] = { "cat", "Cat", "cat" };
	cerr << positionOfMax(persons, 6) << endl;
	cerr << positionOfMax(cat, 0) << endl;

	//Testing rotateLeft
	string politician[5] = { "mike", "donald", "lindsey", "nancy", "adam" };
	print(politician, 5);
	cerr << rotateLeft(politician, 1, -2) << endl; // returns 1
	print(politician, 5);
	string rl[4] = { "mick", "marie", "lindsey", "nancy" };
	assert(rotateLeft(rl, 4, 1) == 1 && rl[1] == "lindsey" && rl[3] == "marie");

	//Testing countRuns
	 string cr[9] = {
	"rudy", "adam", "mike", "mike", "fiona", "fiona", "fiona", "mike", "mike"
	};
	cerr << countRuns(cr, 9) << endl;  // entire array returns 5
	string cr2[5] = { "marie", "marie", "marie", "rudy", "rudy" };
	assert(countRuns(cr2, 5) == 2);

	//Testing flip
	string folks[7] = { "adam", "", "fiona", "mike", "rudy", "nancy", "donald" };
	print(folks, 7);
	cerr << flip(folks, 3) << endl;  // returns 5
	print(folks, 7);
		//5, folks now contains:  "rudy"  "mike"  "fiona"  ""  "adam"  "nancy"  "donald"
	string flip2[3] = { "lindsey", "fiona", "mike" };
	assert(flip(flip2, 3) == 3 && flip2[0] == "mike" && flip2[2] == "lindsey");

	//Testing differ
	string difFolks[7] = { "adam", "", "fiona", "mike", "rudy", "nancy", "donald" };
	string difGroup[6] = { "adam", "", "fiona", "donald", "mike", "rudy" };
	cerr << differ(difFolks, 7, difGroup, 6) << endl;  //  returns 3
	cerr << differ(difFolks, 2, difGroup, 4) << endl; //  returns 2
	string difH[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	string difG[4] = { "mick", "marie", "lindsey", "nancy" };
	assert(differ(difH, 4, difG, 4) == 2);

	//Testing subsequence
	string subNames[10] = { "gordon", "marie", "nancy", "mick", "gordon", "marie", "nancy", "mick", "adam", "lindsey" };
	string subNames2[10] = { "marie", "nancy", "mick" };
	cerr << subsequence(subNames, 6, subNames2, 3) << endl;  // returns 1
	//string subNames2[10] = { "gordon", "mick" };
	//cerr << subsequence(subNames, 4, subNames2, 0) << endl; // returns -1
	string sub1[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	string sub2[4] = { "fiona", "rudy", "", "gordon" };
	assert(subsequence(sub1, 7, sub2, 4) == 2);

	//Testing lookupAny
	string lookUp1[10] = { "gordon", "marie", "nancy", "mick", "adam", "lindsey" };
	string lookUp2[10] = { "donald", "adam", "mick", "marie" };
	//cerr << lookupAny(lookUp1, 6, lookUp2, 4) << endl; // returns 1 (a1 has "marie" there)
	string lookUp3[10] = { "rudy", "fiona" };
	cerr << lookupAny(lookUp1, 5, lookUp3, 1) << endl; // returns -1 (a1 has none)
	string lookUpH[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	string lookUpF[3] = { "lindsey", "fiona", "mike" };
	assert(lookupAny(lookUpH, 7, lookUpF, 3) == 2);

	//Testing separate
	string sepPersons[6] = { "donald", "marie", "marie", "rudy", "fiona", "adam" };
	print(sepPersons, 6);
	cerr << separate(sepPersons, 5, "rudy") << endl;  //  returns 3 for gordon
	print(sepPersons, 6);
	string sepPersons2[4] = { "marie", "nancy", "lindsey", "mike" };
	print(sepPersons2, 4);
	cerr << separate(sepPersons2, 2, "") << endl;  //  returns 2
	print(sepPersons2, 4); */

	string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	assert(lookup(h, 7, "gordon") == 5);
	assert(lookup(h, 7, "fiona") == 2);
	assert(lookup(h, 2, "fiona") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "mick", "marie", "lindsey", "nancy" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");

	string e[4] = { "fiona", "rudy", "", "gordon" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "lindsey", "fiona", "mike" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

	assert(separate(h, 7, "lindsey") == 3);

	/*string empty[5] = {};
	string numbers[6] = { "one", "two", "three", "four", "one", "one" };
	string ones[3] = { "one", "one", "one" };
	print(numbers, 6);
	cerr << separate(numbers, 6, "one") << endl;
	print(numbers, 6); */

	cout << "All tests succeeded" << endl;
}
void print(string arr[], int size) {
	for (int i = 0; i < size; i++)
		cerr << arr[i] << endl;
}

//Appends value to the end of each of the n elements of the arrays
//Return n if successful, return -1 if bad argument
int appendToAll(string a[], int n, string value) {
	if (n < 0) //User entered negative array size/# of elements
		return -1;
	for (int i = 0; i < n; i++)
		a[i] += value;
	
	return n;
}

//Returns position of string in array that is equal to target (case-sensitive)
//If more than one string, return first/smallest index of matching string, return -1 if no matching string
int lookup(const string a[], int n, string target) {
	if(n < 0) //User entered negative array size/# of elements
		return -1;
	for (int i = 0; i < n; i++) { //Loops through array until finds matching string
		if (a[i] == target)
			return i;
	}

	return -1; //No matching string, returns -1
}

//Returns index of string in array that is >= every string in array
//If more than one greatest string, return first/smallest index of string
//If array has no interesting elements, return -1
int positionOfMax(const string a[], int n) {
	int indexMax = -1;

	if (n < 0) //User entered negative array size/# of elements
		return -1;
	else if (n == 0) //User entered 0 elements
		return -1;
	else {
		string temp = a[0];
		indexMax = 0;
		for (int i = 1; i < n; i++) {
			string iTemp = a[i];
			if (iTemp > temp) { //If the string is greater than the stored string, store greater string + index
				temp = iTemp;
				indexMax = i;
			}
		}
	}

	return indexMax;
}

//Move all items to the right of pos to the left by one, put item at pos at the end
//Return the orig position of the item that was moved to the end, return -1 if bad argument
int rotateLeft(string a[], int n, int pos) {
	if (n <= 0 || pos < 0) //User entered negative array size/# of elements or neg item index
		return -1;
	if (pos >= n) //User entered nonexistent pos index greater than/equal # of elements
		return -1;
	
	string moved = a[pos];
	for (int i = pos; i < n-1; i++) { //Loops until second-last item, shifts items one to left
		a[i] = a[i + 1];
	}
	a[n - 1] = moved; //Moves original pos item to the end of the array

	return pos;
}

//Returns number of sequences of 1/more consecutive same items in array
int countRuns(const string a[], int n) {
	if (n < 0) //User entered negative array size/# of elements
		return -1;
	else if (n == 0)
		return 0;

	int count = 1;
	for (int i = 0; i < n-1; i++) { 
		// string testA = a[i];  //for debugging
		// string testA1 = a[i + 1];
		if (a[i] != a[i + 1]) //If the next item is different, count a new sequence
			count++;
	}

	return count;
}

//Reverse the elements in the array
//Return n if successful, return -1 if bad argument/unsuccessful
int flip(string a[], int n) {
	if (n < 0) //User entered negative array size/# of elements
		return -1;
	for (int i = 0; i < n/2; i++) {
		string temp = a[i];
		//string testminus = a[n - 1 - i]; //debugging purposes
		a[i] = a[n - 1 - i]; 
		a[n - 1 - i] = temp;
	}

	return n;
}

//Return index of first same-index elements of a1, a2 that aren't the same
//If both array are equal up to point where n1/n2 runs out, return the value of n1 / n2 less than/equal to other
//If bad argument/other error, return -1
int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) //User entered negative array sizes/# of elements
		return -1;

	int index;
	if (n1 <= n2) //Set index to equal the smaller of n1 and n2
		index = n1;
	else
		index = n2;

	for (int i = 0; i < index; i++) { //Go up to the smallest of n1, n2
		if(a1[i] != a2[i]) //If two corresponding elements are unequal, returns the index
			return i;
	}

	return index; //If unequal elements aren't found, returns the smaller of n1 and n2
}

//Returns index of where n2 elements of a2 appear contiguously in a1
//Return -1 if a1 doesn't contain continuous a2
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) //User entered negative array sizes/# of elements
		return -1;
	if (n2 == 0) //Sequence n2 of 0 elements is a subsequence of any sequence
		return 0;
	if (n2 > n1) //If there are more elements n2 than n1, not possible for there to be n2 elements of a2 in n1 elements of a1
		return -1;

	int index = -1;
	int count = 0;
	bool indexSet = false;

	for (int i = 0; i < n1; i++) {
		if (a1[i] == a2[count]) { //If the item matches the corresponding item in a2
			if (!indexSet) { //Sets the index to the item's index if it is the first matching item
				index = i;
				indexSet = true;
			}
			count++;
			if (count == n2) //Returns the index when all matching items have been found
				return index;
		}
		else { //If the item doesn't match, resets the index and item counter
			index = -1;
			indexSet = false;
			count = 0;
		}
	}

	return -1; //If the index of the subsequence is not found
}

//Return the index of the first element in a1 that matches an element a2
//Return -1 if bad argument or no match
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) //User entered negative array sizes/# of elements
		return -1;
	for (int i = 0; i < n1; i++) { //Loop through each item in a1
		string temp = a1[i];
		for (int j = 0; j < n2; j++) { //Loop through each item in a2 and return index if finds matching element
			if (temp == a2[j])
				return i;
		}
	}

	return -1; //If none matching are found, return -1
}     

//Rearranges array so that all elements < separator come before elements > separator, separator if there is in between
//Return position of first element after rearrangement that >= separator, return n if no elements >= separator
//Return -1 for bad argument
int separate(string a[], int n, string separator) {
	if (n < 0) //User entered negative # of elements, bad argument
		return -1;

	bool containsSeparator = false;
	int index = n;

	//If an element is greater than the separator, moves it to the end and shifts the array
	for (int i = 0; i < n; i++) {
		if (a[i] > separator)
			rotateLeft(a, n, i);
		if (a[i] == separator)
			containsSeparator = true;
	}

	for (int i = 0; i < n; i++) { //Loops second time to check skipped spots
		if (a[i] > separator) //If an element is greater than the separator, moves it to the end and shifts the array
			rotateLeft(a, n, i);
	}

	//If the array contains the separator, rotates the elements < separator until the separator is rightmost
	//add a while loop?? for number of separators present + add loop to check how many separators
	if (containsSeparator) {
		//Finds the index of the first item greater than the separator for the separator loop
		for (int i = 0; i < n; i++) {
			if (a[i] > separator) {
				index = i;
				break;
			}
		}
		for (int i = 0; i < index; i++) { 
			//string ai = a[i]; //debugging
			if(a[i] == separator)
				rotateLeft(a, index, i);  
		}
		for (int i = 0; i < index; i++) { //Loops through a second time to check skipped spots
			if (a[i] == separator)
				rotateLeft(a, index, i);
		}
	}

	for (int i = 0; i < n; i++) { //Finds the index of the first item greater than the separator again
		if (a[i] >= separator) {
			index = i;
			break;
		}
	}

	return index;
}

