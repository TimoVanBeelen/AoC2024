// Day 1
// Advent of Code 2024
// 01-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


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


// Remove whitespace from the lines
int *splitstring(char line[]) {
    // Split string into the two numbers
    char* num1_line = strtok(line, " ");
    char* num2_line = strtok(NULL, " ");

    // Convert string to the numbers
    int num1 = std::atoi(num1_line);
    int num2 = std::atoi(num2_line);

    std::cout << num1 << "\t" << num2 << std::endl;

    // Create integer list with resulst
    int* nums = new int[2];
    nums[0] = num1;
    nums[1] = num2;

    return nums;
}


// Main function
int main() {
    // Read the file
    std::vector<std::string> input_lines = read_file("input.txt");

    // Variables
    int listLength = input_lines.size();
    std::vector<int> left_list;
    std::vector<int> right_list;
    int difference_sum = 0;

    // Get the numbers from the input lines
    // Split on space
    for (int i=0; i<listLength; i++) {
        // Get line length and create appropriate char array size
        int n = input_lines[i].length();
        char arr[n+1];
        
        // Get the two nums out of the line
        int *nums = splitstring(strcpy(arr, input_lines[i].c_str()));

        // Add the numbers to the end of the vector
        left_list.push_back(nums[0]);
        right_list.push_back(nums[1]);

        delete[] nums;
    }

    // Sort the list on numbers
    sort(left_list.begin(), left_list.end());
    sort(right_list.begin(), right_list.end());

    // Get the differnce and sum this
    for (int i=0; i<listLength; i++) {
        int difference = abs(left_list.at(i) - right_list.at(i));
        difference_sum += difference;
    }

    std::cout << difference_sum << std::endl;

    // END
    return 0;
}

// Try 1: 944535002 is too high
// Try 2: 1938424