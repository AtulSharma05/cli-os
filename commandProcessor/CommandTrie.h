// CommandTrie.h
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
class TrieNode {
public:
    bool isEndOfCommand;
    unordered_map<char, TrieNode*> children;

    TrieNode() : isEndOfCommand(false) {}
};

class CommandTrie {
private:
    TrieNode* root;

    void autoCompleteHelper(TrieNode* node, const string& prefix, vector<string>& results) {
        if (node->isEndOfCommand) {
            results.push_back(prefix);
        }
        for (auto& [ch, child] : node->children) {
            autoCompleteHelper(child, prefix + ch, results);
        }
    }

public:
    CommandTrie() {
        root = new TrieNode();
    }

    // Insert a command into the trie
    void insertCommand(const string& command) {
        TrieNode* current = root;
        for (char ch : command) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfCommand = true;
    }

    vector<string> getAutoCompleteSuggestions(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return {};  
            }
            current = current->children[ch];
        }
        vector<string> suggestions;
        autoCompleteHelper(current, prefix, suggestions);
        return suggestions;
    }
};
