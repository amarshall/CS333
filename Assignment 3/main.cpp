#include <stdio.h>
#include <vector>

using namespace std;

struct op_args_t {
	int start;
	int end;
	int column;
};
struct node {
	node* next;
	vector<char>* string_ptr;
};
inline node* add_node(node* top, vector<char>* string_ptr) {
	node* new_top = new node;
	new_top->string_ptr = string_ptr;
	new_top->next = top;
	return new_top;
}

vector< vector<char>* > strings;
const int counts_length = 59;
node* counts[counts_length];
vector<op_args_t> stack;

void sort_column(const op_args_t &op_args) {
	const int start = op_args.start;
	const int end = op_args.end;
	const int column = op_args.column;
	for(int i=start; i <= end; ++i) {
		int ascii = (*strings[i])[column] - 64;
		if(ascii < 0) ascii = 0;
		counts[ascii] = add_node(counts[ascii], strings[i]);
	}
	
	int cur_pos = start;
	for(int i=0; i < counts_length; ++i) {
		const int start_pos = cur_pos;
		node* cur_ptr = counts[i];
		while(cur_ptr != NULL) {
			strings[cur_pos] = cur_ptr->string_ptr;
			node* delete_me = cur_ptr;
			cur_ptr = cur_ptr->next;
			delete delete_me;
			++cur_pos;
		}
		if(cur_pos - start_pos > 2 && i != 0) {
			op_args_t op_args;
			op_args.start = start_pos;
			op_args.end = cur_pos - 1;
			op_args.column = column + 1;
			stack.push_back(op_args);
		}
		counts[i] = NULL;
	}
}

inline void sort() {
	op_args_t main_args;
	main_args.start = 0;
	main_args.end = strings.size() - 1;
	main_args.column = 0;
	sort_column(main_args);
	while(stack.size() > 0) {
		op_args_t op_args = stack.back();
		stack.pop_back();
		sort_column(op_args);
	}
}

inline void read_input() {
	char c = getchar();
	vector<char>* s = new vector<char>;
	s->reserve(8);
	while(c != EOF) {
		if(c != '\n') {
			s->push_back(c);
		} else {
			s->push_back(0);
			strings.push_back(s);
			s = new vector<char>;
		}
		c = getchar();
	}
}

inline void print_output() {
	for(unsigned int i=0; i < strings.size(); ++i) {
		for(int j=0; (*strings[i])[j] != 0; ++j) {
			putchar((*strings[i])[j]);
		}
		putchar('\n');
	}
}

int main() {
	strings.reserve(64);
	read_input();
	stack.reserve(64);
	sort();
	print_output();
	return 0;
}
