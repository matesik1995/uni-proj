#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import division             # Division in Python 2.7
import matplotlib
matplotlib.use('Agg')                       # So that we can render files without GUI
import matplotlib.pyplot as plt
from matplotlib import rc
import numpy as np
import math

from matplotlib import colors

def plot_color_gradients(gradients, names):
    # For pretty latex fonts (commented out, because it does not work on some machines)
    #rc('text', usetex=True) 
    #rc('font', family='serif', serif=['Times'], size=10)
    rc('legend', fontsize=10)

    column_width_pt = 400         # Show in latex using \the\linewidth
    pt_per_inch = 72
    size = column_width_pt / pt_per_inch

    fig, axes = plt.subplots(nrows=len(gradients), sharex=True, figsize=(size, 0.75 * size))
    fig.subplots_adjust(top=1.00, bottom=0.05, left=0.25, right=0.95)


    for ax, gradient, name in zip(axes, gradients, names):
        # Create image with two lines and draw gradient on it
        img = np.zeros((2, 1024, 3))
        for i, v in enumerate(np.linspace(0, 1, 1024)):
            img[:, i] = gradient(v)

        im = ax.imshow(img, aspect='auto')
        im.set_extent([0, 1, 0, 1])
        ax.yaxis.set_visible(False)

        pos = list(ax.get_position().bounds)
        x_text = pos[0] - 0.25
        y_text = pos[1] + pos[3]/2.
        fig.text(x_text, y_text, name, va='center', ha='left', fontsize=10)

    fig.savefig('my-gradients.pdf')


def hsv2rgb(h, s, v):
    h = float(h)
    s = float(s)
    v = float(v)
    h60 = h / 60.0
    h60f = math.floor(h60)
    hi = int(h60f) % 6
    f = h60 - h60f
    p = v * (1 - s)
    q = v * (1 - f * s)
    t = v * (1 - (1 - f) * s)
    r, g, b = 0, 0, 0
    if hi == 0: r, g, b = v, t, p
    elif hi == 1: r, g, b = q, v, p
    elif hi == 2: r, g, b = p, v, t
    elif hi == 3: r, g, b = p, q, v
    elif hi == 4: r, g, b = t, p, v
    elif hi == 5: r, g, b = v, p, q
    return r, g, b


def gradient_rgb_bw(v):
    return (v, v, v)


def gradient_rgb_gbr(v):
    if v<=0.5:
        return (0, 1-v*2, v*2)
    else:
        return (1-(1-v)*2, 0, (1-v)*2)
 

def gradient_rgb_gbr_full(v):
    if v <= 0.25:
        return (0, 1, v*4)
    elif v <= 0.5:
        return (0, (0.5-v)*4, 1)
    elif v <= 0.75:
        return ((v-0.5)*4, 0, 1)
    else:
        return (1, 0, (1-v)*4)
    return (0,0,0)


def gradient_rgb_wb_custom(v):
    if v <= 1.0/7: return (1,1 - v*7,1)
    elif v <= 2.0/7: return ((2.0/7 - v)*7, 0, 1)
    elif v <= 3.0/7: return (0, 1 - (3.0/7 - v)*7, 1)
    elif v <= 4.0/7: return (0, 1, (4.0/7 - v)*7)
    elif v <= 5.0/7: return (1 - (5.0/7 - v)*7, 1,0)
    elif v <= 6.0/7: return (1, (6.0/7 - v)*7, 0)
    else: return ((1- v)*7, 0,0)

def gradient_hsv_bw(v):
    return hsv2rgb(0, 0, v)


def gradient_hsv_gbr(v):
    return hsv2rgb(120+v*240, 1, 1)


def gradient_hsv_unknown(v):
    return hsv2rgb(120-v*120, 0.5, 1)


def gradient_hsv_custom(v):  #france
    if v<0.5:
    	return hsv2rgb(-v*120, 1-v*2, 1)
    else:
        return hsv2rgb(-v*120, v*2-1, 1)


if __name__ == '__main__':
    def toname(g):
        return g.__name__.replace('gradient_', '').replace('_', '-').upper()

    gradients = (gradient_rgb_bw, gradient_rgb_gbr, gradient_rgb_gbr_full, gradient_rgb_wb_custom,
                 gradient_hsv_bw, gradient_hsv_gbr, gradient_hsv_unknown, gradient_hsv_custom)

    plot_color_gradients(gradients, [toname(g) for g in gradients])
