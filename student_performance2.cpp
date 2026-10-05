#include <iostream>
using namespace std;

int main() {
    int rollNo[5], search;
    bool found = false;

    cout << "Enter roll numbers of 5 students:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> rollNo[i];
    }

    cout << "\nEnter roll number to search: ";
    cin >> search;

    for (int i = 0; i < 5; i++) {
        if (rollNo[i] == search) {
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