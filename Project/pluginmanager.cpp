#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
        string description, author, category;
        cout << "Enter Plugin Description: ";
        cin.ignore(); // Consume newline from previous input
        getline(cin, description);
        cout << "Enter Plugin Author: ";
        getline(cin, author);
        cout << "Enter Plugin Category (e.g., 'Effect', 'Instrument'): ";
        getline(cin, category);

        Plugin newPlugin;
        newPlugin.name = pluginName;
        newPlugin.description = description;
        newPlugin.author = author;
        newPlugin.category = category;
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
            cout << i + 1 << ". " << plugins[i].name << endl;
            cout << "   Description: " << plugins[i].description << endl;
            cout << "   Author: " << plugins[i].author << endl;
            cout << "   Category: " << plugins[i].category << endl;
        }
    }

    void listPluginsByCategory(const string& category) {
        vector<Plugin> categoryPlugins;

        for (const auto& plugin : plugins) {
            if (plugin.category == category) {
                categoryPlugins.push_back(plugin);
            }
        }
        if (categoryPlugins.empty()) {
            cout << "\n⚠️ No plugins found in category '" << category << "'." << endl;
            return;
        }

        cout << "\n🎛️ Plugins in category '" << category << "':\n";
        for (size_t i = 0; i < categoryPlugins.size(); ++i) {
             cout << i + 1 << ". " << categoryPlugins[i].name << endl;
             cout << "   Description: " << categoryPlugins[i].description << endl;
             cout << "   Author: " << categoryPlugins[i].author << endl;
        }
    }

    void loadPlugin(int pluginIndex) {
        if (pluginIndex < 1 || pluginIndex > plugins.size()) {
            cout << "\n❌ Invalid plugin selection!" << endl;
            return;
        }
        cout << "\n🔊 Applying '" << plugins[pluginIndex - 1].name << "' effect..." << endl;
    }

    void removePlugin(int pluginIndex) {
        if (pluginIndex < 1 || pluginIndex > plugins.size()) {
            cout << "\n❌ Invalid plugin selection!" << endl;
            return;
        }
        cout << "\n🗑️ Removing plugin: " << plugins[pluginIndex - 1].name << endl;
        plugins.erase(plugins.begin() + (pluginIndex - 1));
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
    int choice, index;
    string pluginName;

    //Example plugin data:
    manager.addPlugin("Izotope Ozone", "Mastering Suite", "Izotope", "Effect");
    manager.addPlugin("Serum", "Advanced Wavetable Synthesizer", "Xfer Records", "Synthesizer");
    manager.addPlugin("FabFilter Pro-Q 3", "EQ Plugin", "FabFilter", "Effect");

    while (true) {
        choice = displayMenu();

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
                cin >> listChoice;

                if (listChoice == 1) {
                    manager.listPlugins();
                } else if (listChoice == 2) {
                    string category;
                    cin.ignore(); // Consume newline
                    cout << "Enter Category: ";
                    getline(cin, category);
                    manager.listPluginsByCategory(category);
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
            case 3:
                manager.listPlugins();
                cout << "\nEnter Plugin Number to Load: ";
                cin >> index;
                manager.loadPlugin(index);
                break;
            case 4:
                manager.listPlugins();
                cout << "\nEnter Plugin Number to Remove: ";
                cin >> index;
                manager.removePlugin(index);
                break;
            case 5:
                cout << "\n👋 Exiting Plugin Manager...\n";
                return 0;
            default:
                cout << "\n❌ Invalid choice! Try again.\n";
        }
    }
}