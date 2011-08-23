#!/usr/bin/env python
# encoding: utf-8

import unittest

import numpy as np
from numpy.testing import assert_almost_equal

from bezier import HornerBezier, DeCasteljauBezier, HornerPowerBezier

class SomeTestClass(unittest.TestCase):
    def setUp(self):
        self.pts = np.asarray([ (0,0), (40.,20.), (50.,10), (60,20) ])
        self.hz = HornerBezier(*self.pts)
        self.hp = HornerPowerBezier(*self.pts)
        self.dc = DeCasteljauBezier(*self.pts)

    def _do_test(self, val):
        gt = self.dc(val)
        assert_almost_equal(gt, self.hz(val))
        assert_almost_equal(gt, self.hp(val))

    def test1(self): self._do_test(0.12)
    def test2(self): self._do_test(0.33)
    def test3(self): self._do_test(0.76)
    def test4(self): self._do_test(0.09)
    def test5(self): self._do_test(0.41)

if __name__ == '__main__':
   unittest.main()
   # k = SomeTestClass()
   # unittest.TextTestRunner().run(k)


