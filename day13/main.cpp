// Day 13
// Advent of Code 2024
// 14-12-2024
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


// Find linear equation pairs -> create an array of size 3 with the X and Y components
std::pair<ulong, ulong> *str_to_arr(std::vector<std::string> *stringsPtr, int starting_index) {
    // Search for the digits
    std::regex digs("\\d+");
    std::smatch match1;     // Matching to two pairs of digits
    std::smatch match2;

    // There should be 3 lines with all two matches
    std::pair<ulong, ulong> *pairArr = new std::pair<ulong, ulong>[3];
    for (int i=starting_index; i<starting_index+3; i++) {
        // Find the digits in a string
        std::regex_search(stringsPtr->at(i), match1, digs);
        std::string suff = match1.suffix().str();
        std::regex_search(suff, match2, digs);

        // Append the digits to the array
        pairArr[i-starting_index] = {std::stoi(match1.str()), std::stoi(match2.str())};
    }

    return pairArr;
}

// Function to check if addition will overflow
bool willAdditionOverflow(unsigned int a, unsigned int b)
{
    return b > std::numeric_limits<unsigned int>::max() - a;
}

// Function to check if multiplication will overflow
bool willMultiplicationOverflow(unsigned int a,
                                unsigned int b)
{
    if (a == 0 || b == 0) {
        return false; // Multiplication with zero never
                      // overflows
    }
    return a > std::numeric_limits<unsigned int>::max() / b;
}


// Calculate the combination of A and B buttons to reach the result
ulong tokensNeeded(std::pair<ulong, ulong> *eqs) {
    // Results
    ulong vectR[2] = {eqs[2].first, eqs[2].second};

    // Matrix of vectors
    ulong vectA[2] = {eqs[0].first, eqs[0].second};
    ulong vectB[2] = {eqs[1].first, eqs[1].second};

    // Calculate alpha and beta from this
    
    ulong alpha = round(((double)vectR[1] - ((double)vectB[1] / (double)vectB[0]) * (double)vectR[0])/(((double)vectA[1] / (double)vectA[0])-((double)vectB[1] / (double)vectB[0]))/ (double)vectA[0]);
    ulong beta = (double)(vectR[0] - alpha*vectA[0]) / (double)vectB[0];
    
    // Check if beta is actually an integer number, otherwise leave at 0 (impossible state)
    if (willMultiplicationOverflow(alpha, (double)vectA[0]/(double) vectR[0])) std::cout << "OVERFLOW" << '\n';
    if (!((double)alpha*((double)vectA[0]/(double)vectR[0])+(double)beta*((double)vectB[0]/(double)vectR[0]) == 1)) return 0;
    std::cout << "aAx: " << alpha*vectA[0] << " & Beta: " << beta*vectB[0] << "=" << alpha*vectA[0]+beta*vectB[0] << '\n';
    std::cout << "result should be: " << vectR[0] << '\n';
    std::cout << "Alpha: " << alpha << " & Beta: " << beta << '\n';

    // if ( alpha <= 0 || beta <= 0) return 0;
    return 3*alpha + beta;
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

    // PART 2 variable
    ulong additionPt2 = 10000000000000;

    // Per 4 lines -> array of size 3 with ulong pairs
    ulong result = 0;
    for (size_t i=0; i<input_lines.size(); i+=4) {
        // Create an array of integer pairs to store the linear equations
        std::pair<ulong, ulong> *linEq_pairs = new std::pair<ulong, ulong>[3];
        linEq_pairs = str_to_arr(&input_lines, i);      // Get the array with the digits of the lin equations

        // PART 2: add addition of pt 2 to the result vector
        linEq_pairs[2].first += additionPt2;
        linEq_pairs[2].second += additionPt2;
        
        // Calculate the result
        std::cout << i/4+1 << ": \t" << linEq_pairs[0].first << "," << linEq_pairs[0].second << "|" << linEq_pairs[1].first << "," << linEq_pairs[1].second << '\n';
        ulong new_tokens = tokensNeeded(linEq_pairs);
        // if (new_tokens > 0) std::cout << i/4+1 << '\n';
        result += new_tokens;
        std::cout << "Runsum of result: " << result << '\n';
        // std::cout << '\n';
    }

    std::cout << "Answer 1: " << result << std::endl;
    return 0;
}

// 41331329 too low
// 314033368007 too low
// 314033366346 too low
// 99543406944928 too high
// 97921515885735 incorrect
// 99001608330460 incorrect
// 82535418533953 incorrect
// 91525080552802 incorrect