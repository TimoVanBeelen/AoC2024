// Day 6
// Advent of Code 2024
// 06-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>


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


// Create a char matrix from a string array
char **strarr_to_chararr(std::vector<std::string> string_array) {
    int height = string_array.size();           // Height of the matrix
    int width = string_array[0].size();         // Width of the matrix

    char **char_array = new char*[height];                   // Create an output variable
    for (int i = 0; i < height; i++) {
        char_array[i] = new char[width];        // Create each row with the correct width

        for (int j=0; j<width; j++)             // Set each character of the string to the correct char in the char array
            char_array[i][j] = string_array[i].at(j);
    }

    return char_array;
}


// Run main code here
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Create a map: a matrix of characters, from the input lines
    int height = input_lines.size();
    int width = input_lines[0].size();
    char **matrix = strarr_to_chararr(input_lines);

    // Walk the guard where they need to go and replace each step with an X
    return 0;
}