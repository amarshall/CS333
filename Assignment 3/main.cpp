#include <iostream> // REMOVE ME
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
	int* op_args;
};
node* add_node(node* top, vector<char>* string_ptr) {
	node* new_top = new node;
	new_top->string_ptr = string_ptr;
	new_top->next = top;
	return new_top;
}
node* add_node(node* top, int op_args[]) {
	node* new_top = new node;
	new_top->op_args = op_args;
	new_top->next = top;
	return new_top;
}
node* remove_top(node* top) {
	node* new_top = top->next;
	delete top;
	return new_top;
}

void print_stack(node* stack) {
	cout << "stack is:" << endl;
	while(stack != NULL) {
		cout << stack->op_args[0] << " | " << stack->op_args[1] << " | " << stack->op_args[2] << endl;
		stack = stack->next;
	}
	cout << "end stack" << endl;
}

void print_string(vector<char>* string) {
	for(int j=0; (*string)[j] != 0; ++j) {
		putchar((*string)[j]);
	}
	putchar('\n');
}

vector< vector<char>* > strings; // Array holding all the strings
int strings_length = 0;
node* counts[127]; // Array holding the temporary counts as a linked list of pointers
int counts_length = 127; // Change to constant
//node* stack;
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
		while(cur_ptr != NULL /* && cur_pos <= end */) {
			/* Old: */
			//strings[cur_pos] = *(counts[i]->data);
			//counts[i] = remove_top(counts[i]);
			/* end Old; New: */ // This way should be a little faster
			
			cout << "putting in spot " << cur_pos << ": ";
			print_string(cur_ptr->string_ptr);
			
			strings[cur_pos] = cur_ptr->string_ptr;
			//node* delete_me = cur_ptr;
			cur_ptr = cur_ptr->next;
			//delete delete_me;
			/* end New */
			++cur_pos;
			++runs;
		}
		if(runs > 1) {
			cout << "adding " << cur_pos-runs << " | " << cur_pos - 1 << " | " << column+1 << endl;
			op_arg op_args;
			op_args.start = cur_pos - runs;
			op_args.end = cur_pos - 1;
			op_args.column = column + 1;
			stack.push_back(op_args);
		}
	}
}

void sort() {
	sort_column(0, strings_length-1, 0);
	while(stack.size() > 0) {
		op_arg op_args = stack.back();
		cout << "running " << op_args.start << " | " << op_args.end << " | " <<  op_args.column << endl;
		stack.pop_back();
		sort_column(op_args.start, op_args.end, op_args.column);
	}
}

void read_input() {
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

void print_output() {
	for(int i=0; i < strings_length; ++i) {
		vector<char>* string = strings[i];
		for(int j=0; (*string)[j] != 0; ++j) {
			putchar((*string)[j]);
		}
		putchar('\n');
	}
}

int main() {
	/*
	for(int i=0; i < counts_length; ++i) {
		counts[i] = NULL;
	}
	*/
	read_input();
	sort();
	print_output();
}
