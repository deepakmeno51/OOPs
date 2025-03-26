#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <map>

using namespace std;

// --- Forward Declarations ---
class PluginManager; // Required for friend class declarations
class User;
// --- Plugin Structure ---
struct Plugin {
    string name;
    string description;
    string author;
    string category;

    // Constructors
    Plugin() : name(""), description(""), author(""), category("") {}  // Default constructor
    Plugin(const string& name, const string& description, const string& author, const string& category)
        : name(name), description(description), author(author), category(category) {} // Parameterized Constructor
    Plugin(const Plugin& other) : name(other.name), description(other.description), author(other.author), category(other.category) {} // Copy Constructor

    //Destructor (Optional, but good practice)
    ~Plugin() {}
};

// --- User Roles (Abstract Base Class and Derived Classes) ---
class User {
public:
    string username;

    // --- Access Specifiers ---
    // Member variables (public - accessible from anywhere)
    // virtual to allow method overriding
    virtual string getRole() const = 0;    // Pure virtual function (abstract method)
    virtual bool canBook() const = 0;
    virtual bool canCancel() const = 0;
    virtual bool canList() const = 0;
    virtual bool isAdmin() const = 0;
    virtual ~User() {}                     // Virtual Destructor
    // --- Abstraction and Encapsulation: User hides implementation details.
    // --- Member variables and function.
    User(const string& name) : username(name) {} // Constructor
    // --- Virtual Function and Polymorphism
    virtual void displayPermissions() const = 0; // Pure virtual to be implemented by derived classes
};
// Polymorphism: Different roles behave differently.

