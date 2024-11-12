
#include "../commandProcessor/CommandProcessor.h"
#include "../commandProcessor/CommandProcessorfuncs.h"
#include "../stack/Stack.h"
#include "../stack/Stackfunc.h"
#include "../fileSystem/FileSystem.h"
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
   FileSystem *currentDirectory;
    string command;
    CommandProcessor cp;
    Stack<string> commands;
    Stack<string> tempCommands;
    cout << "Welcome to the CLI Operating System.\n";
    cout << "Type 'exit' to quit.\n";
    cout << "Type 'help' for a list of available commands.\n";
  char ch;
  cp.printCurrDir();
     cout << "> ";
     while (true) {
        ch = getchar();  

        if (ch == '\033') {  
            getchar();  // Skip the '[' character
            switch (getchar()) {
                case 'A':  // Up arrow (navigate through command history)
                    
                        if(commands.isEmpty()){
                        
                            break;
                        }
                        command = commands.top(); 
                        tempCommands.push(command);
                        commands.pop(); // Retrieve previous command
                        clearLine();  
                        cp.printCurrDir();
                        cout << "> " << command;  
                    
                    break;
                case 'B':  
                        if(tempCommands.isEmpty()){
                            clearLine();
                            cp.printCurrDir();
                            cout<<"> ";
                            break;
                        }
                        if(command==tempCommands.top()){
                            tempCommands.pop();
                        }
                        command = tempCommands.top(); 
                        commands.push(command);
                        tempCommands.pop(); // Retrieve previous command
                        clearLine();  
                        cp.printCurrDir();
                        cout << "> " << command;  
                    
                    break;
            }
        } else if (ch == '\n') {  
            if (!command.empty()) {
                if (command == "exit") {
                    break; 
                }

                commands.push(command);  
                cout<<endl;
             cp.printCurrDir();
                cout<<"> ";
                cp.processCommand(users, command);  
                cout<<endl;
             cp.printCurrDir();
                cout<<"> ";
                command.clear();  

             }
            else{cout<<endl;
             cp.printCurrDir();
                cout<<"> "; }
        } else if (ch == 127) { //Backspace key 
            if (!command.empty()) {
                command.pop_back();  
                clearLine();
                cp.printCurrDir();
                cout << "> " << command;  
            }
        } else {
            command += ch;
            cout << ch;
        }
    }


    setNonCanonicalMode(false);

    return 0;
}
