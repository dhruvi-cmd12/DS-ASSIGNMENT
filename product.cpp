#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ---------- Linked list node (one product) ----------
struct Product {
    int id;
    string name;
    double price;
    int quantity;
    Product* next;

    Product(int i, string n, double p, int q)
        : id(i), name(n), price(p), quantity(q), next(nullptr) {}
};

// ---------- Hash table with chaining (each bucket = linked list) ----------
class ProductCatalog {
    static const int SIZE = 10;
    Product* table[SIZE];

    int hashFunction(int id) const {
        return id % SIZE;
    }

public:
    ProductCatalog() {
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }

    ~ProductCatalog() {
        for (int i = 0; i < SIZE; i++) {
            Product* cur = table[i];
            while (cur) {
                Product* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }

    // Fast lookup by Product ID: O(1) average
    Product* search(int id) const {
        Product* cur = table[hashFunction(id)];
        while (cur) {
            if (cur->id == id) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Add new product (collision handled by chaining: insert at head of list)
    void addProduct(int id, const string& name, double price, int qty) {
        if (search(id)) {
            cout << "Product ID " << id << " already exists.\n";
            return;
        }
        int idx = hashFunction(id);
        if (table[idx]) {
            cout << "(Collision at index " << idx << " -> resolved by chaining)\n";
        }
        Product* p = new Product(id, name, price, qty);
        p->next = table[idx];
        table[idx] = p;
        cout << "Product added successfully.\n";
    }

    // Update product details
    void updateProduct(int id) {
        Product* p = search(id);
        if (!p) {
            cout << "Product not found.\n";
            return;
        }
        cout << "Enter new name: ";
        cin >> ws;
        getline(cin, p->name);
        cout << "Enter new price: ";
        cin >> p->price;
        cout << "Enter new quantity: ";
        cin >> p->quantity;
        cout << "Product updated successfully.\n";
    }

    // Remove discontinued product
    void removeProduct(int id) {
        int idx = hashFunction(id);
        Product* cur = table[idx];
        Product* prev = nullptr;

        while (cur) {
            if (cur->id == id) {
                if (prev) prev->next = cur->next;
                else table[idx] = cur->next;
                delete cur;
                cout << "Product removed successfully.\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Product not found.\n";
    }

    // Display all available products
    void displayAll() const {
        bool empty = true;
        cout << "\n--- Product Catalog ---\n";
        for (int i = 0; i < SIZE; i++) {
            Product* cur = table[i];
            if (cur) {
                empty = false;
                cout << "Bucket " << i << ": ";
                while (cur) {
                    cout << "[ID:" << cur->id << ", " << cur->name
                         << ", Rs." << cur->price
                         << ", Qty:" << cur->quantity << "]";
                    if (cur->next) cout << " -> ";
                    cur = cur->next;
                }
                cout << "\n";
            }
        }
        if (empty) cout << "No products available.\n";
    }

    void displayProduct(int id) const {
        Product* p = search(id);
        if (!p) {
            cout << "Product not found.\n";
            return;
        }
        cout << "ID: " << p->id << ", Name: " << p->name
             << ", Price: Rs." << p->price
             << ", Quantity: " << p->quantity << "\n";
    }
};

int main() {
    ProductCatalog catalog;
    int choice, id, qty;
    double price;
    string name;

    do {
        cout << "\n===== E-Commerce Inventory System =====\n"
             << "1. Add Product\n"
             << "2. Update Product\n"
             << "3. Remove Product\n"
             << "4. Search Product\n"
             << "5. Display All Products\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter Product ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> qty;
            catalog.addProduct(id, name, price, qty);
            break;
        case 2:
            cout << "Enter Product ID to update: ";
            cin >> id;
            catalog.updateProduct(id);
            break;
        case 3:
            cout << "Enter Product ID to remove: ";
            cin >> id;
            catalog.removeProduct(id);
            break;
        case 4:
            cout << "Enter Product ID to search: ";
            cin >> id;
            catalog.displayProduct(id);
            break;
        case 5:
            catalog.displayAll();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
