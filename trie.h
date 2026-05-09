#include <iostream>
#include <string>

#ifndef TRIE_H
#define TRIE_H

class TrieNode {
    public:
        bool endOfWord;
        TrieNode* children[26];

        TrieNode();
};

class Trie {
    private: 
        TrieNode* root;

        void print(const TrieNode* node, std::string prefix);
    
    public:
        Trie();
        ~Trie();

        void insert(const std::string& word);

        bool search(const std::string& word);

        bool startsWith(const std::string& prefix);

        void deleteWord(const std::string& word);

        void print(TrieNode* node, std::string prefix) const;

        // Helper function for destructor
        void clear(TrieNode* node);

        void print() const;
};

#endif
