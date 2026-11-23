#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ---------- Linked list node for an enrolled course ----------
struct Course {
    string courseName;
    Course* next;

    Course(string c) : courseName(c), next(nullptr) {}
};

// ---------- Linked list node for a student record ----------
struct Student {
    int rollNo;
    string name;
    string department;
    Course* courses;   // linked list of enrolled courses
    Student* next;     // next student in the same bucket (chaining)

    Student(int r, string n, string d)
        : rollNo(r), name(n), department(d), courses(nullptr), next(nullptr) {}
};

// ---------- Hash table with chaining ----------
class RegistrationSystem {
    static const int SIZE = 10;
    Student* table[SIZE];

    int hashFunction(int rollNo) const {
        return rollNo % SIZE;
    }

    void freeCourses(Course* c) {
        while (c) {
            Course* tmp = c;
            c = c->next;
            delete tmp;
        }
    }

public:
    RegistrationSystem() {
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }

    ~RegistrationSystem() {
        for (int i = 0; i < SIZE; i++) {
            Student* cur = table[i];
            while (cur) {
                Student* tmp = cur;
                cur = cur->next;
                freeCourses(tmp->courses);
                delete tmp;
            }
        }
    }

    // Quick retrieval by Roll Number: O(1) average
    Student* search(int rollNo) const {
        Student* cur = table[hashFunction(rollNo)];
        while (cur) {
            if (cur->rollNo == rollNo) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Register new student
    void registerStudent(int rollNo, const string& name, const string& dept) {
        if (search(rollNo)) {
            cout << "Roll Number " << rollNo << " already exists.\n";
            return;
        }
        int idx = hashFunction(rollNo);
        if (table[idx]) {
            cout << "(Collision at index " << idx << " -> resolved by chaining)\n";
        }
        Student* s = new Student(rollNo, name, dept);
        s->next = table[idx];
        table[idx] = s;
        cout << "Student registered successfully.\n";
    }

    // Update student information
    void updateStudent(int rollNo) {
        Student* s = search(rollNo);
        if (!s) {
            cout << "Student not found.\n";
            return;
        }
        cout << "Enter new name: ";
        cin >> ws;
        getline(cin, s->name);
        cout << "Enter new department: ";
        getline(cin, s->department);
        cout << "Student information updated.\n";
    }

    // Enroll student in a course
    void enrollCourse(int rollNo, const string& course) {
        Student* s = search(rollNo);
        if (!s) {
            cout << "Student not found.\n";
            return;
        }
        for (Course* c = s->courses; c; c = c->next) {
            if (c->courseName == course) {
                cout << "Student is already enrolled in " << course << ".\n";
                return;
            }
        }
        Course* c = new Course(course);
        c->next = s->courses;
        s->courses = c;
        cout << "Enrolled in " << course << " successfully.\n";
    }

    // Withdraw student from a course
    void withdrawCourse(int rollNo, const string& course) {
        Student* s = search(rollNo);
        if (!s) {
            cout << "Student not found.\n";
            return;
        }
        Course* cur = s->courses;
        Course* prev = nullptr;
        while (cur) {
            if (cur->courseName == course) {
                if (prev) prev->next = cur->next;
                else s->courses = cur->next;
                delete cur;
                cout << "Withdrawn from " << course << " successfully.\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Student is not enrolled in " << course << ".\n";
    }

    // Remove student record
    void removeStudent(int rollNo) {
        int idx = hashFunction(rollNo);
        Student* cur = table[idx];
        Student* prev = nullptr;

        while (cur) {
            if (cur->rollNo == rollNo) {
                if (prev) prev->next = cur->next;
                else table[idx] = cur->next;
                freeCourses(cur->courses);
                delete cur;
                cout << "Student record removed successfully.\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Student not found.\n";
    }

    void printStudent(const Student* s) const {
        cout << "Roll No: " << s->rollNo << ", Name: " << s->name
             << ", Dept: " << s->department << "\n   Courses: ";
        if (!s->courses) cout << "None";
        for (Course* c = s->courses; c; c = c->next) {
            cout << c->courseName;
            if (c->next) cout << ", ";
        }
        cout << "\n";
    }

    void displayStudent(int rollNo) const {
        Student* s = search(rollNo);
        if (!s) {
            cout << "Student not found.\n";
            return;
        }
        printStudent(s);
    }

    void displayAll() const {
        bool empty = true;
        cout << "\n--- Registered Students ---\n";
        for (int i = 0; i < SIZE; i++) {
            for (Student* s = table[i]; s; s = s->next) {
                empty = false;
                cout << "[Bucket " << i << "] ";
                printStudent(s);
            }
        }
        if (empty) cout << "No students registered.\n";
    }
};

int main() {
    RegistrationSystem sys;
    int choice, roll;
    string name, dept, course;

    do {
        cout << "\n===== University Registration System =====\n"
             << "1. Register Student\n"
             << "2. Update Student Info\n"
             << "3. Enroll in Course\n"
             << "4. Withdraw from Course\n"
             << "5. Remove Student Record\n"
             << "6. Search Student\n"
             << "7. Display All Students\n"
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
            cout << "Enter Roll Number: ";
            cin >> roll;
            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter Department: ";
            getline(cin, dept);
            sys.registerStudent(roll, name, dept);
            break;
        case 2:
            cout << "Enter Roll Number: ";
            cin >> roll;
            sys.updateStudent(roll);
            break;
        case 3:
            cout << "Enter Roll Number: ";
            cin >> roll;
            cout << "Enter Course Name: ";
            cin >> ws;
            getline(cin, course);
            sys.enrollCourse(roll, course);
            break;
        case 4:
            cout << "Enter Roll Number: ";
            cin >> roll;
            cout << "Enter Course Name: ";
            cin >> ws;
            getline(cin, course);
            sys.withdrawCourse(roll, course);
            break;
        case 5:
            cout << "Enter Roll Number: ";
            cin >> roll;
            sys.removeStudent(roll);
            break;
        case 6:
            cout << "Enter Roll Number: ";
            cin >> roll;
            sys.displayStudent(roll);
            break;
        case 7:
            sys.displayAll();
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
