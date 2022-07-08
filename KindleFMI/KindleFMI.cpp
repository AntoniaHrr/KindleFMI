#include <iostream>
#include "Kindle.h"
#define MAX 4069
#define MAX_LENGHT 100

using namespace std;

int main()
{
    Kindle kindleFMI;
    kindleFMI.ReadUsersandBooks();
    char input[MAX];

   
    while (true) {
        cout << "command:";
        cin.getline(input, MAX);

        if (strcmp(input, "menu") == 0) {
            cout << "login" << endl;
            cout << "register" << endl;
            cout << "write" << endl;
            cout << "list" << endl;
            cout << "grade book" << endl;
            cout << "view grade of book" << endl;
            cout << "leave comment" << endl;
            cout << "view comments" << endl;
            cout << "read page from book" << endl;
            cout << "read" << endl;
            cout << "update" << endl;
            cout << "quit" << endl;
        }
        
        if (strcmp(input, "login") == 0) {
            char username[MAX_LENGHT];
            char password[MAX_LENGHT];
            cout << "enter username: ";
            cin.getline(username, MAX_LENGHT);
            cout << "enter password: ";
            cin.getline(password, MAX_LENGHT);
            if (kindleFMI.Login(username, password) == 0)
            {
                cout << "No user found! Please sign up!" << endl;
            }
            else cout << "Login successful!"<<endl;
      
        }
        if (strcmp(input, "register") == 0) {
            char username[MAX_LENGHT];
            char password[MAX_LENGHT];
            cout << "enter username: ";
            cin.getline(username, MAX_LENGHT);
            cout << "enter password: ";
            cin.getline(password, MAX_LENGHT);
            kindleFMI.Register(username, password);  
           
        }
        if (strcmp(input, "write") == 0) {
            char content[MAX_LENGHT];
            char author[MAX_LENGHT];
            char title[MAX_LENGHT];
            cout << "enter author: ";
            cin.getline(author, MAX_LENGHT);
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            cout << "enter content: ";
            cin.getline(content, MAX_LENGHT);
            
            kindleFMI.WriteBook(author, title, content);

        }
        if (strcmp(input, "list") == 0) {
            kindleFMI.ViewContent();
        }
        if (strcmp(input, "view grade of book") == 0) {
            char title[100];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            kindleFMI.ViewRating(title);
        }
        if (strcmp(input, "grade book") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            int grade = 0;
            cout << "Rate the book:";
            cin >> grade;
            cin.ignore();
            kindleFMI.AddRate(title, grade);
        }
        if (strcmp(input, "view comments") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            kindleFMI.ViewComments(title);
        }
        if (strcmp(input, "read page from book") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            int page;
            cout << "enter page:";
            cin>> page;
            cin.ignore();
            kindleFMI.ReadPageFromBook(title, page);
        }
        if (strcmp(input, "leave comment") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            char comment[MAX];
            cout << "enter comment: ";
            cin.getline(comment, MAX);
            
            kindleFMI.AddComment(title, comment);
        }
        if (strcmp(input, "update") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title: ";
            cin.getline(title, MAX_LENGHT);
            char content[MAX];
            cout << "enter content: ";
            cin.getline(content, MAX);
            char author[MAX_LENGHT];
            cout << "enter author: ";
            cin.getline(author, MAX_LENGHT);
            kindleFMI.UpdateBook(title, author, content);
        }
        if (strcmp(input, "read") == 0) {
            char title[MAX_LENGHT];
            cout << "enter title:";
                cin.getline(title, MAX_LENGHT);
                kindleFMI.ReadBook(title);
        }
        if (strcmp(input, "quit") == 0) {
            kindleFMI.Quit();
        }

    }
    


    return 0;
}
