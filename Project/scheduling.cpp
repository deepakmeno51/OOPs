#include <iostream> // For input/output operations (e.g., cout, cin)
#include <fstream> // For file input/output operations (e.g., reading from and writing to files)
#include <vector>  // For using the vector container (dynamic array) to store bookings
#include <string>  // For using the string class to represent text data
#include <algorithm> // For using std::remove_if, a useful algorithm

using namespace std; // Avoids repeatedly writing std:: before standard library elements

class StudioScheduler {
private:
    // Nested struct to represent a booking
    struct Booking {
        string artist; // Name of the artist
        string date;   // Date of the booking (e.g., "2025-02-12")
        string time;   // Time slot of the booking (e.g., "10:00 AM - 12:00 PM")
    };

    vector<Booking> bookings; // A vector to store multiple Booking objects (the bookings)
    const string filename = "bookings.txt";  // The name of the file to store bookings persistently

    // Helper function to save the booking data to a file
    void saveToFile() {
        ofstream file(filename); // Open the file for writing (creates it if it doesn't exist, overwrites if it does)
        if (file.is_open()) { // Check if the file was opened successfully
            for (const auto& booking : bookings) { // Iterate through each booking in the bookings vector
                file << booking.artist << "," << booking.date << "," << booking.time << endl; // Write the artist, date, and time to the file, separated by commas, and a newline at the end
            }
            file.close(); // Close the file to ensure data is written and resources are released
        }
    }

    // Helper function to load booking data from a file
    void loadFromFile() {
        ifstream file(filename); // Open the file for reading
        if (file.is_open()) { // Check if the file opened successfully
            bookings.clear(); // Clear the bookings vector to remove any existing bookings before loading
            string line; // Holds a line of the file
            while (getline(file, line)) {  // Read the file line by line, reading entire lines, and store each line in the 'line' string
                size_t pos1 = line.find(',');   // Find the position of the first comma (separates artist and date)
                size_t pos2 = line.find(',', pos1 + 1); // Find the position of the second comma (separates date and time), starting the search after the first comma
                if (pos1 != string::npos && pos2 != string::npos) { // Check if both commas were found (valid format)
                    string artist = line.substr(0, pos1);              // Extract the artist name (from the beginning to the first comma)
                    string date = line.substr(pos1 + 1, pos2 - pos1 - 1); // Extract the date (from after the first comma to the second comma)
                    string time = line.substr(pos2 + 1);              // Extract the time (from after the second comma to the end of the line)
                    bookings.push_back({artist, date, time}); // Create a Booking object with the extracted data and add it to the bookings vector
                }
            }
            file.close(); // Close the file
        }
    }

public:
    // Constructor: Called when a StudioScheduler object is created
    StudioScheduler() {
        loadFromFile();  // Load bookings from the file when the scheduler is created (so bookings persist between runs)
    }

    // Function to check if a given time slot is available (not already booked)
    bool isAvailable(const string& date, const string& time) const { //Added const to the function signature, added const to the string&
        for (const auto& booking : bookings) { // Iterate through all existing bookings
            if (booking.date == date && booking.time == time) { // Check if the date and time match an existing booking
                return false;  // If a match is found, the time slot is already booked, so return false
            }
        }
        return true; // If no match is found, the time slot is available, so return true]
    }

    // Function to book a studio session
    void bookSession(const string& artist, const string& date, const string& time) { // Added const to the function signature, added const to the string&
        if (isAvailable(date, time)) { // Check if the time slot is available using the isAvailable() function
            bookings.push_back({artist, date, time}); // If available, create a new Booking object and add it to the bookings vector
            saveToFile();  // Save the updated bookings to the file to persist the new booking
            cout << "Booking confirmed for " << artist << " on " << date << " at " << time << endl; // Print a success message
        } else {
            cout << "Error: Time slot already booked!" << endl; // Print an error message if the time slot is not available
        }
    }

    // Function to cancel a booking
    void cancelSession(const string& artist, const string& date, const string& time) { // Added const to the function signature, added const to the string&
        // Use std::remove_if to efficiently remove the booking matching the artist, date, and time.

        // remove_if iterates through the bookings vector and moves all the elements that do NOT match the condition to the beginning.
        // It returns an iterator to the beginning of the "removed" section of the vector
        auto it = remove_if(bookings.begin(), bookings.end(),
                           [&](const Booking& booking) { // Lambda function to define the removal condition.  [&] captures variables from the enclosing scope by reference.
                               return booking.artist == artist && booking.date == date && booking.time == time; // The lambda returns true if the booking should be removed.
                           });

        if (it != bookings.end()) {
            bookings.erase(it, bookings.end());  // Erase the elements marked for removal (from 'it' to the end of the vector)
            saveToFile();  // Save the updated bookings to the file
            cout << "Session canceled for " << artist << " on " << date << " at " << time << endl; // Print confirmation message
        } else {
            cout << "Error: No matching booking found!" << endl; // Print an error message if no matching booking was found
        }
    }

    // Function to list all current bookings
    void listBookings() const { // Added const to the function signature
        if (bookings.empty()) { // Check if the bookings vector is empty
            cout << "No bookings available." << endl; // If empty, print a message indicating no bookings
            return; // Exit the function
        }

        cout << "\nCurrent Studio Bookings:\n"; // Print a header for the list of bookings
        for (const auto& booking : bookings) { // Iterate through each booking in the bookings vector
            cout << "Artist: " << booking.artist << " | Date: " << booking.date << " | Time: " << booking.time << endl; // Print the booking details
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
    StudioScheduler scheduler; // Create an instance of the StudioScheduler class (this loads any existing bookings from file)
    int choice;
    string artist, date, time;

    do {
        choice = displayMenu(); // Display the menu and get the user's choice

        switch (choice) {
            case 1: // Book a Session
                getBookingDetails(artist, date, time);
                scheduler.bookSession(artist, date, time);
                break;
            case 2: // Cancel a Session
                getBookingDetails(artist, date, time);
                scheduler.cancelSession(artist, date, time);
                break;
            case 3: // List Bookings
                scheduler.listBookings();
                break;
            case 4: // Exit
                cout << "Exiting Studio Booking System. Goodbye!" << endl;
                break;
            default: // Invalid choice
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4); // Continue looping until the user chooses to exit (option 4)

    return 0; // Indicates successful program execution
}