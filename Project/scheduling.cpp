#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <ctime>
#include <iomanip> // For formatting output



//Explanation of the libraries used in the making of the scheduling system 
// <iostream> -> std in and out operations
// <fstream> -> used in file managing and file reading which is required when a session is booked
// <vector> -> to allow the usage of dynamic arrays where we can store data of the same data type
// <string> -> used to represent string 
// <algorithms> -> Contains a large collection of generic algorithms that operate on containers (like vector). These algorithms perform common operations without you having to write the code yourself.


using namespace std;

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

    // Helper method to determine if a date is a weekend
    bool isWeekend(const string& date) {
        // Use a simplified approach, avoiding get_time and tm structs if possible
        // This assumes dates are always in YYYY-MM-DD format, and only checks if the day is Saturday or Sunday
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            return false; // Invalid date format
        }

        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

        // Zeller's congruence to calculate the day of the week
        //  0 = Saturday, 1 = Sunday, ..., 6 = Friday

        if (month < 3) {
            month += 12;
            year--;
        }
        int dayOfWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 2) % 7;


        return (dayOfWeek == 0 || dayOfWeek == 1); // 0 is Saturday, 1 is Sunday
    }

    // Helper to calculate hours from time string
    double getHoursFromTime(const string& time) {
        size_t dash = time.find(" - ");
        if (dash == string::npos) return 0.0;
        string start = time.substr(0, dash);
        string end = time.substr(dash + 3);

        int startHour, startMinute, endHour, endMinute;
        sscanf(start.c_str(), "%d:%d", &startHour, &startMinute);
        sscanf(end.c_str(), "%d:%d", &endHour, &endMinute);

        double duration = (endHour - startHour) + (endMinute - startMinute) / 60.0;
        return duration;
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

        if (tokens.size() >= 4) {
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
            return nextSlot;
        }

        int nextStartHour = requestedEndHour;
        int nextEndHour = requestedEndHour + 2;

        string nextStartTime = to_string(nextStartHour) + ":00";
        string nextEndTime = to_string(nextEndHour) + ":00";
        string nextTimeSlot = nextStartTime + " - " + nextEndTime;

        if(isAvailable(requestedDate, nextTimeSlot)){
            nextSlot = make_pair(requestedDate, nextTimeSlot);
        }

        return nextSlot;
    }



public:
    StudioScheduler() {
        loadFromFile();
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
        double rate = isWeekend(date) ? 15.0 : 10.0;
        double hours = getHoursFromTime(time);
        double price = hours * rate;

        if (isAvailable(date, time)) {
            bookings.push_back({artist, date, time, price});
            saveToFile();
            cout << "Booking confirmed for " << artist << " on " << date << " at " << time << ". Total Cost: $" << fixed << setprecision(2) << price << endl;

            cout << "Already booked slots for " << artist << ":" << endl;
            for (const auto& booking : bookings) {
                if (booking.artist == artist) {
                    cout << booking.date << " at " << booking.time << " - Cost: $" << fixed << setprecision(2) << booking.price << endl;
                }
            }
        } else {
            cout << "Error: Time slot already booked!" << endl;

            auto nextSlot = findNextAvailableSlot(date, time);
            if (!nextSlot.first.empty()) {
                cout << "Next available slot is on " << nextSlot.first << " at " << nextSlot.second << endl;
            } else {
                cout << "No other slots available" << endl;
            }
        }
    }

    void cancelSession(const string& artist, const string& date, const string& time) {
         auto it = remove_if(bookings.begin(), bookings.end(),
                           [&](const Booking& booking) {
                               return booking.artist == artist && booking.date == date && booking.time == time;
                           });

        if (it != bookings.end()) {
            bookings.erase(it, bookings.end());
            saveToFile();
            cout << "Session canceled for " << artist << " on " << date << " at " << time << endl;
        } else {
            cout << "Error: No matching booking found!" << endl;
        }
    }

    void listBookings() const {
        if (bookings.empty()) {
            cout << "No bookings available." << endl;
            return;
        }

        cout << "\nCurrent Studio Bookings:\n";
        for (const auto& booking : bookings) {
            cout << "Artist: " << booking.artist << " | Date: " << booking.date << " | Time: " << booking.time << " | Cost: $" << fixed << setprecision(2) << booking.price << endl;
        }
    }
};

// Function to display the menu and get user input
int displayMenu() {
    int choice;
    cout << "\n🎵 Studio Booking System 🎵" << endl;
    cout << "1. Book a Session" << endl;
    cout << "2. Cancel a Session" << endl;
    cout << "3. List Bookings" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to get booking details from the user
void getBookingDetails(string& artist, string& date, string& time) {
    cin.ignore(); // Consume the newline character left in the buffer

    cout << "Enter Artist Name: ";
    getline(cin, artist);

    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter Time Slot (e.g., 10:00 AM - 12:00 PM): ";
    getline(cin, time);
}


// Main function (program entry point)
int main() {
    StudioScheduler scheduler;
    int choice;
    string artist, date, time;

    do {
        choice = displayMenu();

        switch (choice) {
            case 1:
                getBookingDetails(artist, date, time);
                scheduler.bookSession(artist, date, time);
                break;
            case 2:
                getBookingDetails(artist, date, time);
                scheduler.cancelSession(artist, date, time);
                break;
            case 3:
                scheduler.listBookings();
                break;
            case 4:
                cout << "Exiting Studio Booking System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}