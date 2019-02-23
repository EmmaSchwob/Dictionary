#pragma once

class Dictionary
{
	static const int LENGTH_ALPHABET = 26; //0 is a stop, 1 an a, 2 a b, etc; change this if the language used has more/less than 26 characters
	struct Word {
		Word** next;
		Word* previous;
		std::string* definition;
	};
	Word* dictionary;
	Word* stop; //to indicate that a word ending with this letter exists
	int c_to_i(char c);
	char i_to_c(int i);
	Word* getWord(std::string word);
	Word* destroyWord(Word* word);
	void recursive_display(Word* word, char* buffer, int n);

public:
	Dictionary();
	~Dictionary();
	void addWord(std::string word, std::string definition);
	void removeWord(std::string word);
	bool searchWord(std::string word);
	void changeWordDefinition(std::string word, std::string definition);
	void display();
};

