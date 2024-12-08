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
    return int(str(x)+str(y))


# Check the options itteratively
def is_correct_on_concat(sum: list):
    # print(sum)
    # Check if the running sum is equal to the final answer
    if len(sum[1]) <= 1:
        if sum[0] == sum[1][0]: return True
        else: 
            # print("FALSE")
            return False
    
    if sum[0] < sum[1][0]: return False

    # Split the input into the two parts
    components = sum[1]

    # Get the different options
    mult = components[0]*components[1]
    addition = components[0]+components[1]
    conc = concat(components[0], components[1])

    # Delete the two components used
    del components[0]
    del components[0]

    # Append the new value at the start
    mult_comp = components.copy()
    mult_comp.insert(0, mult)
    add_comp = components.copy()
    add_comp.insert(0, addition)
    conc_comp = components.copy()
    conc_comp.insert(0, conc)

    # Return the found value, itterate until an answer is found
    if is_correct_on_concat([sum[0], mult_comp]): return True
    elif is_correct_on_concat([sum[0], add_comp]): return True
    elif is_correct_on_concat([sum[0], conc_comp]): return True
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
        if is_correct_on_concat(sum):       # If correct, add to result
            result += sum[0]

    print("Answer: ", result)