// Day 12
// Advent of Code 2024
// 12-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "map.h"


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


// Fill the map with the correct values
void fill_fields(map *m, std::vector<std::string> input) {
    for (int i=0; i<m->get_height(); i++) {
        for (int j=0; j<m->get_width(); j++) {
            m->set_val(i, j, input[i].at(j));
            m->is_visited[i][j] = false;
        }
    }
}


// Get the position(s) of neighbouring field(s) with the same mark
std::vector<std::pair<int, int>> pos_of_neighbours(map *m, int x, int y) {
    std::vector<std::pair<int, int>> result;    // Return a vector with the neighbours that need to be accounted for
    char value = m->get_val(x, y);              // Get the mark of the current field

    // For all borderings of other fields, check mark and add to vector
    if (x != 0 && m->get_val(x-1, y) == value)
        result.push_back({x-1, y});
    if (y != 0 && m->get_val(x, y-1) == value)
        result.push_back({x, y-1});
    if (x != m->get_height()-1 && m->get_val(x+1, y) == value)
        result.push_back({x+1, y});
    if (y != m->get_width()-1 && m->get_val(x, y+1) == value)
        result.push_back({x, y+1});

    return result;
}


// Get the position(s) of neighbouring field(s) with the same mark
std::vector<std::pair<int, int>> pos_of_neighbours(map *m, int x, int y, char value) {
    std::vector<std::pair<int, int>> result;    // Return a vector with the neighbours that need to be accounted for
    
    // For all borderings of other fields, check mark and add to vector
    if (x != 0 && m->get_val(x-1, y) == value)
        result.push_back({x-1, y});
    if (y != 0 && m->get_val(x, y-1) == value)
        result.push_back({x, y-1});
    if (x != m->get_height()-1 && m->get_val(x+1, y) == value)
        result.push_back({x+1, y});
    if (y != m->get_width()-1 && m->get_val(x, y+1) == value)
        result.push_back({x, y+1});

    return result;
}


// Get the position(s) of neighbouring field(s) with another mark
std::vector<std::pair<int, int>> next_with_other_mark(map *m, int x, int y, char value) {
    std::vector<std::pair<int, int>> result;    // Return a vector with the neighbours that need to be accounted for

    // For all borderings of other fields, check mark and add to vector
    if (x != 0 && m->get_val(x-1, y) != value)
        result.push_back({x-1, y});
    if (y != 0 && m->get_val(x, y-1) != value)
        result.push_back({x, y-1});
    if (x != m->get_height()-1 && m->get_val(x+1, y) != value)
        result.push_back({x+1, y});
    if (y != m->get_width()-1 && m->get_val(x, y+1) != value)
        result.push_back({x, y+1});

    return result;
}


// Itteratively check each field and return the (area, perim) pair
std::pair<int, int> calc_plot_cost(map *m, int x_start, int y_start) {
    // Set up variables
    int area = 1;           // Area of the current position
    int perim = 4;          // Each field has a perimiter of 4, start with that
    m->is_visited[x_start][y_start] = true;     // We have visited, so true  

    // While there is a neighbour with same mark, add to area and perimiter
    std::vector<std::pair<int, int>> neighbours = pos_of_neighbours(m, x_start, y_start); 
    for (std::pair<int, int> neighbour: neighbours){
        perim --;                                                       // Remove the perim count for neighbouring fields of the same kind
        if (m->is_visited[neighbour.first][neighbour.second]) continue; // don't count double
        
        std::pair<int, int> itres;
        itres = calc_plot_cost(m, neighbour.first, neighbour.second);   // Get the result of the iteration
        area += itres.first;                                            
        perim += itres.second;                                        
    }      

    return {area, perim};
}


// Check if a position is on a diagonal of another position
bool onDiagonal(map *m, std::pair<int, int> pos1, std::pair<int, int> pos2) {
    // Check the left top diagonal position
    if (pos1.first > 0 && pos1.second > 0)
        return (pos2.first == pos1.first-1 && pos2.second == pos1.second-1);
    // Check the right top diagonal position
    if (pos1.first > 0 && pos1.second < m->get_width()-1)
        return (pos2.first == pos1.first-1 && pos2.second == pos1.second+1);
    // Check the left bottom diagonal position
    if (pos1.first < m->get_height()-1 && pos1.second > 0)
        return (pos2.first == pos1.first+1 && pos2.second == pos1.second-1);
    // Check the right bottom diagonal position
    if (pos1.first < m->get_height()-1 && pos1.second < m->get_width()-1)
        return (pos2.first == pos1.first+1 && pos2.second == pos1.second+1);

    // Default response
    return false;
}


