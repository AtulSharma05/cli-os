#pragma once
#include "FileSystem.h"
#include "file.h"
#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
using namespace std;

void setNonCanonicalModes(bool enable) {    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);

    if (enable) {
        tty.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable flow control (Ctrl+S and Ctrl+Q)
    } else {
        tty.c_lflag |= (ICANON | ECHO);  // Enable canonical mode and echoing
        tty.c_iflag |= (IXON | IXOFF | IXANY);  // Enable flow control (Ctrl+S and Ctrl+Q)
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);}

void clearLines() {
    cout << "\r";  
    cout << string(100, ' '); 
    cout << "\r";  
}

void FileSystem::nanoEditor(string& fileName){
    file* temp = this->findFile(fileName);  // Locate the file in the file system
int line=1;
    if (temp == nullptr) {
        cout << "File not found" << endl;
        return;
    }

    string content = temp->content;  
    string editedContent = content; 
    char ch;
    int cursorPosition = content.size(); 
    setNonCanonicalModes(true);  

    cout << "Editing file: " << fileName << " (Press Ctrl+S to save, Ctrl+X to exit)\n";
    cout << editedContent;  // Display the current content of the file

    while (true) {
        ch = getchar();

        if (ch == 24) {  
            break;
        }

        if (ch == 19) {  
            temp->content=editedContent;  
            cout << "\nFile saved as " << fileName << endl;
        }

        if (ch == 10) {  // Enter key (newline)
            editedContent.insert(cursorPosition, "\n");  
            cursorPosition++;
            line++;
           
            clearLines();
            cout << editedContent;  
        } else if (ch == 127) {  // Backspace key
            if (cursorPosition > 0) {
                editedContent.erase(cursorPosition - 1, 1);  
                cursorPosition--;
                
                clearLines();
                cout << editedContent; 
            }
        } else {  
            editedContent.insert(cursorPosition, 1, ch);  
            cursorPosition++; 
             
            clearLines();
            cout << editedContent;  // Reprint the edited content
        }
    }

    setNonCanonicalModes(false);  
    cout << "\nExiting nano...\n";

  
}