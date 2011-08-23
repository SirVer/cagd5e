#!/usr/bin/env python
# encoding: utf-8

import sys

# Hack: Boilerplate so that Blender 2.5 finds my numpy installation.
bpath = "/usr/local/Cellar/python3/3.2.1/lib/python3.2/"
if bpath not in sys.path:
    sys.path.extend((bpath, bpath + "site-packages"))

import bpy
from bpy_extras import object_utils

def replace_mesh(context, name, verts, edges = [], faces = [], related_obj = None):
    # Remove the old object, if it exists.
    scn = context.scene
    for obj in scn.objects:
        if obj.name == name or obj.name.startswith(name + '.'):
            scn.objects.unlink(obj)
            bpy.data.objects.remove(obj)

    for mesh in bpy.data.meshes:
        if mesh.name == name or mesh.name.startswith(name + '.'):
            bpy.data.meshes.remove(mesh)

    # Generate a new object with the given vertices
    mesh = bpy.data.meshes.new(name)
    mesh.from_pydata(verts, edges, faces)
    mesh.update()
    no = object_utils.object_data_add(context, mesh, operator=None).object

    # Move the object to the same space as the original object
    if related_obj is not None:
        no.matrix_world = related_obj.matrix_world

        # Make sure to keep the frame object selected so that we can change the 
        # parameters again.
        for obj in bpy.context.selected_objects:
            obj.select = False
        related_obj.select = True

    return no



