/**
 * CS333 Assignment #4
 * main.cpp
 * @author J. Andrew Marshall (jmarsha6)
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct Huffman {
	char character;
	int frequency;
	string encoding;
};

struct Node {
	Node* left;
	Node* right;
	Huffman* data;
	int frequency;
};

bool compareCharacter(const Huffman one, const Huffman two) {
	return one.character > two.character;
}

bool compareFrequency(const Huffman one, const Huffman two) {
	return one.frequency < two.frequency;
}

bool compareNode(const Node* one, const Node* two) {
	return one->frequency < two->frequency;
}

string getEncodingFromStack(const vector<int> &s) {
	string encoding = "";
	int stack_size = s.size();
	for(int i = 0; i < stack_size; ++i) {
		encoding += s[i];
	}
	return encoding;
}

template <class T, class C>
void sort(vector<T> &v, bool(*comparator)(const C, const C)) {
	int size = v.size();
	for(int i = 0; i < size; ++i) {
		T current = v[i];
		int j = i - 1;
		while(j >= 0 && comparator(v[j], current)) {
			v[j+1] = v[j];
			--j;
		}
		v[j+1] = current;
	}
}

Node* buildTree(vector<Huffman> &characters) {
	vector<Node*> nodes;
	for(unsigned int i = 0; i < characters.size(); ++i) {
		Node* node = new Node;
		node->left = NULL;
		node->right = NULL;
		node->data = &characters[i];
		node->frequency = characters[i].frequency;
		nodes.push_back(node);
	}
	sort(nodes, &compareNode);
	
	while(nodes.size() > 1) {
		Node* top = new Node;
		top->left = nodes.back();
		nodes.pop_back();
		top->right = nodes.back();
		nodes.pop_back();
		top->frequency = top->left->frequency + top->right->frequency;
		nodes.push_back(top);
		top->data = NULL;
		sort(nodes, &compareNode);
	}
	return nodes[0];
}

// Please don't call directly
void _generateEncoding(Node* node, vector<int> &encoding_stack) {
	if(node->data != NULL) {
		node->data->encoding = getEncodingFromStack(encoding_stack);
	}
	if(node->left != NULL) {
		encoding_stack.push_back('0');
		_generateEncoding(node->left, encoding_stack);
		encoding_stack.pop_back();
	}
	if(node->right != NULL) {
		encoding_stack.push_back('1');
		_generateEncoding(node->right, encoding_stack);
		encoding_stack.pop_back();
	}
}

void generateEncoding(Node* node) {
	vector<int> s;
	_generateEncoding(node, s);
}

void printCharacters(const vector<Huffman> &characters, int character_count) {
	cout << "Total Characters: " << character_count << endl;
	for(unsigned int i = 0; i < characters.size(); ++i) {
		cout << characters[i].character << ": ";
		cout << characters[i].frequency << " ";
		cout << characters[i].encoding << endl;
	}
}

int main(int argc, char* argv[]) {
	int character_count = 0;
	const int CHARACTER_ARRAY_SIZE = 26;
	int character_frequencies[CHARACTER_ARRAY_SIZE];
	for(int i = 0; i < CHARACTER_ARRAY_SIZE; ++i) {
		character_frequencies[i] = 0;
	}
	//vector<string*> words; // To be used in part two
	
	// Read input
	char current_char;
	//int current_word_count = 0;
	//string current_word = "";
	while((current_char = getchar()) != EOF) {
		if(current_char != '\n') {
			int character_index = current_char - 97;
			//word += current_char;
			++character_frequencies[character_index];
			++character_count;
		} else {
			//words.push_back(current_word);
			//current_word = "";
		}
	}
	
	vector<Huffman> characters;
	for(int i = 0; i < CHARACTER_ARRAY_SIZE; ++i) {
		Huffman h;
		h.character = i + 97;
		h.frequency = character_frequencies[i];
		h.encoding = "";
		characters.push_back(h);
	}
	
	sort(characters, &compareFrequency);
	Node* huffman_tree = buildTree(characters);
	generateEncoding(huffman_tree);
	
	char flag = *(argv[1] + 1);
	if(flag == 'f') {
		printCharacters(characters, character_count);
	} else if(flag == 'a') {
		sort(characters, &compareCharacter);
		printCharacters(characters, character_count);
	} else {
		cout << "Bad argument. Just did a whole lot of work for nothing." << endl;
	}
	
	return 0;
}
