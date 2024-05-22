#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
using namespace std;

struct Task {
    string taskname;
    string description;
    string dueDate;
    bool isHighPriority;
    bool done;
    Task* next;

    Task(const string& name, const string& desc, const string& date, bool priority, bool isDone)
        : taskname(name), description(desc), dueDate(date), isHighPriority(priority), done(isDone), next(nullptr) {}
};

class TaskList {
private:
    Task* head;

    string toLower(const string& str) {
        string lowerStr = str;
        for (char& c : lowerStr) {
            c = tolower(c);
        }
        return lowerStr;
    }

    bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
        return toLower(str1) == toLower(str2);
    }

public:
    TaskList() : head(nullptr) {}

    void insertTask(const string& name, const string& desc, const string& date, bool priority, bool isDone) {
        Task* newTask = new Task(name, desc, date, priority, isDone);
        newTask->next = head;
        head = newTask;
    }

    void removeTask(const string& taskName) {
        Task* prev = nullptr;
        Task* current = head;

        while (current != nullptr) {
            if (current->taskname == taskName) {
                if (prev == nullptr) {
                    head = current->next; // If the first node matches, update head.
                } else {
                    prev->next = current->next;
                }
                delete current; // Free the memory.
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Task not found." << endl;
    }

    void markAsDone(const string& taskName) {
        Task* current = head;

        while (current != nullptr) {
            if (current->taskname == taskName) {
                current->done = true;
                return;
            }
            current = current->next;
        }

        cout << "Task not found." << endl;
    }

    void markAsUndone(const string& taskName) {
        Task* current = head;

        while (current != nullptr) {
            if (current->taskname == taskName) {
                current->done = false;
                return;
            }
            current = current->next;
        }

        cout << "Task not found." << endl;
    }

    void displayTasks() {
        Task* current = head;
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
            string formattedDueDate = "(" + current->dueDate + ")";
            cout << left << setw(colWidthTaskName) << current->taskname
                 << setw(colWidthDescription) << current->description
                 << setw(colWidthDueDate) << formattedDueDate
                 << setw(colWidthPriority) << (current->isHighPriority ? "Yes" : "No")
                 << setw(colWidthDone) << (current->done ? "Yes" : "No") << endl;
            current = current->next;
        }
    }

    void searchTasks(const string& keyword) {
        Task* current = head;
        const int colWidthTaskName = 30;
        const int colWidthDescription = 30;
        const int colWidthDueDate = 30;
        const int colWidthPriority = 15;
        const int colWidthDone = 8;

        while (current != nullptr) {
            if (caseInsensitiveStringCompare(current->taskname, keyword) ||
                caseInsensitiveStringCompare(current->description, keyword) ||
                caseInsensitiveStringCompare(current->dueDate, keyword) ||
                (current->isHighPriority && toLower(keyword) == "yes") ||
                (!current->isHighPriority && toLower(keyword) == "no") ||
                (current->done && toLower(keyword) == "yes") ||
                (!current->done && toLower(keyword) == "no")) {
                string formattedDueDate = "(" + current->dueDate + ")";
                cout << left << setw(colWidthTaskName) << current->taskname
                     << setw(colWidthDescription) << current->description
                     << setw(colWidthDueDate) << formattedDueDate
                     << setw(colWidthPriority) << (current->isHighPriority ? "Yes" : "No")
                     << setw(colWidthDone) << (current->done ? "Yes" : "No") << endl;
            }
            current = current->next;
        }
    }

    void sortTasksByName() {
        Task* newHead = nullptr;
        while (head != nullptr) {
            Task* current = head;
            head = head->next;
            if (newHead == nullptr || current->taskname < newHead->taskname) {
                current->next = newHead;
                newHead = current;
            } else {
                Task* prev = newHead;
                while (prev->next != nullptr && !(current->taskname < prev->next->taskname)) {
                    prev = prev->next;
                }
                current->next = prev->next;
                prev->next = current;
            }
        }
        head = newHead;
    }
};

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
        cout << "7. Sort Tasks by Name" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, description, dueDate;
                char isHighPriority;
                bool priority, isDone;

                cin.ignore();
                cout << "Enter the task name: ";
                getline(cin, name);
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter due date (MM/DD/YYYY): ";
                getline(cin, dueDate);
                cout << "Is this task high priority? (Y/N): ";
                cin >> isHighPriority;

                priority = (isHighPriority == 'Y' || isHighPriority == 'y');
                isDone = false;
                taskList.insertTask(name, description, dueDate, priority, isDone);
                break;
            }
            case 2: {
                cin.ignore();
                cout << "Enter task name to remove: ";
                string taskName;
                getline(cin, taskName);
                taskList.removeTask(taskName);
                break;
            }
            case 3: {
                cin.ignore();
                cout << "Enter task name to mark as done: ";
                string taskName;
                getline(cin, taskName);
                taskList.markAsDone(taskName);
                break;
            }
            case 4: {
                cin.ignore();
                cout << "Enter task name to mark as undone: ";
                string taskName;
                getline(cin, taskName);
                taskList.markAsUndone(taskName);
                break;
            }
            case 5:
                taskList.displayTasks();
                break;
            case 6: {
                cin.ignore();
                cout << "Enter keyword: ";
                string keyword;
                getline(cin, keyword);
                taskList.searchTasks(keyword);
                break;
            }
            case 7:
                taskList.sortTasksByName();
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
