#include <iostream>   // Input and outpu1
#include <vector>     // Standard C++ vectors
#include <list>       // Standard C++ lists
#include <algorithm>  // Standard C++ algorithms like sort, search etc
#include <stack>      // Standard C++ stack
#include <queue>      // Standard C++ queue
#include <ctime>      // Date and time functions
#include <iomanip>    // Input/output manipulators
#include <cctype>     // Character handling functions
#include <string>     // String manipulation
#include <sstream>    // String stream classes
#include <limits>     // Provides constants for minimum and maximum values
using namespace std;

// Task structure
struct Task {
    string taskname;
    string description;
    string dueDate;
    bool isHighPriority;
    bool done;
};
 
// Convert string to lower case
string toLower(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}
 
// Case insensitive string comparison
bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
    return toLower(str1) == toLower(str2);
}
 
// Task manager interface    
class TaskManager {
public:
    virtual void insertTask(vector<Task>& tasks) = 0;
    virtual void removeTask(vector<Task>& tasks) = 0;
    virtual void markAsDone(vector<Task>& tasks) = 0;
    virtual void markAsUndone(vector<Task>& tasks) = 0;
    virtual void printTasks(const vector<Task>& tasks) = 0;
    virtual void searchTasks(const vector<Task>& tasks) = 0;
    virtual void sortTasks(vector<Task>& tasks) = 0;
    virtual void undo(vector<Task>& tasks) = 0;
    virtual void redo(vector<Task>& tasks) = 0;
};
 
 // Motivational Quotes
 const char* motivationalQuotes[] = {
    "Sir Kwatro. Baka naman. ;) - Andaya",
    "Success is not final, failure is not fatal: It is the courage to continue that counts. - Winston Churchill",
    "The only way to do great work is to love what you do. - Steve Jobs",
    "Believe you can and you're halfway there. - Theodore Roosevelt",
    "Don't watch the clock; do what it does. Keep going. - Sam Levenson",
    "The only limit to our realization of tomorrow will be our doubts of today. - Franklin D. Roosevelt",
    "The road to success and the road to failure are almost exactly the same. - Colin R. Davis",
    "Don't be afraid to give up the good to go for the great. - John D. Rockefeller",
    "You are never too old to set another goal or to dream a new dream. - C.S. Lewis",
    "The only person you are destined to become is the person you decide to be. - Ralph Waldo Emerson",
    "Success is not the key to happiness. Happiness is the key to success. If you love what you are doing, you will be successful. - Albert Schweitzer",
    "It's either you evolve or you evaporate. - Ginoong Halimaw",
    "Pag kaya ng iba, ipagawa mo sa kanila. - Lapu Lapu",
    "Aray! -Joze Rizal",
    "The pain you feel today, will be the strength you feel tomorrow. - Unknown",
   
};
 
 // Vector Task Manager

class VectorTaskManager : public TaskManager {
    private:
    stack<vector<Task>> undoStack;
    stack<vector<Task>> redoStack;
 
