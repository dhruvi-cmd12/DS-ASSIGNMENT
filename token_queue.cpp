#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> tokens;
    int token;

    cout << "Enter 5 customer token numbers:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Token " << i + 1 << ": ";
        cin >> token;
        tokens.push(token);
    }

    cout << "\nServing customers in order:\n";
    while (!tokens.empty()) {
        cout << "Serving token: " << tokens.front() << endl;
        tokens.pop();
    }

    return 0;
}