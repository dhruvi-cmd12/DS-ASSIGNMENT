#include <iostream>
using namespace std;

int main()
{
    int book[100];
    int count = 0;
    int choice;
    int id;
    bool found;

    do
    {
        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book ID\n";
        cout << "2. Display Book IDs\n";
        cout << "3. Search Book ID\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1)
        {
            cout << "Enter Book ID: ";
            cin >> book[count];

            count++;

            cout << "Book ID added successfully.\n";
        }

        else if(choice == 2)
        {
            cout << "\nBook IDs are:\n";

            if(count == 0)
            {
                cout << "No books added.\n";
            }
            else
            {
                for(int i = 0; i < count; i++)
                {
                    cout << book[i] << " ";
                }
                cout << endl;
            }
        }

        else if(choice == 3)
        {
            cout << "Enter Book ID to search: ";
            cin >> id;

            found = false;

            for(int i = 0; i < count; i++)
            {
                if(book[i] == id)
                {
                    found = true;
                    break;
                }
            }

            if(found)
            {
                cout << "Book ID found.\n";
            }
            else
            {
                cout << "Book ID not found.\n";
            }
        }

        else if(choice == 4)
        {
            cout << "Thank You! \n";
        }

        else
        {
            cout << "Invalid choice. Please enter 1 to 4.\n";
        }

    } while(choice != 4);

    return 0;
}