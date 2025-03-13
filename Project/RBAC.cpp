#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <ctime>
#include <iomanip>

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
    virtual ~User() {} // Virtual Destructor
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
    const string userFile = "users.txt"; // File for user data

    struct UserData {
        string username;
        string password;
        string role;
    };

    // Load users from file
    vector<UserData> loadUsers() {
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
    void login() {
        string username, password;
        cout << "\n--- Login ---" << endl;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

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
        string username, password;
        cout << "\n--- Register Admin ---" << endl;
        cout << "Enter new Admin Username: ";
        cin >> username;
        cout << "Enter new Admin Password: ";
        cin >> password;

        vector<UserData> users = loadUsers();
        for (const auto& user : users) {
            if (user.username == username) {
                cout << "Username already exists." << endl;
                return;
            }
        }
        users.push_back({username, password, "Admin"}); // Add new user
        saveUsers(users);
        cout << "Admin registered successfully." << endl;
    }

    void logout() {
        delete currentUser;
        currentUser = nullptr;
        cout << "Logged out." << endl;
    }

    bool hasPermission(const string& action) const {
        if (!currentUser) {
            cout << "Not logged in." << endl;
            return false;
        }
        if (action == "book") return currentUser->canBook();
        if (action == "cancel") return currentUser->canCancel();
        if (action == "list") return currentUser->canList();
        if (action == "isAdmin") return currentUser->isAdmin(); // Check admin status
        return false; // Default: no permission
    }

    User* getCurrentUser() const {
        return currentUser;
    }

    ~AccessControlManager() {
        delete currentUser;
    }
};

// --- Studio Scheduler ---
class StudioScheduler {
private:
    struct Booking {
        string artist;
        string date;
        string time;
        double price;
    };
    vector<Booking> bookings;
    const string filename = "bookings.txt";
    AccessControlManager& accessControl; // Reference to AccessControlManager

    bool isWeekend(const string& date) {
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            return false;
        }
        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
        if (month < 3) { month += 12; year--; }
        int dayOfWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 2) % 7;
        return (dayOfWeek == 0 || dayOfWeek == 6);
    }
    double getHoursFromTime(const string& time) {
        size_t dash = time.find(" - ");
        if (dash == string::npos) return 0.0;
        string start = time.substr(0, dash);
        string end = time.substr(dash + 3);
        int startHour, startMinute, endHour, endMinute;
        sscanf(start.c_str(), "%d:%d", &startHour, &startMinute);
        sscanf(end.c_str(), "%d:%d", &endHour, &endMinute);
        double duration = (endHour + endMinute / 60.0) - (startHour + startMinute / 60.0);
        return (duration < 0) ? 0 : duration;
    }

    void saveBookingsToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& booking : bookings) {
                file << booking.artist << "," << booking.date << "," << booking.time << "," << fixed << setprecision(2) << booking.price << endl;
            }
            file.close();
        }
    }
    void loadBookingsFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            bookings.clear();
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(','), pos2 = line.find(',', pos1 + 1), pos3 = line.find(',', pos2 + 1);
                if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                    string artist = line.substr(0, pos1);
                    string date = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string time = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    double price = stod(line.substr(pos3 + 1));
                    bookings.push_back({artist, date, time, price});
                }
            }
            file.close();
        }
    }

public:
    StudioScheduler(AccessControlManager& acm) : accessControl(acm) {
        loadBookingsFromFile();
    }
    bool isAvailable(const string& date, const string& time) const {
        for (const auto& booking : bookings) {
            if (booking.date == date && booking.time == time) {
                return false;
            }
        }
        return true;
    }
    void bookSession(const string& artist, const string& date, const string& time) {
        if (!accessControl.hasPermission("book")) {
            cout << "No permission." << endl;
            return;
        }
        double rate = isWeekend(date) ? 15.0 : 10.0;
        double hours = getHoursFromTime(time);
        double price = hours * rate;
        if (isAvailable(date, time)) {
            bookings.push_back({artist, date, time, price});
            saveBookingsToFile();
            cout << "Booked for " << artist << " on " << date << " at " << time << " for $" << fixed << setprecision(2) << price << endl;
        } else {
            cout << "Time slot unavailable." << endl;
        }
    }
    void cancelSession(const string& artist, const string& date, const string& time) {
        if (!accessControl.hasPermission("cancel")) {
            cout << "No permission." << endl;
            return;
        }
        auto it = remove_if(bookings.begin(), bookings.end(),
                            [&](const Booking& booking) {
                                return booking.artist == artist && booking.date == date && booking.time == time;
                            });
        if (it != bookings.end()) {
            bookings.erase(it, bookings.end());
            saveBookingsToFile();
            cout << "Cancelled." << endl;
        } else {
            cout << "Not found." << endl;
        }
    }
    void listBookings() const {
        if (!accessControl.hasPermission("list")) {
            cout << "No permission." << endl;
            return;
        }
        if (bookings.empty()) {
            cout << "No bookings." << endl;
            return;
        }
        cout << "\nBookings:\n";
        for (const auto& booking : bookings) {
            cout << booking.artist << " | " << booking.date << " | " << booking.time << " | $" << fixed << setprecision(2) << booking.price << endl;
        }
    }
};

// --- Menu and Main Function ---
int displayMenu() {
    cout << "\n--- Studio Booking ---" << endl;
    cout << "1. Book\n2. Cancel\n3. List\n4. Exit" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    AccessControlManager accessControl;  // Create Access Control Manager
    StudioScheduler scheduler(accessControl); // Pass accessControl to StudioScheduler
    string username, password;

    // Login or Register
    int authChoice;
    do {
        cout << "\n1. Login\n2. Register Admin\nEnter choice: ";
        cin >> authChoice;
        if (authChoice == 1) {
            accessControl.login();
        } else if (authChoice == 2) {
            accessControl.registerAdmin();
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (authChoice != 1 && authChoice != 2 && accessControl.getCurrentUser() == nullptr);

    if (!accessControl.getCurrentUser()) {
        cout << "Exiting." << endl;
        return 1; // Exit if no user is logged in
    }

    int choice;
    string artist, date, time;

    do {
        cout << "\nLogged in as: " << accessControl.getCurrentUser()->username << " (" << accessControl.getCurrentUser()->getRole() << ")";
        choice = displayMenu();

        switch (choice) {
            case 1:
                cin.ignore(); // Consume newline
                cout << "Enter Artist: "; getline(cin, artist);
                cout << "Enter Date (YYYY-MM-DD): "; getline(cin, date);
                cout << "Enter Time: "; getline(cin, time);
                scheduler.bookSession(artist, date, time);
                break;
            case 2:
                cin.ignore(); // Consume newline
                cout << "Enter Artist: "; getline(cin, artist);
                cout << "Enter Date (YYYY-MM-DD): "; getline(cin, date);
                cout << "Enter Time: "; getline(cin, time);
                scheduler.cancelSession(artist, date, time);
                break;
            case 3:
                scheduler.listBookings();
                break;
            case 4:
                cout << "Exiting." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 4);
    delete accessControl.getCurrentUser();
    return 0;
}