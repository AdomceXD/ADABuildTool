#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    float BuildVersion {0.01};
    string BuildArgs      {};
    string Linkers        {};
    string BuildFile      {};
    string ExecutableName {};
    string Author         {};

    const std::string configFileName = "BebulaBuild.cfg";
    bool deleteConfig = false;
    bool helpConfig = false;
    if (argc > 1 && std::string(argv[1]) == "-d") {
        deleteConfig = true;
    }
    if (argc > 1 && std::string(argv[1]) == "-h") {
        helpConfig = true;
    }

    if (deleteConfig) {
        if (fs::exists(configFileName)) {
            fs::remove(configFileName);
            cout << "Config file deleted." << endl;
        } else {
            cout << "Config file doesn't exist. Skipping deletion." << endl;
        }
    } else if (!helpConfig) {
        cout << "\nBuild Args: ";
        getline(cin, BuildArgs);
        cout << "Linkers: ";
        getline(cin, Linkers);
        cout << "Build File: ";
        getline(cin, BuildFile);
        cout << "Executable name: ";
        getline(cin, ExecutableName);
        cout << "Author: ";
        getline(cin, Author);
        if (!fs::exists(configFileName)) {
            ofstream config(configFileName);
            config << "Build version: " << BuildVersion << "\n"
                   << "Build Args: " << BuildArgs << "\n"
                   << "Linkers: " << Linkers << "\n"
                   << "BuildFile: " << BuildFile << "\n"
                   << "Executable name: " << ExecutableName << "\n"
                   << "Author: " << Author << "\n";
            config.close();
            cout << "Config file created." << endl;
        } else {
            cout << "Config file already exists. Skipping creation." << endl;
        }
    }

    if (helpConfig){
        cout << "\nUsage: ./config [OPTION]... \n"
             << "-h     Prints help text \n"
             << "-d     Deletes the config file \n";
    }

    return 0;
}