    void saveStateToUndoStack(const vector<Task>& tasks) {
        undoStack.push(tasks);
        redoStack = stack<vector<Task>>(); // Clear redo stack
    }

// Task Manager Functions
public:
    // Insert Task
    void insertTask(vector<Task>& tasks) override {
        saveStateToUndoStack(tasks);
        Task newTask;
        char isHighPriority;
        string dummy; 
        cin.ignore();
        cout << "Enter the task name: ";
        getline(cin, newTask.taskname);
        cout << "Enter task description: ";
        getline(cin, newTask.description);
        cout << "Enter due date (MM/DD/YYYY): ";
        getline(cin, newTask.dueDate);
        newTask.done = false;
         do {
        cout << "Is this task high priority? (Y/N): ";
        cin >> isHighPriority;
        if (isHighPriority == 'Y' || isHighPriority == 'y') {
            newTask.isHighPriority = true;
        } else if (isHighPriority == 'N' || isHighPriority == 'n') {
            newTask.isHighPriority = false;
        } else {
            cout << "Invalid input. Please enter 'Y' or 'N': ";
            cin >> dummy;
        }
    } while (!(isHighPriority == 'Y' || isHighPriority == 'y' || isHighPriority == 'N' || isHighPriority == 'n'));

    tasks.push_back(newTask);
}
    // Remove Task
    void removeTask(vector<Task>& tasks) override {
         saveStateToUndoStack(tasks);
        if (!tasks.empty()) {
            tasks.erase(tasks.begin());
            cout << "Task removed." << endl;
        } else {
            cout << "No tasks to remove." << endl;
        }
    }
    // Mark as Done
    void markAsDone(vector<Task>& tasks) override {
        saveStateToUndoStack(tasks);
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
    // Mark as Undone
    void markAsUndone(vector<Task>& tasks) override {
        saveStateToUndoStack(tasks);
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
    // Print Tasks
    void printTasks(const vector<Task>& tasks) override {
    if (tasks.empty()) {
        cout << "No tasks to display." << endl;
        return;
    }
    const int colWidthTaskName = 30;
    const int colWidthDescription = 30;
    const int colWidthDueDate = 30;
    const int colWidthPriority = 15;
    const int colWidthDone = 8;

    cout << "-------------------------------------------------------------------------------------------------------------------------"<< endl;
    cout << "| " << left << setw(colWidthTaskName) << "Task Name"
         << "| " << setw(colWidthDescription) << "Description"
         << "| " << setw(colWidthDueDate) << "Due Date"
         << "| " << setw(colWidthPriority) << "High Priority"
         << "| " << setw(colWidthDone) << "Done |" << endl;

    for (const auto& task : tasks) {
        string formattedDueDate = formatDate(task.dueDate);
        cout << " _______________________________________________________________________________________________________________________"<< endl;
        cout<< "| "  << left << setw(colWidthTaskName) << task.taskname
            << "| "  << setw(colWidthDescription) << task.description
            << "| "  << setw(colWidthDueDate) << formattedDueDate
            << "| "  << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
            << "| "  << setw(colWidthDone) << (task.done ? "Yes |" : "No   |") << endl;
    }
}
// Search Tasks
    void searchTasks(const vector<Task>& tasks) override {
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
                string formattedDueDate = formatDate(task.dueDate);
                cout << left << setw(colWidthTaskName) << task.taskname
                     << setw(colWidthDescription) << task.description
                     << setw(colWidthDueDate) << formattedDueDate
                     << setw(colWidthPriority) << (task.isHighPriority ? "Yes" : "No")
                     << setw(colWidthDone) << (task.done ? "Yes" : "No") << endl;
            }
        }
    }
   // Undo
    void undo(vector<Task>& tasks) override {
        if (!undoStack.empty()) {
            redoStack.push(tasks);
            tasks = undoStack.top();
            undoStack.pop();
        } else {
            cout << "Nothing to undo." << endl;
        }
    }
    // Redo
    void redo(vector<Task>& tasks) override {
        if (!redoStack.empty()) {
            undoStack.push(tasks);
            tasks = redoStack.top();
            redoStack.pop();
        } else {
            cout << "Nothing to redo." << endl;
        }
    }
 // Sort Tasks
void sortTasks(vector<Task>& tasks) override {
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
                // Alphabetically
                case 1:  
                    saveStateToUndoStack(tasks);
                    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                        if (tolower(a.taskname[0]) == tolower(b.taskname[0])) {
                            return caseInsensitiveStringCompare(a.taskname, b.taskname);
                        }
                        return tolower(a.taskname[0]) < tolower(b.taskname[0]);
                    });
                    break;
                // Due Date
                case 2:
                    saveStateToUndoStack(tasks);
                    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                        string aDate = a.dueDate.substr(6) + a.dueDate.substr(0, 2) + a.dueDate.substr(3, 2);
                        string bDate = b.dueDate.substr(6) + b.dueDate.substr(0, 2) + b.dueDate.substr(3, 2);
                        return aDate < bDate;
                    });
                    break;
                // High Priority
                case 3:
                    saveStateToUndoStack(tasks);
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
                // Done
                case 4:
                    saveStateToUndoStack(tasks);
                    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                        return a.done && !b.done;
                    });
                    break;
                // Not Done
                case 5:
                    saveStateToUndoStack(tasks);
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
            // Print Tasks
            printTasks(tasks);
            return;
        }
    }
 // Format Date Function 
    string formatDate(const string& date) {  // Function to format a date string
    struct tm tm = {};  // Initialize a tm structure to hold the components of the date and time
    stringstream ss(date);  // Create a stringstream to parse the input date string
    ss >> get_time(&tm, "%m/%d/%Y");  // Extract components of the date and store them in tm structure
 
    if (ss.fail()) {  // Check if the extraction failed (invalid date)
        return "Invalid Date";  // Return an error message if the date is invalid
    }
 
    char buffer[80];  // Create a character buffer to store the formatted date
    strftime(buffer, sizeof(buffer), "(%m/%d/%Y) %A", &tm);  // Format the date and time according to the specified format
    return string(buffer);  // Convert the buffer to a string and return the formatted date
}
};
 
