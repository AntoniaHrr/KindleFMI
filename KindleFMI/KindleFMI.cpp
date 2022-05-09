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
                cout << "No user found! Please sign up!" << endl;
            }
            else cout << "Login successful!"<<endl;
      
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
            
            kindleFMI.WriteBook(author, title, content);

        }
        if (strcmp(input, "list") == 0) {
            kindleFMI.ViewContent();
        }
        /*if (strcmp(input, "view grade of book") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, 100);
            kindleFMI;
        }*/
        if (strcmp(input, "grade book") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, 100);
            int grade = 0;
            cout << "Rate the book:";
            cin >> grade;
            kindleFMI.AddRate(title, grade);
        }
        if (strcmp(input, "view comments") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, 100);
            kindleFMI.ViewComments(title);
        }
        if (strcmp(input, "leave comment") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, 100);
            char comment[4069];
            cout << "enter comment: ";
            cin.getline(comment, 4069);
            
            kindleFMI.AddComment(title, comment);
        }
        if (strcmp(input, "update") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, 100);
            char content[4069];
            cout << "enter content: ";
            cin.getline(content, 4069);
            char author[100];
            cout << "enter author: ";
            cin.getline(author, 100);
            kindleFMI.UpdateBook(title, author, content);
        }
        if (strcmp(input, "read") == 0) {
            char title[100];
            cout << "enter title:";
                cin.getline(title, 100);
                kindleFMI.ReadBook(title);
        }
        if (strcmp(input, "quit") == 0) {
            kindleFMI.Quit();
        }

    }
    


    return 0;
}
