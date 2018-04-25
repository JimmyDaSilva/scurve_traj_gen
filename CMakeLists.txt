cmake_minimum_required(VERSION 2.8.3)
project(scurve_traj_gen)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

# Add catkin support
find_package(catkin QUIET)
if(${catkin_FOUND})
    catkin_package(
        INCLUDE_DIRS include
        LIBRARIES SCurveProfile
    )
else()
    set(CATKIN_PACKAGE_INCLUDE_DESTINATION include/${PROJECT_NAME})
    set(CATKIN_PACKAGE_LIB_DESTINATION lib)
    set(CATKIN_PACKAGE_BIN_DESTINATION bin)
endif()

# Compile the SCurveProfile library
include_directories(include)
add_library(SCurveProfile src/SCurveProfile.cpp)
install(TARGETS SCurveProfile DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

# Compile viewer if found
find_package(Qt5 QUIET COMPONENTS Core Gui Charts Widgets)
if(${Qt5_FOUND})
    message(STATUS "Building SCurveQtViewer with qt5")

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC_COMPILER_PREDEFINES OFF)
    set(CMAKE_AUTOMOC ON)
    
    add_executable(SCurveQtViewer src/SCurveQtViewer.cpp src/SCurveQtWidget.cpp)

    target_link_libraries(SCurveQtViewer SCurveProfile Qt5::Charts Qt5::Widgets)
    install(TARGETS SCurveQtViewer DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
else()
    message(STATUS "qt5 not found, not building SCurveQtViewer")
endif()
