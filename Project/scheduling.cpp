#include <iostream> // For input/output operations (e.g., cout, cin)
#include <fstream> // For file input/output operations (reading and writing)
#include <vector>  // For using dynamic arrays (vectors)
#include <string>  // For using strings
#include <algorithm> // For algorithms like `remove_if`
#include <sstream>   // For string stream operations (parsing strings)
#include <utility>   // For using `std::pair`
#include <ctime>     // For date and time operations
#include <iomanip>   // For output formatting (e.g., setting precision)

// Conditional inclusion for getch() - handles both Windows and Unix-like systems
#ifdef _WIN32
#include <conio.h> // For _getch() on Windows (non-standard)
#define getch _getch // Define getch to be _getch on Windows
#else
#include <termios.h> // For getch() on Unix-like systems (Linux, macOS)
#include <unistd.h>
#include <stdio.h> // Required for getchar() in the Linux getch implementation (for getch())

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

using namespace std; // Use the standard namespace

// --- User Roles ---

// Abstract base class for users. Defines the common interface for all user roles.
class User {
public:
    string username;                      // User's username
    virtual string getRole() const = 0;    // Pure virtual function to get the user's role (e.g., "Artist")
    virtual bool canBook() const = 0;    // Pure virtual function: Can the user book?
    virtual bool canCancel() const = 0;  // Pure virtual function: Can the user cancel?
    virtual bool canList() const = 0;    // Pure virtual function: Can the user list?
    virtual bool isAdmin() const = 0;   // Pure virtual function: Is the user an admin?
    virtual ~User() {}                   // Virtual destructor for proper cleanup (polymorphism)
    User(const string& name) : username(name) {} // Constructor to initialize username
};

// Concrete user role: Artist
class Artist : public User {
public:
    Artist(const string& name) : User(name) {} // Constructor: calls the User constructor
    string getRole() const override { return "Artist"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
};

// Concrete user role: Producer
class Producer : public User {
public:
    Producer(const string& name) : User(name) {} // Constructor: calls the User constructor
    string getRole() const override { return "Producer"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
};

// Concrete user role: Engineer
class Engineer : public User {
public:
    Engineer(const string& name) : User(name) {} // Constructor: calls the User constructor
    string getRole() const override { return "Engineer"; }
    bool canBook() const override { return false; } // Engineers cannot book
    bool canCancel() const override { return false; } // Engineers cannot cancel
    bool canList() const override { return true; }    // Engineers can list
    bool isAdmin() const override { return false; }
};

// Concrete user role: Admin
class Admin : public User {
public:
    Admin(const string& name) : User(name) {} // Constructor: calls the User constructor
    string getRole() const override { return "Admin"; }
    bool canBook() const override { return true; }     // Admins can book
    bool canCancel() const override { return true; }   // Admins can cancel
    bool canList() const override { return true; }     // Admins can list
    bool isAdmin() const override { return true; }    // Admins are admins
};

// --- Access Control Manager ---
class AccessControlManager {
private:
    User* currentUser = nullptr;    // Pointer to the currently logged-in user
    const string userFile = "users.txt"; // Name of the file to store user data

    // Structure to hold user data (username, password, role)
    struct UserData {
        string username;
        string password;
        string role;
    };

    // Helper function to load user credentials from the user file
    vector<UserData> loadUsers() const {
        vector<UserData> users;
        ifstream file(userFile); // Open the user file for reading
        if (file.is_open()) {
            string line;
            while (getline(file, line)) { // Read the file line by line
                stringstream ss(line);       // Create a stringstream to parse the line
                UserData userData;            // Create a UserData object
                getline(ss, userData.username, ','); // Extract the username (up to the first comma)
                getline(ss, userData.password, ','); // Extract the password (up to the second comma)
                getline(ss, userData.role, ',');     // Extract the role (up to the end of the line)
                users.push_back(userData); // Add the extracted user data to the vector
            }
            file.close(); // Close the file
        }
        return users; // Return the vector of user data
    }

    // Helper function to save user credentials to the user file
    void saveUsers(const vector<UserData>& users) {
        ofstream file(userFile); // Open the user file for writing (overwrite if it exists)
        if (file.is_open()) {
            for (const auto& user : users) { // Iterate through the users vector
                file << user.username << "," << user.password << "," << user.role << endl; // Write user data to the file, comma separated
            }
            file.close(); // Close the file
        }
    }

    // Helper function to authenticate a user
    User* authenticate(const string& username, const string& password) {
        vector<UserData> users = loadUsers(); // Load users from the file
        for (const auto& user : users) {      // Iterate through the users
            if (user.username == username && user.password == password) { // Check for matching username and password
                // Create and return a User object based on the user's role
                if (user.role == "Artist") return new Artist(username);
                if (user.role == "Producer") return new Producer(username);
                if (user.role == "Engineer") return new Engineer(username);
                if (user.role == "Admin") return new Admin(username);
            }
        }
        return nullptr; // Authentication failed
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
        cout << "\n--- New User Registration ---" << endl;
        cout << "Enter Username: ";
        cin >> username;

        vector<UserData> users = loadUsers();
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
        vector<UserData> users = loadUsers();
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


    void registerAdmin() {
        // This function is now redundant, as admin registration is part of registerUser
        cout << "Admin registration is now part of the regular registration process." << endl;
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
    int choice;
    cout << "\n🎵 Studio Booking System 🎵" << endl;
    cout << "1️⃣ Book a Session" << endl;
    cout << "2️⃣ Cancel a Session" << endl;
    cout << "3️⃣ List Bookings" << endl;
    cout << "4️⃣ Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void getBookingDetails(string& artist, string& date, string& time) {
    cin.ignore();
    cout << "Enter Artist Name: ";
    getline(cin, artist);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Time Slot (e.g., 10:00 AM - 12:00 PM): ";
    getline(cin, time);
}

int main() {
    AccessControlManager accessControl;  // Create Access Control Manager
    //StudioScheduler scheduler(accessControl); // Pass accessControl to StudioScheduler
    int choice;
    string artist, date, time;
    // Removed Booking

    // Login or Register
    int authChoice;
    do {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> authChoice;

        switch (authChoice) {
            case 1: // Sign Up
                accessControl.registerUser(); // Call the registerUser function
                break;
            case 2:
                accessControl.login();
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0; // Exit the program
            default:
                cout << "Invalid choice." << endl;
        }
    } while (authChoice != 2 && accessControl.getCurrentUser() == nullptr && authChoice != 3); // Continue if not logged in or exit chosen

    if (!accessControl.getCurrentUser()) {
        cout << "Exiting." << endl;
        return 1; // Exit if no user is logged in
    }

    // Removed rest of code as per request, now only shows the authentication.
    cout << "\nLogged in as: " << accessControl.getCurrentUser()->username << " (" << accessControl.getCurrentUser()->getRole() << ")" << endl;

    return 0;
}