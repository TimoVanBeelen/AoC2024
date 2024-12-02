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
    char delims[1]; 
    delims[0] = delim;
    result[0] = std::atoi(strtok(line, delims));
    for (int i=1; i< arrayLength; i++) {
        char* int_in_chars = strtok(NULL, delims);
        result[i] = std::atoi(int_in_chars);
    }

    return result;
}


// Run main code here
int main() {
    // Read file
    std::vector<std::string> input_lines =  read_file("ref.txt");

    // Transform input lines to an array of numbers
    int* data = str_to_dat(input_lines[0], ' ');

    delete[] data;

    return 0;
}