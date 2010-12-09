/**
 * CS333 Assignment #4 & 5
 * main.cpp
 * @author J. Andrew Marshall (jmarsha6)
 */

#include <iomanip>
#include <iostream>
#include <fstream>
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
	string encoding;
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

bool compareRatio(const Word one, const Word two) {
	return ((double)one.value / one.weight) < ((double)two.value / two.weight);
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

string getEncodingFromStack(const vector<int> &s) {
	string encoding = "";
	int stack_size = s.size();
	for(int i = 0; i < stack_size; ++i) {
		encoding += s[i];
	}
	return encoding;
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

void populateWords(vector<Word> &words, const vector<Huffman> &characters) {
	for(unsigned int i = 0; i < words.size(); ++i) {
		int weight = 0;
		string encoding = "";
		string word = words[i].word;
		for(unsigned int j = 0; j < word.length(); ++j) {
			weight += characters[word[j] - 97].encoding.length();
			encoding += characters[word[j] - 97].encoding;
		}
		words[i].weight = weight;
		words[i].encoding = encoding;
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

double fractional(vector<Word> &words, const int size, string &binaryKnapsack) {
	cout.flush();
	sort(words, &compareRatio);
	int actualSize = 0;
	double finalCost = 0;
	unsigned int lastWordUsed;
	
	for(lastWordUsed = 0; actualSize < size && lastWordUsed < words.size(); ++lastWordUsed) {
		const Word currentWord = words[lastWordUsed];
		if(actualSize + currentWord.weight <= size) {
			actualSize += currentWord.weight;
			finalCost += currentWord.value;
			binaryKnapsack += currentWord.encoding + '\n';
		} else {
			const double fraction = (double)(size - actualSize) / currentWord.weight;
			actualSize += currentWord.weight * fraction;
			finalCost += currentWord.value * fraction;
			binaryKnapsack += currentWord.encoding.substr(0, currentWord.word.length() * fraction) + '\n';
			break;
		}
	}
	
	return finalCost;
}

int knapsack(const vector<Word> &words, const int size, string &binaryKnapsack) {
	int** solutions = new int*[words.size()];
	for(int i = 0; (unsigned int)i < words.size(); ++i) {
		solutions[i] = new int[size];
		for(int j = 0; j < size; ++j) {
			if(i == 0 && j >= words[0].weight) {
				solutions[0][j] = words[0].value;
			} else {
				solutions[i][j] = 0;
			}
		}
	}
	
	for(int i = 1; (unsigned int)i < words.size(); ++i) {	
		const int weight = words[i].weight;
		const int value = words[i].value;
		for(int j = 0; j <= size; ++j) {
			if(weight <= j && solutions[i-1][j - weight] + value > solutions[i-1][j]){
				solutions[i][j] = solutions[i-1][j-weight] + value;
			} else {
				solutions[i][j] = solutions[i-1][j];
			}
		}
	}
	
	int j = size - 1;
	for(int i = words.size() - 1; i > 0 && j >= 0; --i) {
		if(solutions[i][j] != solutions[i-1][j]) {
			binaryKnapsack += words[i].encoding + '\n';
			j -= words[i].weight;
		}
	}
	if(solutions[0][j] != 0) binaryKnapsack += words[0].encoding + '\n';
	
	return solutions[words.size()-1][size-1];
}

int main(const int argc, const char* argv[]) {
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
	populateWords(words, characters);
	
	const char flag = *(argv[1] + 1);
	const int knapsackSize = atoi(argv[2]);
	const string outputFile = argv[3];
	if(flag == 'f') {
		sort(characters, &compareFrequency);
		printCharacters(characters, character_count);
	} else if(flag == 'a') {
		sort(characters, &compareCharacter);
		printCharacters(characters, character_count);
	} else if(flag == 'd') {
		string binaryKnapsack = "";
		double finalCost = knapsack(words, knapsackSize, binaryKnapsack);
		ofstream output;
		output.open(outputFile.data());
		output << binaryKnapsack;
		output.close();
		cout << finalCost << endl;
	} else if(flag == 'g') {
		string binaryKnapsack = "";
		double finalCost = fractional(words, knapsackSize, binaryKnapsack);
		ofstream output;
		output.open(outputFile.data());
		output << binaryKnapsack;
		output.close();
		cout << setprecision(2) << fixed << finalCost << endl;
	} else {
		cout << "Bad argument. Just did a whole lot of work for nothing." << endl;
	}
	
	return 0;
}
