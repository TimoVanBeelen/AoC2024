// Day 8
// Advent of Code 2024
// 08-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string.h>


// Create a struct for a char matrix
struct matrix {
    char **field;
    int height;
    int width;
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


// Find the next antenna in the matrix, if none found, return 0
int *find_next_ant(matrix m, int *old_pos, char mark) {
    int *new_pos = new int[2];
    for (int i=old_pos[0]; i<m.height; i++) {
        for (int j=0; j<m.width; j++) {
            // Check if the new antenna is after the old one and return it
            if (i==old_pos[0] && j<=old_pos[1]) continue;
            if (m.field[i][j] == mark) {
                new_pos[0] = i;
                new_pos[1] = j;
                return new_pos;
            }
        }
    }

    return 0;
}


// Find the antinode from the two positions
int *find_antinode(int *pos, int *other_ant) {
    int *antinode = new int[2];
    antinode[0] = pos[0]+(pos[0] - other_ant[0]);
    antinode[1] = pos[1]+(pos[1] - other_ant[1]);
    return antinode;
}


// Get the distance between an antenna and an antinode
int *ant_to_antinode(int *antenna, int *antinode) {
    int *distance = new int[2];
    distance[0] = antinode[0]-antenna[0];
    distance[1] = antinode[1]-antenna[1];
    return distance; 
}


// Check if a position is on the map
bool on_map(matrix m, int *pos) {
    if (m.height>pos[0] && m.width>pos[1] && pos[0]>=0 && pos[1]>=0) return true;
    else return false;
}


// Count the amount of marks
int count_marks(matrix m, char mark) {
    int nr_marks = 0;   // Amount of marks in the matrix

    // Go through the matrix and count the marks
    for (int i=0; i<m.height; i++) {
        for (int j=0; j<m.width; j++) {
            if (m.field[i][j] == mark) nr_marks++;
        }
    }

    return nr_marks;
}


// Main program body
int main(int argc, char *argv[]) {
    // Read the file and get the different strings as a char matrix
    matrix m;
    std::vector<std::string> input_lines = read_file(argv[1]);
    m.field = strarr_to_chararr(input_lines);
    m.height = input_lines.size();
    m.width = input_lines[0].size();

    bool pt2 = true;


    // Create a field for only placing the marks
    matrix mf;
    mf.height = m.height;
    mf.width = m.width;
    mf.field = strarr_to_chararr(input_lines);
    for (int i=0; i<mf.height; i++) {
        for (int j=0; j<mf.width; j++) {
            mf.field[i][j] = '.';
        }
    } 


    // Set up start positions for the loops
    int start_pos[2] = {0,0};
    // Create an array containing all digits, uppercase, and lowercase letters
    char marks[] = 
        "0123456789"  // Digits
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  // Uppercase letters
        "abcdefghijklmnopqrstuvwxyz"; // Lowercase letters

    // Calculate the size of the array
    size_t arraySize = sizeof(marks) - 1; // Subtract 1 to exclude null terminator


    // Go through each possible antenna and calculate the points
    for (size_t i=0; i<arraySize; i++) {
        // Set first position and mark
        char mark = marks[i];
        int *pos = find_next_ant(m, start_pos, mark);
        if (pos == 0) continue; // Character is not in matrix

        while (pos != 0) {
            // For each found antenna, go through this loop
            int *other_ant = find_next_ant(m, start_pos, mark);
            while (other_ant != 0) {
                // Check if pos and other_ant aren't the same
                if (pos[0] == other_ant[0] && pos[1] == other_ant[1]) {
                    other_ant = find_next_ant(m, other_ant, mark);
                    continue;
                }
                // With the position and the other antenna, find the antinode
                int *antinode = find_antinode(pos, other_ant);

                // Place antinode on the map
                if (on_map(m, antinode) && !pt2) {
                    mf.field[antinode[0]][antinode[1]] = '#';
                }

                // For pt 2, go through its multiples as well until not on map anymore (array size is 50)
                if (pt2) {
                    // Create on the antenna itself an antinode
                    mf.field[pos[0]][pos[1]] = '#';

                    // Create for each multiple of the antenna's antinode an antinode
                    for (int j=1; j<48; j++) {
                        int *distance = ant_to_antinode(pos, antinode);
                        int *new_pos = new int[2]; 
                        new_pos[0] = distance[0]*j+pos[0];
                        new_pos[1] = distance[1]*j+pos[1];
                        if (!on_map(m, new_pos)) break;
                        mf.field[new_pos[0]][new_pos[1]] = '#';
                    }
                }

                other_ant = find_next_ant(m, other_ant, mark);      // Find another antenna of the same mark
            }
            pos = find_next_ant(m, pos, mark);
        }
    }

    for (int i=0; i<mf.height; i++) {
        for (int j=0; j<mf.width; j++) {
            std::cout << mf.field[i][j];
        }
        std::cout << "\n";
    }

    int result = count_marks(mf, '#');

    std::cout << result << std::endl;
    return 0;
}