class Artist : public User {  // Base and derived classes
public:
    Artist(const string& name) : User(name) {}
    string getRole() const override { return "Artist"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
    // --- Method Overriding ---
    void displayPermissions() const override {
        cout << "  - Book: Yes" << endl;
        cout << "  - Cancel: Yes" << endl;
        cout << "  - List: Yes" << endl;
    }
};

class Producer : public User {
public:
    Producer(const string& name) : User(name) {}
    string getRole() const override { return "Producer"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
    void displayPermissions() const override {
        cout << "  - Book: Yes" << endl;
        cout << "  - Cancel: Yes" << endl;
        cout << "  - List: Yes" << endl;
    }
};

class Engineer : public User {
public:
    Engineer(const string& name) : User(name) {}
    string getRole() const override { return "Engineer"; }
    bool canBook() const override { return false; }
    bool canCancel() const override { return false; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return false; }
    void displayPermissions() const override {
        cout << "  - Book: No" << endl;
        cout << "  - Cancel: No" << endl;
        cout << "  - List: Yes" << endl;
    }
};

class Admin : public User {
public:
    Admin(const string& name) : User(name) {}
    string getRole() const override { return "Admin"; }
    bool canBook() const override { return true; }
    bool canCancel() const override { return true; }
    bool canList() const override { return true; }
    bool isAdmin() const override { return true; }
    void displayPermissions() const override {
        cout << "  - Book: Yes" << endl;
        cout << "  - Cancel: Yes" << endl;
        cout << "  - List: Yes" << endl;
        cout << "  - Admin: Yes" << endl;
    }
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
    // Constructor - Creates users.txt if it doesn't exist
    AccessControlManager() {
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

        cout << "Enter Role (Artist/Producer/Engineer): ";
        cin >> role;
        // Validate role input
        if (role != "Artist" && role != "Producer" && role != "Engineer") {
            cout << "Invalid role. Registration cancelled." << endl;
            return;
        }

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

// --- PluginManager Class ---

// --- Friend Class Declarations for Accessing Private Members ---
class PluginManager {
private:
    vector<Plugin> plugins;

    // A map to link functionalities to plugin names (for suggestions)
    map<string, vector<string>> functionalityToPlugins = {
        {"EQ", {"FabFilter Pro-Q 3", "SSL Native X-EQ 2", "Maag EQ4"}},
        {"Compression", {"FabFilter Pro-C 2", "Waves CLA-76", "Tube-Tech CL 1B", "OTT (Xfer Records)"}},
        {"Limiting", {"FabFilter Pro-L 2", "Waves SSL G-Master Buss Compressor"}},
        {"Reverb", {"Valhalla Room", "FabFilter Pro-R", "Eventide H3000"}},
        {"Delay", {"Waves H-Delay Hybrid Delay", "Soundtoys Echoboy"}},
        {"Distortion", {"Soundtoys Decapitator", "Waves Abbey Road J37 Tape", "Sausage Fattener", "RC-20 Retro Color", "Thermal (Output)"}},
        {"Chorus", {"Waves Chorus", "TAL Chorus-LX", "MicroShift", "Eventide H3000"}},
        {"Flanger", {"Waves Chorus", "Eventide H3000"}}, // Reusing chorus plugins since both have similar effect
        {"Phaser", {"Phaser BI-TRON", "Eventide H3000"}},
        {"Gate", {"Waves NS1 Noise Suppressor", "Waves Clarity Vx"}},
        {"Noise Reduction", {"Waves Clarity Vx", "Waves NS1 Noise Suppressor"}},
        {"De-esser", {"Waves Clarity Vx", "Waves Curves Equator"}},
        {"Pitch Correction", {"Waves Tune Real-Time", "Waves Clarity Vx", "Melodyne 5", "Auto-Tune Pro"}},
        {"Synthesizer", {"Serum (Xfer Records)", "Omnisphere (Spectrasonics)", "Massive (Native Instruments)", "u-he Diva", "Korg Minilogue"}},
        {"Drums", {"Addictive Drums 2", "XLN Audio XO", "Superior Drummer 3"}},
        {"Virtual Instruments", {"Arturia Analog Lab", "Korg Minilogue", "Keyscape (Spectrasonics)"}},
        {"Mastering", {"iZotope Ozone", "Waves SSL G-Master Buss Compressor", "T-RackS 5"}},
        {"Spectrum Analyzer", {"SPAN (Voxengo)"}},
        {"Loudness Meter", {"Youlean Loudness Meter"}},
        {"Vocal Processing", {"VocalSynth 2", "Waves Tune Real-Time", "Waves Clarity™ Vx"}}, // VocalSynth and Tuner
        {"Mixing", {"Neutron 4 (iZotope)"}},
        {"Audio Analysis", {"Mastering The Mix EXPOSE 2"}},
        {"Special FX", {"ShaperBox 3", "Portal (Output)", "Looperator (Sugar Bytes)", "Effectrix (Sugar Bytes)"}}
    };
    // --- Abstraction --- Hiding implementation details of plugin management.

public:
    // Constructor - Adds the predefined plugins
    PluginManager() {
        //  1. Instruments
        addPlugin("Serum (Xfer Records)", "Wavetable synthesizer", "Xfer Records", "Synthesizer");
        addPlugin("Omnisphere (Spectrasonics)", "Powerful synthesizer", "Spectrasonics", "Synthesizer");
        addPlugin("Kontakt (Native Instruments)", "Sampler", "Native Instruments", "Virtual Instruments");
        addPlugin("Massive (Native Instruments)", "Synthesizer", "Native Instruments", "Synthesizer");
        addPlugin("Keyscape (Spectrasonics)", "Keyboard and piano instruments", "Spectrasonics", "Virtual Instruments");
        addPlugin("Addictive Drums 2 (XLN Audio)", "Realistic drum sounds", "XLN Audio", "Drums");
        addPlugin("Superior Drummer 3 (Toontrack)", "Advanced drum sampling", "Toontrack", "Drums");

        // 2. Effects
        addPlugin("Valhalla Room (Valhalla DSP)", "Algorithmic reverb", "Valhalla DSP", "Reverb");
        addPlugin("FabFilter Pro-R (FabFilter)", "Natural and flexible reverb", "FabFilter", "Reverb");
        addPlugin("EchoBoy (Soundtoys)", "Analog-style delay", "Soundtoys", "Delay");
        addPlugin("H-Delay (Waves)", "Classic delay", "Waves", "Delay");
        addPlugin("FabFilter Pro-Q 3 (FabFilter)", "Parametric EQ with dynamic capabilities", "FabFilter", "EQ");
        addPlugin("SSL Native X-EQ 2 (Solid State Logic)", "Precision equalizer", "Solid State Logic", "EQ");
        addPlugin("Maag EQ4 (Maag Audio)", "Air-band EQ", "Maag Audio", "EQ");
        addPlugin("FabFilter Pro-C 2 (FabFilter)", "Versatile compressor", "FabFilter", "Compression");
        addPlugin("Waves CLA-76 (Waves)", "FET-style compressor", "Waves", "Compression");
        addPlugin("Tube-Tech CL 1B (Softube)", "Opto compressor", "Softube", "Compression");
        addPlugin("OTT (Xfer Records)", "Multi-band compression", "Xfer Records", "Compression");
        addPlugin("Decapitator (Soundtoys)", "Analog saturation and distortion", "Soundtoys", "Distortion");
        addPlugin("Sausage Fattener (Dada Life)", "Saturation for adding thickness", "Dada Life", "Distortion");
        addPlugin("RC-20 Retro Color (XLN Audio)", "Lo-fi, tape saturation", "XLN Audio", "Distortion");
        addPlugin("Thermal (Output)", "Multi-stage distortion", "Output", "Distortion");
        addPlugin("Waves Chorus (Waves)", "Chorus effect", "Waves", "Chorus");
        addPlugin("TAL Chorus-LX (TAL Software)", "Juno-60-style chorus effect", "TAL Software", "Chorus");
        addPlugin("MicroShift (Soundtoys)", "Stereo widening", "Soundtoys", "Modulation");
        addPlugin("Phaser BI-TRON (Arturia)", "Analog phaser", "Arturia", "Modulation");
        addPlugin("Waves NS1 Noise Suppressor", "Noise reduction", "Waves", "Noise Reduction");
        addPlugin("Waves Clarity Vx", "Noise reduction and vocal processing", "Waves", "De-esser");
        addPlugin("Waves Curves Equator", "EQ", "Waves", "EQ");
        addPlugin("Waves Tune Real-Time", "Pitch Correction", "Waves", "Pitch Correction");
        addPlugin("Melodyne 5 (Celemony)", "Pitch correction", "Celemony", "Pitch Correction");
        addPlugin("Auto-Tune Pro (Antares)", "Real-time pitch correction", "Antares", "Pitch Correction");

        // 3. Mixing and Mastering
        addPlugin("iZotope Ozone", "All-in-one mastering suite", "iZotope", "Mastering");
        addPlugin("Neutron 4 (iZotope)", "Mixing assistant", "iZotope", "Mixing");
        addPlugin("FabFilter Pro-L 2 (FabFilter)", "Transparent and powerful limiter", "FabFilter", "Limiting");
        addPlugin("T-RackS 5 (IK Multimedia)", "Complete mastering and mixing suite", "IK Multimedia", "Mastering");
        addPlugin("Mastering The Mix EXPOSE 2", "Audio analysis tool", "Mastering The Mix", "Audio Analysis");

        // 4. Special FX & Creative Plugins
        addPlugin("ShaperBox 3 (Cableguys)", "Time, volume, filter, and distortion modulation tool", "Cableguys", "Special FX");
        addPlugin("Portal (Output)", "Granular synthesis effect", "Output", "Special FX");
        addPlugin("Looperator (Sugar Bytes)", "Sequenced multi-effect processor", "Sugar Bytes", "Special FX");
        addPlugin("VocalSynth 2 (iZotope)", "Vocal processing", "iZotope", "Vocal Processing");
        addPlugin("Effectrix (Sugar Bytes)", "Multi-effects sequencer", "Sugar Bytes", "Special FX");

        // 5. Utility Plugins
        addPlugin("SPAN (Voxengo)", "Spectrum analyzer", "Voxengo", "Spectrum Analyzer");
        addPlugin("Youlean Loudness Meter", "LUFS Metering Tool", "Youlean", "Loudness Meter");

    }

    // Changed addPlugin to take all Plugin members as arguments, which solves the error
    void addPlugin(const string& pluginName, const string& description, const string& author, const string& category) { // Parameterized Constructor
        Plugin newPlugin{pluginName, description, author, category};
        plugins.push_back(newPlugin);
        cout << "\n✅ Plugin '" << pluginName << "' added successfully!" << endl;
    }

    void listPlugins() {
        if (plugins.empty()) {
            cout << "\n⚠️ No plugins available." << endl;
            return;
        }
        cout << "\n🎛️ Available Plugins:\n";
        for (size_t i = 0; i < plugins.size(); ++i) {
            cout << i + 1 << ". " << plugins.at(i).name << endl;
            cout << "   Description: " << plugins.at(i).description << endl;
            cout << "   Author: " << plugins.at(i).author << endl;
            cout << "   Category: " << plugins.at(i).category << endl;
        }
    }

    void suggestPlugins(const string& userNeed) {
        cout << "\nAnalyzing your needs..." << endl;
        string lowerNeed = userNeed;
        transform(lowerNeed.begin(), lowerNeed.end(), lowerNeed.begin(), ::tolower);

        vector<string> suggestions;
        for (const auto& [functionality, pluginNames] : functionalityToPlugins) {
            string lowerFunctionality = functionality;
            transform(lowerFunctionality.begin(), lowerFunctionality.end(), lowerFunctionality.begin(), ::tolower);
            if (lowerNeed.find(lowerFunctionality) != string::npos) {
                suggestions.insert(suggestions.end(), pluginNames.begin(), pluginNames.end());
            }
        }

        if (suggestions.empty()) {
            cout << "No matching plugins found based on your description." << endl;
            return;
        }

        cout << "Based on your needs, you might consider these plugins:" << endl;
        for (const string& pluginName : suggestions) {
            cout << " - " << pluginName << endl;
        }
    }
};

// --- Menu and Main Function ---
int displayMenu() {
    int choice;
    cout << "\n🎵 Plugin Manager Menu 🎵" << endl;
    cout << "1️⃣ Add Plugin" << endl; // This functionality is now disabled, but left for menu structure.
    cout << "2️⃣ List Plugins" << endl;
    cout << "3️⃣ Suggest Plugin" << endl;
    cout << "4️⃣ Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    AccessControlManager accessControl;  // Create Access Control Manager
    //  Class and Object
    PluginManager manager; // Create a PluginManager object (This *now* automatically loads plugins).
    string pluginName;  // For user input
    int choice;         // For menu choice

    while (true) { // Main program loop
        choice = displayMenu(); // Display the menu and get the user's choice

        switch (choice) {
            case 1: // Add Plugin (disabled)
                cout << "Adding plugins manually is disabled. Please select Suggest Plugin or Exit." << endl;
                break;
            case 2: // List Plugins
                manager.listPlugins();
                break;
            case 3: // Suggest Plugin
                cin.ignore(); // Consume the newline character
                cout << "Enter the reason why you need a plugin: ";
                getline(cin, pluginName);
                manager.suggestPlugins(pluginName);
                break;
            case 4: // Exit
                cout << "\n👋 Exiting Plugin Manager...\n";
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}