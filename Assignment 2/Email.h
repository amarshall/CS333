#include <string>

class Email {
	public:
		int id;
		int timestamp;
		std::string subject;
		std::string sender;
		std::string recipient;
		std::string* body;
		int lineCount;
		Email();
};
