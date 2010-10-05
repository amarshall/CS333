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
	
	int* a = new int[count];
	for(int i=0; i<count; ++i) { a[i] = i; }
	Heap* dh = new DateHeap(a, count, emails);
	Heap* sh = new SubjectHeap(a, count, emails);
	Heap* lh = new LinesHeap(a, count, emails);
	delete a;
	
	dh->buildHeap();
	sh->buildHeap();
	lh->buildHeap();
	
	string command;
	string argument;
	while(1) {
		cout << "Command please: ";
		cin >> command;
		if(command == "quit" || command == "QUIT") {
			break;
		}
		cin >> argument;
		if(command == "sort") {
			if(argument == "oldest") {
				dh->heapSort();
				cout << *dh;
				dh->buildHeap();
			} else if(argument == "alphabetical") {
				sh->heapSort();
				cout << *sh;
				sh->buildHeap();
			} else if(argument == "longest") {
				lh->heapSort();
				cout << *lh;
				lh->buildHeap();
			}
		} else if(command == "extract") {
			if(argument == "oldest") {
				cout << emails[dh->getHeap()[0]];
				int* h = dh->popTop();
				sh->buildHeap(h);
				lh->buildHeap(h);
			} else if(argument == "alphabetical") {
				cout << emails[sh->getHeap()[0]];
				int* h = sh->popTop();
				dh->buildHeap(h);
				lh->buildHeap(h);
			} else if(argument == "longest") {
				cout << emails[lh->getHeap()[0]];
				int* h = lh->popTop();
				dh->buildHeap(h);
				sh->buildHeap(h);
			}
		} else if(command == "report") {
			if(argument == "oldest") {
				cout << emails[dh->getHeap()[0]];
			} else if(argument == "alphabetical") {
				cout << emails[sh->getHeap()[0]];
			} else if(argument == "longest") {
				cout << emails[lh->getHeap()[0]];
		}
		} else {
			cout << "**Invalid command**" << endl;
		}
	}
	
	delete dh;
	delete sh;
	delete lh;
	delete[] emails;
	return 0;
}