class LinkedListTaskManager : public TaskManager {
private:
    stack<vector<Task>> undoStack;
    stack<vector<Task>> redoStack;

    void saveStateToUndoStack(const vector<Task>& tasks) {
        undoStack.push(tasks);
        redoStack = stack<vector<Task>>();
    }

public:
    struct Node {
        Task task;
        Node* next;
        Node* prev;
        Node(const Task& t) : task(t), next(nullptr), prev(nullptr) {}
    };

    Node* singleHead;
    Node* doubleHead;

    LinkedListTaskManager() : singleHead(nullptr), doubleHead(nullptr) {}
 
    ~LinkedListTaskManager() {
        while (singleHead != nullptr) {
            Node* temp = singleHead;
            singleHead = singleHead->next;
            delete temp;
        }
        while (doubleHead != nullptr) {
            Node* temp = doubleHead;
            doubleHead = doubleHead->next;
            delete temp;
        }
    }
 
     void insertTask(vector<Task>& tasks) override {
        saveStateToUndoStack(tasks);
        Task newTask;
        char isHighPriority;
        string dummy;
        cin.ignore();
        cout << "Enter the task name: ";
        getline(cin, newTask.taskname);
        cout << "Enter task description: ";
        getline(cin, newTask.description);
        cout << "Enter due date (MM/DD/YYYY): ";
        getline(cin, newTask.dueDate);
        newTask.done = false;
        do {
        cout << "Is this task high priority? (Y/N): ";
        cin >> isHighPriority;
        if (isHighPriority == 'Y' || isHighPriority == 'y') {
            newTask.isHighPriority = true;
        } else if (isHighPriority == 'N' || isHighPriority == 'n') {
            newTask.isHighPriority = false;
        } else {
            cout << "Invalid input. Please enter 'Y' or 'N': ";
            cin >> dummy;
        }
    } while (!(isHighPriority == 'Y' || isHighPriority == 'y' || isHighPriority == 'N' || isHighPriority == 'n'));

        Node* singleNode = new Node(newTask);
        Node* doubleNode = new Node(newTask);

        if (singleHead == nullptr) {
            singleHead = singleNode;
        } else {
            singleNode->next = singleHead;
            singleHead = singleNode;
        }

        if (doubleHead == nullptr) {
            doubleHead = doubleNode;
        } else {
            doubleNode->next = doubleHead;
            doubleHead->prev = doubleNode;
            doubleHead = doubleNode;
        }

        tasks.push_back(newTask);
        cout << "Task added." << endl;
    }

    void removeTask(vector<Task>& tasks) override {
    saveStateToUndoStack(tasks);
    if (!tasks.empty()) {
        string taskname;
        cin.ignore();
        cout << "Enter task name to remove: ";
        getline(cin, taskname);

        Node* current = doubleHead;
        while (current != nullptr) {
            if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
                // Remove task from doubly linked list
                removeTaskFromDoublyLinkedList(current);
                // Remove task from vector
                tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [&taskname](const Task& task) {
                    return caseInsensitiveStringCompare(task.taskname, taskname);
                }), tasks.end());

                cout << "Task removed." << endl;
                return;
            }

