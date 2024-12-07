# Day 7
# Advent of Code
# 07-12-12024
# Timo van Beelen

import math

file_name = "input.txt"


# Find numbers as [total, [individuals]]
def get_nums(lines: list):
    numbers = []            # Resulting var
    for line in lines:      
        line = line.strip()                # Strip '\n' from each
        line = line.split(": ")      # Split on ": ", directly removing trailing space
        ans = int(line[0])          # Answer of sum is found on index 0
        line = line[1].split(" ")   # Split on " " for individual components
        nums = []                   # Create a list for the individual components
        for num in line: nums.append(int(num))
        numbers.append([ans, nums])

    return numbers


# Part 2: concatenate numbers
def concat(x: int, y: int):
    base10 = math.ceil(math.log10(y))
    return x*math.pow(10, base10)+y


# Check itterative with each last component being a summation and do this for all components before
def itteratively_correct(sum: list):
    # Check if the length of the components is appropriate to be checked
    if len(sum[1]) == 1 and int(sum[0]) == sum[1][0]: return True       # If last remaining item is same as total, it is correct
    elif len(sum[1]) <= 1: return False                                 # Otherwise: nah

    total = sum[0]
    components = sum[1]
    
    last_comp = components[-1]              # Get last component for use
    del components[-1]                      # Remove last part of components, as it is used
    comp_copy = components.copy()           # Python shenanigans

    tot_min = total-last_comp
    if total%last_comp > 0:                # Last item cannot be multiplications
        return itteratively_correct([tot_min, components])    # Check if the sum is correct

    if itteratively_correct([tot_min, components]): return True     # Try with using addition
    elif itteratively_correct([total/last_comp, comp_copy]): return True    # Try with using multiplication
    else: return False
    


if __name__ == "__main__":
    # Read the input file
    with open(file_name, "r") as file:
        input_lines = file.readlines()
    
    # Go through each line and get the nums from it
    nums = get_nums(input_lines)
    
    # Go through each sum and if the answer can be found, add the ans to the result
    result = 0
    for sum in nums:
        if itteratively_correct(sum):       # If correct, add to result
            result += sum[0]

    print("Answer 1: ", result)
