// Day 2
// Advent of Code 2024
// 02-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>


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


// Transform the input string to an array of integers
int* str_to_dat(std::string s, char delim) {
    // Create an int array with appropriate length
    int arrayLength = std::count(s.begin(), s.end(), delim)+1;
    int* result = new int[arrayLength];

    // Convert string to char array
    char arr[s.length()+1];
    char* line = strcpy(arr, s.c_str());

    // Split char array into integers
    char delims[1];                                 // Function wants char array
    delims[0] = delim;                              // so we give char array with single element

    result[0] = std::atoi(strtok(line, delims));    // Take the first result
    for (int i=1; i< arrayLength; i++) {            // Now loop through to get the others
        char* int_in_chars = strtok(NULL, delims);
        result[i] = std::atoi(int_in_chars);
    }

    return result;
}


// Check the safety of a number array
bool is_safe(int* data, int data_len) {
    // See if the system is increasing or not
    bool increasing = false;
    if (data[0] < data[1]) increasing = true;
    else if (data[0]==data[1]) return false;

    // Limits in change to check
    int max_change = 3;
    int min_change = 1;

    // Check all items
    for (int i=0; i<data_len-1; i++) {
        // Does it keep increasing?
        if (increasing && data[i]>data[i+1]) 
            return false;
        // Does it keep decreasing?
        if (!increasing && data[i]<data[i+1])
            return false;

        // Check delta conditions
        int change = abs(data[i]-data[i+1]);
        if (change > max_change || change < min_change) 
            // Too much change or no change == bad!
            return false;
    }

    return true;
}


// remove an element and see if that creates a safe report
bool try_erase_option(std::vector<int> v, int remove, int data_len) {
    v.erase(v.begin()+remove);
    return is_safe(&v[0], data_len-1);
}


// Check the safety of a number array with the dampner
bool safe_with_dampner(int* data, int data_len) {
    // Return true for the original ones
    if (is_safe(data, data_len)) return true;

    // Create a vector of the array
    std::vector<int> data_v;
    for (int i=0; i<data_len; i++) data_v.push_back(data[i]);

    // Check all items while removing one of the options
    for (int i=0; i<data_len; i++) {
        // Check if the report is safe when removing a number
        if (try_erase_option(data_v, i, data_len))
            return true;
    }

    // Reaching this point means the report is utterly unsafe
    return false;
}


// Run main code here
int main() {
    // Read file
    std::vector<std::string> input_lines =  read_file("input.txt");

    int safe_reports = 0; // Result variable
    int safe_w_dampner = 0; // Result part 2

    // Go through each report to check if it is safe
    for (int i=0; i<input_lines.size(); i++) {
        // Transform input lines to an array of numbers
        std::string s = input_lines[i];
        int arrayLength = std::count(s.begin(), s.end(), ' ')+1;
        int* data = str_to_dat(input_lines[i], ' ');


        // Check if report is safe on its own (pt1)
        if (is_safe(data, arrayLength))
            safe_reports++;


        // Check if report is safe with dampner case
        if (safe_with_dampner(data, arrayLength)) {
            safe_w_dampner++;
        }


        // Free the data array memory
        delete[] data;
    }

    // Print answers
    std::cout << "Answer 1: " << safe_reports << std::endl;
    std::cout << "Answer 2: " << safe_w_dampner << std::endl;

    return 0;
}