#include <iostream>
#include <fstream>
#include "Email.h"
#include "Heap.h"

using namespace std;

int main(int argc, const char* argv[]) {
	ifstream input (argv[1]);
	Email* emails;
	int count;
	
	if(input.is_open()) {
		string line;
		getline(input, line);
		count = atoi(line.c_str());
		emails = new Email[count];
		for(int i=0; i<count && !input.eof(); ++i) {
			/*// Skip over "blank" lines
			do {
				getline(input, line);
			} while(line.find("ID") == string::npos && !input.eof());
			if(input.eof()) break;
			*/
			
			Email cur;
			
			// ID
			getline(input, line);
			line = line.substr(line.find(":") + 2);
			cur.id = atoi(line.c_str());
			
			// Subject
			getline(input, line);
			cur.subject = line.substr(line.find(":") + 2);
			
			// Date
			getline(input, line);
			cur.timestamp = atoi(line.substr(line.find(":") + 2).c_str());
			
			// Sender
			getline(input, line);
			cur.sender = line.substr(line.find(":") + 2);
			
			// Recipient
			getline(input, line);
			cur.recipient = line.substr(line.find(":") + 2);
			
			// Body
			getline(input, line);
			int bodyLines = atoi(line.substr(line.find(":") + 2).c_str());
			string* body = new string[bodyLines];
			for(int j=0; j<bodyLines; ++j) {
				getline(input, line);
				body[j] = line;
			}
			cur.lineCount = bodyLines;
			cur.body = body;
			
			emails[i] = cur;
		}
		input.close();
	}
	
	
	for(int i=0; i<count; ++i) {
		cout << emails[i];
	}
	
	int* a = new int[count];
	for(int i=0; i<count; ++i) { a[i] = i; }
	Heap dh = DateHeap(a, count, emails);
	dh.buildHeap();
	//cout << dh;
	
	delete[] emails;
	return 0;
}
