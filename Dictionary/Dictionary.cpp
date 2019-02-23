#include <string>
#include <iostream>
#include "Dictionary.h"
using namespace std;

//do not forget to tweak this function if you change the alphabet
int Dictionary::c_to_i(char c) {
	switch (c) {
	case 'a': return 1; case 'A': return 1;
	case 'b': return 2; case 'B': return 2;
	case 'c': return 3; case 'C': return 3;
	case 'd': return 4; case 'D': return 4;
	case 'e': return 5; case 'E': return 5;
	case 'f': return 6; case 'F': return 6;
	case 'g': return 7; case 'G': return 7;
	case 'h': return 8; case 'H': return 8;
	case 'i': return 9; case 'I': return 9;
	case 'j': return 10; case 'J': return 10;
	case 'k': return 11; case 'K': return 11;
	case 'l': return 12; case 'L': return 12;
	case 'm': return 13; case 'M': return 13;
	case 'n': return 14; case 'N': return 14;
	case 'o': return 15; case 'O': return 15;
	case 'p': return 16; case 'P': return 16;
	case 'q': return 17; case 'Q': return 17;
	case 'r': return 18; case 'R': return 18;
	case 's': return 19; case 'S': return 19;
	case 't': return 20; case 'T': return 20;
	case 'u': return 21; case 'U': return 21;
	case 'v': return 22; case 'V': return 22;
	case 'w': return 23; case 'W': return 23;
	case 'x': return 24; case 'X': return 24;
	case 'y': return 25; case 'Y': return 25;
	case 'z': return 26; case 'Z': return 26;
	default: throw "illegal character";
	}
}

//do not forget to tweak this function if you change the alphabet
char Dictionary::i_to_c(int i) {
	switch (i) {
	case 1: return 'a';
	case 2: return 'b';
	case 3: return 'c';
	case 4: return 'd';
	case 5: return 'e';
	case 6: return 'f';
	case 7: return 'g';
	case 8: return 'h';
	case 9: return 'i';
	case 10: return 'j';
	case 11: return 'k';
	case 12: return 'l';
	case 13: return 'm';
	case 14: return 'n';
	case 15: return 'o';
	case 16: return 'p';
	case 17: return 'q';
	case 18: return 'r';
	case 19: return 's';
	case 20: return 't';
	case 21: return 'u';
	case 22: return 'v';
	case 23: return 'w';
	case 24: return 'x';
	case 25: return 'y';
	case 26: return 'z';
	default: throw "illegal integer";
	}
}

Dictionary::Word* Dictionary::getWord(string word) {
	Word* iterator = dictionary;
	for (int i = 0; i < word.length(); i++) {
		if (iterator == NULL)
		{
			return NULL;
		}
		iterator = iterator->next[c_to_i(word.at(i))];
	}
	if ((iterator == NULL) || (iterator->next[0] == NULL))
	{
		return NULL;
	}
	return iterator;
}

Dictionary::Word* Dictionary::destroyWord(Word* word) {
	if (word == NULL) return NULL;
	for (int i = 1; i <= LENGTH_ALPHABET; i++) { //do not start at 0 because 0 points to the class variable "stop"
		destroyWord(word->next[i]);
	}
	delete word->definition;
	delete word;
	return NULL;
}

//subroutine used in display
//initial call should be recursive_display(dictionary, an allocated buffer at least as long as the longest word in the dictionnary + 1, 0)
void Dictionary::recursive_display(Word* word, char* buffer, int n)
{
	if (word->next[0] == stop) {
		buffer[n] = '\0';
		printf("\t%s : %s\n", buffer, word->definition->data());
	}
	for (int i = 1; i <= LENGTH_ALPHABET; i++) {
		if (word->next[i] != NULL) {
			buffer[n] = i_to_c(i);
			recursive_display(word->next[i], buffer, n + 1);
		}
	}
}

Dictionary::Dictionary()
{
	dictionary = new Word;
	dictionary->definition = NULL;
	dictionary->next = new Word*[LENGTH_ALPHABET + 1];
	for (int i = 0; i <= LENGTH_ALPHABET; i++) {
		dictionary->next[i] = NULL;
	}
	stop = new Word;
	stop->previous = NULL;
	stop->next = NULL;
	stop->definition = NULL;
}


