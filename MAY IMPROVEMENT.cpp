#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

struct Task {
    string taskname;
    string description;
    string dueDate;
    string duration;
    bool isHighPriority;
    bool done;
};

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
    cout << "Enter task taskname: ";
    getline(cin, taskname);

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->taskname == taskname) {
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
    cout << "Enter task name: ";
    getline(cin, taskname);

    for (auto& task : tasks) {
        if (task.name == taskname) {
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
    cout << "Enter task name: ";
    getline(cin, taskname);

    for (auto& task : tasks) {
        if (task.name == taskname) {
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

    const int colWidthtaskname = 30;
    const int colWidthDescription = 30;
    const int colWidthDueDate = 30;
    const int colWidthDone = 8;
    const int colWidthPriority = 15;

    cout << left << setw(colWidthtaskname) << "Task Name"
         << setw(colWidthDescription) << "Description"
         << setw(colWidthDueDate) << "Due Date"
         << setw(colWidthPriority) << "High Priority"
         << setw(colWidthDone) << "Done" << endl;

    for (const auto& task : tasks) {
        cout << left << setw(colWidthtaskname) << task.taskname
             << setw(colWidthDescription) << task.description
             << setw(colWidthDueDate) << task.dueDate
             << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
             << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
    }
}

void searchTasks(const vector<Task>& tasks) {
    string keyword;
    cin.ignore();
    cout << "Enter keyword: ";
    getline(cin, keyword);

    cout << "Description\t\tDue Date\t\tHigh Priority\t\tDone" << endl;
    for (const auto& task : tasks) {
        if (task.description.find(keyword) != string::npos) {
            cout << task.description << "\t\t" << task.dueDate << "\t\t"
                 << (task.isHighPriority ? "Yes" : "No") << "\t\t" << (task.done ? "Yes" : "No") << endl;
        }
    }
}

void sortTasks(vector<Task>& tasks) {
    cout << "Sort by:" << endl;
    cout << "1. Alphabetically" << endl;
    cout << "2. Due Date" << endl;
    cout << "3. High Priority" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.description < b.description;
        });
        break;
    case 2:
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.dueDate < b.dueDate;
        });
        break;
    case 3:
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.isHighPriority > b.isHighPriority;
        });
        break;
    default:
        cout << "Invalid choice." << endl;
        return;
    }
}

int main() {
    vector<Task> tasks;
    int choice;

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
        cout << "Enter choice: ";
        cin >> choice;

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
            return 0;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
        cout.flush();
    }
}