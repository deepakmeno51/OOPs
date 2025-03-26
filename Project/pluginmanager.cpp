#include <iostream> // Include for standard input/output operations (e.g., cout, cin)
#include <vector>  // Include for using dynamic arrays (vectors)
#include <string>  // Include for using strings
#include <algorithm> // Include for using algorithms like `transform` (for lowercasing)
#include <stdexcept> // Include for exception handling (e.g., `invalid_argument`)
#include <map>       // Include for using maps (key-value pairs) - used for plugin suggestions

using namespace std; // Use the standard namespace to avoid repeatedly typing std::

// --- Plugin Structure ---

// Structure to represent a plugin.  Holds information about a single plugin.
struct Plugin {
    string name;          // Plugin's name (e.g., "FabFilter Pro-Q 3")
    string description;   // Brief description of the plugin's function
    string author;        // The plugin's author or developer
    string category;      // The plugin's category (e.g., "EQ", "Reverb")
};

// --- Plugin Manager Class ---
class PluginManager {
private:
    vector<Plugin> plugins; // Vector to store all the Plugin objects. This is the list of plugins.

    // A map to link functionalities (keywords) to plugin names (for suggestions).
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

public:
    // Constructor - Adds the predefined plugins.
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
    void addPlugin(const string& pluginName, const string& description, const string& author, const string& category) {
        // This add plugin functionality is redundant with the automatic initialization of plugins.
        // It's left here for compatibility, but will not be used.  You can remove it.
        // This is now used only for adding the plugins that have been created
        Plugin newPlugin{pluginName, description, author, category};
        plugins.push_back(newPlugin);
        cout << "\n✅ Plugin '" << pluginName << "' added successfully!" << endl;
    }

    // Function to list the available plugins
    void listPlugins() {
        if (plugins.empty()) {
            cout << "\n⚠️ No plugins available." << endl;  // Display a message if there are no plugins to list
            return; // Exit the function if there are no plugins
        }
        cout << "\n🎛️ Available Plugins:\n"; // Print the header for listing the plugins
        for (size_t i = 0; i < plugins.size(); ++i) {  // Loop through the plugins vector
            cout << i + 1 << ". " << plugins.at(i).name << endl; // Print the plugin name with an index
            cout << "   Description: " << plugins.at(i).description << endl; // Print the plugin's description
            cout << "   Author: " << plugins.at(i).author << endl; // Print the plugin's author
            cout << "   Category: " << plugins.at(i).category << endl; // Print the plugin's category
        }
    }

    // Function to suggest plugins based on a user's description of their needs
    void suggestPlugins(const string& userNeed) {
        cout << "\nAnalyzing your needs..." << endl; // Inform the user that the system is analyzing
        string lowerNeed = userNeed;
        transform(lowerNeed.begin(), lowerNeed.end(), lowerNeed.begin(), ::tolower); // Convert the user's input to lowercase for case-insensitive matching

        vector<string> suggestions; // Vector to store suggested plugin names
        for (const auto& [functionality, pluginNames] : functionalityToPlugins) { // Loop through the functionalityToPlugins map
            string lowerFunctionality = functionality;
            transform(lowerFunctionality.begin(), lowerFunctionality.end(), lowerFunctionality.begin(), ::tolower); // Convert the functionality keyword to lowercase
            if (lowerNeed.find(lowerFunctionality) != string::npos) { // Check if the user's need contains the functionality keyword
                suggestions.insert(suggestions.end(), pluginNames.begin(), pluginNames.end()); // Add the plugin names associated with the functionality to suggestions
            }
        }

        if (suggestions.empty()) { // If no suggestions were found
            cout << "No matching plugins found based on your description." << endl; // Print a message
            return; // Exit the function
        }

        cout << "Based on your needs, you might consider these plugins:" << endl; // Print a header for the suggested plugins
        for (const string& pluginName : suggestions) { // Loop through the suggestions
            cout << " - " << pluginName << endl; // Print each suggested plugin
        }
    }
};

// --- Menu and Main Function ---
int displayMenu() {
    int choice;
    cout << "\n🎵 Plugin Manager Menu 🎵" << endl;
    cout << "1️⃣ List Plugins" << endl;
    cout << "2️⃣ Suggest Plugin" << endl;
    cout << "3️⃣ Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice; // Get user's menu choice
    return choice; // Return the choice
}

int main() {
    PluginManager manager;  // Create an instance of the PluginManager class
    string pluginName; // Stores the plugin name
    int choice;      // Stores the user's menu choice

    while (true) { // Main program loop - continues until the user chooses to exit
        choice = displayMenu(); // Display the menu and get the user's choice

        switch (choice) { // Process user's choice using a switch statement
            case 1:
                manager.listPlugins(); // Call the listPlugins() method to display plugins
                break;
            case 2:
                cin.ignore(); // Consume the newline character left in the input buffer
                cout << "Enter the reason why you need a plugin: "; // Prompt the user to enter the reason
                getline(cin, pluginName); // Read the user's need (can include spaces)
                manager.suggestPlugins(pluginName); // Call the suggestPlugins() method to provide plugin suggestions
                break;
            case 3:
                cout << "\n👋 Exiting Plugin Manager...\n"; // Display exit message
                return 0; // Exit the program with a success code
            default:
                cout << "Invalid choice. Please try again." << endl; // Handle invalid menu choices
        }
    }
}