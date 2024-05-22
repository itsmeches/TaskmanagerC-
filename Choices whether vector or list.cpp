#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

struct Task {
    string taskname;
    string description;
    string dueDate;
    bool isHighPriority;
    bool done;
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
bool caseInsensitiveStringCompare(const string &str1, const string &str2) {
    return toLower(str1) == toLower(str2);
}

class TaskManager {
public:
    virtual void insertTask(vector<Task>& tasks) = 0;
    virtual void removeTask(vector<Task>& tasks) = 0;
    virtual void markAsDone(vector<Task>& tasks) = 0;
    virtual void markAsUndone(vector<Task>& tasks) = 0;
    virtual void printTasks(const vector<Task>& tasks) = 0;
    virtual void searchTasks(const vector<Task>& tasks) = 0;
};

class VectorTaskManager : public TaskManager {
public:
    void insertTask(vector<Task>& tasks) {
        Task newTask;
        char isHighPriority;
        cin.ignore();
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
        if (isHighPriority == 'N' || isHighPriority == 'n') {
            newTask.isHighPriority = false;
        }
        tasks.push_back(newTask);
    }

    void removeTask(vector<Task>& tasks) {
        string taskname;
        cin.ignore();
        cout << "Enter task name to remove: ";
        getline(cin, taskname);

        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (caseInsensitiveStringCompare(it->taskname, taskname)) {
                tasks.erase(it);
                cout << "Task removed." << endl;
                return;
            }
        }
        cout << "Task not found." << endl;
    }

    void markAsDone(vector<Task>& tasks) {
        string taskname;
        cin.ignore();
        cout << "Enter task name to mark as done: ";
        getline(cin, taskname);

        for (auto& task : tasks) {
            if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                task.done = true;
                cout << "Task marked as done." << endl;
                return;
            }
        }
        cout << "Task not found." << endl;
    }

    void markAsUndone(vector<Task>& tasks) {
        string taskname;
        cin.ignore();
        cout << "Enter task name to mark as undone: ";
        getline(cin, taskname);

        for (auto& task : tasks) {
            if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                task.done = false;
                cout << "Task marked as undone." << endl;
                return;
            }
        }

        cout << "Task not found." << endl;
    }

    void printTasks(const vector<Task>& tasks) {
        if (tasks.empty()) {
            cout << "No tasks to display." << endl;
            return;
        }

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

        for (const auto& task : tasks) {
            string formattedDueDate = "(" + task.dueDate + ")";
            cout << left << setw(colWidthTaskName) << task.taskname
                 << setw(colWidthDescription) << task.description
                 << setw(colWidthDueDate) << formattedDueDate
                 << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
                 << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
        }
    }

    void searchTasks(const vector<Task>& tasks) {
        string keyword;
        cin.ignore();
        cout << "Enter keyword: ";
        getline(cin, keyword);
        string keywordLower = toLower(keyword);

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

        for (const auto& task : tasks) {
            if (caseInsensitiveStringCompare(task.taskname, keyword) ||
                caseInsensitiveStringCompare(task.description, keyword) ||
                caseInsensitiveStringCompare(task.dueDate, keyword) ||
                (task.isHighPriority && keywordLower == "yes") ||
                (!task.isHighPriority && keywordLower == "no") ||
                (task.done && keywordLower == "yes") ||
                (!task.done && keywordLower == "no")) {
                string formattedDueDate = "(" + task.dueDate + ")";
                cout << left << setw(colWidthTaskName) << task.taskname
                     << setw(colWidthDescription) << task.description
                     << setw(colWidthDueDate) << formattedDueDate
                     << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
                     << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
            }
        }
    }
};

class LinkedListTaskManager : public TaskManager {
public:
    struct Node {
        Task task;
        Node* next;
        Node* prev;
        Node(const Task& t) : task(t), next(nullptr), prev(nullptr) {}
    };

    Node* head; // Pointer to the head of the linked list

    LinkedListTaskManager() : head(nullptr) {}

