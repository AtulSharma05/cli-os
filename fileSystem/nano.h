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

    if (temp == nullptr) {
        cout << "File not found" << endl;
        return;
    }

    string content = temp->content;  // Assuming getContent() retrieves the file's content as a string
    string editedContent = content;  // We'll modify this string as the user types
    char ch;
    int cursorPosition = content.size(); // Tracks the current position of the cursor in the content
    setNonCanonicalModes(true);  // Disable canonical mode for interactive editing

    cout << "Editing file: " << fileName << " (Press Ctrl+S to save, Ctrl+C to exit)\n";
    cout << editedContent;  // Display the current content of the file

    while (true) {
        ch = getchar();

        if (ch == 24) {  // Ctrl+C to exit without saving
            break;
        }

        if (ch == 19) {  // Ctrl+S to save the file
            temp->content=editedContent;  // Assuming setContent() stores the modified content
            cout << "\nFile saved as " << fileName << endl;
        }

        if (ch == 10) {  // Enter key (newline)
            editedContent.insert(cursorPosition, "\n");  // Insert a newline at the current cursor position
            cursorPosition++;
            clearLines();
            cout << editedContent;  // Reprint the edited content
        } else if (ch == 127) {  // Backspace key
            if (cursorPosition > 0) {
                editedContent.erase(cursorPosition - 1, 1);  // Remove one character before the cursor
                cursorPosition--;
                clearLines();
                cout << editedContent;  // Reprint the edited content
            }
        } else {  // Any other key input
            editedContent.insert(cursorPosition, 1, ch);  // Insert the character at the cursor position
            cursorPosition++;  // Move the cursor position forward
            clearLines();
            cout << editedContent;  // Reprint the edited content
        }
    }

    setNonCanonicalModes(false);  // Restore normal terminal behavior
    cout << "\nExiting nano...\n";

  
}