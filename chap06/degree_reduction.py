#!/usr/bin/env python
# encoding: utf-8

import sys; sys.path.append("..")

import numpy as np

import bpy
from bpy.props import *

from blender_utils import replace_mesh

from common.bezier import DeCasteljauBezier

def draw_spline(context, o, name):
    pts = [ k.co for k in o.data.vertices]
    s = DeCasteljauBezier(*pts)
    ts = np.linspace(0,1,100)
    verts = [ tuple(s(t)) for t in ts ]
    replace_mesh(context, name, verts, related_obj = o)

def find_best_approximation(pts):
    n = len(pts) - 1
    if n <= 0:
        raise ValueError("No further dimensional reduction possible!")

    # Construct the Matrix
    M = np.zeros((n+1,n))
    M[0,0] = 1
    M[-1,-1] = 1
    for i in range(1,n):
        M[i,i-1] = i / (n+1)
        M[i,i] = 1 - i/(n+1)

    # Find the least squares solution
    K = np.dot(np.linalg.inv(np.dot(M.T,M)), M.T)

    pts = np.asarray(pts)
    print("K.shape: {}, pts.shape: {}".format(K.shape, pts.shape))

    return np.dot(K, pts)

def draw(obj, context):
    scn = bpy.context.scene
    o = context.selected_objects[0]

    draw_spline(context, o, o.name +  "_spline")

    pts = [k.co for k in o.data.vertices]
    new_pts = find_best_approximation(pts)

    new_poly = replace_mesh(context, o.name + "_reduced_poly", new_pts,
            [ (i-1,i) for i in range(1, len(new_pts)) ], related_obj = o)
    draw_spline(context, new_poly, new_poly.name + "_spline")


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
    bl_label = "Reduction of Spline degree"

    @classmethod
    def poll(self, context):
        if not context.selected_objects:
            return False

        obj = context.selected_objects[0]
        if (obj and obj.type == 'MESH' and "spline" not in obj.name):
                return True
        return False

    def draw(self, context):
        """Draw the Menu"""
        layout = self.layout

        scn = context.scene
        col = layout.column(align=True)

        col.prop(scn, 't')
        layout.operator("object.doit")

# Register the module so that the menu shows
bpy.utils.register_module(__name__)
