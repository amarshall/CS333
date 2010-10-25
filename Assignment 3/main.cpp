#include <stdio.h>
#include <pthread.h>
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
inline void op_args_init(op_args_t &op_args, int start, int end, int column) {
	op_args.start = start;
	op_args.end = end;
	op_args.column = column;
}

vector< vector<char>* > strings;
int strings_length = 0;
const int counts_length = 127;
vector<op_args_t> stack;
pthread_mutex_t stack_mutex;
pthread_mutex_t strings_mutex;

void* sort_column(void* args) {
	op_args_t op_args = *((op_args_t*)args);
	int start = op_args.start;
	int end = op_args.end;
	int column = op_args.column;
	node* counts[counts_length];
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
			op_args_t op_args;
			op_args_init(op_args, cur_pos - runs, cur_pos - 1, column + 1);
			pthread_mutex_lock(&stack_mutex);
			stack.push_back(op_args);
			pthread_mutex_unlock(&stack_mutex);
		}
	}
	pthread_exit(NULL);
}

inline void sort() {
	pthread_mutex_init(&stack_mutex, NULL);
	pthread_mutex_init(&strings_mutex, NULL);
	op_args_t main_args;
	op_args_init(main_args, 0, strings_length - 1, 0);
	stack.push_back(main_args);
	while(stack.size() >= 1) {
		bool two = stack.size() >= 2;
		two = false;
		op_args_t op_args[2];
		op_args[0] = stack.back();
		stack.pop_back();
		if(two) {
			op_args[1] = stack.back();
			stack.pop_back();
		}
		pthread_t thread1, thread2;
		pthread_create(&thread1, NULL, sort_column, (void*) &op_args[0]);
		if(two) pthread_create(&thread1, NULL, sort_column, (void*) &op_args[1]);
		pthread_join(thread1, NULL);
		if(two) pthread_join(thread2, NULL);
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
