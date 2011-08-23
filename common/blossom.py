#!/usr/bin/env python
# encoding: utf-8

import numpy as np

__all__ = ["Blossom"]

class Blossom:
    def __init__(self, *pts):
        self._b = np.asarray(pts, dtype=np.float64)

    def __call__(self, *ts):
        ts = np.asarray(ts)
        if len(ts)+1 != len(self._b):
            raise RuntimeError("Invalid number of ts given!")

        b, n = self._b.copy(), len(self._b)
        for t,r in zip(ts,range(1,n)):
            for i in range(n-r):
                b[i] = (1-t)*b[i]+t*b[i+1]
        return b[0]

    def derivative(self, n = 1):
        """Returns the derivative of this blossom"""
        assert(n == 1)

        pts = np.empty((len(self._b)-1,) + self._b.shape[1:], dtype=self._b.dtype)
        for i in range(len(pts)):
            pts[i] = self._b[i+1] - self._b[i]
        pts *= len(self._b)-1 # degree
        return Blossom(*pts)


