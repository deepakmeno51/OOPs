#include <iostream> // Fro input/output operations
#include <vector> //For using the vector container (dynamic array) to store plugins
#include <string> // For using the string class to represert plugin names

using namespace std; 

class PluginManager {
private:
    vector<string> plugins; //List of available plugins

public:
    // Function to add a new plugin to the list 
    void addPLugin(const string& pluginName) {
        plugins.push_back(pluginName);  //Adds the plugin nmae to the end of the plugins vector
        cout << "\n✅ Plugin ' " << pluginName << "' added successfully!" <<  endl;
    }

// Function to list all available plugins (display them)
void listPlugins() {
    if (plugins.empty()) { // Check if the plugins vector is empty
        cout << "\n ⚠️ No plugins available. " << endl; // Prints a message if there are no plugins
        return; //Exits the function (nothing more to do)
    }
    
    cout << "\n 🎛️ Available Plugins: \n " ; // Prints a header for the list
    for (size_t i = 0; i < plugins.size(); ++i) { // loops through the plugins vector
        cout << i + 1 << ". " << plugins[i] << endl; // Prints the index
        }
    }

    // Function to load a plugin (simulate applying an effect)
    void loadPlugin(int pluginIndex) { // Takes the index (position) of the plugin to load as input
        if (pluginIndex < 1 || pluginIndex > plugins.size()) { // Checks if the provided index is valid (within the bounds of the vector, indexing starts at 1 for the user)
            cout << "\n❌ Invalid plugin selection!" << endl; // Prints an error message if the index is invalid
            return; // Exits the function
        }

        cout << "\n 🔊 Applying '" << plugins[pluginIndex - 1] << "' effect .... "
    // Function to remove a plugin from the list
    void removePlugin(int pluginIndex) { // Takes the index of the plugin to remove as input
        if (pluginIndex < 1 || pluginIndex > plugins.size()) { // Checks for a valid index (similar to loadPlugin)
            cout << "\n❌ Invalid plugin selection!" << endl; // Prints an error message
            return; // Exits the function
        }

        cout << "\n🗑️ Removing plugin: " << plugins[pluginIndex - 1] << endl; // Prints a message indicating the plugin being removed
        plugins.erase(plugins.begin() + (pluginIndex - 1)); // Removes the plugin from the vector.  `plugins.begin() + (pluginIndex - 1)` creates an iterator to the element to be removed.
    }
};

// Main Function (program entry point) - this is where the program execution starts
int main() {
    PluginManager manager; // Creates an instance(object) of the PluginManager class
    int choice, index; //Variables to store the user's menu choice and plugin index
    string programme; // Variables to store the name of a plugin

    while (true) { // Creates an infinite loop (the program will keep running until explicitly exited)
        cout << "\n🎵 Plugin Manager Menu 🎵"; // Displays the main menu
        cout << "\n1️⃣ Add Plugin\n2️⃣ List Plugins\n3️⃣ Load Plugin\n4️⃣ Remove Plugin\n5️⃣ Exit"; // Displays the menu options
        cout << "\nEnter your choice: "; // Prompts the user for their choice
        cin >> choice; // Reads the user's choice from standard input (keyboard)

        switch (choice) { // Uses a switch statement to handle different menu choices
            case 1: // If the user chose 1 (Add Plugin)
                cout << "\nEnter Plugin Name: "; // Prompts the user to enter the plugin name
                cin.ignore(); // Clears the input buffer. This is important because when the user types "1" (for add plugin) and presses enter, the enter key is left in the input buffer. `getline` would read the newline character from this enter key instead of waiting for user input.  So we need to 'ignore' that character.
                getline(cin, pluginName); // Reads the plugin name from the input (including spaces)
                manager.addPlugin(pluginName); // Calls the addPlugin function to add the plugin to the manager
                break; // Exits the switch case
            case 2: // If the user chose 2 (List Plugins)
                manager.listPlugins(); // Calls the listPlugins function to display the available plugins
                break; // Exits the switch case
            case 3: // If the user chose 3 (Load Plugin)
                manager.listPlugins(); // Lists plugins again so the user can see the available plugins and their numbers
                cout << "\nEnter Plugin Number to Load: "; // Prompts the user to enter the number of the plugin to load
                cin >> index; // Reads the plugin number from the input
                manager.loadPlugin(index); // Calls the loadPlugin function to simulate loading the selected plugin
                break; // Exits the switch case
            case 4: // If the user chose 4 (Remove Plugin)
                manager.listPlugins(); // Lists the plugins so the user can choose which one to remove
                cout << "\nEnter Plugin Number to Remove: "; // Prompts the user to enter the number of the plugin to remove
                cin >> index; // Reads the plugin number from input
                manager.removePlugin(index); // Calls the removePlugin function to remove the selected plugin
                break; // Exits the switch case
            case 5: // If the user chose 5 (Exit)
                cout << "\n👋 Exiting Plugin Manager...\n"; // Prints an exit message
                return 0; // Exits the program with a success code (0)
            default: // If the user entered an invalid choice (not 1-5)
                cout << "\n❌ Invalid choice! Try again.\n"; // Prints an error message
        }
    }
}

