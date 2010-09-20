/**
 * insertion.cpp
 * CS333 Assignment #1
 * @author J. Andrew Marshall (jmarsha6)
 */

#include <iostream>

#define MAX_ELEMENTS 10000

using namespace std;

void putInPlace(int arr[], int i, int elem) {
	if(elem < arr[i] && i >= 0) {
		arr[i+1] = arr[i];
		putInPlace(arr, i-1, elem);
	} else {
		arr[i+1] = elem;
	}
}

void recInsertion(int arr[], int start, int end) {
	if(start < end) {
		putInPlace(arr, start, arr[start+1]);
		recInsertion(arr, start+1, end);
	}
}

int main() {
	int val;
	int count = 0;
	int values[MAX_ELEMENTS];
	
	// Input
	while(cin >> val && count < MAX_ELEMENTS) {
		values[count] = val;
		count++;
	}
	
	// Sort!
	recInsertion(values, 0, count-1);
	
	// Output
	for(int i=0; i < count; ++i) {
		cout << values[i] << endl;
	}
	
	return 0;
}
