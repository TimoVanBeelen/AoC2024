// Day 5
// Advent of Code 2024
// 05-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string.h>


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


// Function to split string on delim
std::vector<int> split_to_ints(std::string s, char delim) {
    // Create an int array with appropriate length
    int arrayLength = std::count(s.begin(), s.end(), delim)+1;
    std::vector<int> results;

    // Convert string to char array
    char arr[s.length()+1];
    char* line = strcpy(arr, s.c_str());

    // Split char array into integers
    char delims[1];                                 // Function wants char array
    delims[0] = delim;                              // so we give char array with single element

    results.push_back(std::atoi(strtok(line, delims)));    // Take the first result
    for (int i=1; i< arrayLength; i++) {            // Now loop through to get the others
        char* int_in_chars = strtok(NULL, delims);
        results.push_back(std::atoi(int_in_chars));
    }

    return results;
}


// Find the rules of page orders
std::vector<std::vector<int>> find_rules(std::vector<std::string> input_lines) {
    // Set the regex up for the delims and digits
    std::regex digend("[0-9]+$");
    std::regex digstart("^[0-9]+");
    std::smatch match1;     // Matching to two pairs of digits
    std::smatch match2;

    // Output variable
    std::vector<std::vector<int>> rules;
    
    // Find all int couples
    for (int i=0; i<input_lines.size(); i++) {
        // Find the delimiter
        std::string line = input_lines[i];
        std::regex_search(line, match1, digstart);
        std::cout << match1.str() << std::endl;

        // If the delimiter is not in the line: stop
        if (match1.empty() || line == "") break;

        // Put matches into numbers in the array
        std::regex_search(line, match2, digend);
        std::cout << match2.str() << std::endl;
        rules[i][0] = std::stoi(match1.str());
        rules[i][1] = std::stoi(match2.str());
        std::cout<<rules[i][0]<<"\t"<<rules[i][1]<<std::endl;
    }
    
    return rules;
}


// Find the number of rules
int find_num_rules(std::vector<std::string> input_lines) {
    // Set the regex up for the delims and digits
    std::regex digs("\\d+");
    std::smatch match;
    int i = 0;

    // Go through all lines until the delim is not found
    for (std::string line: input_lines) {
        i++;
        std::regex_search(line, match, digs);
        if (match.empty()) return i;            // If delim not found, return i
    }

    return i; // If there were only matches, still return i
}


// Find the manuals that need to be printed (at the bottom of the file)
std::vector<std::vector<int>> find_manuals(std::vector<std::string> input_lines, int num_manuals) {
    // Return variable
    std::vector<std::vector<int>> result;

    // Loop through all manuals
    for (int i=input_lines.size()-num_manuals; i<input_lines.size(); i++) {
        // Split on comma and add to vector
        std::cout << input_lines[i] << std::endl;
        std::vector<int> split_vect = split_to_ints(input_lines[i], ',');
        result.push_back(split_vect);
    }

    return result;
} 


// Check each manual if they adhere to the rules
bool adheres_to_rules(std::vector<int> manual, int **rules, int num_rules) {
    // For each element in the manual check the rules
    for (int i: manual) {
        // Check if the item does not appear after not allowed
        
    }

    return true;
}


// Main program
int main(int argc, char *argv[]) {
    // Read the file into a vector of strings
    std::vector<std::string> input_lines = read_file(argv[1]);

    // Parse input into manuals and rules
    std::vector<std::vector<int>> rules = find_rules(input_lines);
    int num_rules = find_num_rules(input_lines);

    for (int i=0; i<num_rules; i++) {
        std::cout<<rules[i][0] << "\t" << rules[i][1] << std::endl;
    }

    int num_manuals = input_lines.size()-num_rules-1;
    std::vector<std::vector<int>> manuals = find_manuals(input_lines, num_manuals);

    for (std::vector<int> manual: manuals) {
        // For each manual
    }    

    return 0;
}