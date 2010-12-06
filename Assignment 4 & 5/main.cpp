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

struct Word {
	string word;
	int value;
	int weight;
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
void _generateEncoding(Node* node, vector<int> &encoding_stack, int* weights) {
	if(node->data != NULL) {
		node->data->encoding = getEncodingFromStack(encoding_stack);
		weights[node->data->character - 97] = node->data->encoding.length();
	}
	if(node->left != NULL) {
		encoding_stack.push_back('0');
		_generateEncoding(node->left, encoding_stack, weights);
		encoding_stack.pop_back();
	}
	if(node->right != NULL) {
		encoding_stack.push_back('1');
		_generateEncoding(node->right, encoding_stack, weights);
		encoding_stack.pop_back();
	}
}

void generateEncoding(Node* node, int* weights) {
	vector<int> s;
	_generateEncoding(node, s, weights);
}

int generateWordWeights(vector<Word> &words, const vector<Huffman> &characters) {
	int largest = 0;
	for(unsigned int i = 0; i < words.size(); ++i) {
		int weight = 0;
		string word = words[i].word;
		for(unsigned int j = 0; j < word.length(); ++j) {
			weight += characters[word[j] - 97].encoding.length();
		}
		if(weight > largest) largest = weight;
		words[i].weight = weight;
	}
	return largest;
}

void printCharacters(const vector<Huffman> &characters, int character_count) {
	cout << "Total Characters: " << character_count << endl;
	for(unsigned int i = 0; i < characters.size(); ++i) {
		cout << characters[i].character << ": ";
		cout << characters[i].frequency << " ";
		cout << characters[i].encoding << endl;
	}
}

void printWords(const vector<Word> &words) {
	cout << endl << "Word: value | weight" << endl;
	for(unsigned int i = 0; i < words.size(); ++i) {
		cout << words[i].word << ": ";
		cout << words[i].value << " | " << words[i].weight << endl;
	}
}

void knapsack(const vector<Word> &words, int size, int largest, int &finalCost, int &finalSize) {
	int solutionsSize = size + largest;
	int* solutions = new int[solutionsSize];
	vector<int>* usedWords = new vector<int>[solutionsSize];
	for(int i = 0; i < solutionsSize; ++i) solutions[i] = 0;
	for(int i = 0; i < size; ++i) {
		if(i == 0 || solutions[i] > 0) {
			for(unsigned int j = 0; j < words.size(); ++j) {
				/*
				bool nope = false;
				for(unsigned int k = 0; k < usedWords[i].size(); ++k) {
					if(usedWords[i][k] == (signed int)j) {
						nope = true;
						break;
					}
				}
				if(nope) continue;
				*/
				int weight = words[j].weight;
				int value = words[j].value;
				if(solutions[i + weight] == 0 || solutions[i + weight] < solutions[i] + value) {
					solutions[i + weight] = solutions[i] + value;
					//usedWords[i + weight] = usedWords[i];
					//usedWords[i + weight].push_back(j);
				}
			}
		}
	}
	
	finalCost = solutions[size];
	finalSize = 0;
	for(int i = 0; i <= size; ++i) {
		if((finalCost == 0 || solutions[i] > finalCost) && solutions[i] != 0) {
			finalCost = solutions[i];
			finalSize = i;
		}
	}
}

int main(int argc, char* argv[]) {
	int character_count = 0;
	const int CHARACTER_ARRAY_SIZE = 26;
	int character_frequencies[CHARACTER_ARRAY_SIZE];
	for(int i = 0; i < CHARACTER_ARRAY_SIZE; ++i) {
		character_frequencies[i] = 0;
	}
	vector<Word> words; // To be used in part two
	
	// Read input
	char current_char;
	string current_word = "";
	int current_word_value = 0;
	while((current_char = getchar()) != EOF) {
		if(current_char != '\n') {
			int character_index = current_char - 97;
			current_word += current_char;
			current_word_value += current_char - 96;
			++character_frequencies[character_index];
			++character_count;
		} else {
			Word w;
			w.word = current_word;
			w.weight = 0;
			w.value = current_word_value;
			words.push_back(w);
			current_word = "";
			current_word_value = 0;
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
	int characterWeights[26];
	generateEncoding(huffman_tree, characterWeights);
	sort(characters, &compareCharacter);
	int largestWeight = generateWordWeights(words, characters);
	
	char flag = *(argv[1] + 1);
	if(flag == 'f') {
		sort(characters, &compareFrequency);
		printCharacters(characters, character_count);
		printWords(words);
	} else if(flag == 'a') {
		sort(characters, &compareCharacter);
		printCharacters(characters, character_count);
		printWords(words);
		int finalCost;
		int finalSize;
		knapsack(words, 700, largestWeight, finalCost, finalSize);
		cout << "Knapsack is cost " << finalCost << " with size " << finalSize << endl;
	} else {
		cout << "Bad argument. Just did a whole lot of work for nothing." << endl;
	}
	
	return 0;
}