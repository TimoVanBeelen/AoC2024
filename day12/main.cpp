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


// struct to keep track of data for each different plot
struct field {
    int area = 0;
    int perim = 0;
    char c = '.';

    field(char val) {
        this->c = val;
    }
    field() {}
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


// Fill the map with the correct values
void fill_fields(map *m, std::vector<std::string> input) {
    for (int i=0; i<m->get_height(); i++) {
        for (int j=0; j<m->get_width(); j++) {
            m->set_val(i, j, input[i].at(j));
            m->is_visited[i][j] = false;
        }
    }
}


// Check if the plot with a certain letter already exists
bool field_exists(std::vector<field> *flds, char val) {
    for (size_t i=0; i<flds->size(); i++) {
        if (flds->at(i).c == val) return true;
    }
    return false;
}


// Find the field data and also that of its neighbours
void set_field_data(std::vector<field> *flds, map m, int x, int y) {
    // Check if the field exists, otherwise append it to the vector
    char value = m.get_val(x, y);
    if (!field_exists(flds, value))
        flds->push_back(field(value));

    int index = -1;          // Now we can call the field by its index
    for (size_t i=0; i<flds->size(); i++) {
        if (flds->at(i).c == value) {
            index = i;
            break;
        }
    }
    
    // Increase the area by 1
    flds->at(index).area++;

    // Check if we are at a border, then add an extra fence
    if (x == 0 || y == 0 || x == m.get_height()-1 || y == m.get_width()-1) {
        if (x == y || (x == m.get_height()-1 && y == 0) || (x == 0 && y == m.get_width()-1)) {
            flds->at(index).perim++;    // Corners have two border fences
        }
        flds->at(index).perim += 1;
    }

    // For all borderings of other fields, add a fence
    if (x != 0 && m.get_val(x-1, y) != value)
        flds->at(index).perim++;
    if (y != 0 && m.get_val(x, y-1) != value)
        flds->at(index).perim++;
    if (x != m.get_height()-1 && m.get_val(x+1, y) != value)
        flds->at(index).perim++;
    if (y != m.get_width()-1 && m.get_val(x, y+1) != value)
        flds->at(index).perim++;

}


// Fill the field data with area and perimiter
std::vector<field> get_field_data(map m) {
    std::vector<field> result;
    for (int i=0; i<m.get_height(); i++) {
        for (int j=0; j<m.get_width(); j++){
            // For each place on the map add to a field
            set_field_data(&result, m, i, j);
        }
    }
    return result;
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



// Main program body
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) return 0;

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Initialize the map and fill its fields
    map plots(input_lines.size(), input_lines[0].size());
    fill_fields(&plots, input_lines);

    // Create a vector of fields and add to those the size and perimiter
    std::vector<field> fields = get_field_data(plots);

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
        std::pair<int, int> APpair = calc_plot_cost(&plots, x, y);
        std::cout << "Area: " << APpair.first << " and perim: " << APpair.second << '\n';
        std::cout << "Resulting in costs of: " << APpair.first*APpair.second << '\n' << '\n';
        fence_cost += APpair.first * APpair.second;
    }

    // for (field f: fields){
    //     std::cout << f.c << " " << f.area << " " << f.perim << '\n';
    //     fence_cost += f.area*f.perim;
    // }

    std::cout << "Answer: " << fence_cost << std::endl;
    return 0;
}