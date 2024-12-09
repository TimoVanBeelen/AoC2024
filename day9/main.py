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

def part1(shuffled_sys, item, i):
    # Insert from the back at free space
    if item is None:
        try:
            del shuffled_sys[i]
            shuffled_sys.insert(i, shuffled_sys[-1])
            del shuffled_sys[-1]
            return shuffled_sys
        except IndexError: return shuffled_sys


def get_block_size(lst: list, id: int):
    size = 0
    for item in lst:
        if item == id: size +=1
    return size


def get_space_size(lst: list, index: int):
    size = 0
    for i in range(index, len(lst)):
        if lst[i] == lst[index]: size +=1
        else: break
    return size


def fill_space(lst: list, space_index: int, block_index: int, block_size: int):
    lst[space_index:space_index+block_size] = lst[block_index:block_index+block_size]
    for i in range(block_index, block_index+block_size): lst[i] = None 
    return lst


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


    not_changed = False
    prev_item = -1
    for item in shuffled_sys[::-1]:
        if item is prev_item: continue
        item_index = shuffled_sys.index(item)

        # # if item is none
        # if item is None:
            
        #     del shuffled_sys[-1]
        #     continue
        block_size = get_block_size(shuffled_sys, item)
        
        # Get information about space
        space = 0
        space_index = -1
        for i in range(0, item_index):
            if shuffled_sys[i] != None: continue
            space = get_space_size(shuffled_sys, i)
            if space >= block_size: 
                space_index = i
                break

        # No large enough space is found
        if space_index == -1: continue

        shuffled_sys = fill_space(shuffled_sys, space_index, shuffled_sys.index(item), block_size)
        prev_item = item

        

        

    
    runsum = 0
    for i in range(0, len(shuffled_sys)):
        if shuffled_sys[i] is None: continue
        runsum += shuffled_sys[i]*i

    print(runsum)