            current = current->next;
        }

        cout << "Task not found." << endl;
    } else {
        cout << "No tasks to remove." << endl;
    }
}

   void removeTaskFromDoublyLinkedList(Node* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        doubleHead = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }

    delete node;
}

    void markAsDone(vector<Task>& tasks) override {
    saveStateToUndoStack(tasks);
    string taskname;
    cin.ignore();
    cout << "Enter task name to mark as done: ";
    getline(cin, taskname);

    Node* current = doubleHead;

    while (current != nullptr) {
        if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
            current->task.done = true;
            // Also update the done status in the vector
            for (Task& task : tasks) {
                if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                    task.done = true;
                    break;
                }
            }
            cout << "Task marked as done." << endl;
            return;
        }

        current = current->next;
    }

    cout << "Task not found." << endl;
}
 
    void markAsUndone(vector<Task>& tasks) override {
    saveStateToUndoStack(tasks);
    string taskname;
    cin.ignore();
    cout << "Enter task name to mark as undone: ";
    getline(cin, taskname);

    Node* current = doubleHead;

    while (current != nullptr) {
        if (caseInsensitiveStringCompare(current->task.taskname, taskname)) {
            current->task.done = false;
            for (Task& task : tasks) {
                if (caseInsensitiveStringCompare(task.taskname, taskname)) {
                    task.done = false;
                    break;
                }
            }
            cout << "Task marked as undone." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Task not found." << endl;
}
 
    void printTasks(const vector<Task>& tasks) override {
        Node* current = doubleHead;

        if (current == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }
 
        const int colWidthTaskName = 30;
        const int colWidthDescription = 30;
        const int colWidthDueDate = 30;
        const int colWidthPriority = 15;
        const int colWidthDone = 8;
 
        cout << "-------------------------------------------------------------------------------------------------------------------------"<< endl;
        cout << left << setw(colWidthTaskName) << "Task Name"
             << setw(colWidthDescription) << "Description"
             << setw(colWidthDueDate) << "Due Date"
             << setw(colWidthPriority) << "High Priority"
             << setw(colWidthDone) << "Done" << endl;
 
        while (current != nullptr) {
            const Task& task = current->task;
            string formattedDueDate = formatDate(task.dueDate);
            cout << " _______________________________________________________________________________________________________________________"<< endl;
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
 
        Node* current = doubleHead;
 
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
 
   void sortTasks(vector<Task>& tasks) override {
    saveStateToUndoStack(tasks);
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
                    return tolower(a.taskname[0]) > tolower(b.taskname[0]);
                });
                // Rebuild the linked list based on the sorted vector
                clearLinkedList();
                for (const Task& task : tasks) {
                    insertTaskToLinkedList(task);
                }
                break;
            case 2:
                // Sorting by Due Date is similar to sorting by Task Name, with appropriate modifications
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    string aDate = a.dueDate.substr(6) + a.dueDate.substr(0, 2) + a.dueDate.substr(3, 2);
                    string bDate = b.dueDate.substr(6) + b.dueDate.substr(0, 2) + b.dueDate.substr(3, 2);
                    return aDate > bDate;
                });
                // Rebuild the linked list based on the sorted vector
                clearLinkedList();
                for (const Task& task : tasks) {
                    insertTaskToLinkedList(task);
                }
                break;
            case 3:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                if (!a.isHighPriority && b.isHighPriority) {
                    return true; // a is high priority, b is not, so a comes first
                 }
                if (a.isHighPriority && !b.isHighPriority) {
                    return false; // b is high priority, a is not, so b comes first
                }
                // Both have the same priority, sort by task name in descending order (Z to A)
                    return toLower(b.taskname) > toLower(a.taskname);
                });
                // Rebuild the linked list based on the sorted vector
                clearLinkedList();
                for (const Task& task : tasks) {
                    insertTaskToLinkedList(task);
                }
                break;
 
 
            case 4:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return b.done && !a.done;
                });
                // Rebuild the linked list based on the sorted vector
                clearLinkedList();
                for (const Task& task : tasks) {
                    insertTaskToLinkedList(task);
                }
                break;
            case 5:
                sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                    return !b.done && a.done;
                });
                // Rebuild the linked list based on the sorted vector
                clearLinkedList();
                for (const Task& task : tasks) {
                    insertTaskToLinkedList(task);
                }
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

    void undo(vector<Task>& tasks) override {
    if (!undoStack.empty()) {
        redoStack.push(tasks);
        tasks = undoStack.top();
        undoStack.pop(); 

        clearLinkedList();
        for (const Task& task : tasks) {
            insertTaskToLinkedList(task);
        }
        cout << "Undo successful." << endl;
    } else {
        cout << "Nothing to undo." << endl;
    }
}

void redo(vector<Task>& tasks) override {
    if (!redoStack.empty()) {
        saveStateToUndoStack(tasks);
        tasks = redoStack.top();
        redoStack.pop();

        clearLinkedList();
        for (const Task& task : tasks) {
            insertTaskToLinkedList(task);
        }
        cout << "Redo successful." << endl;
    } else {
        cout << "Nothing to redo." << endl;
    }
}

//Updates the linked list
    void clearLinkedList() {
        while (singleHead != nullptr) {
            Node* temp = singleHead;
            singleHead = singleHead->next;
            delete temp;
        }
        doubleHead = nullptr;
    }
