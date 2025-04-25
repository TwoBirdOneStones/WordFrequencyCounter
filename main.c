
// Includes stuff
#include <stdio.h>
#include <string.h> // mem stuff
#include <stdlib.h>

// Linked List Node struct,
typedef struct Node{
    char *word;
    struct Node* next;
} Node;


// global vars
Node wordList = {NULL, NULL};

// other global vars
void AddWordToList(char *_word);
Node* CreateNode();
char* CreateWord(char *_word);
Node* FindEndOfList(Node *_startingNode);
void PrintList(Node *_startingNode);
void FreeList(Node *_startingNode);
FILE* OpenFile(char *_fileName);
void CloseFile(FILE *_file);
void SplitLineIntoWords(char *_line);
int GetWordFreq(Node *_startingNode, char *_word);


// Main Fuction.
int main(void) {
    char _input[256];
    fscanf(stdin, "%s", _input);
    FILE *_file = OpenFile(_input);
    if (_file == NULL) {
        printf("Could not open file %s\n", _input);
        return 0;
    }
    char _line[256];
    while (fgets(_line, sizeof(_line), _file)) {
        _line[strcspn(_line, "\n")] = '\0';
        SplitLineIntoWords(_line);
    }
    PrintList(&wordList);
    FreeList(&wordList);
    CloseFile(_file);
    return 0;
}

/*
 * Splits a line into words based on spaces,
 * then adds each word to the linked list.
 */
void SplitLineIntoWords(char *_line) {
    int _len = strlen(_line);
    int _start = 0;
    for (int i = 0; i <= _len; i++) {
        if (_line[i] == ' ' || _line[i] == '\0') {
            if (i > _start) {
                char _word[256] = {0};
                strncpy(_word, &_line[_start], i - _start);
                AddWordToList(_word);
            }
            _start = i + 1;
        }
    }
}



/*
 * Returns how many times _word appears in the list
 */
int GetWordFreq(Node *_startingNode, char *_word) {
    int _freq = 0;
    Node *_currentNode = _startingNode;
    while (_currentNode != NULL) {
        if (_currentNode->word != NULL && strcmp(_currentNode->word, _word) == 0) {
            _freq++;
        }
        _currentNode = _currentNode->next;
    }
    return _freq;
}


/*
 * Opens a file with read mode
 */
FILE* OpenFile(char *_fileName) {
    return fopen(_fileName, "r");
}


/*
 * Closes the given file
 */
void CloseFile(FILE *_file) {
    fclose(_file);
}

/*
 * Adds a word to the end of the linked list
 */
void AddWordToList(char *_word) {
    Node *_newNode = CreateNode();
    _newNode->word = CreateWord(_word);
    Node *_lastNode = FindEndOfList(&wordList);
    _lastNode->next = _newNode;
}

/*
 * Creates a new linked list node with NULL fields
 */
Node* CreateNode() {
    Node* _newNode = malloc(sizeof(Node));
    _newNode->next = NULL;
    _newNode->word = NULL;
    return _newNode;
}

/*
 * Dynamically allocates and returns a copy of the given word
 */
char* CreateWord(char *_word) {
    char* _newWord  = calloc((strlen(_word)+ 1), sizeof(char));
    strcpy(_newWord, _word);
    return _newWord;
}

/*
 * Traverses the list to find the last node
 */
Node* FindEndOfList(Node *_startingNode) {
    Node *_currentNode = _startingNode;
    while (_currentNode->next != NULL) {
        _currentNode = _currentNode->next;
    }
    return _currentNode;
}

/*
 * Prints each word and how many times it appears in the list
 */
void PrintList(Node *_startingNode) {
    Node* _nextNode = _startingNode->next;
    while (_nextNode != NULL) {
        char *_wordInNode = _nextNode->word;
        int _freqOfWordInNode = GetWordFreq(_startingNode, _wordInNode);
        printf("%s - %d\n", _wordInNode, _freqOfWordInNode);
        _nextNode = _nextNode->next;
    }
}

/*
 * Frees all nodes and their word strings from the list
 */
void FreeList(Node *_startingNode) {
    Node *_currentNode = _startingNode->next;
    Node *_nextNode;
    while (_currentNode != NULL) {
        _nextNode = _currentNode->next;
        free(_currentNode->word);
        free(_currentNode);
        _currentNode = _nextNode;
    }
    _startingNode->next = NULL;
}