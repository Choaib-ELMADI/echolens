import random

data = {
    "Set 0": [
        [68, -23, -13],
        [79, -13, 40],
        [-28, -1, 30],
        [29, -21, -33],
        [-8, -36, -16],
        [-26, 14, 36],
        [79, -38, -13],
        [78, -29, -6],
    ],
    "Set 10": [[3, -38, 59], [74, -25, 41]],
    "Set 11": [[77, -2, 51]],
}


def generate_random_colors():
    random_set = random.choice([0, 1])
    random_set_10_or_11 = None

    if random_set == 0:
        random_list = random.choice(data["Set 0"])
    else:
        random_set_10_or_11 = random.choice([10, 11])
        if random_set_10_or_11 == 10:
            random_list = random.choice(data["Set 10"])
        else:
            random_list = random.choice(data["Set 11"])

    return random_set, random_set_10_or_11, random_list


def get_limit_values(random_set, random_set_10_or_11):
    if random_set == 0:
        min_limit = 0
        max_limit = 200
    else:
        if random_set_10_or_11 == 10:
            min_limit = 0
        else:
            min_limit = 60
        max_limit = 255

    return min_limit, max_limit


if __name__ == "__main__":
    random_set, random_set_10_or_11, random_list = generate_random_colors()
    print(random_set, random_set_10_or_11, random_list)
    print(get_limit_values(random_set, random_set_10_or_11))
