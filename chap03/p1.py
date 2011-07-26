#!/usr/bin/env python
# encoding: utf-8

import sys; sys.path.append("..")

import numpy as np

import bpy
from bpy.props import *

from blender_utils import replace_mesh

"""
Draw the blossom as points in Blender
"""

class Blossom(object):
    "The basic blossom. Defined by tree points"

    def __init__(self, p1, p2, p3):
        self._pts = np.asarray([p1, p2, p3])

    def __call__(self, t, s):
        return np.dot((
            (1-t)*(1-s),
            (1-t)*s+t*(1-s),
            s*t),
            self._pts)

def draw(obj, context):
    """Always called when one of the parameters changes. Removes
    any existing Blossom object and redraws it. Uses the currently
    selected object as the 3 Points to interpolate in between.

    The z coordinate is ignored
    """
    # Use the currently selected object as the 3 Points to interpolate in between
    new_name = context.select_objects[0].name + "_blossom"

    # Generate the vertices for the Blossom
    b = Blossom(*[(p.co[0],p.co[1]) for p in o.data.vertices])
    ts = np.linspace(0,1, obj['tsteps'])
    ss = np.linspace(0,1, obj['ssteps'])
    verts = [ tuple(b(s,t)) + (0,) for s in ss for t in ts ]

    replace_mesh(context, new_name, verts, related_obj = o)


class VIEW3D_PT_3dnavigationPanel(bpy.types.Panel):
    """This is the class that displays GUI elements"""

    bl_space_type = "VIEW_3D"
    bl_region_type = "TOOLS"
    bl_label = "Blossom Visualizer"

    @classmethod
    def poll(self, context):
        """
        This method returns True when a Mesh object with exactly 3 points
        is selected; only than will the menu be shown
        """
        if not context.selected_objects:
            return False

        obj = context.selected_objects[0]
        if (obj and obj.type == 'MESH' and len(obj.data.vertices) == 3):
                return True
        return False

    def draw(self, context):
        """Draw the Menu"""
        layout = self.layout

        scn = context.scene
        col = layout.column(align=True)

        col.prop(scn, 'tsteps')
        col.prop(scn, 'ssteps')

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
    bpy.types.Scene.ssteps = IntProperty(
        name = "ssteps",
        description = "Deltas between steps",
        default = 10,
        min = 1,
        max = 100,
        update = draw
    )
initSceneProperties(bpy.context.scene)

# Register the module so that the menu shows
bpy.utils.register_module(__name__)
