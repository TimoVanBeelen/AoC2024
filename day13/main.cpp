// Day 13
// Advent of Code 2024
// 13-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>


// Read file and return string vector with all lines
std::vector<std::string> read_file(std::string file_name) {
    std::vector<std::string> input_data;
    std::ifstream inputFile(file_name);
    std::string line;

    // Store the file contents in a string vector
    while (getline(inputFile, line)) 
        input_data.push_back(line);
    inputFile.close();  // Close the file after finishing

    return input_data;
}


// Find linear equation pairs -> create an array of size 3 with the X and Y components
std::pair<int, int> *str_to_arr(std::vector<std::string> *strings, int starting_index) {
    // Search for the digits
}


// Main program body
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        std::cout << "Not enough output arguments" << '\n';
        return 0;
    }

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Per 4 lines -> array of size 3 with int pairs
    for (size_t i=0; i<input_lines.size(); i+=4) {
        // Create an array of integer pairs to store the linear equations
        std::pair<int, int> *linEq_pairs = new std::pair<int, int>[3];

    }

    std::cout << std::endl;


    return 0;
}