//Inserts the updated linked list
    void insertTaskToLinkedList(const Task& task) {
        Node* singleNode = new Node(task);
        Node* doubleNode = new Node(task);

        if (singleHead == nullptr) {
            singleHead = singleNode;
        } else {
            singleNode->next = singleHead;
            singleHead = singleNode;
        }

        if (doubleHead == nullptr) {
            doubleHead = doubleNode;
        } else {
            doubleNode->next = doubleHead;
            doubleHead->prev = doubleNode;
            doubleHead = doubleNode;
        }
    }

    string formatDate(const string& date) {
        struct tm tm = {};
        stringstream ss(date);
        ss >> get_time(&tm, "%m/%d/%Y");
 
        if (ss.fail()) {
            return "Invalid Date";
        }
 
        char buffer[80];
        strftime(buffer, sizeof(buffer), "(%m/%d/%Y) %A", &tm);
        return string(buffer);
    }
};

 
void performOperations(TaskManager& taskManager, std::vector<Task>& tasks) {
    while (true) {
        cout << "                                                " << endl;
        cout << "                                                " << endl;
        cout << "                                                " << endl;
        cout << "                                                " << endl;
        cout << " ______________________________________________ " << endl;
        cout << "|         Task Manager Operations Menu         |" << endl;
        cout << "|______________________________________________|" << endl;
        cout << "|Choose an operation:                          |" << endl;
        cout << "|______________________________________________|" << endl;
        cout << "|1. Insert Task                                |" << endl;
        cout << "|2. Remove Task                                |" << endl;
        cout << "|3. Mark as Done                               |" << endl;
        cout << "|4. Mark as Undone                             |" << endl;
        cout << "|5. Print Tasks                                |" << endl;
        cout << "|6. Search Tasks                               |" << endl;
        cout << "|7. Sort Tasks                                 |" << endl;
        cout << "|8. Undo                                       |" << endl;
        cout << "|9. Redo                                       |" << endl;
        cout << "|10. In the mood for some motivation?          |" << endl;
        cout << "|11. Quit                                      |" << endl;
        cout << "|______________________________________________|" << endl;
        cout << "                            Enter your choice: ";
        int choice;
        cin >> choice;
        cout << "                                               " << endl;
        cout << "                                               " << endl;
        cout << "                                               " << endl;
        cout << "                                               " << endl;
        cout << "                                               " << endl;
 
        switch (choice) {
            case 1:
                taskManager.insertTask(tasks);
                break;
            case 2:
                taskManager.removeTask(tasks);
                break;
            case 3:
                taskManager.markAsDone(tasks);
                break;
            case 4:
                taskManager.markAsUndone(tasks);
                break;
            case 5:
                taskManager.printTasks(tasks);
                break;
            case 6:
                taskManager.searchTasks(tasks);
                break;
            case 7:
                taskManager.sortTasks(tasks);
                break;  
            case 8:
                taskManager.undo(tasks);
                break;
            case 9:
                taskManager.redo(tasks);
                break;
            case 10:
                {
                    int randomIndex = std::rand() % (sizeof(motivationalQuotes) / sizeof(motivationalQuotes[0]));
                    cout << "Motivational Quote: " << motivationalQuotes[randomIndex] << endl;
                }
                break;
            case 11:
                cout << "Exiting the program. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
 
int main() {
    cout << " ______________________________________________" << endl;
    cout << "|            Task Manager Main Menu            |" << endl;
    cout << "|______________________________________________|" << endl;
    cout << "|Choose the type of task list:                 |" << endl;
    cout << "|______________________________________________|" << endl;
    cout << "|1. My Daily goals                             |" << endl;
    cout << "|2. My Monthly Planner                         |" << endl;
    cout << "|0. Quit                                       |" << endl;
    cout << "|______________________________________________|" << endl;
    cout << "                            Enter your choice: ";
    int managerChoice;
    cin >> managerChoice;
 
    if (managerChoice == 1) {
        VectorTaskManager vectorTaskManager;
        vector<Task> vectorTasks;
        performOperations(vectorTaskManager, vectorTasks);
    } else if (managerChoice == 2) {
        LinkedListTaskManager linkedListTaskManager;
        vector<Task> linkedListTasks;
        performOperations(linkedListTaskManager, linkedListTasks);
    } else if (managerChoice == 0) {
        cout << "Invalid choice. Please run the program again and select a valid option. Bye :( " << endl;
    } else {
        cout << "Invalid choice. Please run the program again and select a valid option." << endl;
    }
    return 0;
}