#include <iostream>        // For error messages
#include <fstream>         // For file operations
#include <sstream>         // For string stream operations
#include <Eigen/Dense>     // For Eigen vector operations
#include "observation_io.hpp"  // Header file for this implementation

using std::vector;
using std::string;
using std::ifstream;
using std::cerr;
using std::getline;
using std::istringstream;
using std::stod;

// Function to read observations from a CSV file
// Each line in the CSV file contains: time, right ascension, declination, and observer position (x,y,z)
vector<Observation> ObsFromCSV(const string& filename) {
    vector<Observation> observations;  // Vector to store all observations
    ifstream file(filename);           // File stream for reading
    string line;                       // Buffer for each line of CSV

    // Check if file opened successfully
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << "\n";  // Error message
        return observations;  // Return empty vector if file can't be opened
    }

    // Process each line in the file
    while (getline(file, line)) {
        // Create a string stream from the current line to parse CSV fields
        // The string stream allows us to extract comma-separated values
        istringstream ss(line);
        
        // Temporary buffer to hold each comma-separated value as we extract it
        // This token will be reused for each field in the CSV line
        string token;
        
        Observation obs;              // Create new observation object

        // Parse time (t) - extract first value (before first comma)
        getline(ss, token, ',');  // Extract value up to next comma
        obs.t = stod(token);     // Convert string to double

        // Parse right ascension (ra) - start from after the first comma
        // The string stream automatically advances to the next token after each getline
        getline(ss, token, ',');
        obs.ra = stod(token);

        // Parse declination (dec)
        getline(ss, token, ',');
        obs.dec = stod(token);

        // Parse observer position (x,y,z)
        double x, y, z;
        getline(ss, token, ','); x = stod(token);
        getline(ss, token, ','); y = stod(token);
        getline(ss, token, ','); z = stod(token);

        // Create Eigen vector from position coordinates
        obs.observer_pos = Eigen::Vector3d(x, y, z);

        // Add the parsed observation to the vector
        observations.push_back(obs);
    }

    // Return the vector of all parsed observations
    return observations;
}