#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> tokens;
    int nextToken = 1;
    int choice;

    do {
        cout << "\n===== Bank Token System =====\n";
        cout << "1. Issue a token\n";
        cout << "2. Display all tokens\n";
        cout << "3. Serve a customer\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tokens.push(nextToken);
                cout << "Token issued: " << nextToken << endl;
                nextToken++;
                break;

            case 2:
                if (tokens.empty()) {
                    cout << "No tokens in the queue." << endl;
                } else {
                    cout << "Tokens waiting: ";
                    queue<int> temp = tokens;   // copy so the original is unchanged
                    while (!temp.empty()) {
                        cout << temp.front() << " ";
                        temp.pop();
                    }
                    cout << endl;
                }
                break;

            case 3:
                if (tokens.empty()) {
                    cout << "No customers to serve." << endl;
                } else {
                    cout << "Serving token: " << tokens.front() << endl;
                    tokens.pop();
                }
                break;

            case 4:
                cout << "Exiting program. Thank you!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}