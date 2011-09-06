#!/usr/bin/env python
# encoding: utf-8

import numpy as np

from p1 import AitkenLagrangeInterpolation, BlendInterpolation

f = lambda x: 3*np.sin(np.pi*2/10 * x)

def plot():
    from matplotlib import pyplot as plt

    fig1 = plt.figure(1); fig1.clf()
    fig2 = plt.figure(2); fig2.clf()
    plot1 = fig1.add_subplot(111)
    plot2 = fig2.add_subplot(111)

    # Find some random points in the range 0..1, but somewhat nicely
    # sepearated
    xs = np.linspace(0,10,30) + (np.random.rand(30) - 0.5) * 2 / 10.
    pts = f(xs)
    fine_xs = np.linspace(0,10,1000)
    l, = plot1.plot(fine_xs, f(fine_xs), 'r-')
    plot2.plot(fine_xs, f(fine_xs), 'r-')
    plot1.plot(xs, pts, 'x', color=l.get_color())
    plot2.plot(xs, pts, 'x', color=l.get_color())

    # Plot the normal Interpolant
    aitken = AitkenLagrangeInterpolation(xs, pts)
    interpolated = [ aitken(t) for t in fine_xs ]
    plot1.plot(fine_xs, interpolated, '-')

    # Swap two points and plot in the other figure
    i, j = np.random.randint(0,len(xs), size=2)
    print "i: %s, j: %s" % (i,j )
    xs[i], xs[j] = xs[j], xs[i]
    aitken = AitkenLagrangeInterpolation(xs, pts)
    interpolated = [ aitken(t) for t in fine_xs ]
    plot2.plot(fine_xs, interpolated, '-')

    plot1.set_ylim(-3,3)
    plot2.set_ylim(-3,3)
    plt.show()

if __name__ == '__main__':
    plot()
