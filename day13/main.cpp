// Day 13
// Advent of Code 2024
// 13-12-2024
// Timo van Beelen

// Packages needed in the program
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <math.h>
#include <map>


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
std::pair<int, int> *str_to_arr(std::vector<std::string> *stringsPtr, int starting_index) {
    // Search for the digits
    std::regex digs("\\d+");
    std::smatch match1;     // Matching to two pairs of digits
    std::smatch match2;

    // There should be 3 lines with all two matches
    std::pair<int, int> *pairArr = new std::pair<int, int>[3];
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


// Function to calculate the presses
std::vector<int> iterateAlpha(int *vec1, int *vec2, int *res) {
    // Apply the buttons max 100 times
    std::vector<int> alphaVect;
    for (int i=0; i<100; i++) {
        // Try a value of alpha, if match -> correct alpha found
        if ((res[0]-i*vec1[0])/vec2[0] == (res[1]-i*vec1[1])/vec2[1]) {
            // std::cout << "Alpha option: " << i << '\n';
            int b = (res[0]-i*vec1[0])/vec2[0];
            if (vec1[0]*i+vec2[0]*b == res[0]) alphaVect.push_back(i);
        }
    }
    return alphaVect;
}


// Function to iterate over beta
std::vector<int> iterateBeta(int *vec1, int *vec2, int *res) {
    // Apply the buttons max 100 times
    std::vector<int> betaVect;
    for (int i=0; i<=100; i++) {
        // Try a value of alpha, if match -> correct alpha found
        if ((res[0]-i*vec2[0])/vec1[0] == (res[1]-i*vec2[1])/vec1[1]) {
            // std::cout << "Beta option: " << i << '\n';
            int a = (res[0]-i*vec2[0])/vec1[0];
            if (vec1[0]*a+vec2[0]*i == res[0]) betaVect.push_back(i);
        }
    }
    return betaVect;
}


// Calculate most efficient
int BfromA(std::vector<int> alpha, std::vector<int> beta) {
    int lowest = 3*alpha[0]+beta[0];
    for (size_t i=0; i<alpha.size(); i++) {
        int probe = 3*alpha[i] + beta[i];
        if (probe<lowest) lowest = probe;
    }

    return lowest;
}

int AfromB(int *vec1, int *vec2, int *res, std::vector<int> alpha) {
    std::vector<int> betaVect;
    betaVect.reserve(alpha.size());
    for (int a: alpha) {
        int b = (res[0]-a*vec2[0])/vec1[0];
        // std::cout << "A from B: " << b << "|" << a << '\n';
        betaVect.push_back(b);
    }

    int lowest = 3*alpha[0]+betaVect[0];
    for (size_t i=0; i<alpha.size(); i++) {
        int probe = 3*alpha[i] + betaVect[i];
        if (probe<lowest) lowest = probe;
    }

    return lowest;
}


// Calculate the combination of A and B buttons to reach the result
int tokensNeeded(std::pair<int, int> *eqs) {
    // Results
    int vectR[2] = {eqs[2].first, eqs[2].second};

    // Matrix of vectors
    int vectA[2] = {eqs[0].first, eqs[0].second};
    int vectB[2] = {eqs[1].first, eqs[1].second};

    // Calculate all possible A values
    std::vector<int> aVect = iterateAlpha(vectA, vectB, vectR);
    std::vector<int> bVect = iterateBeta(vectA, vectB, vectR);
    for (size_t i=0; i<aVect.size(); i++)
        std::cout << "It A ans: " << aVect.at(i) << '\n';
    // int Bstart = iterateBeta(vectA, vectB, vectR);
    // std::cout << "It B ans: " << Bstart << '\n';
    if (aVect.size() == 0 && bVect.size() != 0) return bVect.at(0);
    if (bVect.size() == 0 && aVect.size() != 0) return aVect.at(0);
    if (aVect.size() == 0 && bVect.size() == 0) return 0; 

    int resultA = BfromA(aVect, bVect); 
    // std::cout << "Result A: " << resultA << '\n'; 
    // int resultB = AfromB(vectA, vectB, vectR, bVect);
    // std::cout << "Result B: " << resultB << '\n'; 

    if (resultA < 0) return 0;
    return resultA;
    // if (resultA < resultB) return resultA;
    // else return resultB;
}


// Main program body
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        std::cout << "Not enough output arguments" << '\n';
        return 0;
    }

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Per 4 lines -> array of size 3 with ulong pairs
    int result = 0;
    for (size_t i=0; i<input_lines.size(); i+=4) {
        // Create an array of integer pairs to store the linear equations
        std::pair<int, int> *linEq_pairs = new std::pair<int, int>[3];
        linEq_pairs = str_to_arr(&input_lines, i);      // Get the array with the digits of the lin equations
        
        // Calculate the result
        std::cout << i/4+1 << ": \t" << linEq_pairs[0].first << "," << linEq_pairs[0].second << "|" << linEq_pairs[1].first << "," << linEq_pairs[1].second << '\n';
        result += tokensNeeded(linEq_pairs);

        // std::cout << "Runsum of result: " << result << '\n';
    }

    std::cout << "Answer 1: " << result << std::endl;
    return 0;
}