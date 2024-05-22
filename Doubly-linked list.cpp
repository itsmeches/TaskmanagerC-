#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
using namespace std;

// Define the Task structure
struct Task {
    string taskname;
    string description;
    string dueDate;
    bool isHighPriority;
    bool done;
};

// Define a doubly-linked list node for tasks
struct TaskNode {
    Task task;
    TaskNode* next;
    TaskNode* prev;
    TaskNode(const Task& t) : task(t), next(nullptr), prev(nullptr) {}
};

class TaskList {
private:
    TaskNode* head;
    TaskNode* tail;

public:
    // Constructor to initialize the list
    TaskList() : head(nullptr), tail(nullptr) {}

    // Function to insert a new task at the end of the list
    void insertTask(const Task& newTask) {
        TaskNode* newNode = new TaskNode(newTask);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to remove a task with a given task name
    void removeTask(const string& taskname) {
        TaskNode* current = head;
        while (current) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    head = current->next;
                    head->prev = nullptr;
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                cout << "Task removed." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task not found." << endl;
    }

    // Function to mark a task as done with a given task name
    void markAsDone(const string& taskname) {
        TaskNode* current = head;
        while (current) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                current->task.done = true;
                cout << "Task marked as done." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task not found." << endl;
    }

    // Function to mark a task as undone with a given task name
    void markAsUndone(const string& taskname) {
        TaskNode* current = head;
        while (current) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                current->task.done = false;
                cout << "Task marked as undone." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task not found." << endl;
    }

    // Function to print all tasks
    void printTasks() {
        TaskNode* current = head;
        const int colWidthTaskName = 30;
        const int colWidthDescription = 30;
        const int colWidthDueDate = 30;
        const int colWidthPriority = 15;
        const int colWidthDone = 8;

        cout << left << setw(colWidthTaskName) << "Task Name"
             << setw(colWidthDescription) << "Description"
             << setw(colWidthDueDate) << "Due Date"
             << setw(colWidthPriority) << "High Priority"
             << setw(colWidthDone) << "Done" << endl;

        while (current) {
            string formattedDueDate = "(" + current->task.dueDate + ")";
            cout << left << setw(colWidthTaskName) << current->task.taskname
                 << setw(colWidthDescription) << current->task.description
                 << setw(colWidthDueDate) << formattedDueDate
                 << setw(colWidthPriority) << (current->task.isHighPriority ? "Yes" : "No")
                 << setw(colWidthDone) << (current->task.done ? "Yes" : "No") << endl;
            current = current->next;
        }
    }

    // Function to search for tasks containing a keyword
    void searchTasks(const string& keyword) {
        TaskNode* current = head;
        const int colWidthTaskName = 30;
        const int colWidthDescription = 30;
        const int colWidthDueDate = 30;
        const int colWidthPriority = 15;
        const int colWidthDone = 8;

        cout << left << setw(colWidthTaskName) << "Task Name"
             << setw(colWidthDescription) << "Description"
             << setw(colWidthDueDate) << "Due Date"
             << setw(colWidthPriority) << "High Priority"
             << setw(colWidthDone) << "Done" << endl;

        while (current) {
            if (caseInsensitiveStringCompare(current->task.taskname, keyword) ||
                caseInsensitiveStringCompare(current->task.description, keyword) ||
                caseInsensitiveStringCompare(current->task.dueDate, keyword) ||
                (current->task.isHighPriority && keyword == "yes") ||
                (!current->task.isHighPriority && keyword == "no") ||
                (current->task.done && keyword == "yes") ||
                (!current->task.done && keyword == "no")) {
                string formattedDueDate = "(" + current->task.dueDate + ")";
                cout << left << setw(colWidthTaskName) << current->task.taskname
                     << setw(colWidthDescription) << current->task.description
                     << setw(colWidthDueDate) << formattedDueDate
                     << setw(colWidthPriority) << (current->task.isHighPriority ? "Yes" : "No")
                     << setw(colWidthDone) << (current->task.done ? "Yes" : "No") << endl;
            }
            current = current->next;
        }
    }

    // Destructor to clean up memory
    ~TaskList() {
        while (head) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

// Function to perform a case-insensitive string comparison
bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
    return toLower(str1) == toLower(str2);
}

int main() {
    TaskList taskList;

    while (true) {
        cout << "\nTask Manager" << endl;
        cout << "------------" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Mark as Done" << endl;
        cout << "4. Mark as Undone" << endl;
        cout << "5. Print Tasks" << endl;
        cout << "6. Search Tasks" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Task newTask;
                char isHighPriority;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the task name: ";
                getline(cin, newTask.taskname);
                cout << "Enter task description: ";
                getline(cin, newTask.description);
                cout << "Enter due date (MM/DD/YYYY): ";
                getline(cin, newTask.dueDate);
                newTask.done = false;
                cout << "Is this task high priority? (Y/N): ";
                cin >> isHighPriority;
                newTask.isHighPriority = (isHighPriority == 'Y' || isHighPriority == 'y');
                taskList.insertTask(newTask);
                break;
            }
            case 2: {
                string taskname;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter task name to remove: ";
                getline(cin, taskname);
                taskList.removeTask(taskname);
                break;
            }
            case 3: {
                string taskname;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter task name to mark as done: ";
                getline(cin, taskname);
                taskList.markAsDone(taskname);
                break;
            }
            case 4: {
                string taskname;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter task name to mark as undone: ";
                getline(cin, taskname);
                taskList.markAsUndone(taskname);
                break;
            }
            case 5:
                taskList.printTasks();
                break;
            case 6: {
                string keyword;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter keyword: ";
                getline(cin, keyword);
                taskList.searchTasks(keyword);
                break;
            }
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
