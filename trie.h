struct Node {
    Node* childrens[26];
    bool isWord;
};

class Trie {
    Node* root;
    void addWord(std::string word);
    
    public:
        Trie() { root = new Node(); }
        bool isWord(std::string word);
        bool isPrefix(std::string prefix);
        void loadFromFile(std::string filename);
};
