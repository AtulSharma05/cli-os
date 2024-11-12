#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include "../../linkedList/LinkedList.h"
#include "../FileSystem.h"
#include "../file.h"

using namespace std;

unordered_map<char, int> buildFrequencyTable(const string& data) {
    unordered_map<char, int> freqTable;
    for (char ch : data) {
        freqTable[ch]++;
    }
    return freqTable;
}

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

// Build Huffman tree from frequency table
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqTable) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    for (const auto& pair : freqTable) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        int mergedFreq = left->frequency + right->frequency;
        HuffmanNode* mergedNode = new HuffmanNode('\0', mergedFreq);
        mergedNode->left = left;
        mergedNode->right = right;
        minHeap.push(mergedNode);
    }
    return minHeap.top();
}

// Generate Huffman codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) {  
        huffmanCodes[root->character] = code;
    }
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Encode data using Huffman codes
string encodeData(const string& data, const unordered_map<char, string>& huffmanCodes) {
    string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes.at(ch);
    }
    return encodedData;
}

// Decode encoded data using Huffman tree
string decodeData(const string& encodedData, HuffmanNode* root) {
    string decodedData;
    HuffmanNode* current = root;
    for (char bit : encodedData) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {  // Leaf node
            decodedData += current->character;
            current = root;  
        }
    }
    return decodedData;
}

// Zip command: compresses a file's content
void FileSystem::zipCommand(file* fileName) {
    string data = fileName->content;
    if(data=="\0"){
        return;
    }

    // Build frequency table and Huffman tree
    unordered_map<char, int> freqTable = buildFrequencyTable(data);
    HuffmanNode* root = buildHuffmanTree(freqTable);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);
    string encodedData = encodeData(data, huffmanCodes);
    file compressedFile(fileName->name + ".zip");
    compressedFile.content = encodedData;
    this->files.append(compressedFile);
    
    cout << "File compressed successfully to " << compressedFile.name << "\n";
}

void FileSystem::unzipCommand(file* compressedFile) {
    if (compressedFile->name.find(".zip") == string::npos) {
        cout << "Error: File is not compressed.\n";
        return;
    }
    unordered_map<char, int> freqTable = buildFrequencyTable(compressedFile->content);
    HuffmanNode* root = buildHuffmanTree(freqTable);

    // Decode data
    string decodedData = decodeData(compressedFile->content, root);
    file decompressedFile(compressedFile->name.substr(0, compressedFile->name.size() - 4));
    decompressedFile.content = decodedData;
    this->files.append(decompressedFile);
    // Print success message
    cout << "File decompressed successfully to " << decompressedFile.name << "\n";
}
