#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <stack>
using namespace std;
 
// Define a structure for employee information

struct Employee {

    string firstName;

    string lastName;

    int id;

    double salary;

    string category;

    Employee* next;
 
    // Constructor to initialize an employee

    Employee(string first, string last, int i, double s, string cat)

        : firstName(first), lastName(last), id(i), salary(s), category(cat), next(nullptr) {}

};
 
// Define a structure for user login credentials

struct User {

    string username;

    string password;

    User(string u, string p) : username(u), password(p) {}

};
 
// Function to print a title with authors

void printTitle(const string& title) {

    cout << title << endl;

    cout << "           (Final Term Requirement)" << endl << endl;

    cout << "|========================================|" << endl;

    cout << "        BS Computer Science COM221" << endl << endl;

    cout << "        Malaluan, Angel Mikaela E." << endl;

    cout << "        Montano, Dale Vincent A." << endl;

    cout << "        Ghazal, Omar Ahmed P." << endl << endl;

}
 
// Function to print a header with a title

void printHeader(const string& header) {

    cout << "|========================================|" << endl;

    cout << header << endl;

    cout << "|========================================|" << endl;

}
 
// Function to display the main menu options

void displayMainMenu() {

    printHeader("          Employee Payroll System");

    cout << "[1] Add New Employee" << endl;

    cout << "[2] Remove Employee" << endl;

    cout << "[3] Display All Employees" << endl;

    cout << "[4] Search for Employee" << endl;

    cout << "[5] Sort Employees by Salary" << endl;

    cout << "[6] Record Monthly Salary (Push to Stack)" << endl;

    cout << "[7] Process Payroll Request (Pop from Stack)" << endl;

    cout << "[8] Add Leave Request (Enqueue)" << endl;

    cout << "[9] Approve Leave Request (Dequeue)" << endl;

    cout << "[10] Modify Employee" << endl;

    cout << "[11] Exit Payroll System" << endl;

    cout << "Enter your choice: ";

}
 
// Class to manage a linked list of employees (Linked List)

class EmployeeList {

public:

    Employee* head;

    static const int MAX_SALARY_RECORDS = 100;

    unordered_set<int> employeeIdSet;

    stack<double> salaryStack;
 
    EmployeeList() : head(nullptr) {}
 
    // Function to add a new employee to the linked list

    void addEmployee() {

        string firstName, lastName;

        int id;

        double salary;

        string category;

        cout << "Enter employee's first name: ";

        cin >> firstName;

        cout << "Enter employee's last name: ";

        cin >> lastName;

        cout << "Enter employee's ID: ";

        cin >> id;
 
        // Check if an employee with the same ID already exists (Searching Algorithms - Linear Search)

        if (employeeIdSet.find(id) != employeeIdSet.end()) {

            cout << "Employee with the same ID already exists. Employee not added." << endl;

            return;

        }
 
        employeeIdSet.insert(id);
 
        cout << "Enter employee's monthly salary: $";

        cin >> salary;
 
        cout << "Enter employee's category (e.g., full-time, part-time, contract): ";

        cin >> category;
 
        // Create a new employee and add them to the linked list

        Employee* emp = new Employee(firstName, lastName, id, salary, category);

        emp->next = head;

        head = emp;

        cout << "Employee successfully added to the payroll." << endl;

    }
 
    // Function to remove an employee from the linked list

    void removeEmployee(int id) {

        Employee* current = head;

        Employee* prev = nullptr;
 
        while (current != nullptr && current->id != id) {

            prev = current;

            current = current->next;

        }
 
        if (current != nullptr) {

            if (prev == nullptr) {

                head = current->next;

            } else {

                prev->next = current->next;

            }
 
            employeeIdSet.erase(id);

            delete current;

            cout << "Employee with ID " << id << " has been removed from the payroll." << endl;

        } else {

            cout << "Employee with ID " << id << " was not found in the system." << endl;

        }

    }
 
    // Function to display all employees in the linked list

