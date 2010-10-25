#include <stdio.h>
#include <vector>

using namespace std;

struct op_arg {
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
int strings_length = 0;
const int counts_length = 127;
node* counts[counts_length];
vector<op_arg> stack;

void sort_column(int start, int end, int column) {
	for(int i=0; i < counts_length; ++i) {
		counts[i] = NULL;
	}
	for(int i=start; i <= end; ++i) {
		int ascii = (*strings[i])[column];
		if(ascii != 0) {
			counts[ascii] = add_node(counts[ascii], strings[i]);
		}
	}
	
	int cur_pos = start;
	for(int i=0; i < counts_length; ++i) {
		int runs = 0;
		node* cur_ptr = counts[i];
		while(cur_ptr != NULL) {			
			strings[cur_pos] = cur_ptr->string_ptr;
			node* delete_me = cur_ptr;
			cur_ptr = cur_ptr->next;
			delete delete_me;
			++cur_pos;
			++runs;
		}
		if(runs > 1) {
			op_arg op_args;
			op_args.start = cur_pos - runs;
			op_args.end = cur_pos - 1;
			op_args.column = column + 1;
			stack.push_back(op_args);
		}
	}
}

inline void sort() {
	sort_column(0, strings_length-1, 0);
	while(stack.size() > 0) {
		op_arg op_args = stack.back();
		stack.pop_back();
		pthread
		sort_column(op_args.start, op_args.end, op_args.column);
	}
}

inline void read_input() {
	char c = getchar();
	vector<char>* s = new vector<char>;
	while(c != EOF) {
		if(c != '\n') {
			s->push_back(c);
		} else {
			s->push_back(0);
			strings.push_back(s);
			++strings_length;
			s = new vector<char>;
		}
		c = getchar();
	}
}

inline void print_output() {
	for(int i=0; i < strings_length; ++i) {
		for(int j=0; (*strings[i])[j] != 0; ++j) {
			putchar((*strings[i])[j]);
		}
		putchar('\n');
	}
}

int main() {
	read_input();
	sort();
	print_output();
	return 0;
}
