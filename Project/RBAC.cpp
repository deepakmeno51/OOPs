#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <ctime>
#include <iomanip>

// Conditional inclusion for getch() - handles both Windows and Unix-like systems
#ifdef _WIN32
#include <conio.h> // For _getch() on Windows
#define getch _getch
#else
#include <termios.h> // For getch() on Unix-like systems (Linux, macOS)
#include <unistd.h>
#include <stdio.h> // Required for getchar() in the Linux getch implementation

char getch() {
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt); // Save current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings

    ch = getchar(); // Read a character (no echo)

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    return (char)ch;
}

#endif

using namespace std;

// --- User Roles ---
class User {
public:
    string username;
    virtual string getRole() const = 0;
    virtual bool canBook() const = 0;
    virtual bool canCancel() const = 0;
    virtual bool canList() const = 0;
    virtual bool isAdmin() const = 0;
    virtual ~User() {}
    User(const string& name) : username(name) {}
};

class Artist : public User {
public:
    Artist(const string& name) : User(name) {}
    string getRole() const override { return "Artist"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
};

class Producer : public User {
public:
    Producer(const string& name) : User(name) {}
    string getRole() const override { return "Producer"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
};

class Engineer : public User {
public:
    Engineer(const string& name) : User(name) {}
    string getRole() const override { return "Engineer"; }
    bool canBook() const override { return false; }
    bool canCancel() const override { return false; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
};

class Admin : public User {
public:
    Admin(const string& name) : User(name) {}
    string getRole() const override { return "Admin"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return true; }
};

// --- Access Control Manager ---
class AccessControlManager {
private:
    User* currentUser = nullptr;
    const string userFile = "users.txt";

    struct UserData {
        string username;
        string password;
        string role;
    };

    // Load users from file
    vector<UserData> loadUsers() const {
        vector<UserData> users;
        ifstream file(userFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                UserData userData;
                getline(ss, userData.username, ',');
                getline(ss, userData.password, ',');
                getline(ss, userData.role, ',');
                users.push_back(userData);
            }
            file.close();
        }
        return users;
    }

    // Save users to file
    void saveUsers(const vector<UserData>& users) {
        ofstream file(userFile);
        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.username << "," << user.password << "," << user.role << endl;
            }
            file.close();
        }
    }

    User* authenticate(const string& username, const string& password) {
        vector<UserData> users = loadUsers();
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                if (user.role == "Artist") return new Artist(username);
                if (user.role == "Producer") return new Producer(username);
                if (user.role == "Engineer") return new Engineer(username);
                if (user.role == "Admin") return new Admin(username);
            }
        }
        return nullptr;
    }

