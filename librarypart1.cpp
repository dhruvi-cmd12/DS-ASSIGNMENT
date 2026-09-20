#include <iostream>
#include <string>
using namespace std;

int main()
{
    int ID1, ID2, ID3;
    string book1, book2, book3;

    cout << "Enter ID of Book 1: ";
    cin >> ID1;
    cin.ignore();    
    cout << "Enter title of Book 1: ";
    getline (cin, book1);


    cout << "Enter ID of Book 2: ";
    cin >> ID2;
    cin.ignore();
    cout << "Enter title of Book 2: ";
    getline(cin, book2);

    cout << "Enter ID of Book 3: ";
    cin >> ID3;
    cin.ignore();
    cout << "Enter title of Book 3: ";
    getline(cin, book3);

    cout << "\n*************************Library Book Information**************************";

    cout << "\nBook 1 ID: " << ID1 ;
    cout << "\nBook 1 Title: " << book1;

    cout << "\nBook 2 ID: " << ID2;
    cout << "\nBook 2 Title: " << book2 ;

    cout << "Book 3 ID: " << ID3 << endl;
    cout << "\nBook 3 Title: " << book3;

    return 0;
}