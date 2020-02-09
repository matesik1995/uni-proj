from math import sqrt


def mean(a):
    sum = 0
    items = 0
    for i in a:
        if i != -1:
            sum += i
            items += 1
    return sum/items


def calculate_numerator(a, b):
    result = 0
    for x,y in zip(a,b):
        if x != -1 and y != -1:
            result += (x - mean(a)) * (y - mean(b))
    return result


def calculate_length(a):
    result = 0
    for x in a:
        if x != -1:
            result += pow(x - mean(a),2)
    return sqrt(result)


def calculate_all(a, b):
    numerator = calculate_numerator(a,b)
    denominator = calculate_length(a)*calculate_length(b)
    return numerator/denominator


a = [4,3,4,-1,-1,1]
b = [4,1,2,2,-1,1]
c = [4,-1,-1,3,1,-1]
d = [1,4,2,-1,4,-1]
e = [1,-1,3,1,3,2]


print('a ~ b = ' + str(calculate_all(a, b)))
print('a ~ b = ' + str(calculate_all(a, c)))
print('a ~ b = ' + str(calculate_all(a, d)))
print('a ~ b = ' + str(calculate_all(a, e)))
