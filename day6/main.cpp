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


// Find the initial position of the guard
int *find_pos(char **matrix, int height, int width) {
    int *pos;                             // Create a variable of the returning position
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++){        // Go through the whole matrix
            if (matrix[i][j] == '^') {      // Guard is found
                pos[0] = i;                 // Set its position
                pos[1] = j;             
            }
        }
    }
    return pos;
}


// Move the guard
char **update_matrix(char **matrix, int height, int width, int *pos) {
    
}


// Run main code here
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Create a map: a matrix of characters, from the input lines
    int height = input_lines.size();
    int width = input_lines[0].size();
    char **matrix = strarr_to_chararr(input_lines);

    // Find the initial position of the guard
    int *pos = find_pos(matrix, height, width);

    // Walk the guard where they need to go and replace each step with an X
    int dir = 0;    // Set the walking direction, north = 0, west = 1, south = 2, east = 3
    // Walk to next obstacle, check if border is reached, update the direction

    return 0;
}