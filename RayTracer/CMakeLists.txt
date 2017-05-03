cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project( RayTracer )

set (OpenCV_DIR /home/cshome/s/stefanie/Public/opencv-3.2.0/build)
find_package( OpenCV REQUIRED )

add_executable( rayTracer 
Camera.cpp
Camera.h
Colour.cpp
Colour.h
Cone.cpp
Cone.h
Cylinder.cpp
Cylinder.h
Direction.cpp
Direction.h
Display.cpp
Display.h
LightSource.cpp
LightSource.h
Material.h
Matrix.cpp
Matrix.h
NonCopyable.h
Normal.cpp
Normal.h
Object.cpp
Object.h
PinholeCamera.cpp
PinholeCamera.h
Point.cpp
Point.h
PointLightSource.cpp
PointLightSource.h
Ray.h
RayIntersection.h
Scene.cpp
Scene.h
SceneReader.cpp
SceneReader.h
Sphere.cpp
Sphere.h
SpotLightSource.cpp
SpotLightSource.h
Transform.cpp
Transform.h
Vector.cpp
Vector.h
rayTracerMain.cpp
utility.h
)

target_link_libraries( rayTracer ${OpenCV_LIBS} )
