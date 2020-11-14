import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

TABLE_SIZE = 13
PRIME = 7


def hash(x, y):
    return (y % TABLE_SIZE + x * (PRIME - (y % PRIME))) % TABLE_SIZE


if __name__ == '__main__':
    x = np.arange(-13, 14)
    y = np.arange(-1, 2)
    X, Y = np.meshgrid(x, y)
    Z = hash(X, Y)
    ax = plt.axes(projection='3d')
    ax.plot_surface(X, Y, Z)
    plt.show()
