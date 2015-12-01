# -*- coding: utf-8 -*-
"""
Created on Wed Jun 17 12:34:31 2015

@author: luka
"""

try: paraview.simple
except: from paraview.simple import *
paraview.simple._DisableFirstRenderCameraReset()

RenderView1 = GetRenderView()

AnimationScene1 = GetAnimationScene()
AnimationScene1.AnimationTime = 3000.0

fine_OpenFOAM = GetActiveSource()
fine_OpenFOAM.VolumeFields = ['Cp', 'T', 'alphat', 'epsilon', 'k', 'kappa', 'mut', 'p', 'rho', 'U']
fine_OpenFOAM.MeshParts = ['internalMesh', 'symmetryPlane - group', 'wall - group', 'inlet - patch', 'outlet - patch', 'sideWall - patch', 'middlePlane - patch', 'hot - patch', 'cold - patch']

DataRepresentation1 = Show()

Calculator1 = Calculator()
Calculator1.Function = 'U_X'
Calculator1.ResultArrayName = 'Stream'

Slice1 = Slice( SliceType="Plane" )
Slice1.SliceOffsetValues = [0.0]
Slice1.SliceType.Origin = [9.999996647239e-05,0.00039999998989515007, 2.499999936844688e-05]
Slice1.SliceType.Normal = [1, 0, 0.0]

DataRepresentation2 = Show()

DataRepresentation1.Visibility = 0

Transform1 = Transform( Transform="Transform" )
Transform1.Transform = "Transform"
Transform1.Transform.Translate = [0.0, 0, 0.0]
Transform1.Transform.Scale = [1.0, 1.0, 1.0]
Transform1.Transform.Rotate = [0.0, 0.0, 0.0]

DataRepresentation3 = Show()
DataRepresentation2.Visibility = 0

Reflect1 = Reflect()
Reflect1.Plane = 'Y Min'

DataRepresentation4 = Show()
DataRepresentation3.Visibility = 0

a1_Stream_PVLookupTable = GetLookupTableForArray( 'Stream', 1, RGBPoints=[0.5, 0.0, 0.0, 1.0, 181.5, 1.0, 0.0, 0.0], VectorMode='Magnitude', NanColor=[0.498039, 0.498039, 0.498039], NumberOfTableValues=14, ColorSpace='HSV', ScalarRangeInitialized=1.0 )
a1_Stream_PiecewiseFunction = CreatePiecewiseFunction( Points=[0.5, 0.0, 0.5, 0.0, 181.5, 1.0, 0.5, 0.0] )
Stream_Isosurfaces =  [0.5, 13.428571428571427, 26.357142857142854, 39.285714285714285, 52.21428571428571, 65.14285714285714, 78.07142857142857, 91.0, 103.92857142857142, 116.85714285714286, 129.78571428571428, 142.71428571428572, 155.64285714285714, 168.57142857142856, 181.5]
DataRepresentation4.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation4.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation4.LookupTable = a1_Stream_PVLookupTable

Contour1 = Contour( PointMergeMethod="Uniform Binning" )
a1_Stream_PVLookupTable.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
Contour1.PointMergeMethod = "Uniform Binning"
Contour1.Isosurfaces = Stream_Isosurfaces
Contour1.ContourBy = ['POINTS', 'Stream']

DataRepresentation5 = Show()
DataRepresentation5.LookupTable = a1_Stream_PVLookupTable
DataRepresentation4.Visibility = 0
DataRepresentation5.ColorArrayName = ('POINT_DATA', '')
DataRepresentation5.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation4.Visibility = 1

Render()

# Second slice

SetActiveSource(Calculator1)

Slice2 = Slice( SliceType="Plane" )
Slice2.SliceOffsetValues = [0.0]
Slice2.SliceType.Origin = [0.006,0.00039999998989515007,  2.499999936844688e-05]
Slice2.SliceType.Normal = [1.0, 0.0, 0.0]

DataRepresentation6 = Show()

Transform2 = Transform( Transform="Transform" )
Transform2.Transform = "Transform"
Transform2.Transform.Translate = [0, -0.00012, 0.0]
Transform2.Transform.Scale = [1.0, 1.0, 1.0]
Transform2.Transform.Rotate = [0.0, 0.0, 0.0]
DataRepresentation7 = Show()
DataRepresentation6.Visibility = 0

Reflect2 = Reflect()
Reflect2.Plane = 'Y Min'

DataRepresentation8 = Show()
DataRepresentation7.Visibility = 0

DataRepresentation8.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation8.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation8.LookupTable = a1_Stream_PVLookupTable

Contour2 = Contour( PointMergeMethod="Uniform Binning" )
Contour2.PointMergeMethod = "Uniform Binning"
Contour2.Isosurfaces = Stream_Isosurfaces
Contour2.ContourBy = ['POINTS', 'Stream']

DataRepresentation9 = Show()
DataRepresentation9.LookupTable = a1_Stream_PVLookupTable
DataRepresentation9.ColorArrayName = ('POINT_DATA', '')
DataRepresentation9.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation8.Visibility = 1

Render()


# Third slice

SetActiveSource(Calculator1)

Slice3 = Slice( SliceType="Plane" )
Slice3.SliceOffsetValues = [0.0]
Slice3.SliceType.Origin = [ 0.012,0.00039999998989515007, 2.499999936844688e-05]
Slice3.SliceType.Normal = [1.0, 0.0, 0.0]
DataRepresentation10 = Show()

Transform3 = Transform( Transform="Transform" )
Transform3.Transform = "Transform"
Transform3.Transform.Translate = [0, -0.00024, 0.0]
Transform3.Transform.Scale = [1.0, 1.0, 1.0]
Transform3.Transform.Rotate = [0.0, 0.0, 0.0]

