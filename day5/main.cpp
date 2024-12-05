// Day 5
// Advent of Code 2024
// 05-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>


// Create a struct for the rules
struct rule {
    int page_before;
    int page_after;
};


// Read file and return string vector with all lines
std::vector<std::string> read_file(char file_name[]) {
    std::vector<std::string> input_data;
    std::ifstream inputFile(file_name);
    std::string line;

    // Tell user what file is read
    std::cout << "Reading: " << file_name << std::endl;

    // Store the file contents in a string vector
    while (getline(inputFile, line)) 
        input_data.push_back(line);
    inputFile.close();  // Close the file after finishing

    return input_data;
}


// Find the rules of page orders
int **find_rules(std::vector<std::string> input_lines) {
    // Set the regex up for the delims and digits
    std::regex delim("|");
    std::smatch match;

    // Output variable
    int *rules[input_lines.size()];
    for (int i = 0; i < input_lines.size(); i++) 
        rules[i] = new int[2];
    

    for (int i=0; i<input_lines.size(); i++) {
        // Find the delimiter
        std::string line = input_lines[i];
        std::regex_search(line, match, delim);

        // If the delimiter is not in the line: stop
        if (match.empty()) break;

        // Put the prefix and suffix into the array
        rules[i][0] = std::stoi(match.prefix().str());
        rules[i][1] = std::stoi(match.suffix().str());
    }
    
    return rules;
}


// Find the number of rules
int find_num_rules(std::vector<std::string> input_lines) {
    // Set the regex up for the delims and digits
    std::regex delim("|");
    std::smatch match;
    int i = 0;

    // Go through all lines until the delim is not found
    for (std::string line: input_lines) {
        i++;
        std::regex_search(line, match, delim);
        if (match.empty()) return i;            // If delim not found, return i
    }

    return i; // If there were only matches, still return i
}


// Find the manuals that need to be printed (at the bottom of the file)



// Main program
int main(int argc, char *argv[]) {
    // Read the file into a vector of strings
    std::vector<std::string> input_lines = read_file(argv[1]);

    // Parse input into manuals and rules
    int **rules = find_rules(input_lines);
    int num_rules = find_num_rules(input_lines);
    // std::vector<int> manuals[] = 

    return 0;
}