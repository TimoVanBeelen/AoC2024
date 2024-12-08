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


// Crossing border?
bool is_going_to_cross(int height, int width, int *pos, int dir) {
    if (dir == 0 && pos[0] == 0) return true;           // Heading north
    if (dir == 1 && pos[1] == width-1) return true;     // Heading west
    if (dir == 2 && pos[0] == height-1) return true;    // Heading south
    if (dir == 3 && pos[1] == 0) return true;           // Heading east
    return false;
}


// // Move the guard
char **update_matrix(char **matrix, int height, int width, int *pos, int dir, char mark) {
    
    // Keep on walking until gone
    while (!is_going_to_cross(height, width, pos, dir)) {
        // Walk north if no obstacle
        if (dir == 0 && (matrix[pos[0]-1][pos[1]] != '#' || matrix[pos[0]-1][pos[1]] != 'O')) {
            matrix[pos[0]][pos[1]] = mark;
            pos[0] -= 1;    // Move up
        } 
        else if (dir == 1 && (matrix[pos[0]][pos[1]+1] != '#' || matrix[pos[0]][pos[1]+1] != 'O')) {
            matrix[pos[0]][pos[1]] = mark;
            pos[1] += 1;    // Move right
            
        }
        else if (dir == 2 && (matrix[pos[0]+1][pos[1]] != '#' || matrix[pos[0]+1][pos[1]] != 'O')) {
            matrix[pos[0]][pos[1]] = mark;
            pos[0] += 1;    // Move down
        }
        else if (dir == 3 && (matrix[pos[0]][pos[1]-1] != '#' || matrix[pos[0]][pos[1]-1] != 'O')) {
            matrix[pos[0]][pos[1]] = mark;
            pos[1] -= 1;    // Move left
        } else {
            dir = (dir+1)%4;    // Change the dir, because an obstacle is reached
        }
    }

    return matrix;
}


// Count the amount of marks
int count_marks(char **matrix, int height, int width, char mark) {
    int nr_marks = 0;   // Amount of marks in the matrix

    // Go through the matrix and count the marks
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (matrix[i][j] == mark) nr_marks++;
        }
    }

    return nr_marks;
}


// Get a spot for an obstacle, only consider places where we have an X placed (otherwise we do not even move there)
int *obs_pos(char **matrix, int height, int width, int *old_pos, char mark) {
    int *pos;       // The next position to test for an obstacle

    // Loop through the matrix
    for (int i=old_pos[0]; i<height; i++) {
        for (int j=old_pos[1]; j<width; j++) {
            if (matrix[i][j] == mark) {
                // Next position found, return it
                pos[0] = i;
                pos[1] = j;
                return pos;
            }
        }
    }

    return pos;
}


// Find loops
int loops(char **matrix) {
    
    return 0;
}


// Check if a position is a repetition
int pos_is_rep(char **matrix, int height, int width, int *pos, char mark) {
    int result = 0;

    // Initialize the position of the obstacle
    int *obs;
    obs[0] = 0;
    obs[1] = 0;

    for (int i=0; i<143; i++) {
        obs = obs_pos(matrix, height, width, obs, mark);
        matrix[obs[0]][obs[1]] = 'O';
        matrix = update_matrix(matrix, height, width, pos, 0, mark);
        if (matrix[0][0] == '1') result++;
        matrix[obs[0]][obs[1]] = '-';
        std::cout<<result<<std::endl;
    }

    return result;
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
    char mark = 'X';
    matrix = update_matrix(matrix, height, width, pos, dir, mark);
    int resultA = count_marks(matrix, height, width, mark)+1;

    int resultB = 0;

    std::cout << "Answer 1: " << resultA << std::endl;
    std::cout << "Answer 2: " << resultB << std::endl;

    return 0;
}