DataRepresentation11 = Show()
DataRepresentation10.Visibility = 0

Reflect3 = Reflect()
Reflect3.Plane = 'Y Min'

DataRepresentation12 = Show()
DataRepresentation11.Visibility = 0

DataRepresentation12.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation12.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation12.LookupTable = a1_Stream_PVLookupTable

Contour3 = Contour( PointMergeMethod="Uniform Binning" )
Contour3.PointMergeMethod = "Uniform Binning"
Contour3.Isosurfaces = Stream_Isosurfaces
Contour3.ContourBy = ['POINTS', 'Stream']

DataRepresentation13 = Show()
DataRepresentation13.LookupTable = a1_Stream_PVLookupTable
DataRepresentation13.ColorArrayName = ('POINT_DATA', '')
DataRepresentation13.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation12.Visibility = 1

Render()

# Fourth slice

SetActiveSource(Calculator1)
Slice4 = Slice( SliceType="Plane" )
Slice4.SliceOffsetValues = [0.0]
Slice4.SliceType.Origin = [0.018,0.00039999998989515007,  2.499999936844688e-05]
Slice4.SliceType.Normal = [1.0, 0.0, 0.0]

DataRepresentation14 = Show()

Transform4 = Transform( Transform="Transform" )
Transform4.Transform = "Transform"
Transform4.Transform.Translate = [0, -0.00036, 0.0]
Transform4.Transform.Scale = [1.0, 1.0, 1.0]
Transform4.Transform.Rotate = [0.0, 0.0, 0.0]

DataRepresentation15 = Show()
DataRepresentation14.Visibility = 0

Reflect4 = Reflect()
Reflect4.Plane = 'Y Min'

DataRepresentation16 = Show()
DataRepresentation15.Visibility = 0

DataRepresentation16.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation16.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation16.LookupTable = a1_Stream_PVLookupTable

Contour4 = Contour( PointMergeMethod="Uniform Binning" )
Contour4.PointMergeMethod = "Uniform Binning"
Contour4.Isosurfaces = Stream_Isosurfaces
Contour4.ContourBy = ['POINTS', 'Stream']

DataRepresentation17 = Show()
DataRepresentation17.LookupTable = a1_Stream_PVLookupTable
DataRepresentation17.ColorArrayName = ('POINT_DATA', '')
DataRepresentation17.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation16.Visibility = 1

Render()

# Fifth slice
SetActiveSource(Calculator1)

Slice5 = Slice( SliceType="Plane" )
Slice5.SliceOffsetValues = [0.0]
Slice5.SliceType.Origin = [0.024,0.00039999998989515007,  2.499999936844688e-05]
Slice5.SliceType.Normal = [1.0, 0.0, 0.0]

DataRepresentation18 = Show()

Transform5 = Transform( Transform="Transform" )
Transform5.Transform = "Transform"
Transform5.Transform.Translate = [0, -0.00048, 0.0]
Transform5.Transform.Scale = [1.0, 1.0, 1.0]
Transform5.Transform.Rotate = [0.0, 0.0, 0.0]

DataRepresentation19 = Show()
DataRepresentation18.Visibility = 0

Reflect5 = Reflect()
Reflect5.Plane = 'Y Min'

DataRepresentation20 = Show()
DataRepresentation19.Visibility = 0

DataRepresentation20.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation20.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation20.LookupTable = a1_Stream_PVLookupTable

Contour5 = Contour( PointMergeMethod="Uniform Binning" )
Contour5.PointMergeMethod = "Uniform Binning"
Contour5.Isosurfaces = Stream_Isosurfaces
Contour5.ContourBy = ['POINTS', 'Stream']

DataRepresentation21 = Show()
DataRepresentation21.LookupTable = a1_Stream_PVLookupTable
DataRepresentation21.ColorArrayName = ('POINT_DATA', '')
DataRepresentation21.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation20.Visibility = 1

Render()

# Sixth slice
SetActiveSource(Calculator1)

Slice6 = Slice( SliceType="Plane" )
Slice6.SliceOffsetValues = [0.0]
Slice6.SliceType.Origin = [0.0299,0.00039999998989515007, 2.499999936844688e-05]
Slice6.SliceType.Normal = [1.0, 0.0, 0.0]

DataRepresentation22 = Show()

Transform6 = Transform( Transform="Transform" )
Transform6.Transform = "Transform"
Transform6.Transform.Translate = [0, -0.0006, 0.0]
Transform6.Transform.Scale = [1.0, 1.0, 1.0]
Transform6.Transform.Rotate = [0.0, 0.0, 0.0]

DataRepresentation23 = Show()
DataRepresentation22.Visibility = 0

Reflect6 = Reflect()
Reflect6.Plane = 'Y Min'

DataRepresentation24 = Show()
DataRepresentation23.Visibility = 0

DataRepresentation24.ScalarOpacityFunction = a1_Stream_PiecewiseFunction
DataRepresentation24.ColorArrayName = ('POINT_DATA', 'Stream')
DataRepresentation24.LookupTable = a1_Stream_PVLookupTable

Contour6 = Contour( PointMergeMethod="Uniform Binning" )
Contour6.Isosurfaces = Stream_Isosurfaces
Contour6.ContourBy = ['POINTS', 'Stream']

DataRepresentation25 = Show()
DataRepresentation25.LookupTable = a1_Stream_PVLookupTable
DataRepresentation25.ColorArrayName = ('POINT_DATA', '')
DataRepresentation25.DiffuseColor = [0.0, 0.0, 0.0]

RenderView1.CameraParallelScale = 0.0010395213440635481

DataRepresentation24.Visibility = 1

Render()