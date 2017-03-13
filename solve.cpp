#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include "trie.h"

#define BOARD_SIZE 4

struct Board {
    char elements[BOARD_SIZE][BOARD_SIZE];
    void fill(std::string letters);
    void display();
    bool isValidCell(std::pair<int,int> coordinates);
    void solve(Trie& t);
    void solve(std::string prefix, 
               std::pair<int,int> coordinates, 
               Trie& tree, 
               std::set<std::pair<int,int>> combinations,
               std::vector<std::string>& results);
};

void Board::fill(std::string letters) {
    // Fills the board from a string
    int idx = 0;
    for (char& c : letters) {
        elements[idx/BOARD_SIZE][idx%BOARD_SIZE]=c;
        ++idx;
    }
}

void Board::display() {
    for (int i=0 ; i<BOARD_SIZE ; ++i) {
        for (int j=0; j<BOARD_SIZE ; ++j) {
            std::cout << elements[i][j];
        }
        std::cout << std::endl;
    }
}

bool Board::isValidCell(std::pair<int, int> coordinates) {
  return (coordinates.first >= 0 &&
          coordinates.first < BOARD_SIZE &&
          coordinates.second >= 0 &&
          coordinates.second < BOARD_SIZE);
}

void Board::solve(std::string prefix, 
                  std::pair<int,int> coordinates, 
                  Trie& tree, 
                  std::set<std::pair<int,int>> combinations,
                  std::vector<std::string>& results) {

     // Recursive function called for each new cell on the board
     // It checks if the current word exists, if it is still a prefix
     // And moves to next possibilities

     combinations.insert(coordinates);
     std::string newWord=prefix+elements[coordinates.first][coordinates.second];
     if (tree.isWord(newWord)) {
       results.push_back(newWord);
     }
     if (tree.isPrefix(newWord)) {
       for (int i=-1; i<2; ++i) {
         for (int j=-1; j<2 ; ++j) {
           std::pair<int, int> newCoord(coordinates.first + i, coordinates.second+j);
           if (this->isValidCell(newCoord)) {
               auto alreadyUsed = combinations.find(newCoord);
               if (alreadyUsed == combinations.end()) {
                   solve(newWord, newCoord, tree, combinations, results);
               }
           }
         }
       }
     }
}

void Board::solve(Trie& t) {

    // Entry point function to solve a board

    // Set to store all the combinations that have been explored
    std::set<std::pair<int,int>> combinations;

    // Should probably be a set
    std::vector<std::string> results;

    // Calls the recursive function for each cell, starting with an empty word
    // The combinations start empty
    // The results are passed by reference, the same object is kept
    for (int i=0; i<4 ; ++i) {
        for (int j=0; j<4 ; ++j) {
          std::pair<int, int> coordinates(i,j);
          solve("", coordinates, t, combinations, results);
        }
    }


    // All this can be done better with a better compare function or using a set??
    // First sorting, lexicographic
    std::sort(results.begin(), results.end());
    // Remove duplicates
    auto last = std::unique(results.begin(), results.end());
    results.erase(last, results.end());
    // Sort by length
    std::sort(results.begin(), results.end(), [](std::string a, std::string b) { return a.size() < b.size(); });

    for (auto word: results) {
      std::cout << word << std::endl;
    }
}

int main() {

    Trie t;
    t.loadFromFile("dictionary.txt");

    Board b;
    std::cout << "Enter board:" << std::endl;
    std::string boardInput;
    std::cin >> boardInput;
    b.fill(boardInput);
    //b.display();
    b.solve(t);
}
