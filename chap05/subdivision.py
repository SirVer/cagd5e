#!/usr/bin/env python
# encoding: utf-8

import sys; sys.path.append("..")

import numpy as np

import bpy
from bpy.props import *

from blender_utils import replace_mesh

from common.blossom import Blossom
from common.bezier import DeCasteljauBezier


def draw_spline(context, o, name):
    pts = [ k.co for k in o.data.vertices]
    s = DeCasteljauBezier(*pts)
    ts = np.linspace(0,1,100)
    verts = [ tuple(s(t)) for t in ts ]
    replace_mesh(context, name, verts, related_obj = o)

def subdivision_polygon(context, pts, t, name):
    bl = Blossom(*pts)
    cis = []
    n = len(pts) - 1
    for i in range(n+1):
        ts = (0,)*(n-i) + (t,)*i
        cis.append(bl(*ts))

    verts = [ tuple(v) for v in cis ]
    edges = [ (i,i+1) for i in range(len(verts)-1) ]
    return replace_mesh(context, name, verts, edges)

def draw(obj, context):
    scn = bpy.context.scene
    o = context.selected_objects[0]
    pts = [ k.co for k in o.data.vertices]

    draw_spline(context, o, o.name +  "_main_spline")
    p0 = subdivision_polygon(context, pts, scn.t, o.name + "_p0")
    p0.matrix_world = o.matrix_world
    draw_spline(context, p0, o.name + "_s0")

    p1 = subdivision_polygon(context, pts[::-1], 1-scn.t, o.name + "_p1")
    p1.matrix_world = o.matrix_world
    draw_spline(context, p1, o.name + "_s1")

class OpDoIt(bpy.types.Operator):
    bl_idname = "object.doit"
    bl_label = "Do it!"

    def execute(self, context):
        draw(context.scene, context)
        return{'FINISHED'}


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

        col.prop(scn, 't')
        layout.operator("object.doit")

def initSceneProperties(scn):
    """Set the properties up, this seems to be the canoncial way to do it"""
    bpy.types.Scene.t = FloatProperty(
        name = "t",
        description = "Where to subdivide",
        default = .5,
        min = 0,
        max = 1,
        update = draw
    )
initSceneProperties(bpy.context.scene)

# Register the module so that the menu shows
bpy.utils.register_module(__name__)
