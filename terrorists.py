import math
from itertools import combinations
from random import random


def run(people_count, probability, hotel_count, days_number):
    pairs = {}
    for d in range(days_number):
        daily = {}
        for person in [a for a in range(people_count) if random() < probability]:
            hotel = int(random() * hotel_count)
            if hotel not in daily.keys():
                daily[hotel] = []
            daily[hotel].append(person)
        for hotel, guests in daily.items():
            for a, b in combinations(guests, 2):
                if str(a) + '_' + str(b) not in pairs:
                    pairs[str(a) + '_' + str(b)] = 0
                pairs[str(a) + '_' + str(b)] += 1

    pairs_count = 0
    pairs_sum = 0
    pairs_hist = {}
    unique_people = set()
    for pair, count in pairs.items():
        if count > 1:
            pairs_count += 1
            if count == 2:
                pairs_sum += 1
            else:
                pairs_sum += math.factorial(count)
            a, b, = pair.split('_')
            unique_people.add(a)
            unique_people.add(b)
        if count not in pairs_hist:
            pairs_hist[count] = 0
        pairs_hist[count] += 1

    # print(pairs_sum)
    # print(pairs_count)
    # pprint(pairs_hist)
    # print(len(unique_people))

    return [pairs_sum, pairs_count, len(unique_people)]


if __name__ == "__main__":
    x = 0
    y = 0
    z = 0
    for i in range(100):
        print(i)
        a, b, c = run(10000, 0.1, 100, 100)
        x += a
        y += b
        z += c
    print(x / 100, y / 100, z / 100)
