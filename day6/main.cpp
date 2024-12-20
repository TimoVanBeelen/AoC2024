// Day 6
// Advent of Code 2024
// 06-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std::chrono;


// Structures 
struct guard {
    std::pair<int, int> pos;
    int dir;

    guard (std::pair<int, int> startPos) {
        this->pos = startPos;
        this->dir = 0;  
    }
};

struct matrix {
    int width;
    int height;
    int **last_dir;
    char **val;

    matrix (int h, int w) {
        this->height = h;
        this->width = w;

        this->last_dir = new int*[w];
        this->val = new char*[w];
        for (int i=0; i<w; i++) {
            this->last_dir[i] = new int[h];
            this->val[i] = new char[h];
            
            for (int j=0; j<h; j++) 
                this->last_dir[i][j] = -1;
        }
    }

    int get_last_dir (std::pair<int, int> pos) {
        return this->last_dir[pos.first][pos.second];
    }

    void reset_dirs() {
        for (int x=0; x<this->width; x++) {
            for (int y=0; y<this->height; y++) {
                this->last_dir[x][y] = -1;
            }
        }
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


// Create a char matrix from a string array
void strarr_to_chararr(std::vector<std::string> *string_array, matrix *m) 
{
    for (int i = 0; i < m->width; i++) 
    {
        for (int j=0; j<m->height; j++)          // Set each character of the string to the correct char in the char array
        {            
            m->val[i][j] = string_array->at(i).at(j);
        }
    }
}


// Find the initial position of the guard
std::pair<int, int> find_pos(matrix *m) 
{
    std::pair<int, int> pos;                     // Create a variable of the returning position
    for (int y=0; y<m->height; y++) {
        for (int x=0; x<m->width; x++){          // Go through the whole matrix
            if (m->val[x][y] == '^') {           // Guard is found
                pos.first = x;                   // Set its position
                pos.second = y;
                m->val[x][y] = '.';             
            }
        }
    }
    return pos;
}


// // Crossing border?
bool is_going_to_cross(matrix *m, guard *grd) 
{
    if (grd->dir == 0 && grd->pos.first  == 0) return true;              // Heading north
    if (grd->dir == 1 && grd->pos.second == m->width-1) return true;     // Heading west
    if (grd->dir == 2 && grd->pos.first  == m->height-1) return true;    // Heading south
    if (grd->dir == 3 && grd->pos.second == 0) return true;              // Heading east
    return false;
}


// Move the guard
bool update_matrix(matrix *m, guard *grd, char mark) 
{
    // Keep on walking until gone
    while (!is_going_to_cross(m, grd)) {
        // Walk north if no obstacle
        if (grd->dir == 0 && (m->val[grd->pos.first-1][grd->pos.second] != '#')) 
        {
            grd->pos.first -= 1;            // Move up
        } 
        else if (grd->dir == 1 && (m->val[grd->pos.first][grd->pos.second+1] != '#')) 
        {
            grd->pos.second += 1;           // Move right
            
        }
        else if (grd->dir == 2 && (m->val[grd->pos.first+1][grd->pos.second] != '#')) 
        {
            grd->pos.first += 1;            // Move down
        }
        else if (grd->dir == 3 && (m->val[grd->pos.first][grd->pos.second-1] != '#')) 
        {
            grd->pos.second -= 1;           // Move left
        } 
        else 
        {
            grd->dir = (grd->dir+1)%4;      // Change the dir, because an obstacle is reached
        }
        m->val[grd->pos.first][grd->pos.second] = mark;

        // Change the field's last direction
        if (grd->dir == m->get_last_dir(grd->pos)) return true;
        m->last_dir[grd->pos.first][grd->pos.second] = grd->dir;
    }

    return false;
}


// Function to rotate
int rotate(matrix *m, guard *grd, int dir) 
{
    if (dir == 0 && m->val[grd->pos.first][grd->pos.second+1] == '#') 
    {
        return 2;
    }
    else if (dir == 1 && m->val[grd->pos.first+1][grd->pos.second] == '#') 
    {
        return 3;
    }
    else if (dir == 2 && m->val[grd->pos.first][grd->pos.second-1] == '#') 
    {
        return 0;
    }
    else if (dir == 3 && m->val[grd->pos.first-1][grd->pos.second] == '#') 
    {
        return 1;
    }
    else return (dir+1)%4;
}


// Move the guard
bool update_matrix(matrix *m, guard *grd) 
{
    bool going_back = false;
    // Keep on walking until gone
    while (!is_going_to_cross(m, grd)) {
        // Walk north if no obstacle
        if (grd->dir == 0 && (m->val[grd->pos.first-1][grd->pos.second] != '#')) 
        {
            grd->pos.first -= 1;            // Move up
        } 
        else if (grd->dir == 1 && (m->val[grd->pos.first][grd->pos.second+1] != '#')) 
        {
            grd->pos.second += 1;           // Move right
            
        }
        else if (grd->dir == 2 && (m->val[grd->pos.first+1][grd->pos.second] != '#')) 
        {
            grd->pos.first += 1;            // Move down
        }
        else if (grd->dir == 3 && (m->val[grd->pos.first][grd->pos.second-1] != '#')) 
        {
            grd->pos.second -= 1;           // Move left
        } 
        else 
        {
            int new_dir = rotate(m, grd, grd->dir);     // Change the dir, because an obstacle is reached
            if (abs(grd->dir)-new_dir > 1 && going_back) return true;
            grd->dir = new_dir;       
        }

        // Change the field's last direction
        if (grd->dir == m->get_last_dir(grd->pos)) return true;
        if ((grd->dir+2)%4 == m->get_last_dir(grd->pos)) going_back = true;
        else going_back = false;
        m->last_dir[grd->pos.first][grd->pos.second] = grd->dir;
    }

    return false;
}


// Get a spot for an obstacle, only consider places where we have an X placed (otherwise we do not even move there)
int *obs_pos(char **matrix, int height, int width, int *old_pos, char mark) {
    int *pos = new int[2];       // The next position to test for an obstacle

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


void print_map(matrix *map) {
    for (int x=0; x<map->width; x++) {
        for (int y=0; y<map->height; y++) {
            std::cout << map->val[x][y];
        }
        std::cout << '\n';
    }
}


// Run main code here
int main(int argc, char *argv[]) {// Check if there are enough arguments
    if (argc < 2) {
        std::cout << "Not enough input arguments" << '\n';
        return 0;
    }
    auto start = high_resolution_clock::now();  

    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Create a map: a matrix of characters, from the input lines
    matrix map = matrix(input_lines.size(), input_lines[0].size());
    std::cout << "Map: " << map.width << "x" << map.height << "\n";
    strarr_to_chararr(&input_lines, &map);
    std::pair<int, int> starting_pos = find_pos(&map);

    // Create a guard struct
    guard grd = guard(starting_pos);

    // Run to see which fields might create a loop and reset the system
    update_matrix(&map, &grd, 'X');
    map.reset_dirs();
    grd.pos = starting_pos;
    grd.dir = 0;

    // Loop through the possible fields and see if a loop is created. 8.60 is the problem
    int res = 0;
    for (int x=0; x<map.width; x++) {
        for (int y=0; y<map.height; y++) {
            if (map.val[x][y] != 'X' || map.val[x][y] == '#' || (grd.pos.first == x && grd.pos.second == y) ) continue;
            
            map.val[x][y] = '#';
            if (update_matrix(&map, &grd)) res++;
            map.val[x][y] = '.';
            map.reset_dirs();
            grd.pos = starting_pos;
            grd.dir = 0;
        }
    }

    // Stop timer
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "End time: " << duration.count() << '\n'; 

    std::cout << "Answer 2: " << res << std::endl;

    return 0;
}