import csv

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rc
from matplotlib.ticker import FuncFormatter

PLOTS_COUNT = 5
PLOT_DATA = ("data/rsel.csv", "data/cel.csv", "data/cel-rs.csv", "data/2cel.csv", "data/2cel-rs.csv")
PLOT_NAME = ("1-Evol-RS", "1-Coev", "1-Coev-RS", "2-Coev", "2-Coev-RS")
PLOT_LINE_STYLE = ("r-o", "b-v", "c-s", "m-h", "y-p")


def get_data_from_file(path):
    score = []
    mean = []
    with open(path) as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            if row[0] == "generation":
                continue
            score.append(int(row[1]))
            mean.append(np.mean([float(x) for x in row[2:]]))
    return score, mean


def get_last_row_from_file(path):
    lastrow = None
    with open(path) as csvfile:
        lastrow = None
        for lastrow in csv.reader(csvfile, delimiter=','):
            pass
    return [float(x) for x in lastrow[2:]]


def generate_linear_plot(fig):
    sub = fig.add_subplot(121)

    for n in range(PLOTS_COUNT):
        games_played, games_won = get_data_from_file(PLOT_DATA[n])
        sub.plot(games_played, games_won, PLOT_LINE_STYLE[n], label=PLOT_NAME[n], lw=1, markevery=0.2, ms=5, mec='k',
                 mew=1)

    sub.xaxis.set_major_formatter(FuncFormatter(lambda x, pos: int(x / 1000)))
    sub.yaxis.set_major_formatter(FuncFormatter(lambda x, pos: int(x * 100)))
    sub.set_xlabel("Rozegranych gier (x1000)")
    sub.set_ylabel("Odsetek wygranych gier [%]")
    sub.axis([0, 500000, 0.6, 1])

    topy = sub.twiny()
    topy.set_xticks(range(0, 201, 40))
    topy.set_xlabel("Pokolenie")

    sub.legend(numpoints=2)
    sub.grid(linestyle='--')


def generate_box_plot(fig):
    sub = fig.add_subplot(122)
    dataset = []
    for n in range(PLOTS_COUNT):
        dataset.append(get_last_row_from_file(PLOT_DATA[n]))

    sub.boxplot(dataset, notch=True, showmeans=True,
                meanprops={'marker': 'o', 'markeredgecolor': 'black', 'markerfacecolor': 'blue'},
                boxprops={'color': 'blue'},
                medianprops={'color': 'red'},
                capprops={'color': 'black'},
                whiskerprops={'color': 'blue', 'linestyle': '-.'},
                flierprops={'marker': '+'}
                )
    sub.yaxis.set_major_formatter(FuncFormatter(lambda x, pos: int(x * 100)))
    sub.yaxis.tick_right()
    sub.set_xticklabels(PLOT_NAME, rotation=25)
    sub.axis([0.5, 5.5, 0.6, 1])
    sub.grid(ls='--')


def main():
    rc('font', **{'family': 'serif', 'serif': ['Consolas']})
    fig = plt.figure(figsize=(6, 5))
    # fig.suptitle('Laboratorium: Python i wizualizacja')
    generate_linear_plot(fig)
    generate_box_plot(fig)
    # plt.show()
    fig.savefig('myplot.pdf')
    plt.close()


if __name__ == '__main__':
    main()
