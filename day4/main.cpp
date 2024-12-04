// Day 4
// Advent of Code 2024
// 04-12-2024
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


// Main program
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    


    // Print the result
    std::cout << "Answer 1: " << std::endl; 
    std::cout << "Answer 2: " << std::endl;

    // END
    return 0;
}