
#include "./commandProcessor/CommandProcessor.h"
#include "./commandProcessor/CommandProcessorfuncs.h"
#include "./stack/Stack.h"
#include "./stack/Stackfunc.h"
#include "./fileSystem/FileSystem.h"
#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>

using namespace std;
void setNonCanonicalMode(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    
    if (enable) {
        tty.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    } else {
        tty.c_lflag |= (ICANON | ECHO);   // Enable canonical mode and echoing
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
void clearLine() {
    cout << "\r";  // Move cursor to the beginning of the line
    cout << string(100, ' ');  // Clear the line by overwriting with spaces
    cout << "\r";  // Move cursor back to the beginning of the line
}
int main() {
    setNonCanonicalMode(true);
    UserManager root;
   vector<UserManager> users;
   users.push_back(root);
    string command;
    CommandProcessor cp;
    Stack<string> commands;
    Stack<string> tempCommands;
    cout << "Welcome to the CLI Operating System.\n";
    cout << "Type 'exit' to quit.\n";
    cout << "Type 'help' for a list of available commands.\n";
int historyIndex=-1;
  char ch;
    // while (true) {
    //     ch = getchar();  // Get single character input
        
    //     if (ch == '\033') { // If the first character is an escape sequence
    //         getchar();      // Skip the '[' character
    //         switch(getchar()) {
    //             case 'A':   // Up arrow
    //                 cout << "Up arrow pressed!" << endl;
    //                 break;
    //             case 'B':   // Down arrow
    //                 cout << "Down arrow pressed!" << endl;
    //                 break;
    //             case 'C':   // Right arrow
    //                 cout << "Right arrow pressed!" << endl;
    //                 break;
    //             case 'D':   // Left arrow
    //                 cout << "Left arrow pressed!" << endl;
    //                 break;
    //         }
    //     } else if (ch == '\n') {
    //         commands.push(command);
    //         cp.processCommand(users,command);
    //     }
    //     else {
    //         command += ch;
    //         cout<<ch;
    //         }

    // }
     cout << "> ";
     while (true) {
        ch = getchar();  // Get single character input

        if (ch == '\033') {  // If the first character is an escape sequence (arrow key)
            getchar();  // Skip the '[' character
            switch (getchar()) {
                case 'A':  // Up arrow (navigate through command history)
                    
                        if(commands.isEmpty()){
                        
                            break;
                        }
                        command = commands.top(); 
                        tempCommands.push(command);
                        commands.pop(); // Retrieve previous command
                        clearLine();  // Clear the line before displaying the command
                        cout << "> " << command;  // Show previous command
                    
                    break;
                case 'B':  
                        if(tempCommands.isEmpty()){
                            clearLine();
                            cout<<"> ";
                            break;
                        }
                        if(command==tempCommands.top()){
                            tempCommands.pop();
                        }
                        command = tempCommands.top(); 
                        commands.push(command);
                        tempCommands.pop(); // Retrieve previous command
                        clearLine();  // Clear the line before displaying the command
                        cout << "> " << command;  // Show previous command
                    
                    break;
            }
        } else if (ch == '\n') {  // Enter key
            if (!command.empty()) {
                if (command == "exit") {
                    break;  // Exit the CLI
                }

                commands.push(command);  // Store the command in history
             
                cout<<"\n>";
                cp.processCommand(users, command);  // Process the command
                
                command.clear();  // Clear the command after processing
            }
            cout << "\n> ";  // Prompt for the next command
        } else if (ch == 127) {  
            if (!command.empty()) {
                command.pop_back();  // Remove the last character from the command
                clearLine();
                cout << "> " << command;  // Update the displayed command
            }
        } else {
            command += ch;  // Append character to the current command
            cout << ch;  // Print the character as typed
        }
    }


    setNonCanonicalMode(false);

    return 0;
}
