struct node {
	node* next = NULL;
	int data;  // THIS IS A MEMORY ADDRESS. ALWAYS.
};
inline node* add_node(node* top, int* data) {
	node* new_top = new node;
	new_top->data = data;
	new_top->next = top;
	return new_top;
}
inline node* remove_top(node* node) {
	node* new_top = node->next;
	delete node;
	return new_top;
}

int* strings; // Array holding all the strings. Actually an array of pointers to character arrays
int strings_length = 0;
node* counts; // Array holding the temporary counts as a linked list of pointers to each "String". Index is ASCII value
int counts_length; // Change to constant
node* stack;

void sort_column(int start, int end, int column) {
	// Store counts in array
	// TODO: Ensure counts array is zeroed first
	for(int i=start; i < end; ++i) {
		int ascii = [strings[i][column]];
		if(ascii != 0) {
			counts[ascii] = add_node(counts[ascii], strings[i]);
		}
	}
	
	int cur_pos = start;
	for(int i=0; i < counts_length; ++i) {
		int runs = 0;
		node* cur_ptr = counts[i];
		while(counts[i] != NULL /* && cur_pos <= end */) {
			/* Old: */
			//strings[cur_pos] = *(counts[i]->data);
			//counts[i] = remove_top(counts[i]);
			/* end Old; New: */ // This way should be a little faster
			strings[cur_pos] = cur_ptr->data;
			node* delete_me = cur_ptr;
			cur_ptr = cur_ptr->next;
			delete delete_me;
			/* end New */
			++cur_pos;
			++runs;
		}
		if(runs > 1) {
			int* op_args = { cur_pos, cur_pos + runs, column + 1 };
			stack = add_node(stack, op_args);
		}
	}
}

void sort() {
	sort_column(0, strings_length, 0);
	while(stack != NULL) {
		int* op_args = stack->data;
		stack = remove_top(stack);
		sort_column(op_args[0], op_args[1], op_args[2]);
		delete op_args;
	}
}