    void displayEmployees() {

        Employee* current = head;

        while (current != nullptr) {

            cout << "Name: " << current->firstName << " " << current->lastName << " | ID: " << current->id

                 << " | Salary: $" << current->salary << " per month | Category: " << current->category << endl;

            current = current->next;

        }

    }
 
    // Function to search for an employee by name in the linked list

    void searchEmployee(const string& name) {

        cout << "Search Results:" << endl;

        Employee* current = head;

        bool found = false;

        while (current != nullptr) {

            if (current->firstName == name || current->lastName == name) {

                cout << "Name: " << current->firstName << " " << current->lastName << " | ID: " << current->id

                     << " | Salary: $" << current->salary << " per month | Category: " << current->category << endl;

                found = true;

            }

            current = current->next;

        }
 
        if (!found) {

            cout << "No employee with the name " << name << " was found in the system." << endl;

        }

    }
 
    // Function to sort employees by salary in ascending order (Sorting Algorithms - Bubble Sort)

    void sortEmployees() {

        if (head == nullptr || head->next == nullptr) {

            return;

        }
 
        bool swapped;

        do {

            swapped = false;

            Employee* prev = nullptr;

            Employee* current = head;

            Employee* next = head->next;
 
            while (next != nullptr) {

                if (current->salary > next->salary) {

                    if (prev != nullptr) {

                        prev->next = next;

                    } else {

                        head = next;

                    }

                    current->next = next->next;

                    next->next = current;

                    prev = next;

                    swapped = true;

                } else {

                    prev = current;

                    current = next;

                }

                next = current->next;

            }

        } while (swapped);
 
        cout << "Employees have been sorted by their monthly salary in ascending order." << endl;

    }
 
    // Destructor to free memory when the object is destroyed

    ~EmployeeList() {

        while (head != nullptr) {

            Employee* temp = head;

            head = head->next;

            delete temp;

        }

    }

};
 
    // Function to add a leave request to a queue (Queue)

    void addLeaveRequest(queue<string>& leaveQueue) {

        string leaveType;

        string leaveDates;

        cout << "Enter type of leave (e.g., vacation, sick leave): ";

        cin.ignore();

        getline(cin, leaveType);

        cout << "Enter leave dates: ";

        getline(cin, leaveDates);

        string leaveRequest = "Type: " + leaveType + " | Dates: " + leaveDates;

        leaveQueue.push(leaveRequest);

        cout << "Leave request added and waiting for approval." << endl;

    }
 
    // Function to approve a leave request from a queue (Queue)

    void approveLeaveRequest(queue<string>& leaveQueue) {

        if (!leaveQueue.empty()) {

            cout << "Approved leave request: " << leaveQueue.front() << endl;

            leaveQueue.pop();

        } else {

            cout << "No pending leave requests to approve." << endl;

        }

    }
 
    // Function to authenticate a user (Arrays)

    bool authenticateUser(const string& username, const string& password) {

        vector<User> validUsers = {

            User("Mikayski", "McLaren123"),

            User("Omar", "BMW456"),

            User("Dale", "Porsche789")

        };
 
        for (const User& user : validUsers) {

            if (user.username == username && user.password == password) {

                return true;

            }

        }
 
        return false;

    }
 
    // Function to record an employee's monthly salary and push it onto a stack (Stack)

    void recordSalary(EmployeeList& employees, int id) {

        Employee* current = employees.head;

        while (current != nullptr) {

            if (current->id == id) {

                employees.salaryStack.push(current->salary);

                cout << "Monthly salary of $" << current->salary << " recorded and pushed onto the stack." << endl;

                return;

            }

            current = current->next;

        }

        cout << "Employee with ID " << id << " not found." << endl;

    }
 
    // Function to modify an existing employee

    void modifyEmployee(EmployeeList& employees, int id) {

        Employee* current = employees.head;

        while (current != nullptr) {

            if (current->id == id) {

                cout << "Employee found. Please enter the new information:" << endl;

                string firstName, lastName;

                double salary;

                string category;
 
                cout << "Enter employee's first name: ";

                cin >> firstName;

                cout << "Enter employee's last name: ";

                cin >> lastName;

                cout << "Enter employee's monthly salary: $";

                cin >> salary;

                cout << "Enter employee's category (e.g., full-time, part-time, contract): ";

                cin >> category;
 
                // Update the employee's information

                current->firstName = firstName;

                current->lastName = lastName;

                current->salary = salary;

                current->category = category;
 
                cout << "Employee information updated successfully." << endl;

                return;

            }

            current = current->next;

        }

        cout << "Employee with ID " << id << " not found." << endl;

    }
 
