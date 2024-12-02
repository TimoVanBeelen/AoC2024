file_name = "day2/ref.txt"


def is_safe(nums):
    isIncreasing = False
    if (nums[0] < nums[1]): isIncreasing = True

    prev_num = None
    for num in nums:
        if isIncreasing and num < prev_num:
            return False
    return True


if __name__ == "__main__":
    # Open file and read lines
    with open(file_name, "r") as file:
        lines = file.readlines()

    safe_reports = 0

    for line in lines:
        line = line.strip()
        num_chars = line.split(' ')
        nums = []
        for char in num_chars:
            nums.append(int(char))
        print(nums)

    print("Answer 2: ")