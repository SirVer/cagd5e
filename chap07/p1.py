#!/usr/bin/env python
# encoding: utf-8

import numpy as np

class AitkenLagrangeInterpolation:
    def __init__(self, ts, pts):
        """
        Interpolation of pts at t values in ts using Lagrange Interpolation. This
        uses Aitkens Algorithm
        """
        self._b = np.asarray(pts, dtype=np.float64)
        self._t = ts

    def __call__(self, t):
        b, n = self._b.copy(), len(self._b)
        for r in range(1,n):
            for i in range(n-r):
                ts = self._t
                w = (ts[i+r] - t) / (ts[i+r] - ts[i])
                b[i] =  w*b[i]+(1-w)*b[i+1]
        return b[0]


class BlendInterpolation:
    def __init__(self, alpha, ts, pts):
        """
        This class blends Bezier and Lagrange Interpolation using the Aitkens
        Algorithm and the De-Casteljau Algorithm. They are just so similar.

        alpha = 0: Aitken Algorith, Lagrange Interpolation
        alpha = 1: De-Casteljau Algorithm, Bezier Interpolation

        all alphas in R are funny to try.
        """
        self._b = np.asarray(pts, dtype=np.float64)
        self._t = ts
        self._alpha = alpha

    def __call__(self, t):
        b, n = self._b.copy(), len(self._b)
        for r in range(1,n):
            for i in range(n-r):
                a = self._alpha
                ts = self._t
                w = (a + (1.-a)* ts[i+r] - t) / (a + (1. - a)*(ts[i+r] - ts[i]))
                b[i] = w*b[i]+(1-w)*b[i+1]
        return b[0]

def plot():
    from matplotlib import pyplot as plt

    pts = np.asarray((
        (0,0),
        (0,2),
        (8,2),
        (4,0),
        (10,1)
    ))
    ts = np.linspace(0, 1, len(pts))
    fine_ts = np.linspace(0,1,100)

    fig = plt.figure(1); fig.clf()
    ax = fig.add_subplot(111)

    ax.plot([p[0] for p in pts], [p[1] for p in pts], 'o-')

    for alpha in np.linspace(0, 1, 4):
        b = BlendInterpolation(alpha, ts, pts)
        vals = [ b(t) for t in fine_ts ]
        ax.plot([p[0] for p in vals], [p[1] for p in vals], 'x-', label="%.2f" % alpha)

    ax.legend(loc="best")
    plt.show()

if __name__ == '__main__':
    plot()

