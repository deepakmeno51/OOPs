#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <map> // For a more organized plugin suggestion system

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
    void addPlugin(const string& pluginName, const string& description, const string& author, const string& category) {
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

int displayMenu() {
    int choice;
    cout << "\n🎵 Plugin Manager Menu 🎵" << endl;
    cout << "1.List Plugins" << endl;
    cout << "2.Suggest Plugin" << endl;
    cout << "3.Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    PluginManager manager;
    string pluginName;
    int choice;

    while (true) {
        choice = displayMenu();

        switch (choice) {
            case 1:
                // Manual addition is disabled, handled in the constructor
                cout << "Adding plugins manually is disabled. Please select Suggest Plugin or Exit." << endl;
                break;
            case 2:
                manager.listPlugins();
                break;
            case 3:
                cin.ignore(); // Consume the newline
                cout << "Enter the reason why you need a plugin: ";
                getline(cin, pluginName);
                manager.suggestPlugins(pluginName);
                break;
            case 4:
                cout << "\n Exiting Plugin Manager...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}