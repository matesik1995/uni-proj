import matplotlib.pyplot as plt
import numpy as np
import colorsys as clr
from matplotlib import rc
import matplotlib
matplotlib.use('Agg')  

def load_data(path):
    first = []
    rest = []
    with open(path, 'r') as file:
        first.extend([int(x) for x in file.readline().split()])
        for line in file:
            rest.append([float(x) for x in line.split()])
    return first, rest 


def generate_map(sub, size, data):
    img = np.zeros((size[0], size[1], 3))

    #normalize data values
    max = np.amax(data)
    min = np.amin(data)
    diff = max-min
    data -= min
    data /= diff

    for i in range(len(data)):
        for j in range(len(data[i])):    
            # v = data[i][j]
            img[i,j] = gradient(data[i, j], data[i, j-1], data[i-1,j])
    
    sub.imshow(img, aspect='auto')


def gradient(p, dl, dt):
    h = 1/3 - p/3
    s = 1
    v = 1

    diff = (p-dl)*4
    if diff > 0:
        s-=diff
    else:
        v+=diff

    diff = (p-dt)*4
    if diff > 0:
        s-=diff
    else:
        v+=diff

    return clr.hsv_to_rgb(h, s, v)


def main():
    size, data = load_data("big.dem")
    fig = plt.figure(figsize=(7, 7))
    generate_map(fig.add_subplot(111), size, data)
    fig.savefig('map.pdf')
    plt.show()
    plt.close()


if __name__ == '__main__':
    main()
