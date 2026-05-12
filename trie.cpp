#include <iostream>
#include "trie.h"

// Initialize node with nullptrs
TrieNode::TrieNode::TrieNode(){
    endOfWord = false;
    hint = "";
    for (int i = 0; i < 26; i++){
        children[i] = nullptr;
    }
}

// Trie constructor
Trie::Trie(){
    root = new TrieNode();
}

Trie::~Trie(){
    clear(root);
}

void Trie::clear(TrieNode* node){
    for (int i = 0; i < 26; i++){
        if (node->children[i]){
            clear(node->children[i]);
        }
    }
    delete node;
}

void Trie::insert(const std::string& word, const std::string& hint) {
    TrieNode* node = root;
    // for every character in the word
    for (char c : word){
        // get the alphabetical position of the character starting from 0 using the ASCII integer values of the characters
        int index = c - 'a';
        if (!node->children[index]){
            // if the root node doesn't have that character, add a new node that has that character
            node->children[index] = new TrieNode(); 
        }
        node = node->children[index];
    }
    node->endOfWord = true;
    node->hint = hint;
}

void Trie::batchInsert(std::vector<std::string>& words, std::vector<std::string>& hints){
    for(int i = 0; i < words.size(); i++){
        this->insert(words[i], hints[i]);
    }
}

std::string Trie::search(const std::string& word){
    TrieNode* node = root;
    for (char c : word){
        int index = c - 'a';
        if(!node->children[index]){
            return "";
        }
        node = node->children[index];
    }
    if (node->endOfWord){
        return node->hint;
    }
    return "";
}

bool Trie::startsWith(const std::string& prefix){
    TrieNode* node = root;
    for (char c : prefix){
        int index = c - 'a';
        if(!node->children[index]){
            return false;
        }
        node = node->children[index];
    }
    return true;
}

void Trie::deleteWord(const std::string& word){
    TrieNode* node = root;
    for (char c : word){
        int index = c - 'a';
        if(!node->children[index]){
            return;
        }
        node = node->children[index];
    }
    if (node->endOfWord){
        node->endOfWord = false;
        node->hint = "";
    }
}

void Trie::printWord(TrieNode* node, std::string prefix) const {
    if (node->endOfWord){
        std::cout << prefix << std::endl;
    }
    for (int i = 0; i < 26; i++){
        if (node->children[i]){
            printWord(node->children[i], prefix + char('a' + i));
        }
    }
}
void Trie::printHint(const std::string& word) const {
    TrieNode* node = root;
    for (char c : word){
        int index = c - 'a';
        if (!node->children[index]){
            return;
        }
        node = node->children[index];
    }

    if (node->endOfWord){
        std::cout << node->hint << std::endl;
    }
}

void Trie::print() const {
    printWord(root,"");
}


