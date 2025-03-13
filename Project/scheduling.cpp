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

// Forward Declarations
class StudioScheduler;

class User {
public:
    string username;
    virtual string getRole() const = 0;
    virtual bool canBook() const = 0;
    virtual bool canCancel() const = 0;
    virtual bool canList() const = 0;
    virtual ~User() {}
};

class Artist : public User {
public:
    Artist(const string& name) { username = name; }
    string getRole() const override { return "Artist"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
};

class Producer : public User {
public:
    Producer(const string& name) { username = name; }
    string getRole() const override { return "Producer"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
};

class Engineer : public User {
public:
    Engineer(const string& name) { username = name; }
    string getRole() const override { return "Engineer"; }
    bool canBook() const override { return false; }
    bool canCancel() const override { return false; }
    bool canList() const override { return true; }
};

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
    User* currentUser = nullptr;

    bool isWeekend(const string& date) {
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            return false;
        }
        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
        if (month < 3) {
            month += 12;
            year--;
        }
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

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& booking : bookings) {
                file << booking.artist << "," << booking.date << "," << booking.time << "," << fixed << setprecision(2) << booking.price << endl;
            }
            file.close();
        }
    }

    void loadFromFile() {
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

    pair<int, int> extractTimeRange(const string& timeSlot) {
        int startHour = -1;
        int endHour = -1;
        stringstream ss(timeSlot);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 3) {
            string startTime = tokens[0];
            string endTime = tokens[2];
            size_t colonPos1 = startTime.find(':');
            if (colonPos1 != string::npos) {
                startHour = stoi(startTime.substr(0, colonPos1));
            }
            size_t colonPos2 = endTime.find(':');
            if (colonPos2 != string::npos) {
                endHour = stoi(endTime.substr(0, colonPos2));
            }
        }
        return make_pair(startHour, endHour);
    }

    pair<string, string> findNextAvailableSlot(const string& requestedDate, const string& requestedTime) {
        pair<string, string> nextSlot = make_pair("", "");

        auto requestedTimeRange = extractTimeRange(requestedTime);
        int requestedStartHour = requestedTimeRange.first;
        int requestedEndHour = requestedTimeRange.second;

        if (requestedStartHour == -1 || requestedEndHour == -1) {
            return nextSlot; // Invalid time format
        }

        int nextStartHour = requestedEndHour;
        int nextEndHour = requestedEndHour + 2; // Assuming bookings are in 2-hour blocks

        string nextStartTime = to_string(nextStartHour) + ":00";
        string nextEndTime = to_string(nextEndHour) + ":00";
        string nextTimeSlot = nextStartTime + " - " + nextEndTime;

        if (isAvailable(requestedDate, nextTimeSlot)) {
            nextSlot = make_pair(requestedDate, nextTimeSlot);
        }
        return nextSlot;
    }

public:
    StudioScheduler() {
        loadFromFile();
    }

    ~StudioScheduler() {  // Added destructor to clean up currentUser
        delete currentUser;
        currentUser = nullptr;
    }

    bool isAvailable(const string& date, const string& time) const {
        for (const auto& booking : bookings) {
            if (booking.date == date && booking.time == time) {
                return false;
            }
        }
        return true;
    }

    User* authenticateUser(const string& username, const string& password) {
        if (username == "artist" && password == "artistpass") {
            return new Artist(username);
        } else if (username == "producer" && password == "producerpass") {
            return new Producer(username);
        } else if (username == "engineer" && password == "engineerpass") {
            return new Engineer(username);
        }
        return nullptr;
    }

    friend void bookSession(StudioScheduler& scheduler, const string& artist, const string& date, const string& time);
    friend void cancelSession(StudioScheduler& scheduler, const string& artist, const string& date, const string& time);
    friend void listBookings(const StudioScheduler& scheduler);
    friend void login(StudioScheduler& scheduler);
};

