#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Plugin {
    string name;
    string description;
    string author;
    string category;
};

class PluginManager {
private:
    vector<Plugin> plugins;

public:
    void addPlugin(const string& pluginName) {
        try {
            string description, author, category;
            cout << "Enter Plugin Description: ";
            cin.ignore();
            getline(cin, description);
            cout << "Enter Plugin Author: ";
            getline(cin, author);
            cout << "Enter Plugin Category (e.g., 'Effect', 'Instrument'): ";
            getline(cin, category);

            if (pluginName.empty()) {
                throw invalid_argument("Plugin name cannot be empty");
            }

            Plugin newPlugin{pluginName, description, author, category};
            plugins.push_back(newPlugin);
            cout << "\n✅ Plugin '" << pluginName << "' added successfully!" << endl;
        }
        catch (const invalid_argument& e) {
            cout << "\n❌ Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "\n❌ Unexpected error adding plugin: " << e.what() << endl;
        }
    }

    void listPlugins() {
        try {
            if (plugins.empty()) {
                throw runtime_error("No plugins available");
            }

            cout << "\n🎛️ Available Plugins:\n";
            for (size_t i = 0; i < plugins.size(); ++i) {
                cout << i + 1 << ". " << plugins.at(i).name << endl;
                cout << "   Description: " << plugins.at(i).description << endl;
                cout << "   Author: " << plugins.at(i).author << endl;
                cout << "   Category: " << plugins.at(i).category << endl;
            }
        }
        catch (const runtime_error& e) {
            cout << "\n⚠️ " << e.what() << "." << endl;
        }
        catch (const out_of_range& e) {
            cout << "\n❌ Error accessing plugin list: " << e.what() << endl;
        }
    }

    void listPluginsByCategory(const string& category) {
        try {
            vector<Plugin> categoryPlugins;
            for (const auto& plugin : plugins) {
                if (plugin.category == category) {
                    categoryPlugins.push_back(plugin);
                }
            }
            if (categoryPlugins.empty()) {
                throw runtime_error("No plugins found in category '" + category + "'");
            }

            cout << "\n🎛️ Plugins in category '" << category << "':\n";
            for (size_t i = 0; i < categoryPlugins.size(); ++i) {
                cout << i + 1 << ". " << categoryPlugins.at(i).name << endl;
                cout << "   Description: " << categoryPlugins.at(i).description << endl;
                cout << "   Author: " << categoryPlugins.at(i).author << endl;
            }
        }
        catch (const runtime_error& e) {
            cout << "\n⚠️ " << e.what() << "." << endl;
        }
        catch (const exception& e) {
            cout << "\n❌ Error: " << e.what() << endl;
        }
    }

    void loadPlugin(int pluginIndex) {
        try {
            if (pluginIndex < 1 || pluginIndex > static_cast<int>(plugins.size())) {
                throw out_of_range("Invalid plugin index: " + to_string(pluginIndex));
            }
            cout << "\n🔊 Applying '" << plugins.at(pluginIndex - 1).name << "' effect..." << endl;
        }
        catch (const out_of_range& e) {
            cout << "\n❌ " << e.what() << "!" << endl;
        }
    }

    void removePlugin(int pluginIndex) {
        try {
            if (pluginIndex < 1 || pluginIndex > static_cast<int>(plugins.size())) {
                throw out_of_range("Invalid plugin index: " + to_string(pluginIndex));
            }
            cout << "\n🗑️ Removing plugin: " << plugins.at(pluginIndex - 1).name << endl;
            plugins.erase(plugins.begin() + (pluginIndex - 1));
        }
        catch (const out_of_range& e) {
            cout << "\n❌ " << e.what() << "!" << endl;
        }
    }
};

int displayMenu() {
    int choice;
    cout << "\n🎵 Plugin Manager Menu 🎵" << endl;
    cout << "1️⃣ Add Plugin" << endl;
    cout << "2️⃣ List Plugins" << endl;
    cout << "3️⃣ Load Plugin" << endl;
    cout << "4️⃣ Remove Plugin" << endl;
    cout << "5️⃣ Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    PluginManager manager;
    string pluginName;

    try {
        // Example plugin data with exception handling
        manager.addPlugin("Izotope Ozone");
        manager.addPlugin("Serum");
        manager.addPlugin("FabFilter Pro-Q 3");

        while (true) {
            int choice = displayMenu();

            switch (choice) {
                case 1:
                    cout << "\nEnter Plugin Name: ";
                    cin.ignore();
                    getline(cin, pluginName);
                    manager.addPlugin(pluginName);
                    break;

                case 2: {
                    int listChoice;
                    cout << "\n1. List All Plugins\n2. List Plugins by Category: ";
                    if (!(cin >> listChoice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw runtime_error("Invalid input for list choice");
                    }

                    if (listChoice == 1) {
                        manager.listPlugins();
                    } else if (listChoice == 2) {
                        string category;
                        cin.ignore();
                        cout << "Enter Category: ";
                        getline(cin, category);
                        manager.listPluginsByCategory(category);
                    } else {
                        throw invalid_argument("Invalid list option");
                    }
                    break;
                }

                case 3: {
                    int index;
                    manager.listPlugins();
                    cout << "\nEnter Plugin Number to Load: ";
                    if (!(cin >> index)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw runtime_error("Invalid input for plugin number");
                    }
                    manager.loadPlugin(index);
                    break;
                }

                case 4: {
                    int index;
                    manager.listPlugins();
                    cout << "\nEnter Plugin Number to Remove: ";
                    if (!(cin >> index)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw runtime_error("Invalid input for plugin number");
                    }
                    manager.removePlugin(index);
                    break;
                }

                case 5:
                    cout << "\n👋 Exiting Plugin Manager...\n";
                    return 0;

                default:
                    throw invalid_argument("Invalid menu choice");
            }
        }
    }
    catch (const exception& e) {
        cout << "\n❌ Fatal error: " << e.what() << endl;
        return 1;
    }
}