public:
    // Constructor - Creates users.txt if it doesn't exist and checks for admin
    AccessControlManager() {
        // Check if the user file exists. If not, create it.
        ifstream file(userFile);
        if (!file.is_open()) {
            ofstream createFile(userFile); // Create an empty file
            if (createFile.is_open()) {
                createFile.close();
            } else {
                cerr << "Error: Could not create user file." << endl; // Handle the error
            }
        }
    }

    // Function to register a user
    void registerUser() {
        string username, password, confirmPassword, role;
        cout << "\n--- User Registration ---" << endl;
        cout << "Enter Username: ";
        cin >> username;

        // Load users
        vector<UserData> users = loadUsers(); // Load users only once

        for (const auto& user : users) {
            if (user.username == username) {
                cout << "Username already exists." << endl;
                return;
            }
        }

        // Password Input with Masking and Confirmation
        do {
            password = "";
            confirmPassword = "";
            char ch;
            cout << "Enter Password: ";
            while ((ch = getch()) != '\r') { // '\r' is the Enter key
                if (ch == '\b') { // Backspace
                    if (!password.empty()) {
                        cout << "\b \b"; // Erase the '*' from console
                        password.pop_back();
                    }
                }
                else {
                    cout << '*';
                    password += ch;
                }
            }
            cout << endl;

            cout << "Confirm Password: ";
            while ((ch = getch()) != '\r') { // '\r' is the Enter key
                if (ch == '\b') { // Backspace
                    if (!confirmPassword.empty()) {
                        cout << "\b \b"; // Erase the '*' from console
                        confirmPassword.pop_back();
                    }
                } else {
                    cout << '*';
                    confirmPassword += ch;
                }
            }
            cout << endl;

            if (password != confirmPassword) {
                cout << "Passwords do not match. Please re-enter." << endl;
            }
        } while (password != confirmPassword);

        // Determine the role based on the current state
        role = "Artist"; // Default role
        users.push_back({username, password, role});
        saveUsers(users);
        cout << "User registered successfully as " << role << "." << endl;
    }

    void login() {
        string username, password;
        cout << "\n--- Login ---" << endl;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";

        // Password Input with Masking
        password = "";
        char ch;
        while ((ch = getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // Backspace
                if (!password.empty()) {
                    cout << "\b \b"; // Erase the '*' from console
                    password.pop_back();
                }
            } else {
                cout << '*';
                password += ch;
            }
        }
        cout << endl;

        User* user = authenticate(username, password);
        if (user) {
            delete currentUser;
            currentUser = user;
            cout << "Login Successful! Welcome, " << currentUser->username << " (" << currentUser->getRole() << ")" << endl;
        } else {
            cout << "Login Failed." << endl;
        }
    }

    // Function to list registered users
    void listRegisteredUsers() const {
        vector<UserData> users = loadUsers();
        if (users.empty()) {
            cout << "No users registered yet." << endl;
            return;
        }

        cout << "\n--- Registered Users ---" << endl;
        for (const auto& user : users) {
            cout << "Username: " << user.username << ", Role: " << user.role << endl;
        }
    }

    void logout() {
        delete currentUser;
        currentUser = nullptr;
        cout << "Logged out." << endl;
    }

    // Check if a user has permission to perform an action
    bool hasPermission(const string& action) const {
        if (!currentUser) {
            cout << "Not logged in." << endl;
            return false;
        }
        if (action == "book") return currentUser->canBook();
        if (action == "cancel") return currentUser->canCancel();
        if (action == "list") return currentUser->canList();
        if (action == "isAdmin") return currentUser->isAdmin(); // Check admin status
        return false; // Unknown action or no permission
    }

    User* getCurrentUser() const {
        return currentUser;
    }

    ~AccessControlManager() {
        delete currentUser;
    }
};

// --- Menu and Main Function ---
int displayMenu() {
    cout << "\n--- Actions ---" << endl;
    cout << "1. Book Session (Check Permission)" << endl;
    cout << "2. Cancel Session (Check Permission)" << endl;
    cout << "3. List Bookings (Check Permission)" << endl;
    cout << "4. Is Admin? (Check Permission)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    AccessControlManager accessControl; // Create Access Control Manager
    string username, password;
    int authChoice;

    // Login or Register
    do {
        cout << "\n1. Login\n2. Register\n3. List Registered Users\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> authChoice;

        if (authChoice == 1) {
            accessControl.login();
        }
        else if (authChoice == 2) {
            accessControl.registerUser();
        }
        else if (authChoice == 3) {
             if (accessControl.getCurrentUser() != nullptr && accessControl.hasPermission("isAdmin")) {
                accessControl.listRegisteredUsers();
            } else {
                cout << "You do not have the permissions to list users" << endl;
            }
        }
        else if (authChoice == 4) {
            cout << "Exiting..." << endl;
            return 0;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    } while (authChoice != 1 && authChoice != 4 && accessControl.getCurrentUser() == nullptr);

    if (!accessControl.getCurrentUser()) {
        cout << "Exiting." << endl;
        return 1; // Exit if no user is logged in
    }

    int choice;

    do {
        cout << "\nLogged in as: " << accessControl.getCurrentUser()->username << " (" << accessControl.getCurrentUser()->getRole() << ")";
        choice = displayMenu();

        switch (choice) {
            case 1:
                accessControl.hasPermission("book");
                break;
            case 2:
                accessControl.hasPermission("cancel");
                break;
            case 3:
                accessControl.hasPermission("list");
                break;
            case 4:
                 accessControl.hasPermission("isAdmin");
                 break;
            case 5:
                cout << "Exiting." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 4);
    delete accessControl.getCurrentUser();
    return 0;
}