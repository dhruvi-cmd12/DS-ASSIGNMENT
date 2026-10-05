#include <iostream>
using namespace std;

int main() {
    int rollNo[5];

    cout << "Enter roll numbers of 5 students:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> rollNo[i];
    }

    cout << "\nRoll numbers entered:\n";
    for (int i = 0; i < 5; i++) {
        cout << rollNo[i] << endl;
    }

    return 0;
}
