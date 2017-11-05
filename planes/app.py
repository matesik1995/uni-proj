#!/usr/bin/env python
from matplotlib import pyplot as plt
from scipy import ndimage as ndi
from skimage import data, feature, morphology, filters, measure, draw
from skimage import img_as_float
from skimage.color import rgb2gray
import os

DATA_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "data/")

def main():
    plt.figure(figsize=(18, 6), dpi=200)
    files = [f for f in os.listdir(DATA_PATH) if os.path.isfile(os.path.join(DATA_PATH, f))]
    for nr, pic in enumerate(files):
        print("Processing image: " + str(nr).zfill(2))
        o_img = img_as_float(data.load(DATA_PATH+pic))
        img = rgb2gray(o_img)
        img = filters.sobel(img)
        img = feature.canny(img)
        img = morphology.dilation(img, selem=morphology.square(3))
        img = ndi.binary_fill_holes(img)
        contours = measure.find_contours(img, 0.9)
        plt.subplot(3, 6, nr + 1)
        m = max([len(c) for c in contours[:]])
        for contour in contours:
            if len(contour) < int(m / 5):
                continue
            rr, cc = draw.circle(sum(contour[:, 0]) / len(contour[:, 0]),
                                 sum(contour[:, 1]) / len(contour[:, 1]),
                                 int(max(max(contour[:, 0]) - min(contour[:, 0]),
                                         max(contour[:, 1]) - min(contour[:, 1])) / 20))
            o_img[rr, cc] = 1
            plt.plot(contour[:, 1], contour[:, 0], linewidth=1)
            plt.axis('off')
        plt.imshow(o_img)
    print("Generating output file")
    plt.savefig('planes.png', orientation='landscape', bbox_inches='tight')
    print("File \'planes.png\' created")
    plt.close()


if __name__ == "__main__":
    main()
