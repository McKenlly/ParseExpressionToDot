#include <iostream>
#include <string>
#include <zconf.h>

#include "TreeExpresssion.h"

using namespace std;
void Help() {
    std::cout << "Enter actions:" << std::endl;
    std::cout << "1) Calculate expression" << std::endl;
    std::cout << "2) Print all lexem from expression" << std::endl;
    std::cout << "3) Create picture your expression tree" << std::endl;
    return;
}
void Introduce() {
    cout << "Hello from expression!" << endl;
    cout << "Now you must enter an aripthmetic expression with variables, numbers, round brackets and set of operations ('+', '-', '/' and '*')" << endl;
    cout << "If you use variables, application will ask you about their values after read expression. You can set it as by yourself and as by random." << endl;
    cout << "Application will check expression after all complete values and will say, if expression will incorrect." << endl << endl;
}
void CompileToDot();
int main() {
    string answer;
    Introduce();
    do {
        string e;
        cout << "Enter your expression: ";
        getline(cin, e);

        while (e.empty()) {
            cout << "Your expression is empty. Please, try again: ";
            getline(cin, e);
        }

        Expression expression(e);

        if (!expression.correct()) {
            cout << "Your expression is incorrect." << endl <<
                 "Sorry, it`s not my problem. If you want try again with correct expression" << endl;
        } else {
            Tree* tree = expression.createTree();
            Help();
            size_t action;
            cin >> action;
            switch (action) {
                case 1: {
                    cout << "Tree: ";
                    expression.printTree(tree);
                    cout << endl;
                    break;
                }
                case 2: {
                    try {
                        cout << "Result: " << expression.calculate(&tree) << endl;
                    }
                    catch (const char* msg) {
                        cout << endl << "Error: " << msg << endl;
                    }
                    break;
                }
                case 3: {
                    expression.ToDot(tree);
                    cout << "Do you want compile into picture(y/n): ";
                    cin >> answer;
                    if (answer == "y") {
                        CompileToDot();
                    }
                    break;
                }
                default: {
                    cout << "Uncorrect choice" << endl;
                }
            }
            expression.deleteTree(&tree);
        }
        cout << endl << "Do you want to enter new expression? (y/n): ";
        cin >>  answer;
    } while (answer == "y");
}

void CompileToDot() {
    pid_t p;
    p = fork();
    if (p == 0) {
        execl("/bin/sh", "sh",  "./toDot.sh", (char *) 0);
        perror("execl failed");
    } else {
        return;
    }
}
