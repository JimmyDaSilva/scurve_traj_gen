cmake_minimum_required(VERSION 2.8.3)
project(scurve_traj_gen)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

## Hardcoded QT5 path ... Bad !
set(CMAKE_PREFIX_PATH "/opt/Qt/5.8/gcc_64/lib/cmake")

find_package(Qt5 REQUIRED COMPONENTS Core Gui Charts Widgets)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES scurve_traj_gen
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(SCurveProfile src/SCurveProfile.cpp)

add_executable(SCurveQtViewer src/SCurveQtViewer.cpp src/SCurveQtWidget.cpp)

target_link_libraries(SCurveQtViewer
  ${catkin_LIBRARIES}
  SCurveProfile
  Qt5::Charts
  Qt5::Widgets
)