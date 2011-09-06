#!/usr/bin/env python
# encoding: utf-8

import numpy as np

from p1 import AitkenLagrangeInterpolation, BlendInterpolation

f = lambda x: 1./(1 + x*x)

def plot():
    from matplotlib import pyplot as plt

    func_fig = plt.figure(1); func_fig.clf()
    diff_fig = plt.figure(2); diff_fig.clf()
    func_ax = func_fig.add_subplot(111)
    diff_ax = diff_fig.add_subplot(111)

    # Fist, plot the function as is
    fine_ts = np.linspace(-1,1,1000)
    func_ax.plot(fine_ts, f(fine_ts), 'r-')

    for x in [11, 17, 27, 40]:
        # Find the sample points
        ts = np.linspace(-1,1,x)
        pts = f(ts)
        # Interpolate with aitken
        aitken = AitkenLagrangeInterpolation(ts, pts)
        interpolated = [ aitken(t) for t in fine_ts ]

        # Plot
        l, = func_ax.plot(ts, pts, 'x')
        diff_ax.plot(ts, pts - [aitken(t) for t in ts], 'x', color=l.get_color())

        func_ax.plot(fine_ts, interpolated, '-', color=l.get_color())
        diff_ax.plot(fine_ts, interpolated - f(fine_ts), color=l.get_color())

    plt.show()

if __name__ == '__main__':
    plot()