    ~LinkedListTaskManager() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertTask(vector<Task>& tasks) override {
        Task newTask;
        char isHighPriority;
        cin.ignore();
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
        if (isHighPriority == 'N' || isHighPriority == 'n') {
            newTask.isHighPriority = false;
        }

        Node* newNode = new Node(newTask);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }

        cout << "Task added." << endl;
    }

    void removeTask(vector<Task>& tasks) override {
        string taskname;
        cin.ignore();
        cout << "Enter task name to remove: ";
        getline(cin, taskname);

        Node* current = head;

        while (current != nullptr) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next) {
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

    void markAsDone(vector<Task>& tasks) override {
        string taskname;
        cin.ignore();
        cout << "Enter task name to mark as done: ";
        getline(cin, taskname);

        Node* current = head;

        while (current != nullptr) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                current->task.done = true;
                cout << "Task marked as done." << endl;
                return;
            }

            current = current->next;
        }

        cout << "Task not found." << endl;
    }

    void markAsUndone(vector<Task>& tasks) override {
        string taskname;
        cin.ignore();
        cout << "Enter task name to mark as undone: ";
        getline(cin, taskname);

        Node* current = head;

        while (current != nullptr) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                current->task.done = false;
                cout << "Task marked as undone." << endl;
                return;
            }

            current = current->next;
        }

        cout << "Task not found." << endl;
    }

    void printTasks(const vector<Task>& tasks) override {
        Node* current = head;

        if (current == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }

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

        while (current != nullptr) {
            const Task& task = current->task;
            string formattedDueDate = "(" + task.dueDate + ")";
            cout << left << setw(colWidthTaskName) << task.taskname
                 << setw(colWidthDescription) << task.description
                 << setw(colWidthDueDate) << formattedDueDate
                 << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
                 << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
            current = current->next;
        }
    }

    void searchTasks(const vector<Task>& tasks) override {
        string keyword;
        cin.ignore();
        cout << "Enter keyword: ";
        getline(cin, keyword);
        string keywordLower = toLower(keyword);

        Node* current = head;

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

        while (current != nullptr) {
            const Task& task = current->task;
            if (caseInsensitiveStringCompare(task.taskname, keyword) ||
                caseInsensitiveStringCompare(task.description, keyword) ||
                caseInsensitiveStringCompare(task.dueDate, keyword) ||
                (task.isHighPriority && keywordLower == "yes") ||
                (!task.isHighPriority && keywordLower == "no") ||
                (task.done && keywordLower == "yes") ||
                (!task.done && keywordLower == "no")) {
                string formattedDueDate = "(" + task.dueDate + ")";
                cout << left << setw(colWidthTaskName) << task.taskname
                     << setw(colWidthDescription) << task.description
                     << setw(colWidthDueDate) << formattedDueDate
                     << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
                     << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
            }
            current = current->next;
        }
    }
};

int main() {
    vector<Task> tasks; // This can be used to store tasks regardless of the chosen task manager.

    cout << "Task Manager" << endl;
    cout << "Choose a task manager (1 for Vector, 2 for Linked List): ";
    int choice;
    cin >> choice;

    TaskManager* taskManager = nullptr;

    if (choice == 1) {
        taskManager = new VectorTaskManager();
    } else if (choice == 2) {
        taskManager = new LinkedListTaskManager();
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Mark Task as Done\n";
        cout << "4. Mark Task as Undone\n";
        cout << "5. Print Tasks\n";
        cout << "6. Search Tasks\n";
        cout << "7. Exit\n";

        int option;
        cout << "Enter your choice: ";
        cin >> option;
        switch (option) {
            case 1:
                taskManager->insertTask(tasks);
                break;
            case 2:
                taskManager->removeTask(tasks);
                break;
            case 3:
                taskManager->markAsDone(tasks);
                break;
            case 4:
                taskManager->markAsUndone(tasks);
                break;
            case 5:
                taskManager->printTasks(tasks);
                break;
            case 6:
                taskManager->searchTasks(tasks);
                break;
            case 7:
                // Clean up and exit
                delete taskManager;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

