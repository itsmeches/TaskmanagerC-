#include <iostream>
#include <vector>
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

void sortTasks(vector<Task>& tasks) {
    while (true) {
        cout << "Sort by:" << endl;
        cout << "1. Alphabetically" << endl;
        cout << "2. Due Date" << endl;
        cout << "3. High Priority" << endl;
        cout << "4. Done" << endl;
        cout << "5. Not Done" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    if (tolower(a.taskname[0]) == tolower(b.taskname[0])) {
                        return caseInsensitiveStringCompare(a.taskname, b.taskname);
                    }
                    return tolower(a.taskname[0]) < tolower(b.taskname[0]);
                });
                break;
            case 2:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    string aDate = a.dueDate.substr(6) + a.dueDate.substr(0, 2) + a.dueDate.substr(3, 2);
                    string bDate = b.dueDate.substr(6) + b.dueDate.substr(0, 2) + b.dueDate.substr(3, 2);
                    return aDate < bDate;
                });
                break;
            case 3:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    if (a.isHighPriority && !b.isHighPriority) {
                        return true;
                    }
                    if (!a.isHighPriority && b.isHighPriority) {
                        return false;
                    }
                    return toLower(a.taskname) < toLower(b.taskname);
                });
                break;
            case 4:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return a.done && !b.done;
                });
                break;
            case 5:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return !a.done && b.done;
                });
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
        }

        printTasks(tasks);
        return;
    }
}

int getUserChoice() {
    int choice;
    while (true) {
        cout << "Enter choice (1-8): ";
        if (cin >> choice) {
            if (choice >= 1 && choice <= 8) {
                return choice;
            } else {
                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number between 1 and 8." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    vector<Task> tasks;

    while (true) {
        cout << "\nTask Manager" << endl;
        cout << "------------" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Mark as Done" << endl;
        cout << "4. Mark as Undone" << endl;
        cout << "5. Print Tasks" << endl;
        cout << "6. Search Tasks" << endl;
        cout << "7. Sort Tasks" << endl;
        cout << "8. Exit" << endl;

        int choice = getUserChoice();

        switch (choice) {
            case 1:
                insertTask(tasks);
                break;
            case 2:
                removeTask(tasks);
                break;
            case 3:
                markAsDone(tasks);
                break;
            case 4:
                markAsUndone(tasks);
                break;
            case 5:
                printTasks(tasks);
                break;
            case 6:
                searchTasks(tasks);
                break;
            case 7:
                sortTasks(tasks);
                break;
            case 8:
                char exitChoice;
                cout << "Are you sure you want to exit? (Y/N): ";
                cin >> exitChoice;
                if (exitChoice == 'Y' || exitChoice == 'y') {
                    return 0;
                }
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}