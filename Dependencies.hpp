#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Vec3>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/PolygonStipple>
#include <osg/TemplatePrimitiveFunctor>
#include <osg/TemplatePrimitiveIndexFunctor>
#include <osg/io_utils>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/TrackballManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>


#include <osg/Math>
#include <osg/Timer>
#include <iostream>

#include <osgFX/Outline>
#include <osgSim/DOFTransform>

#include <SDL.h>