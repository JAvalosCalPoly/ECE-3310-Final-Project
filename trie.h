#include <iostream>
#include <string>
#include <vector>

#ifndef TRIENODE
#define TRIENODE

class TrieNode {
    public:
        bool endOfWord;
        TrieNode* children[26];
        std::string hint;

        TrieNode();
};
#endif

#ifndef TRIE_H
#define TRIE_H

class Trie {
    private: 
    // First node in the trie
        TrieNode* root;
    // Prints all the words in the trie
        void print(const TrieNode* node, std::string prefix);
    
    public:
    // Trie constructor 
        Trie();
    // Trie destructor
        ~Trie();

    // Inserts words with an associated hint
        void insert(const std::string& word, const std::string& hint);

    // Insert multiple words at a time with its associated hint from two lists of words and hints
        void batchInsert(std::vector<std::string>& words, std::vector<std::string>& hints);

    // Searches for a word in the trie
        std::string search(const std::string& word);

    // Checks if a word starts with a letter
        bool startsWith(const std::string& prefix);

    // Deletes a word from the trie
        void deleteWord(const std::string& word);

    // Prints a word from the trie
        void printWord(TrieNode* node, std::string prefix) const;

    // Prints a hint from the trie
        void printHint(const std::string& word) const;

    // Helper function for destructor
        void clear(TrieNode* node);

    // User accessible print function to print all the words
        void print() const;
};

#endif
