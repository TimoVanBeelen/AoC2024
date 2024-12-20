// Day 17
// Advent of Code 2024
// 18-12-2024
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


// String to int array
std::vector<int> str_to_arr(std::string input) {
    // Search for the digits and append to a vector
    std::regex digs("\\d+");
    std::smatch match;
    std::vector<int> codes;
    codes.reserve((input.size()-9)/2);      // Rough guess of the size

    // See if there are any matches in the input string and output these
    while(std::regex_search(input, match, digs)) {
        codes.push_back(std::stoi(match[0].str()));
        input = match.suffix().str();
    }

    return codes;
}


// Get the integer number to perform the operation with (l_Operand) from the registers/combo operands (c_Operand)
int ctol_operands(int *regs, int c_Operand) 
{
    if (c_Operand == 7)                                 // Check if the operand is valid
    {                                 
        std::cout << "Not a valid program" << '\n';     // If so, return error message
        exit(999);                                      // And exit
    }

    int l_Operand = c_Operand;                          // General case (for c_Operand <= 3) 
    if (c_Operand > 3) l_Operand = regs[c_Operand-4];   // If the operand is bigger than 3, get the according register

    return l_Operand;   
}



// Perform a division on register A and store in register A
int adv (int *regs, int c_Operand) 
{
    int l_Operand = ctol_operands(regs, c_Operand);     // Get the literal operand
    return regs[0]/pow(2, l_Operand);                   // Return the result
}


// Calculate the bitwise XOR of register B and store in register B
int bxl (int regB, int l_Operand)                       
{
    return regB xor l_Operand;                           
}   


// Calculate the value of the combo operand modulo 8 and write it to register B
int bst (int *regs, int c_Operand) 
{
    int l_Operand = ctol_operands(regs, c_Operand);
    return l_Operand % 8;
}


// Check if there should be a jump in the opcode, if return the l_Operand to set the pointer to else return -1
int jnz (int regA, int l_Operand)
{
    if (regA == 0) return -1;
    return l_Operand;
}


// Returns the blx operand for register B and register C
int bxc (int regB, int regC) 
{
    return bxl(regB, regC);
}


// Outputs the value of the c_Operand modulo 8
void out (int *regs, int c_Operand, std::vector<int> *output)
{  
    output->push_back(ctol_operands(regs, c_Operand)%8);
}


// Matching vectors
bool vectMatch(std::vector<int> *vectA, std::vector<int> *vectB)
{   
    for (size_t n=0; n<vectA->size(); n++)
    {
        if (vectA->at(n) != vectB->at(n)) return false;
    }
    return true;
}


// Execute program
bool execute_program(int *regs, std::vector<int> *prog_input)
{   
    std::vector<int> output;
    for (size_t i=0; i < prog_input->size(); i+=2) 
    {
        int opcode = prog_input->at(i);
        int operand = prog_input->at(i+1);
        int jump;
        
        switch (opcode)
        {
        case 0:
            regs[0] = adv(regs, operand);
            break;
        
        case 1:
            regs[1] = bxl(regs[1], operand);
            break;
        
        case 2:
            regs[1] = bst(regs, operand);
            break;
        
        case 3:
            jump = jnz(regs[0], operand);
            if (jump != -1) i = jump-2;
            break;

        case 4:
            regs[1] = bxc(regs[1], regs[2]);
            break;

        case 5:
            out(regs, operand, &output);
            break;

        case 6:
            regs[1] = adv(regs, operand);
            break;
        
        case 7:
            regs[2] = adv(regs, operand);
            break;
        
        default:
            std::cout << "Opcode is not a 3-bit digit" << std::endl;
            exit(999);
        }

        if (output.size() < prog_input->size()) continue;       // See if there is still more to come
        else if(vectMatch(&output, prog_input)) return true;    // Found it!
        else return false;                                      // Output bigger than input, never gonna be ok
    }

    return false;
}


// Function to check if addition will overflow
bool willAdditionOverflow(unsigned int a, unsigned int b)
{
    return b > std::numeric_limits<unsigned int>::max() - a;
}


// Main program body
int main(int argc, char *argv[]) 
{
    // Check if there are enough arguments
    if (argc < 2) {
        std::cout << "Not enough input arguments" << '\n';
        return 0;
    }

    // Load the input data
    std::vector<std::string> input_lines =  read_file(argv[1]);

    // Initialize the 3 registers
    int *regs = new int[3];
    for (int i=0; i<3; i++)
        regs[i] = str_to_arr(input_lines[i]).at(0);
    
    // Get the code array and execute the program
    std::vector<int> prog_input = str_to_arr(input_lines[4]);
    
    // Loop through higher iterating values of i and check whether the output is the program input
    ulong res = 0;
    for (ulong i = pow(2, prog_input.size()); !willAdditionOverflow(i, 2); i+= 8) 
    {
        regs[0] = i;
        std::cout << "Set reg A to: " << i << '\n';                                                // Set register A to i
        if (execute_program(regs, &prog_input))
        {
            res = i;
            break;                                                  // Breaks if output == input
        } 
    }

    std::cout << "Answer pt 2: " << pow(2, prog_input.size()) << std::endl;

}