// Calculate how much extra perimiter is needed
int extra_perimiter(map *m, int x, int y, std::vector<std::pair<int, int>> neighbours) {
    // Get the 'anti' location
    std::vector<std::pair<int, int>> diff_neighbours = next_with_other_mark(m, x, y, m->get_val(x, y));
    std::vector<std::pair<int, int>> next_to_neighbour;
    int diagonalen = 0;

    // Switch dependent on diagonals
    switch (neighbours.size())
    {
    case 1:
        next_to_neighbour = pos_of_neighbours(m, neighbours[0].first, neighbours[0].second);
        for (std::pair<int, int> schuine_buurman: next_to_neighbour) {
            if (onDiagonal(m, {x, y}, schuine_buurman)) diagonalen++;
        }
        if (diagonalen == 0) return 0;
        if (diagonalen == 1) return 2;
        if (diagonalen == 2) return 3;
        break;
    
    case 2:
        next_to_neighbour = pos_of_neighbours(m, neighbours[0].first, neighbours[0].second);
        for (std::pair<int, int> schuine_buurman: next_to_neighbour) {
            if (onDiagonal(m, {x, y}, schuine_buurman)) diagonalen++;
        }
        next_to_neighbour = pos_of_neighbours(m, neighbours[1].first, neighbours[1].second);
        for (std::pair<int, int> schuine_buurman: next_to_neighbour) {
            if (onDiagonal(m, {x, y}, schuine_buurman)) diagonalen++;
        }
        if (diagonalen == 1) return -2;
        if (diagonalen == 3) return 2; // Not necessarily true -> look at the diff_neighbours as well
        if (diagonalen == 4) return 4;
        break;

    case 3:
        if (x == 0 || y == 0 || x == m->get_height()-1 || y == m->get_width()-1) return 0;
        next_to_neighbour = pos_of_neighbours(m, diff_neighbours[0].first, diff_neighbours[0].second, m->get_val(x, y));
        for (std::pair<int, int> schuine_buurman: next_to_neighbour) {
            if (onDiagonal(m, {x, y}, schuine_buurman)) diagonalen++;
        }
        if (diagonalen == 0) return -4;
        if (diagonalen == 1) return -2;
        break;
    case 4:
        return -4;
    default:
        break;
    }
    return 0;
}


// Itteratively check each field and return the (area, perim) pair
int buy_in_bulk(map *m, int x_start, int y_start, int *perimptr) {
    // Set up variables
    int area = 1;                               // Area of the current position
    m->is_visited[x_start][y_start] = true;     // We have visited, so true  

    // Check where the neighbours of the same mark are and use that to get the addition of perimiter
    std::vector<std::pair<int, int>> neighbours = pos_of_neighbours(m, x_start, y_start);
    int dperim = extra_perimiter(m, x_start, y_start, neighbours);
    std::cout << "PERIM ADDITION OF " << dperim << ", pos: " << x_start << "," << y_start << '\n';
    perimptr += dperim;

    // While there is a neighbour with same mark, add to area and perimiter
    for (std::pair<int, int> neighbour: neighbours){
        if (m->is_visited[neighbour.first][neighbour.second]) continue; // don't count double
        area += buy_in_bulk(m, neighbour.first, neighbour.second, perimptr);   // Get the result of the iteration                                      
    }      

    return area;
}




// Main program body
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) return 0;

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Initialize the map and fill its fields
    map plots(input_lines.size(), input_lines[0].size());
    fill_fields(&plots, input_lines);

    // Print some information on each field
    int fence_cost = 0;
    for (int i=0; i<plots.get_height()*plots.get_width(); i++) {
        // Get the field position
        int x=floor(i/plots.get_width());
        int y=i%plots.get_width();

        // If already taken into account: don't do that again
        std::cout << "checking " << x << ',' << y << '\n';
        if (plots.is_visited[x][y]) continue;
        std::cout << x << ',' << y << " not visited" << '\n';

        // Calculate the cost of the fence of a certain plot and add to total
        int perim = 4;
        int area = buy_in_bulk(&plots, x, y, &perim);
        std::pair<int, int> APpair = {area, perim};
        std::cout << "Area: " << APpair.first << " and perim: " << APpair.second << '\n';
        std::cout << "Resulting in costs of: " << APpair.first*APpair.second << '\n' << '\n';
        fence_cost += APpair.first * APpair.second;
    }

    std::cout << "Answer: " << fence_cost << std::endl;
    return 0;
}