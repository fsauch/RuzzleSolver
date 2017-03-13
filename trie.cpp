#include <iostream>
#include <fstream>
#include "trie.h"

void Trie::addWord(std::string word) {
    Node* parent = root;
    for (char& c : word) {
        Node*& node = parent->childrens[c - 'a'];
        if (node) {
            parent = node;
            continue;
        }
        else {
            Node* n = new Node();
            node = n;
            parent = n;
        }
    }
    parent->isWord = true;
}

bool Trie::isWord(std::string word) {
    Node* parent = root;
    for (char& c : word) {
        Node* node = parent->childrens[c - 'a'];
        if (node) {
            parent = node;
        }
        else {
            return false;
        }
    }
    if (parent->isWord) {
       return true;
    }
    return false;
}

bool Trie::isPrefix(std::string prefix) {
    Node* parent = root;
    for (char& c : prefix) {
        Node* node = parent->childrens[c - 'a'];
        if (!node) {
            return false;
        }
        parent = node;
    }
    return true;
}

void Trie::loadFromFile(std::string filename) {
    std::ifstream dict;
    dict.open(filename);
    std::string line;
    if (dict.is_open()) {
        while (getline (dict, line)) {
            this->addWord(line);
        }
        dict.close();
    }
}
