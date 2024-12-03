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


// Check do or don't, return true if do not
bool donut(std::string input) {
    // Set up regex for searching the lines
    std::regex dont_regex("don't\\(\\)");
    std::regex do_regex("do\\(\\)");
    std::smatch match;

    // Keep searching in the line
    while(std::regex_search(input, match, dont_regex)) {
        std::cout << "found " << match[0] << std::endl;
        std::string suff = match.suffix().str();
        if (std::regex_search(suff, match, do_regex)) {
            std::cout << "found: " << match[0] << std::endl;
             continue;
        }
        else return true;
    }

    return false;
}


// Check do or don't, return true if do not (other way round)
bool do_check(std::string input) {
    // Set up regex for searching the lines
    std::regex dont_regex("don't\\(\\)");
    std::regex do_regex("do\\(\\)");
    std::smatch match;

    // Keep searching in the line
    while(std::regex_search(input, match, do_regex)) {
        std::cout << "found " << match[0] << std::endl;
        std::string suff = match.suffix().str();
        if (std::regex_search(suff, match, dont_regex)) {
            std::cout << "found: " << match[0] << std::endl;
             continue;
        }
        else return true;
    }

    return false;
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


// Function to find the regex matches and return this as string vector (part 2)
std::vector<std::string> find_matches2(std::string input) {
    // Set up regex for searching the lines
    std::regex mult_regex("mul\\(\\d{1,3},\\d{1,3}\\)");
    std::smatch match;

    // Create vector to store the matches
    std::vector<std::string> matches;

    // See if there are any matches in the input string and output these
    bool dont_append = false;   // Only append if there was no don't statement
    while (std::regex_search(input, match, mult_regex)) {
        // Check if the match should actually be appended
        if (donut(match.prefix().str())) dont_append = true;
        if (do_check(match.prefix().str())) dont_append = false;

        // Append the match to the vector
        if (!dont_append) {
            matches.push_back(match[0]);
            std::cout<<"Mul found: "<<match[0]<< std::endl;
        }

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
    int mult_sum2 = 0;  // Result of part 2

    // Run program for each line in the file
    for (std::string line : input_lines) {
        // Part 1
        std::vector<std::string> multipliers = find_matches(line);      // Find the mul() commands
        for (std::string item : multipliers)
            mult_sum += calc_mul(item);

        // Part 2
        std::vector<std::string> multipliers2 = find_matches2(line);
        for (std::string item : multipliers2)
            mult_sum2 += calc_mul(item);
    }


    // Print the result
    std::cout << "Answer 1: " << mult_sum << std::endl; 
    std::cout << "Answer 2: " << mult_sum2 << std::endl;

    // END
    return 0;
}