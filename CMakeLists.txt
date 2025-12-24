cmake_minimum_required(VERSION 3.22)
project(Vortex VERSION 0.1.0)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LAYERS_DIR $ENV{Layers})

# if(WIN32)
set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/Layersd.lib")
set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/Layers.lib")
# else()
#     set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/libLayersd.dylib")
#     set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/libLayers.dylib")
# endif()

# Find Qt modules
find_package(Qt6 6.9.1 COMPONENTS Core Gui Widgets Svg Network REQUIRED)

# Add subdirectories
add_subdirectory(core)
add_subdirectory(widgets)
add_subdirectory(demo)
# add_subdirectory(colors)
