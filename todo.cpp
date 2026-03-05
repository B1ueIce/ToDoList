#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

struct Task {
    string name;
    int priority = 5;
    bool completed = false;
};

void addTask(vector<Task>& tasks);
void viewTasks(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void completeTask(vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks);
void loadTasks(vector<Task>& tasks);

int main() {

    vector<Task> tasks;
    int choice = 0;

    loadTasks(tasks);

    while (choice != 5) {

        cout << "\n===== TODO LIST =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Complete Task\n";
        cout << "5. Exit\n\n";

        cout << "Choose option: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {

            case 1:
                addTask(tasks);
                break;

            case 2:
                viewTasks(tasks);
                break;

            case 3:
                deleteTask(tasks);
                break;

            case 4:
                completeTask(tasks);
                break;

            case 5:
                saveTasks(tasks);
                cout << "Tasks saved. Goodbye!\n";
                break;

            default:
                cout << "Invalid option\n";
        }
    }

    return 0;
}

void addTask(vector<Task>& tasks) {

    Task newTask;

    cout << "\nTask Name: ";
    getline(cin, newTask.name);

    cout << "Priority (1-10, optional, default 5): ";

    string input;
    getline(cin, input);

    if (!input.empty()) {
        int p = stoi(input);
        if (p >= 1 && p <= 10)
            newTask.priority = p;
    }

    tasks.push_back(newTask);

    cout << "Task added.\n";
}

void viewTasks(vector<Task>& tasks) {

    if (tasks.empty()) {
        cout << "\nNo tasks.\n";
        return;
    }

    sort(tasks.begin(), tasks.end(), [](Task& a, Task& b) {
        return a.priority < b.priority;
    });

    cout << "\n===== TASKS =====\n\n";

    for (int i = 0; i < tasks.size(); i++) {

        cout << "[" << i+1 << "] ";

        if (tasks[i].completed)
            cout << "[C] ";
        else
            cout << "[ ] ";

        cout << tasks[i].name
             << " (Priority " << tasks[i].priority << ")"
             << "\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

void deleteTask(vector<Task>& tasks) {

    if (tasks.empty()) {
        cout << "\nNo tasks to delete.\n";
        return;
    }

    viewTasks(tasks);

    int choice;

    cout << "\nTask to delete: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice >= 1 && choice <= tasks.size()) {

        tasks.erase(tasks.begin() + choice - 1);

        cout << "Task deleted.\n";
    }
    else
        cout << "Invalid task.\n";
}

void completeTask(vector<Task>& tasks) {

    if (tasks.empty()) {
        cout << "\nNo tasks.\n";
        return;
    }

    viewTasks(tasks);

    int choice;

    cout << "\nTask completed: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice >= 1 && choice <= tasks.size()) {

        tasks[choice-1].completed = true;

        cout << "Task marked completed.\n";
    }
    else
        cout << "Invalid task.\n";
}

void saveTasks(const vector<Task>& tasks) {

    ofstream file("tasks.txt");

    for (const auto& t : tasks) {
        file << t.name << "|"
             << t.priority << "|"
             << t.completed << "\n";
    }
}

void loadTasks(vector<Task>& tasks) {

    ifstream file("tasks.txt");

    if (!file)
        return;

    string name;
    int priority;
    bool completed;

    while (getline(file, name, '|')) {

        file >> priority;
        file.ignore();

        file >> completed;
        file.ignore();

        tasks.push_back({name, priority, completed});
    }
}