// The main function for running the payroll system

int main() {

    string username, password;

    bool authenticated = false;
 
    printTitle("        Data Structures and Algorithms");
 
    while (!authenticated) {

        cout << " " << endl;

        cout << "|========================================|" << endl;

        cout << "          Employee Payroll System" << endl;

        cout << "|========================================|" << endl;

        cout << "                  Log In" << endl;

        cout << "Username: ";

        cin >> username;

        cout << "Password: ";

        cin >> password;
 
        authenticated = authenticateUser(username, password);
 
        if (!authenticated) {

            cout << "Authentication failed. Please try again." << endl;

        }

    }
 
    EmployeeList employees;

    queue<string> leaveQueue;

    string searchName;

    int id;
 
    while (true) {

        int choice;

        cout << " " << endl;

        displayMainMenu();

        cin >> choice;
 
        // In the main function for running the payroll system
 
    switch (choice) {

        case 1:

            // Adding Employees

            // Data Structure: Linked List

            // Algorithm: Insertion at the beginning (Constant time complexity)

            employees.addEmployee();

            break;

        case 2:

            // Removing Employees

            // Data Structure: Linked List

            // Algorithm: Linear search to find and remove an employee by ID

            cout << "Enter the ID of the employee to remove: ";

            cin >> id;

            employees.removeEmployee(id);
            break;
        case 3:
            // Displaying Employees
            // Data Structure: Linked List
            // Algorithm: Iteration to print all employees' details
            printHeader("               Employee List");
            employees.displayEmployees();
            break;
        case 4:
            // Searching for Employees
            // Data Structure: Linked List
            // Algorithm: Linear search by first name or last name to find and display matching employee records
            cout << "Enter the name to search for: ";
            cin >> searchName;
            employees.searchEmployee(searchName);
            break;
        case 5:
            // Sorting Employees
            // Data Structure: Linked List
            // Algorithm: Bubble Sort to sort employees by salary in ascending order
            employees.sortEmployees();
            break;
        case 6:
            // Recording Monthly Salaries
            // Data Structure: Stack
            // Algorithm: Push the monthly salary onto the stack
            cout << "Enter the ID of the employee for salary approval: ";
            cin >> id;
            recordSalary(employees, id);
            break;
        case 7:
            // Processing Payroll Requests
            // Data Structure: Stack
            // Algorithm: Pop from the stack to process payroll requests in a last-in-first-out (LIFO) manner
            if (!employees.salaryStack.empty()) {
                cout << "Payroll for an employee with a monthly salary of $" << employees.salaryStack.top() << " is now processed." << endl;
                employees.salaryStack.pop();
            } else {
                cout << "No payroll records are available." << endl;
            }
            break;
        case 8:
            // Adding Leave Requests
            // Data Structure: Queue
            // Algorithm: Enqueue leave requests to add them to the end of the queue
            addLeaveRequest(leaveQueue);
            break;
        case 9:
            // Approving Leave Requests
            // Data Structure: Queue
            // Algorithm: Dequeue to approve leave requests in a first-in-first-out (FIFO) manner
            approveLeaveRequest(leaveQueue);
            break;
        case 10:
            // Modifying Employees
            // Data Structure: Linked List
            // Algorithm: Linear search by ID to find and update employee information
            cout << "Enter the ID of the employee to modify: ";
            cin >> id;
            modifyEmployee(employees, id);
            break;
        case 11:
            cout << "Exiting the Employee Payroll System. Have a great day!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;

    }
    }
    return 0;
}