void bookSession(StudioScheduler& scheduler, const string& artist, const string& date, const string& time) {
    if (scheduler.currentUser == nullptr || !scheduler.currentUser->canBook()) {
        cout << "Error: You do not have permission to book sessions." << endl;
        return;
    }

    double rate = scheduler.isWeekend(date) ? 15.0 : 10.0;
    double hours = scheduler.getHoursFromTime(time);
    double price = hours * rate;

    if (scheduler.isAvailable(date, time)) {
        scheduler.bookings.push_back({artist, date, time, price});
        scheduler.saveToFile();
        cout << "Booking confirmed for " << artist << " on " << date << " at " << time << ". Total Cost: $" << fixed << setprecision(2) << price << endl;

        cout << "Already booked slots for " << artist << ":" << endl;
        for (const auto& booking : scheduler.bookings) {
            if (booking.artist == artist) {
                cout << booking.date << " at " << booking.time << " - Cost: $" << fixed << setprecision(2) << booking.price << endl;
            }
        }
    } else {
        cout << "Error: Time slot already booked!" << endl;
        auto nextSlot = scheduler.findNextAvailableSlot(date, time);
        if (!nextSlot.first.empty()) {
            cout << "Next available slot is on " << nextSlot.first << " at " << nextSlot.second << endl;
        } else {
            cout << "No other slots available" << endl;
        }
    }
}

void cancelSession(StudioScheduler& scheduler, const string& artist, const string& date, const string& time) {
    if (scheduler.currentUser == nullptr || !scheduler.currentUser->canCancel()) {
        cout << "Error: You do not have permission to cancel sessions." << endl;
        return;
    }
    auto it = remove_if(scheduler.bookings.begin(), scheduler.bookings.end(),
                       [&](const StudioScheduler::Booking& booking) {
                           return booking.artist == artist && booking.date == date && booking.time == time;
                       });

    if (it != scheduler.bookings.end()) {
        scheduler.bookings.erase(it, scheduler.bookings.end());
        scheduler.saveToFile();
        cout << "Session canceled for " << artist << " on " << date << " at " << time << endl;
    } else {
        cout << "Error: No matching booking found!" << endl;
    }
}

void listBookings(const StudioScheduler& scheduler) {
    if (scheduler.currentUser == nullptr || !scheduler.currentUser->canList()) {
        cout << "Error: You do not have permission to list bookings." << endl;
        return;
    }
    if (scheduler.bookings.empty()) {
        cout << "No bookings available." << endl;
        return;
    }

    cout << "\nCurrent Studio Bookings:\n";
    for (const auto& booking : scheduler.bookings) {
        cout << "Artist: " << booking.artist << " | Date: " << booking.date << " | Time: " << booking.time << " | Cost: $" << fixed << setprecision(2) << booking.price << endl;
    }
}

void login(StudioScheduler& scheduler) {
    string username, password;
    cout << "\n--- Login ---" << endl;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    User* user = scheduler.authenticateUser(username, password);
    if (user) {
        if (scheduler.currentUser != nullptr) {  // Check before deletion to avoid double deletion
            delete scheduler.currentUser;        // Delete old user only if it exists
        }
        scheduler.currentUser = user;            // Assign new user
        cout << "Login Successful! Welcome, " << scheduler.currentUser->username << " (" << scheduler.currentUser->getRole() << ")" << endl;
    } else {
        cout << "Login Failed. Invalid username or password." << endl;
    }
}

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
    StudioScheduler scheduler;
    int choice;
    string artist, date, time;

    login(scheduler);
    if (scheduler.currentUser == nullptr) {
        cout << "Exiting, as no user is logged in." << endl;
        return 1;
    }

    do {
        cout << "\nLogged in as: " << scheduler.currentUser->username << " (" << scheduler.currentUser->getRole() << ")";
        choice = displayMenu();

        switch (choice) {
            case 1:
                getBookingDetails(artist, date, time);
                bookSession(scheduler, artist, date, time);
                break;
            case 2:
                getBookingDetails(artist, date, time);
                cancelSession(scheduler, artist, date, time);
                break;
            case 3:
                listBookings(scheduler);
                break;
            case 4:
                cout << "Exiting Studio Booking System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    delete scheduler.currentUser;  // Still valid as final cleanup

    return 0;
}