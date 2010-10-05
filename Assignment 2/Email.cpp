#include "Email.h"

using namespace std;

Email::Email() { }

ostream& operator<<(ostream& output, const Email& e) {
	output << "ID: " << e.id << endl;
	output << "Subject: " << e.subject << endl;
	output << "Date: " << e.timestamp << endl;
	output << "To: " << e.sender << endl;
	output << "From: " << e.recipient << endl;
	output << "Lines: " << e.lineCount << endl;
	for(int i=0; i<e.lineCount; ++i) {
		output << e.body[i] << endl;
	}
	output << endl;
	return output;
}
