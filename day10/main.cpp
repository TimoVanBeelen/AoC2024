// Day 10
// Advent of Code 2024
// 10-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>


// Struct for field
struct field {
    int *pos;
    int value;
    bool visited;
    bool trailhead;

    field () {
        this->visited = false;
    }

    field(int v) {
        this->value = v;
        this->visited = false;
    }
};

// Struct for a map
struct map {
    int height;
    int width;
    field **fld;

    map(int h, int w) {
        this->height = h;
        this->width = w;
        this->fld = new field*[height];
        for (int i=0; i<height; i++)
            this->fld[i] = new field[width];
    }

    bool fld_is_visited(int x, int y) {
        return this->fld[x][y].visited;
    }

    void set_fld_visited(int x, int y, bool b) {
        this->fld[x][y].visited = b;
    }

    int get_fld_val(int x, int y) {
        return this->fld[x][y].value;
    }

    void set_fld_val(int x, int y, int val) {
        this->fld[x][y].value = val;
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


// String to char array
char *stoc(std::string s) {
    char *carr = new char[s.size()];
    for (size_t i=0; i<s.size(); i++) {
        carr[i] = s.at(i);
    }
    return carr;
}


// Char array to int array
int *ctoia(char *carr, int size) {
    int *iarr = new int[size];
    for (int i=0; i<size; i++) {
        iarr[i] = carr[i] - '0';
    }
    return iarr;
}


// See if we have found a trailhead
bool is_trailhead(int **map, int x, int y) {
    if (map[x][y] == 0) return true;
    else return false;
}


// Print an int matrix
void print(map *m) {
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            std::cout << m->get_fld_val(i, j);
        }
        std::cout << '\n';
    }
}


// Check if the trail goes up, but not too steep
bool goes_gently_up(map *m, int *pos1, int *pos2) {
    if (m->get_fld_val(pos2[0], pos2[1]) == m->get_fld_val(pos1[0], pos1[1])+1) return true;
    else return false;
}


// Get new position
int *get_new_pos(int *pos, int up, int right) {
    int *new_pos = new int[2];
    new_pos[0] = pos[0]+up;
    new_pos[1] = pos[1]+right;
    return new_pos;
}


// Go through the field and only step to the number next up
int move_along(map *m, int* pos) {
    // Set the output variable amd check the position as visited
    int score = 0;                          // Set a score
    //m->set_fld_visited(pos[0], pos[1], true);     // Set field to visited

    // See if a top is reached
    if (m->get_fld_val(pos[0], pos[1]) == 9) {
        return 1;
    }

    // Try to move right
    if (pos[1] < m->width-1) {
        int *new_pos = get_new_pos(pos, 0, 1);
        if (goes_gently_up(m, pos, new_pos) && !m->fld_is_visited(new_pos[0], new_pos[1])) score += move_along(m, new_pos);
    }

    // Try to move up
    if (pos[0] < m->height-1) {
        int *new_pos = get_new_pos(pos, 1, 0);
        if (goes_gently_up(m, pos, new_pos) && !m->fld_is_visited(new_pos[0], new_pos[1])) score += move_along(m, new_pos);
    }

    // Try to move left
    if (pos[1] > 0) {
        int *new_pos = get_new_pos(pos, 0, -1);
        if (goes_gently_up(m, pos, new_pos) && !m->fld_is_visited(new_pos[0], new_pos[1])) score += move_along(m, new_pos);
    }

    // Try to move down
    if (pos[0] > 0) {
        int *new_pos = get_new_pos(pos, -1, 0);
        if (goes_gently_up(m, pos, new_pos) && !m->fld_is_visited(new_pos[0], new_pos[1])) score += move_along(m, new_pos);
    }

    return score;
}


// Reset all visited
void reset_visited(map *m) {
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            m->set_fld_visited(i,j, false);
        }
    }
}


// Main program body
int main(int argc, char *argv[]) {
    // Read file
    if (argc < 2) return 0;
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Convert the input lines to a char array
    int height = input_lines.size();        // Height of matrix
    int width = input_lines[0].size();      // Width of matrix
    map m = map(height, width);         // Create a char matrix

    // Init the map and trailheads
    for (int i=0; i<height; i++) {
        int *arr = ctoia(stoc(input_lines[i]), width);
        for (int j=0; j<width; j++) {
            m.set_fld_val(i,j,arr[j]);
        }
    }
    
    // Check trails from each trailhead
    int runsum = 0;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (m.get_fld_val(i,j) != 0) continue;
            int *pos = new int[2];
            pos[0] = i;
            pos[1] = j;
            runsum += move_along(&m, pos);
            reset_visited(&m);
        }
    }

    std::cout << "Answer 1: " << runsum <<  std::endl;

    return 0;
}