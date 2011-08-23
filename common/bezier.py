#!/usr/bin/env python
# encoding: utf-8

from __future__ import division

import numpy as np

from .blossom import Blossom

def _differences(coeff):
    diffs1 = coeff[::-1]

    degree = len(coeff) - 1
    for r in range(1,degree+1):
        for i in range(degree - r + 1):
            diffs1[i] = diffs1[i] - diffs1[i+1]

    return diffs1[::-1]

def _bez_to_power(bez):
    coeff = _differences(bez)

    coeff[0] = bez[0]
    i_factorial = 1
    n_r = 1
    degree = len(bez) - 1
    for i in range(1,degree+1):
        i_factorial = i_factorial * i
        n_r = n_r*(degree-i+1)
        coeff[i] = n_r*coeff[i] / i_factorial

    return coeff

class HornerPowerBezier:
    def __init__(self, *pts):
        self._coeffs = _bez_to_power(np.asarray(pts, dtype=np.float64))

    def __call__(self, t):
        aux = self._coeffs[-1]

        for d in self._coeffs[-2::-1]:
            aux = t*aux + d

        return aux

class HornerBezier:
    def __init__(self, *pts):
        self._b = np.asarray(pts, dtype=np.float64)

    def __call__(self, t):
        t1 = 1. - t
        fact = 1.
        n_choose_i = 1

        aux = self._b[0] * t1

        degree = len(self._b) - 1
        for i in range(1,degree):
            fact = fact * t
            n_choose_i = n_choose_i*(degree-i+1)/i
            aux = (aux + fact*n_choose_i*self._b[i])*t1
        aux = aux + fact*t*self._b[degree]

        return aux

class DeCasteljauBezier(Blossom):
    def __call__(self, t):
        ts = (t,)* (len(self._b) - 1)
        return Blossom.__call__(self, *ts)

