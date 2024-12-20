// Day 16
// Advent of Code 2024
// 16-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


// Enum containing the direction
enum direction {
    east = 0, north, west, south
};


// Create a map structure
struct maze {
    int height;
    int width;
    bool **isPath;

    maze (int h, int w) {
        this->height = h;
        this->width = w;

        this->isPath = new bool*[width];
        for (int i=0; i<w; i++) {
            this->isPath[i] = new bool[height];
            for (int j=0; j<h; j++)
                this->isPath[i][j] = false;
        }
    }
};

// Struct for a reindeer going through the field
struct reindeer {
    std::pair<int, int> pos;            // X and Y position of the reindeer
    direction dir;

    reindeer (std::pair<int, int> start) {
        this->pos = start;
        this->dir = direction::east;
    }
};


int move_along(maze *m, std::pair<int, int> pos, direction dir);

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
void fill_map(maze *m, std::vector<std::string> *input) {
    for (int y=0; y<m->height; y++) {
        for (int x=0; x<m->width; x++) {
            if (input->at(y).at(x) != '#')
                m->isPath[x][y] = true;
        }
    }
}


// Rotate the reindeer to the wanted orientation
int rotate_reindeer(direction currentDir, direction desiredDir) {
    if (currentDir == desiredDir) {
        // std::cout << "Current and desired dir: " << currentDir << '\n';
        return 0;           // No rotation needed
    } 
    if ((currentDir+2)%4 != desiredDir) {             // Rotating 90 degrees needed
        // std::cout << "Current: " << currentDir <<  " and desired dir: " << currentDir << '\n';
        currentDir = desiredDir;
        return 1000; 
    }
    // std::cout << "Turning around" << '\n';
    return -1;                                      // Turning around, please don't do that
}


// Take the next step and rotate
int take_step(maze *m, std::pair<int, int> pos, direction currentDir, direction dir) {
    // Rotational movement
    int rotation = rotate_reindeer(currentDir, dir);
    if (rotation == -1) return -1;                          // No U-turns
    currentDir = dir;
    
    // Move further through the maze
    switch (dir) {
    case direction::north:
        pos.second--;
        break;
    case direction::west:
        pos.first++;
        break;
    case direction::south:
        pos.second++;
        break;
    case direction::east:
        pos.first--;
        break;
    default:
        std::cout << "Moving out of the compas????" << std::endl;
        exit(999);
        break;
    }

    int move_score = move_along(m, pos, dir); 

    return rotation+move_score;
}


// Find the path through the maze
int move_along(maze *m, std::pair<int, int> pos, direction dir) {
    // See if a top is reached
    // std::cout << "Current position: " << pos.first << "," << pos.second << '\n';
    if (pos.first == m->width-2 && pos.second == 1) {
        std::cout << "END FOUND" << '\n';
        return 1;
    }

    // Try to move up
    int north = 0;
    if (m->isPath[pos.first][pos.second-1]) {
        north = take_step(m, pos, dir, direction::north)+1;
        // std::cout << "Moving north to :" << pos.first << "," << pos.second << '\n';
    }
    if (north <= 0) north = 99999;

    // Try to move right
    int west = 0;
    if (m->isPath[pos.first+1][pos.second]) {
        west = take_step(m, pos, dir, direction::west)+1;
        // std::cout << "Moving west to :" << pos.first << "," << pos.second << '\n';
    }
    if (west <= 0) west = 99999;

    // Try to move down
    int south = 0;
    if (m->isPath[pos.first][pos.second+1]) {
        west = take_step(m, pos, dir, direction::south)+1;
        // std::cout << "Moving south to :" << pos.first << "," << pos.second << '\n';
    }
    if (south <= 0) south = 99999;

    // Try to move left
    int east = 0;
    if (m->isPath[pos.first-1][pos.second]) {
        west = take_step(m, pos, dir, direction::east)+1;
        // std::cout << "Moving east to :" << pos.first << "," << pos.second << '\n';
    }
    if (east <= 0) east = 99999;

    return std::min(std::min(north, west), std::min(south, east));
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

    // Create map and reindeer objects
    maze field = maze(input_lines.size(), input_lines[0].size());
    //reindeer pata = reindeer({1, input_lines.size()-2});
    std::pair<int, int> starting_pos = {1, input_lines.size()-2};

    // Fill the map with the input data
    fill_map(&field, &input_lines);

    // Solve the maze
    int result = move_along(&field, starting_pos, direction::east);

    std::cout << "Answer 1: " << result << std::endl;
    
    return 0;
}
