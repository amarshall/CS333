#include <iostream>
#include <fstream>
#include "Email.h"
#include "Heap.h"

using namespace std;

bool sortMax(int first, int second) {
  return first > second;
}

bool sortMin(int first, int second) {
  return first < second;
}

bool sortString(string first, string second) {
  return first.compare(second);
}

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
      // Skip over "blank" lines
      do {
        getline(input, line);
      } while(line.find("ID") == string::npos && !input.eof());
      if(input.eof()) break;
      
      Email cur;
      
      // ID
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
      cur.body = body;
      
      input.close();
      
      emails[i] = cur;
    }
  }
  
  int* a = new int[count];
  for(int i=0; i<count; ++i) { a[i] = i; }
  Heap dh = DateHeap(a, count);
  dh.buildHeap();
  
  delete[] emails;
  return 0;
}