Dictionary::~Dictionary()
{
	for (int i = 1; i <= LENGTH_ALPHABET; i++) { //do not start at 0 because 0 points to the class variable "stop"
		destroyWord(dictionary->next[i]);
	}
	delete(dictionary);
	delete(stop);
}

void Dictionary::addWord(string word, string definition) {
	Word* iterator = dictionary;
	for (int i = 0; i < word.length(); i++) {
		if (iterator->next[c_to_i(word.at(i))] == NULL) {
			iterator->next[c_to_i(word.at(i))] = new Word;
			iterator->next[c_to_i(word.at(i))]->next = new Word*[LENGTH_ALPHABET + 1];
			iterator->next[c_to_i(word.at(i))]->previous = iterator;
			iterator->next[c_to_i(word.at(i))]->definition = NULL;
			for (int j = 0; j <= LENGTH_ALPHABET; j++) {
				iterator->next[c_to_i(word.at(i))]->next[j] = NULL;
			}
		}
		iterator = iterator->next[c_to_i(word.at(i))];
	}
	iterator->next[0] = stop;
	iterator->definition = new string(definition);
}

void Dictionary::removeWord(string word) {
	Word* current = getWord(word);
	if (current) //word is in the the dictionary
	{
		current->next[0] = NULL;
		bool flag;
		for (int i = word.length() - 1; i >= 0; i--) {
			//we want to know if that path is used by another word
			flag = false;
			for (int j = 0; j <= LENGTH_ALPHABET; j++) {
				if (current->next[j] != NULL) {
					flag = true;
					break;
				}
			}
			current = current->previous;
			if (flag == false) {
				current->next[c_to_i(word.at(i))] = destroyWord(current->next[c_to_i(word.at(i))]);
			}
		}

	}
}

bool Dictionary::searchWord(string word) {
	Word* temp = getWord(word);
	if (temp != NULL) {
		printf("%s : %s\n", word.data(), temp->definition->data());
		return true;
	}
	else {
		return false;
	}
}

void Dictionary::changeWordDefinition(string word, string definition) {
	Word* temp = getWord(word);
	if (temp == NULL) {
		printf("Word not in the dictionary\n");
		return;
	}
	delete temp->definition;
	temp->definition = new string(definition);
}

void Dictionary::display() {
	char* buffer = new char[256];
	recursive_display(dictionary, buffer, 0);
	delete[] buffer;
}

int main() {
	Dictionary dico;
	string word;
	string definition;
	int choice;
	do {
		printf("0 = Exit\n1 = Display the dictionary\n2 = Search a word\n3 = Add a word\n4 = Remove a word\n5 = Change definition\n----------\n");
		scanf_s("%d", &choice);
		switch (choice) {
		case 1:
			dico.display();
			break;
		case 2:
			printf("Enter word (0 to exit) : ");
			cin.ignore();
			getline(cin, word);
			if (word[0] != '0') {
				if (!dico.searchWord(word)) printf("%s is not in the dictionary\n", word.data());
			}
			break;
		case 3:
			printf("Enter word (0 to exit) : ");
			cin.ignore();
			getline(cin, word);
			if (word[0] == '0') break;
			printf("Enter definition (0 to exit) : ");
			getline(cin, definition);
			if (definition[0] != '0') {
				dico.addWord(word, definition);
			}
			break;
		case 4:
			printf("Enter word (0 to exit) : ");
			cin.ignore();
			getline(cin, word);
			if (word[0] != '0') {
				dico.removeWord(word);
			}
			break;
		case 5:
			printf("Enter word (0 to exit) : ");
			cin.ignore();
			getline(cin, word);
			if (word[0] == '0') break;
			printf("Enter definition (0 to exit) : ");
			getline(cin, definition);
			if (definition[0] != '0') {
				dico.changeWordDefinition(word, definition);
				dico.searchWord(word);
			}
			break;
		default:
			break;
		}
	} while (choice != 0);

	while (getchar() != '\n');
	return 0;
}