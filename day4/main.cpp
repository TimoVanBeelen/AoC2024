// Day 4
// Advent of Code 2024
// 04-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>


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


int search_word(std::string line, std::string word) {
    // Init result variable and the loop variable
    int occurances = 0;
    int res = 0;

    // Start with the first search
    res = line.find(word, res);
    while (res != std::string::npos) {
        occurances++;                   // Word is found -> increment occurances
        res = line.find(word, res+1);   // Increment res to the new search pos
    }
    
    return occurances;
}


// Check each (horizontal) line for the words
int check_horizontally(std::vector<std::string> input_lines, std::string words[]) {
    // Set output variable and loop through all lines
    int occurances = 0;
    for (std::string line : input_lines) {
        // Search both words and increase occurances
        occurances += search_word(line, words[0]);
        occurances += search_word(line, words[1]);
    }

    return occurances;
}


// Check each vertical line
int check_vertically(std::vector<std::string> input_lines, std::string words[]) {

    // Create new (horizontal) lines from the vertical ones
    std::vector<std::string> v_lines;
    for (int i=0; i<input_lines.size(); i++) {
        std::string new_line;                   // Initiate an instance of a new line
        for (std::string line: input_lines)     // For each line, append the i-th index
            new_line += line.at(i);
        v_lines.push_back(new_line);            // Add the new line to the string vector
    }

    // Return all horizontal occurances now
    return check_horizontally(v_lines, words);
}


// Check each diagonal
int check_diagonal(std::vector<std::string> input_lines, std::string words[]) {
    // Create new strings of the diagonals (ltr)
    int hsize = input_lines[0].size();
    int vsize = input_lines.size();

    std::vector<std::string> new_lines;     // Vector that stores the lines
    for (size_t i = 0; i < hsize; i++) {
        std::string new_line;               // Create a new line here
        if (vsize <= hsize-i) {
            for (size_t j = 0; j < vsize; j++)
                new_line += input_lines[j].at(j);
        }
        else {
            for (size_t j = 0; j < hsize-i; j++)
                new_line += input_lines[j].at(j);
        }
        
    }
    

    // Create new strings of the diagonals (rtl)


    return 0;
}


// Main program
int main(int argc, char *argv[]) {
    // Read file
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Set vars for the words
    std::string xmas = "XMAS";
    std::string samx = "SAMX";  // Now you do not need to change direction
    std::string words[] = {xmas, samx};

    // Set output/result var
    int occurances = 0; 

    // Search all lines -> THIS SCRIPT USES LETTERS TWICE IN A SINGLE LINE
    occurances += check_horizontally(input_lines, words);
    occurances += check_vertically(input_lines, words);


    // Print the result
    std::cout << "Answer 1: " << occurances << std::endl; 
    std::cout << "Answer 2: " << std::endl;

    // END
    return 0;
}