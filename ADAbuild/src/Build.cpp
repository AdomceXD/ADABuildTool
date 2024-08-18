#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono> // For timekeeping
#include <cstdlib> // For system()

int main() {
    std::ifstream configFile("BebulaBuild.cfg");
    std::string buildFile, buildArgs, executableName, linkers;

    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            std::size_t found = line.find(":");
            if (found != std::string::npos && found + 1 < line.size()) {
                if (line.find("BuildFile:") != std::string::npos)
                    buildFile = line.substr(found + 1);
                else if (line.find("Build Args:") != std::string::npos)
                    buildArgs = line.substr(found + 1);
                else if (line.find("Executable name:") != std::string::npos)
                    executableName = line.substr(found + 1);
                else if (line.find("Linkers:") != std::string::npos)
                    linkers = line.substr(found + 1);
            }
        }
        configFile.close();

        std::stringstream concatenatedArgs;
        concatenatedArgs << "g++ " << buildFile << " " << buildArgs << " " << executableName << " " << linkers;

        // Measure the time taken to compile
        auto start = std::chrono::high_resolution_clock::now();
        int result = system(concatenatedArgs.str().c_str());
        auto end = std::chrono::high_resolution_clock::now();

        if (result == 0) {
            std::cout << "Compilation successful." << std::endl;
        } else {
            std::cerr << "Compilation failed." << std::endl;
            return 1;
        }

        // Calculate and display the elapsed time
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken to compile: " << elapsed.count() << " seconds." << std::endl;

    } else {
        std::cerr << "Unable to open config file." << std::endl;
        return 1;
    }

    return 0;
}
