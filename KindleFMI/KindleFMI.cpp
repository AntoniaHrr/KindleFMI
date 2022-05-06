#include <iostream>
#include "Kindle.h"

using namespace std;

int main()
{
    Kindle kindleFMI;
    char input[4096];
   
    while (true) {
        cout << "command: ";
        cin.getline(input, 4096);
        if (strcmp(input, "login") == 0) {
            char username[100];
            char password[100];
            cout << "enter username: ";
            cin.getline(username, 100);
            cout << "enter password: ";
            cin.getline(password, 100);
            if (kindleFMI.Login(username, password) == 0)
            {
                cout << "No user found! Please sign up!"<<endl;
            }
      
        }
        if (strcmp(input, "register") == 0) {
            char username[100];
            char password[100];
            cout << "enter username: ";
            cin.getline(username, 100);
            cout << "enter password: ";
            cin.getline(password, 100);
            kindleFMI.Register(username, password);  
           
        }
        if (strcmp(input, "write") == 0) {
            char content[100];
            char author[100];
            char title[100];
            cout << "enter author: ";
            cin.getline(author, 100);
            cout << "enter title: ";
            cin.getline(title, 100);
            cout << "enter content: ";
            cin.getline(content, 100);
            
            kindleFMI.Write(author, title, content);

        }
        if (strcmp(input, "quit") == 0) {
            kindleFMI.Quit();
        }
        if (strcmp(input, "get") == 0) {
            cout << kindleFMI.getUsername() << endl;
        }

    }
    


    return 0;
}
