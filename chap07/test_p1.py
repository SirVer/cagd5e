import unittest
import numpy as np
from numpy.testing import assert_almost_equal

from common.bezier import DeCasteljauBezier
from p1 import BlendInterpolation, AitkenLagrangeInterpolation

class TestBlendInterpolation(unittest.TestCase):
    def setUp(self):
        self.pts = np.asarray([ (0,0), (40.,20.), (50.,10), (60,20) ])
        self.ts = np.linspace(0,1,len(self.pts))
        self.dc = DeCasteljauBezier(*self.pts)
        self.aitken = AitkenLagrangeInterpolation(self.ts, self.pts)

        self.bi_dc = BlendInterpolation(1., self.ts, self.pts)
        self.bi_aitken = BlendInterpolation(0., self.ts, self.pts)

    def _do_test(self, val):
        gt = self.dc(val)
        assert_almost_equal(gt, self.bi_dc(val))
        gt = self.aitken(val)
        assert_almost_equal(gt, self.bi_aitken(val))

    def test1(self): self._do_test(0.12)
    def test2(self): self._do_test(0.33)
    def test3(self): self._do_test(0.76)
    def test4(self): self._do_test(0.09)
    def test5(self): self._do_test(0.41)


