
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(octo)
set(octomap_DIR "/home/olaf/octomap/lib/cmake/octomap")

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(MSVC)
    set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(PCL_DIR "C:/dev/vcpkg/installed/x64-windows/share/pcl")
    set(EIGEN_INCLUDE_DIR "C:/dev/vcpkg/packages/eigen3_x64-windows/include/eigen3")
    set(Boost_INCLUDE_DIR "C:/dev/vcpkg/installed/x64-windows/include")
    set(FLANN_DIR "C:/dev/vcpkg/installed/x64-windows/share/flann")
    set(VTK_DIR "C:/dev/vcpkg/installed/x64-windows/share/vtk")
    set(lz4_DIR "C:/dev/vcpkg/installed/x64-windows/share/lz4")
    set(OpenCV_DIR "C:/dev/vcpkg/installed/x64-windows/share/opencv")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    set(PCL_DIR "/opt/pcl-pcl-1.11.1/build/")
endif()
find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${Eigen_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


find_package(octomap REQUIRED)
include_directories(${OCTOMAP_INCLUDE_DIRS})
link_directories(${OCTOMAP_LIBRARY_DIRS})
link_libraries(${OCTOMAP_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS})

add_executable(octoViewPts main.cpp)






