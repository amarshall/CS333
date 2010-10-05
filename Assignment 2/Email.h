#include <string>
#include <iostream>

class Email {
	public:
		int id;
		int timestamp;
		std::string subject;
		std::string sender;
		std::string recipient;
		std::string* body;
		int lineCount;
		friend std::ostream& operator<<(std::ostream& output, const Email& e);
		Email();
};
