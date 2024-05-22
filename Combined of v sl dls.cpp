#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
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

// Function to print a task
void printTask(const Task& task) {
    cout << "Task Name: " << task.taskname << endl;
    cout << "Description: " << task.description << endl;
    cout << "Due Date: " << task.dueDate << endl;
    cout << "High Priority: " << (task.isHighPriority ? "Yes" : "No") << endl;
    cout << "Done: " << (task.done ? "Yes" : "No") << endl;
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
                    return caseInsensitiveStringCompare(a.taskname, b.taskname);
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

        cout << "Tasks sorted successfully." << endl;
        break;
    }
}

int main() {
    vector<Task> tasks; // Vector for random access

    while (true) {
        cout << "\nTask Manager" << endl;
        cout << "------------" << endl;
        cout << "1. Add Task (Vector)" << endl;
        cout << "2. Remove Task (Singly-Linked List)" << endl;
        cout << "3. Mark as Done (Doubly-Linked List)" << endl;
        cout << "4. Mark as Undone (Doubly-Linked List)" << endl;
        cout << "5. Print Tasks (Vector)" << endl;
        cout << "6. Search Tasks (Vector)" << endl;
        cout << "7. Sort Tasks (Vector)" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
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

                // Add to vector (random access)
                tasks.push_back(newTask);
                break;
            }
           
            case 2: {
                string taskname;
                cin.ignore();
                cout << "Enter task name to remove: ";
                getline(cin, taskname);

                bool found = false;
                for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                    if (caseInsensitiveStringCompare(it->taskname, taskname)) {
                        tasks.erase(it);
                        cout << "Task removed." << endl;
                        found = true;
                        break;  // Add this line to exit the loop after removing the task
                        }
                    }

                    if (!found) {
                        cout << "Task not found." << endl;
                    }
                    break;
                }

            case 3: {
                string taskname;
                cin.ignore();
                cout << "Enter task name to mark as done: ";
                getline(cin, taskname);

                for (auto& task : tasks) {
                    if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                        task.done = true;
                        cout << "Task marked as done." << endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                string taskname;
                cin.ignore();
                cout << "Enter task name to mark as undone: ";
                getline(cin, taskname);

                for (auto& task : tasks) {
                    if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                        task.done = false;
                        cout << "Task marked as undone." << endl;
                        break;
                    }
                }
                break;
            }
            case 5:
                if (tasks.empty()) {
                    cout << "No tasks to display." << endl;
                } else {
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
                break;
            case 6: {
                string keyword;
                cin.ignore();
                cout << "Enter a keyword: ";
                getline(cin, keyword);

                bool found = false;
                for (const auto& task : tasks) {
                    if (caseInsensitiveStringCompare(task.taskname, keyword) ||
                        caseInsensitiveStringCompare(task.description, keyword) ||
                        caseInsensitiveStringCompare(task.dueDate, keyword) ||
                        (task.isHighPriority && caseInsensitiveStringCompare("yes", keyword)) ||
                        (!task.isHighPriority && caseInsensitiveStringCompare("no", keyword)) ||
                        (task.done && caseInsensitiveStringCompare("yes", keyword)) ||
                        (!task.done && caseInsensitiveStringCompare("no", keyword))) {
                        printTask(task);
                        cout << "--------------" << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "No matching tasks found." << endl;
                }
                break;
            }
            case 7: {
                sortTasks(tasks);
                break;
            }
            case 8: {
                char exitChoice;
                cout << "Are you sure you want to exit? (Y/N): ";
                cin >> exitChoice;
                if (exitChoice == 'Y' || exitChoice == 'y') {
                    return 0;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
