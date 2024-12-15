// Day 15
// Advent of Code 2024
// 15-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>


// Struct for a map to move through
struct map  {
    int height;
    int width;
    char **value;
    std::pair<int, int> robot;

    map(int height, int width) {
        this->height = height;
        this->width = width;

        this->value = new char*[width];
        for (int x=0; x<width; x++)
            this->value[x] = new char[height];
    }
};


// Enum to get directions
enum class direction {
    up, right, down, left
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


// Fill the map with the correct objects/values
void fill_map(map *m, std::vector<std::string> *input) {
    for (int y=0; y<m->height; y++) {
        for (int x=0; x<m->width; x++) {
            char val = input->at(y).at(x);
            if (val == '@') {               // Place a dot for the robot's position, but do keep track
                m->robot = {x, y};          
                m->value[x][y] = '.';   
            }
            else m->value[x][y] = val;      // Else just fill it up with the value of the input
        }
    }
}


// If a box is found, try to move iteratively
bool move_box(map *m, std::pair<int, int> boxPos, direction dir) {
   
    if (dir == direction::up && m->value[boxPos.first][boxPos.second-1] != '#') {
        char& fieldUp = m->value[boxPos.first][boxPos.second-1];
        if (fieldUp == '.') {
            fieldUp = 'O';
            m->value[boxPos.first][boxPos.second] = '.';
            return true;
        } 
    }

    if (dir == direction::right && m->value[boxPos.first+1][boxPos.second] != '#') {
        char& fieldRight = m->value[boxPos.first+1][boxPos.second];
        if (fieldRight == '.') {
            fieldRight = 'O';
            m->value[boxPos.first][boxPos.second] = '.';
            return true;
        }
    }

    if (dir == direction::down && m->value[boxPos.first][boxPos.second+1] != '#') {
        char& fieldDown = m->value[boxPos.first][boxPos.second+1];
        if (fieldDown == '.') {
            fieldDown = 'O';
            m->value[boxPos.first][boxPos.second] = '.';
            return true;
        }
    }

    if (dir == direction::left && m->value[boxPos.first-1][boxPos.second] != '#') {
        char& fieldLeft = m->value[boxPos.first-1][boxPos.second];
        if (fieldLeft == '.') {
            fieldLeft = 'O';
            m->value[boxPos.first][boxPos.second] = '.';
            return true;
        }
    }

    return false;
}


// Try to move the robot
void move_robot(map *m, direction dir) {
    char fieldValue;
    std::pair<int, int> nextPos;

    switch (dir) {
    case direction::up:
        // Try to move up (seperate function)
        nextPos = {m->robot.first, m->robot.second-1};
        fieldValue = m->value[m->robot.first][m->robot.second-1];
        if (fieldValue == '.')
            m->robot.second--;  
        else if (fieldValue == 'O' && move_box(m, nextPos, dir))
            m->robot.second--;

        break;

    case direction::right:
        // Try to move right (seperate function)
        nextPos = {m->robot.first+1, m->robot.second};
        fieldValue = m->value[m->robot.first+1][m->robot.second];
        if (fieldValue == '.')
            m->robot.first++;
        else if (fieldValue == 'O' && move_box(m, nextPos, dir))
            m->robot.first++;
        break; 

    case direction::down:
        // Try to move down (seperate function)
        nextPos = {m->robot.first, m->robot.second+1};
        fieldValue = m->value[m->robot.first][m->robot.second+1];
        if (fieldValue == '.')
            m->robot.second++;   
        else if (fieldValue == 'O' && move_box(m, nextPos, dir))
            m->robot.second++;
        break;

    case direction::left:
        // Try to move left (seperate function)
        nextPos = {m->robot.first-1, m->robot.second};
        fieldValue = m->value[m->robot.first-1][m->robot.second];
        if (fieldValue == '.')
            m->robot.first--;
        else if (fieldValue == 'O' && move_box(m, nextPos, dir))
            m->robot.first--;
        break; 

    default:
        std::cout << "MOVING NOWHERE" << '\n';
        break;
    }
}


// Print the field
void print(map *m) {
    for (int y=0; y<m->height; y++) {
        for (int x=0; x<m->width; x++) {
            std::cout << m->value[x][y];
        }
        std::cout << '\n';
    }
}


// Main program body
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        std::cout << "Not enough input arguments" << '\n';
        return 0;
    }

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Construct a map and fill it up with input data
    size_t i=0;
    while (input_lines[i].size() > 0) i++;          // Find the height of the map
    map field = map(i, input_lines[0].size());      // Construct the playing field
    fill_map(&field, &input_lines);

    std::string instructs = input_lines[i+1];
    for (char instr: instructs) {
        if (instr == '^') move_robot(&field, direction::up);
        if (instr == '>') move_robot(&field, direction::right);
        if (instr == 'v') move_robot(&field, direction::down);
        if (instr == '<') move_robot(&field, direction::left);
        std::cout << field.robot.first << "," << field.robot.second << '\n';
    }

    // Print the field
    print(&field);



    return 0;
}