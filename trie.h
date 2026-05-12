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
        TrieNode* root;

        void print(const TrieNode* node, std::string prefix);
    
    public:
        Trie();
        ~Trie();

        void insert(const std::string& word, const std::string& hint);

        void batchInsert(std::vector<std::string>& words, std::vector<std::string>& hints);

        std::string search(const std::string& word);

        bool startsWith(const std::string& prefix);

        void deleteWord(const std::string& word);

        void printWord(TrieNode* node, std::string prefix) const;

        void printHint(const std::string& word) const;
        // Helper function for destructor
        void clear(TrieNode* node);

        void print() const;
};

#endif
