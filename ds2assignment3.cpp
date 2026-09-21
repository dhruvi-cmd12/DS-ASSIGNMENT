#include <iostream>
using namespace std;

int main() {
    int marks[5];

    cout << "Enter marks of 5 students:\n";
    for (int i = 0; i < 5; i++) {
        cin >> marks[i];
    }

    // Bubble sort in descending order
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (marks[j] < marks[j + 1]) {
                int temp = marks[j];
                marks[j] = marks[j + 1];
                marks[j + 1] = temp;
            }
        }
    }

    cout << "\nMarks from highest to lowest:\n";
    for (int i = 0; i < 5; i++) {
        cout << marks[i] << endl;
    }

    return 0;
}