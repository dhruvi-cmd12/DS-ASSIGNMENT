#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> history;
    int token;

    cout << "Enter 5 recently served token numbers (oldest to newest):\n";
    for (int i = 0; i < 5; i++) {
        cout << "Token " << i + 1 << ": ";
        cin >> token;
        history.push(token);
    }

    cout << "\nService history (most recent first):\n";
    while (!history.empty()) {
        cout << history.top() << endl;
        history.pop();
    }

    return 0;
}