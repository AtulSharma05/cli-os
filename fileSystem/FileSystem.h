

#include <string>

class FileSystem {
private:
    struct Node {
        std::string name;
        bool isDirectory;
        Node* parent;
        Node* firstChild;
        Node* nextSibling;

        Node(const std::string& nodeName, bool isDir, Node* parentNode);
    };

    Node* root;
    Node* currentDir;

public:
   FileSystem() {
    root = new Node("/", true, nullptr);
    currentDir = root;

}

FileSystem(const std::string& nodeName, bool isDir, Node* parentNode){
    root = new Node(nodeName, isDir, parentNode);
    currentDir = root;
    
}
    void createDirectory(const std::string& dirName);
    void listFiles();
    void changeDirectory(const std::string& dirName);
    void printWorkingDirectory();
};

