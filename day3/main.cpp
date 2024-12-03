// Day 3
// Advent of Code 2024
// 03-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>


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


// Function to find the regex matches and return this as string vector
std::vector<std::string> find_matches(std::string input) {
    // Set up regex for searching the lines
    std::regex mult_regex("mul\\(\\d{1,3},\\d{1,3}\\)");
    std::smatch match;

    // Create vector to store the matches
    std::vector<std::string> matches;

    // See if there are any matches in the input string and output these
    while (std::regex_search(input, match, mult_regex)) {
        // Append the match to the vector
        matches.push_back(match[0]);

        // Update the line for a new search
        input = match.suffix().str();
    }

    return matches;
}


// Calculate the multiplications found
int calc_mul(std::string command) {
    // Set up regex for searching the lines
    std::regex num_regex("\\d{1,3}");
    std::smatch match;

    int nums[2];    // We should find two number
    int i=0;
    while (std::regex_search(command, match, num_regex)) {
        // Append the match to the array and increment i
        nums[i++] = std::stoi(match[0].str());

        // Update the line for a new search
        command = match.suffix().str();
    }

    return nums[0]*nums[1];
}


// Main program
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    int mult_sum = 0;   // Result of the program

    // Run program for each line in the file
    for (std::string line : input_lines) {
        std::vector<std::string> multipliers = find_matches(line);      // Find the mul() commands
        for (std::string item : multipliers)
            mult_sum += calc_mul(item);
    }


    // Print the result
    std::cout << "Answer 1: " << mult_sum << std::endl; 

    // END
    return 0;
}