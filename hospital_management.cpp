#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string disease;
    Patient* next;      // Linked List pointer
    Patient* hashNext;  // Hash Table pointer (chaining)
};

const int TABLE_SIZE = 10;

Patient* head = NULL;                // Linked List head
Patient* hashTable[TABLE_SIZE];      // Hash Table (array of chains)

// Hash function
int hashFunction(int id)
{
    return id % TABLE_SIZE;
}

// Search using Hash Table (collision resolved by chaining)
Patient* searchPatient(int id)
{
    int index = hashFunction(id);
    Patient* temp = hashTable[index];
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->hashNext;
    }
    return NULL;
}

// Register a new patient
void registerPatient()
{
    int id, age;
    string name, disease;

    cout << "Enter Patient ID: ";
    cin >> id;

    if (searchPatient(id) != NULL)
    {
        cout << "Patient ID already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Disease: ";
    getline(cin, disease);

    Patient* p = new Patient;
    p->id = id;
    p->name = name;
    p->age = age;
    p->disease = disease;
    p->next = NULL;
    p->hashNext = NULL;

    // Insert at end of Linked List
    if (head == NULL)
        head = p;
    else
    {
        Patient* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = p;
    }

    // Insert into Hash Table (chaining: insert at front of bucket)
    int index = hashFunction(id);
    p->hashNext = hashTable[index];
    hashTable[index] = p;

    cout << "Patient registered successfully!\n";
}

// Search and display a patient
void displaySearch()
{
    int id;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    Patient* p = searchPatient(id);
    if (p == NULL)
        cout << "Patient not found!\n";
    else
    {
        cout << "\n--- Patient Found ---\n";
        cout << "ID      : " << p->id << endl;
        cout << "Name    : " << p->name << endl;
        cout << "Age     : " << p->age << endl;
        cout << "Disease : " << p->disease << endl;
    }
}

// Delete a patient from both Linked List and Hash Table
void deletePatient()
{
    int id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;

    Patient* target = searchPatient(id);
    if (target == NULL)
    {
        cout << "Patient not found!\n";
        return;
    }

    // Remove from Hash Table chain
    int index = hashFunction(id);
    Patient* curr = hashTable[index];
    Patient* prev = NULL;
    while (curr != NULL && curr->id != id)
    {
        prev = curr;
        curr = curr->hashNext;
    }
    if (prev == NULL)
        hashTable[index] = curr->hashNext;
    else
        prev->hashNext = curr->hashNext;

    // Remove from Linked List
    curr = head;
    prev = NULL;
    while (curr != NULL && curr->id != id)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL)
        head = curr->next;
    else
        prev->next = curr->next;

    delete curr;
    cout << "Patient record deleted successfully!\n";
}

// Display all patients (Linked List traversal)
void displayAll()
{
    if (head == NULL)
    {
        cout << "No patient records available.\n";
        return;
    }
    cout << "\n--- All Patient Records ---\n";
    Patient* temp = head;
    while (temp != NULL)
    {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Age: " << temp->age
             << " | Disease: " << temp->disease << endl;
        temp = temp->next;
    }
}

// Display hash table (shows collisions / chains)
void displayHashTable()
{
    cout << "\n--- Hash Table ---\n";
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        cout << "[" << i << "] ";
        Patient* temp = hashTable[i];
        while (temp != NULL)
        {
            cout << temp->id << " -> ";
            temp = temp->hashNext;
        }
        cout << "NULL\n";
    }
}

int main()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;

    int choice;
    do
    {
        cout << "\n===== Smart Hospital Patient Record Management =====\n";
        cout << "1. Register New Patient\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Delete Patient Record\n";
        cout << "4. Display All Patients\n";
        cout << "5. Display Hash Table\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: registerPatient(); break;
            case 2: displaySearch(); break;
            case 3: deletePatient(); break;
            case 4: displayAll(); break;
            case 5: displayHashTable(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
