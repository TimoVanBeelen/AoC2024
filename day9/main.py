# Day 7
# Advent of Code
# 07-12-12024
# Timo van Beelen

import math

file_name = "input.txt"


def append_n_times(append_to: list, num: int, repeats: int):
    for i in range(repeats):
        append_to.append(num)
    return append_to


if __name__ == "__main__":
    # Read the input file
    with open(file_name, "r") as file:
        input_lines = file.readlines()

    int_arr = []
    for i in input_lines[0]:
        int_arr.append(int(i))

    id = 0
    print("starting")
    shuffled_sys = []
    for i in range(0, len(int_arr)):
        # For even numbers append the id an int_arr[i] times
        if i%2==0: 
            shuffled_sys = append_n_times(shuffled_sys, id, int_arr[i])
            id += 1
        # For odd numbers, add from back
        else:
            shuffled_sys = append_n_times(shuffled_sys, None, int_arr[i])

    i=0
    for item in shuffled_sys:
        # Remove trailing free space
        for n in shuffled_sys[::-1]:
            if n != None: break
            del shuffled_sys[-1]

        # Insert from the back at free space
        if item is None:
            try:
                del shuffled_sys[i]
                shuffled_sys.insert(i, shuffled_sys[-1])
                del shuffled_sys[-1]
            except IndexError: break
        i += 1
    
    runsum = 0
    for i in range(0, len(shuffled_sys)):
        runsum += shuffled_sys[i]*i

    print(runsum)

# Try 1: 6288599492129