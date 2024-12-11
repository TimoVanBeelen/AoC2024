// Day 10
// Advent of Code 2024
// 10-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <math.h>


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


// Split the string to a vector of integer numbers
std::vector<ulong> stoia(std::string s) {
    // Set up regex to find digits
    std::regex digits("\\d+");
    std::smatch match;

    // Find all digits
    std::vector<ulong> result;
    while (std::regex_search(s, match, digits)) {
        result.push_back(std::stol(match.str()));   // While there is a match, append it to the vector
        s = match.suffix().str();                   // The new line to search is the suffix (remainder) of the match
    }

    return result;
}


// Calculate how many digits there are in the numberS
ulong num_digs(ulong num) {
    ulong i = 1;
    while (num/10 >= 1) {
        num /= 10;
        i++;
    }
    return i;
}


// Split function to split a number with even amount of digits into two
ulong *split_num(ulong num, ulong nr_digs) {
    ulong *split = new ulong[2];                        // Return var
    ulong mag_order = floor(pow(10, nr_digs/2));      // Calculate the order of magnitude we are working with and take half of it
    split[0] = num/mag_order;                       // Divide by 10 to power of the amount of digits
    split[1] = num%mag_order;                       // The remainder of what is found as the left part, is the right part
    return split;
}


// Loop through new list and apply changes to a copy
std::vector<ulong> change_stones(std::vector<ulong> input) {
    std::vector<ulong> new_iteration;     // The vector to be returned with all the new changes
    for (ulong item: input) {
        ulong digs = num_digs(item);      // Get the number of digits 
        if (item == 0)                  // Check if entry is 0 -> make 1
            new_iteration.push_back(1);
        
        else if (digs%2==0) {            // Check if entry has even amount of digits -> split
            ulong *arr = split_num(item, digs);
            new_iteration.push_back(arr[0]);
            new_iteration.push_back(arr[1]);
        }
        else {                            // Else multiply by 2024
            ulong mult = 2024;
            new_iteration.push_back(item*mult);
        }
    }
    return new_iteration;
}


int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 3) return 0;

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    ulong il = 0;
    std::cout << "ulong: " << il-1 << '\n';

    // Convert string to array of digits
    std::vector<ulong> stones = stoia(input_lines[0]);
    std::cout << "Starting: " << '\n';
    for (ulong stone: stones)
        std::cout << stone << " ";
    std::cout << '\n';

    // Blink 25 times and update
    int blink_times = std::stoi(argv[2]);
    for (int i=0; i < blink_times; i++) {
        std::cout << "Iteration/blink: " << i+1 << '\n';
        
        // Change the stones according to the rules
        stones = change_stones(stones);            

        for (ulong stone: stones)
            std::cout << stone << " ";
        std::cout << '\n' << '\n';
    }

    std::cout << "Answer 1: " << stones.size() << std::endl;
    return 0;
}