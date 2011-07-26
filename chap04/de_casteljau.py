#!/usr/bin/env python
# encoding: utf-8

import sys; sys.path.append("..")

import numpy as np

import bpy
from bpy.props import *

from blender_utils import replace_mesh

"""
Uses the the casteljau alogrithm to Plot Bezier Curves of points
"""

class DeCasteljau:
    def __init__(self, *pts, func = lambda t: t):
        self._b = np.asarray(pts, dtype=np.float64)
        self._func = func

    def __call__(self, t):
        b, n = self._b, len(self._b)
        for r in range(1,n):
            for i in range(n-r):
                b[i] = (1-self._func(t))*b[i]+self._func(t)*b[i+1]

        return b[0]

def draw(obj, context):
    o = context.selected_objects[0]

    for func, new_name in (
            (lambda t: t, "spl"),
            (lambda t: t**3, "spl_t3"),
            (lambda t: t**6, "spl_t6"),
            (lambda t: np.sin(t), "spl_sint"),
            (lambda t: np.cos(t), "spl_cost"),
            (lambda t: t - 2.5, "spl_trans"),
    ):
        spline = DeCasteljau(*[ k.co for k in o.data.vertices], func = func)
        ts = np.linspace(0,1, obj['tsteps'])
        verts = [ tuple(spline(t)) for t in ts ]

        replace_mesh(context, new_name, verts, related_obj = o)


class VIEW3D_PT_3dnavigationPanel(bpy.types.Panel):
    """This is the class that displays GUI elements"""

    bl_space_type = "VIEW_3D"
    bl_region_type = "TOOLS"
    bl_label = "Spline Visualizer"

    @classmethod
    def poll(self, context):
        """
        This method returns True when a Mesh object with exactly 3 points
        is selected; only than will the menu be shown
        """
        if not context.selected_objects:
            return False

        obj = context.selected_objects[0]
        if (obj and obj.type == 'MESH' and len(obj.data.vertices) >= 3 and "spline" not in obj.name):
                return True
        return False

    def draw(self, context):
        """Draw the Menu"""
        layout = self.layout

        scn = context.scene
        col = layout.column(align=True)

        col.prop(scn, 'tsteps')

def initSceneProperties(scn):
    """Set the properties up, this seems to be the canoncial way to do it"""
    bpy.types.Scene.tsteps = IntProperty(
        name = "tsteps",
        description = "Deltas between steps",
        default = 10,
        min = 1,
        max = 100,
        update = draw
    )
initSceneProperties(bpy.context.scene)

# Register the module so that the menu shows
bpy.utils.register_module(__name__)
