# Day 5
# Advent of Code 2024
# 06-12-2024
# Timo van Beelen

import math

file_name = "day5/input.txt"


# Have a function that converts the rule lines in the file to a dict
def rules_to_dict(lines: list):
    # Output variable
    rules = {}

    # Go through the lines in the file
    for line in lines:
        if line == "\n": break      # If the line is empty, the rules are done
        line = line.strip()         # Strip the \n of the lines, it is not needed
        nums = line.split("|")      # Split the line into the nums

        # Add to the dict
        rules.setdefault(int(nums[0]), [])          # If key does not exist, make it an empty list as default
        rules[int(nums[0])].append(int(nums[1]))    # Add the number to the key

    return rules


# Create a list of manuals
def input_to_manual_list(lines: list):
    # Output variable
    manuals = []      # A list containing manuals containing integers

    # Go through each line
    for line in lines:
        if line == "\n" or "|" in line: continue    # Not manuals -> not needed -> just continue to the next
        line = line.strip()                         # Remove the \n from the line, it is of no use
        num_list = line.split(",")                  # Split the manual entries on comma

        nums = []                                   # Create a list of numbers
        for num in num_list: nums.append(int(num))  # Add each number to it as an int 
        manuals.append(nums)                        # Append the list to the manuals

    return manuals


# Check if a number adheres to the rules
def num_is_ok(num: int, checked: list, rules: dict):
    comes_after = rules.get(num)        # Get all the numbers that should come after the one being checked

    if comes_after is None: return True # If the key does not exist, it is also fine

    for i in comes_after:               
        if i in checked: return False   # If the number is after a number it should not be after, return false
    return True


# Check if a manual adheres to the rules
def adheres_to_rules(manual: list, rules: dict):
    # Go through each number in the manual and check if no items in the checked list appear before it
    checked  = []
    for i in manual:
        if num_is_ok(i, checked, rules):
            checked.append(i)
        else: return False

    return True


# Correct the order if wrong
def corrected_order(manual: list, rules: dict):
    # Create a return list where the numbers are in the correct order
    checked = []

    # For each number in the manual, check if in the correct place
    for num in manual:
        if num_is_ok(num, checked, rules): 
            checked.append(num)             # If in correct place, add to list and continue
            continue
        
        index = manual.index(num)           # Otherwise get the index
        manual.remove(num)                  # Remove from old place
        manual.insert(index-1, num)         # Insert in new place and try again
        return corrected_order(manual, rules)
    
    return checked


# Main program body
if __name__ == "__main__":
    # Read the contents of the file
    with open(file_name, "r") as input_file:
        input_lines = input_file.readlines()

    # Parse the input to have the rules and the manuals
    rules_dict  = rules_to_dict(input_lines)
    manuals = input_to_manual_list(input_lines)
    
    # For each manual check if it is OK and if so, add to result
    result = 0
    result2 = 0
    for manual in manuals:
        # Check if the manual adheres to the rules
        if not adheres_to_rules(manual, rules_dict): 
            manual = corrected_order(manual, rules_dict)
            result2 += manual[math.floor(len(manual)/2)]
        result += manual[math.floor(len(manual)/2)]
    
    print(result)
    print(result2)