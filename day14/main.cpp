// Day 14
// Advent of Code 2024
// 14-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <math.h>


// Create a robot struct to store robot data
struct robot {
    std::pair<int, int> position;
    std::pair<int, int> speed;
    int quadrant;                   // 0 if not in a quadrant

    robot() {}      // Simple constructor
};

struct map {
    int height;
    int width;

    map(int h, int w) {
        this->height = h;
        this->width = w;
    }
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


// Find robot information -> create an array of size 4 with the X and Y components for position and speed
int *str_to_arr(std::string input) {
    // Search for the digits
    std::regex digs("(-)?\\d+");
    std::smatch match;

    // There should be 4 digits on each line
    int *roboInfo = new int[4];

    // See if there are any matches in the input string and output these
    for (int i=0; i<4; i++) {
        std::regex_search(input, match, digs);
        roboInfo[i] =std::stoi(match[0].str());
        input = match.suffix().str();
    }

    return roboInfo;
}


// Create an array of robots from the input information
robot *create_robots(const std::vector<std::string> *input) {
    robot *robots = new robot[input->size()];
    for (size_t i=0; i<input->size(); i++) {
        // Get the information out of the string into an array of 4 digits
        int *roboInfo = str_to_arr(input->at(i));

        // Match this information to create a new robot
        robots[i].position = {roboInfo[0], roboInfo[1]};
        robots[i].speed = {roboInfo[2], roboInfo[3]};
        robots[i].quadrant = 0;
    }
    return robots;
}


// Update robs position according to his speed for n times
void updateRobot(robot *rob, map *m, int n) {
    for (int i=0; i<n; i++) {
        // Update x
        rob->position.first = (rob->position.first+rob->speed.first)%m->width;
        if (rob->position.first < 0) rob->position.first += m->width;

        // Update y
        rob->position.second = (rob->position.second+rob->speed.second)%m->height;
        if (rob->position.second < 0) rob->position.second += m->height;
    }

    // Determine position of robot
    int left_border = ceil(m->width/2);
    int top_border = ceil(m->height/2);
    if (rob->position.first < left_border && rob->position.second < top_border) 
        rob->quadrant = 1;
    if (rob->position.first > left_border && rob->position.second < top_border)
        rob->quadrant = 2;
    if (rob->position.first < left_border && rob->position.second > top_border)
        rob->quadrant = 3;
    if (rob->position.first > left_border && rob->position.second > top_border)
        rob->quadrant = 4;
}


void print(map m, robot *robots, int nr_robs) {
    for (int i=0; i<m.width; i++) {
        std::string s;
        for (int j=0; j<m.height; j++) {
            for (int r=0; r<nr_robs; r++) {
                if (robots[r].position.first == i && robots[r].position.second == j) s.push_back('x');
            }
            if ((int)s.size() != j+1) s.push_back(' ');
        }
        std::cout << s << '\n';
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

    // Create an array of robots and fill it with info from input
    int robotAmount = input_lines.size();
    robot *robotArray = create_robots(&input_lines);

    // Create the playing field
    map m = map(103, 101);

    int moves = 10000;
    // ulong *quads = new ulong[4];                // Array to safe the nr of robots in a quadrant
    // quads[0] = 0;
    // quads[1] = 0;
    // quads[2] = 0;
    // quads[3] = 0;

    // Move each robot exactly 100 times -> pt 2 make this 1 and print the board each time
    for (int i=0; i<moves; i++) {
        if (i>=4000) {
            std::cout << "At second " << i << '\n';
            print(m, robotArray, robotAmount);
            std::cout << "\n\n\n";
        }
        // Update position and print position
        for (int i=0; i<robotAmount; i++) {
            updateRobot(&robotArray[i], &m, 1);
            // if (robotArray[i].quadrant == 0) continue;
            // quads[robotArray[i].quadrant-1]++;
        }
    }
    
    // ulong result = quads[0] * quads[1] * quads[2] * quads[3];
    // std::string stuff(10, '.');
    // std::cout << stuff << '\n' << "Answer 1: " << result << std::endl;
    return 0;
}

// 91536300 -> too low
// 217328832