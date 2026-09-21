#include <iostream>
using namespace std;

int main() {
    int rollNo[5], key;
    bool found = false;

    cout << "Enter 5 roll numbers:\n";
    for (int i = 0; i < 5; i++) {
        cin >> rollNo[i];
    }

    cout << "Enter roll number to search: ";
    cin >> key;

    for (int i = 0; i < 5; i++) {
        if (rollNo[i] == key) {
            found = true;
            break;
        }
    }

    if (found)
        cout << "Student found" << endl;
    else
        cout << "Student not found" << endl;

    return 0;
}