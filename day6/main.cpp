// Day 6
// Advent of Code 2024
// 06-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>


// Structures 
struct field {
    int x;
    int y;
    int last_dir;
    char c = '.';
};
struct guard {
    field pos;
    int dir;
};
struct matrix {
    int width;
    int height;
};

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
// void strarr_to_chararr(std::vector<std::string> string_array, field ***fieldptr, matrix m) {
//     char **char_array = new char*[m.height];      // Create an output variable
//     for (int i = 0; i < m.height; i++) {
//         char_array[i] = new char[m.width];        // Create each row with the correct width
//         for (int j=0; j<m.width; j++) {            // Set each character of the string to the correct char in the char array
//             std::cout << "MARCO";
//             fieldptr[0][0]->c = '.'; //string_array[i].at(j);
//             std::cout << "POLO";
//         }
//     }
// }

void change_dir(field *fieldptr) {
    fieldptr->last_dir = 0;
}


// // Find the initial position of the guard
// field find_pos(matrix m) {
//     field pos;                                  // Create a variable of the returning position
//     for (int i=0; i<m.height; i++) {
//         for (int j=0; j<m.width; j++){          // Go through the whole matrix
//             if (m.fields[i][j].c == '^') {      // Guard is found
//                 pos.x = i;                      // Set its position
//                 pos.y = j;             
//             }
//         }
//     }
//     return pos;
// }


// // Crossing border?
// bool is_going_to_cross(map m, guard grd) {
//     if (grd.dir == 0 && grd.pos.x == 0) return true;           // Heading north
//     if (grd.dir == 1 && grd.pos.y == m.width-1) return true;     // Heading west
//     if (grd.dir == 2 && grd.pos.x == m.height-1) return true;    // Heading south
//     if (grd.dir == 3 && grd.pos.y == 0) return true;           // Heading east
//     return false;
// }


// // Move the guard
// map update_matrix(map m, guard grd, char mark) {
    
//     // Keep on walking until gone
//     while (!is_going_to_cross(m, grd)) {
//         // Walk north if no obstacle
//         if (grd.dir == 0 && (m.fields[grd.pos.x-1][grd.pos.y].c != '#' || m.fields[grd.pos.x-1][grd.pos.y].c != 'O')) {
//             m.fields[grd.pos.x][grd.pos.y].c = mark;
//             grd.pos.x -= 1;    // Move up
//         } 
//         else if (grd.dir == 1 && (m.fields[grd.pos.x][grd.pos.y+1].c != '#' || m.fields[grd.pos.x][grd.pos.x+1].c != 'O')) {
//             m.fields[grd.pos.x][grd.pos.x].c = mark;
//             grd.pos.x += 1;    // Move right
            
//         }
//         else if (grd.dir == 2 && (m.fields[grd.pos.x+1][grd.pos.x].c != '#' || m.fields[grd.pos.x+1][grd.pos.x].c != 'O')) {
//             m.fields[grd.pos.x][grd.pos.x].c = mark;
//             grd.pos.x += 1;    // Move down
//         }
//         else if (grd.dir == 3 && (m.fields[grd.pos.x][grd.pos.x-1].c != '#' || m.fields[grd.pos.x][grd.pos.x-1].c != 'O')) {
//             m.fields[grd.pos.x][grd.pos.x].c = mark;
//             grd.pos.x -= 1;    // Move left
//         } else {
//             grd.dir = (grd.dir+1)%4;    // Change the dir, because an obstacle is reached
//         }
//     }

//     return m;
// }


// Count the amount of marks
// int count_marks(map m, char mark) {
//     int nr_marks = 0;   // Amount of marks in the matrix

//     // Go through the matrix and count the marks
//     for (int i=0; i<m.height; i++) {
//         for (int j=0; j<m.width; j++) {
//             if (m.fields[i][j].c == mark) nr_marks++;
//         }
//     }

//     return nr_marks;
// }


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


// Run main code here
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Create a map: a matrix of characters, from the input lines
    field **map;
    matrix m;
    m.height = input_lines.size();
    m.width = input_lines[0].size();
    std::cout << "Map: " << m.height << "x" << m.width << "\n";
    change_dir(&map[0][0]);
    // strarr_to_chararr(input_lines, &map, m);

    // for (int i=0; i<m.height; i++) {
    //     for (int j=0; i<m.width; j++) {
    //         std::cout << map[i][j].c;
    //     }
    //     std::cout << "\n";
    // }

    // Create a guard struct
    // guard grd;
    // grd.pos = find_pos(m);
    // grd.dir = 0;  // Set the walking direction, north = 0, west = 1, south = 2, east = 3

    // char mark = 'X';
    // m = update_matrix(m, grd, mark);
    // int resultA = count_marks(m, mark)+1;

    int resultB = 0;

    // std::cout << "Answer 1: " << resultA << std::endl;
    std::cout << "Answer 2: " << resultB << std::endl;

    return 0;
}