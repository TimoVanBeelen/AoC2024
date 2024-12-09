// Day 8
// Advent of Code 2024
// 08-12-2024
// Timo van Beelen


// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


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


// Convert a string of integers to an array of integers
std::vector<int> stoi_arr(std::string s) {
    std::vector<int> result;            // Create a resulting variable
    for (char i: s) {
        result.push_back(i-'0');
    }
    return result;
}


// Append the vector with free space or numbers or smthing an i amount of times
std::vector<int> repeat_push(std::vector<int> v, int num, int repeats) {
    for (size_t i = 0; i < repeats; i++) {
        v.push_back(num);
    }
    return v;
}


// Put numbers in the free space
std::vector<int> fill_space(std::vector<int> v_out, std::vector<int> v_in, int repeats) {
    return v_out;
}


// Main program body
int main(int argc, char *argv[]) {
    // Read the file as a vector of strings
    std::vector<std::string> input_lines = read_file(argv[1]);

    // Convert the (input) string to an array of integers
    std::vector<int> int_arr = stoi_arr(input_lines[0]);
    int vect_len = int_arr.size();

    // Get the max ID a number can have
    int ID_MAX = vect_len/2;
    if (vect_len%ID_MAX==0) ID_MAX--;

    // Loop through all the elements and add -1 for free space, otherwise the ID the amount of times it appears
    int ID=0;
    std::vector<int> shuffled_sys;
    for (int i = 0; i < int_arr.size(); i++) {
        // If the number is even, add to vector int_arr[i] times:
        if (i%2==0){
            shuffled_sys = repeat_push(shuffled_sys, ID, int_arr[i]);
            ID++;
        }

        // If the number is odd:
        else {
            shuffled_sys = repeat_push(shuffled_sys, -1, int_arr[i]);
        }
    }

    for (int i=0; i<shuffled_sys.size(); i++) {
        // Remove trailing free space
        for (int n=shuffled_sys.size()-1; n>0; n--)  {
            if (shuffled_sys[n] != -1) break;
            shuffled_sys.erase(shuffled_sys.begin()+n);
        }

        // Insert from the back at free space
        if (shuffled_sys[i] == -1) {
            shuffled_sys[i] = shuffled_sys[shuffled_sys.back()];
            shuffled_sys.erase(shuffled_sys.end());
        }
    }
    
    // Print the resulting string
    for (int i=0; i < shuffled_sys.size(); i++) {
        std::cout << shuffled_sys.at(i);
    }

    // END
    std::cout<<std::endl;
    return 0;
}

