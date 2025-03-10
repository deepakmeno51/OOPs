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
        return;
    }
};