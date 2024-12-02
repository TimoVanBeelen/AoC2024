// Day 1
// Advent of Code 2024
// 02-12-2024
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

    // Create integer list with resulst
    int* nums = new int[2];
    nums[0] = num1;
    nums[1] = num2;

    return nums;
}


void part_one(std::string file_name) {
    // Read the file
    std::vector<std::string> input_lines = read_file(file_name);

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

    std::cout << "Answer 1: " << difference_sum << std::endl;
}


void part_two(std::string file_name) {
    // Read the file
    std::vector<std::string> input_lines = read_file(file_name);

    // Variables
    int listLength = input_lines.size();
    std::vector<int> left_list;
    std::vector<int> right_list;
    int sim_score = 0;

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

    // Loop through each element in the left list and compare to the right
    for (int i=0; i<left_list.size(); i++) {
        int instances = 0;
        for (int j=0; j<right_list.size(); j++) {
            if (left_list.at(i) < right_list.at(j)) break;
            if (left_list.at(i) == right_list.at(j)) instances++;
        }

        sim_score += instances*left_list.at(i);
    }

    std::cout << "Answer 2: " << sim_score << std::endl;
}


// Main function
int main() {
    // Part 1
    part_one("input.txt");

    // Part 2
    part_two("input.txt");

    // END
    return 0;
}