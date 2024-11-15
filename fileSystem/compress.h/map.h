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

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) {  
        huffmanCodes[root->character] = code;
    }
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

string encodeData(const string& data, const unordered_map<char, string>& huffmanCodes) {
    string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes.at(ch);
    }
    return encodedData;
}

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

// void FileSystem::zipCommand(file* fileName) {
//     string data = fileName->content;
//     if(data=="\0"){
//         return;
//     }

//     unordered_map<char, int> freqTable = buildFrequencyTable(data);
//     HuffmanNode* root = buildHuffmanTree(freqTable);
//     unordered_map<char, string> huffmanCodes;
//     generateCodes(root, "", huffmanCodes);
//     string encodedData = encodeData(data, huffmanCodes);
//     file compressedFile(fileName->name + ".zip");
//     compressedFile.content = encodedData;
//     this->files.append(compressedFile);
//     this->fileMap.insert(compressedFile.name, compressedFile);
    
//     cout << "File compressed successfully to " << compressedFile.name << "\n";
// }

// void FileSystem::unzipCommand(file* compressedFile) {
//     if (compressedFile->name.find(".zip") == string::npos) {
//         cout << "Error: File is not compressed.\n";
//         return;
//     }
//     unordered_map<char, int> freqTable = buildFrequencyTable(compressedFile->content);
//     HuffmanNode* root = buildHuffmanTree(freqTable);

//     string decodedData = decodeData(compressedFile->content, root);
//     cout<<decodedData;
//     file decompressedFile(compressedFile->name.substr(0, compressedFile->name.size() - 4)+"(2)");
//     decompressedFile.content = decodedData;
//     this->files.append(decompressedFile);
//      this->fileMap.insert(decompressedFile.name, decompressedFile);

//     cout << "File decompressed successfully to " << decompressedFile.name << "\n";
// }
void FileSystem::zipCommand(file* fileName) {
    string data = fileName->content;
    if(data.empty()){
        return;
    }

    unordered_map<char, int> freqTable = buildFrequencyTable(data);
    HuffmanNode* root = buildHuffmanTree(freqTable);
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);
    string encodedData = encodeData(data, huffmanCodes);
    
    string freqTableData;
    for (const auto& pair : freqTable) {
        freqTableData += string(1, pair.first) + "," + to_string(pair.second) + ";";

    }

    file compressedFile(fileName->name + ".zip");
    compressedFile.content = freqTableData + "|" + encodedData;
    this->files.append(compressedFile);
    this->fileMap.insert(compressedFile.name, compressedFile);

    cout << "File compressed successfully to " << compressedFile.name << "\n";
}
void FileSystem::unzipCommand(file* compressedFile) {
    if (compressedFile->name.find(".zip") == string::npos) {
        cout << "Error: File is not compressed.\n";
        return;
    }

    string content = compressedFile->content;
    size_t delimiterPos = content.find("|");
    if (delimiterPos == string::npos) {
        cout << "Error: Invalid compressed file format.\n";
        return;
    }
    
    string freqTableData = content.substr(0, delimiterPos);
    string encodedData = content.substr(delimiterPos + 1);

    unordered_map<char, int> freqTable;
    size_t pos = 0;
   while ((pos = freqTableData.find(";")) != string::npos) {
    string entry = freqTableData.substr(0, pos);
    size_t commaPos = entry.find(",");
    if (commaPos == string::npos) {
        cout << "Error: Invalid frequency table format.\n";
        return;
    }
    char character = entry[0];  // or `entry[0]` depending on how it's stored
    int frequency = stoi(entry.substr(commaPos + 1));
    freqTable[character] = frequency;
    freqTableData.erase(0, pos + 1);
}

    HuffmanNode* root = buildHuffmanTree(freqTable);
    string decodedData = decodeData(encodedData, root);
    
    file decompressedFile(compressedFile->name.substr(0, compressedFile->name.size() - 4) + "(2)");
    decompressedFile.content = decodedData;
    this->files.append(decompressedFile);
    this->fileMap.insert(decompressedFile.name, decompressedFile);

    cout << "File decompressed successfully to " << decompressedFile.name << "\n";
}

