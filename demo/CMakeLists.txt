# Enable AUTOMOC for this directory
set(CMAKE_AUTOMOC ON)# Set the source files for vortex-demo

file(GLOB DEMO_SOURCES "src/*.cpp")

# Add the shared library target
add_executable(vortex-demo ${DEMO_SOURCES})

# Include directories
target_include_directories(vortex-demo PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${LAYERS_DIR}/include"
)

target_link_libraries(vortex-demo PRIVATE
    VortexCore VortexWidgets
    $<$<CONFIG:Debug>:${LAYERS_LIBRARY_DEBUG}>
    $<$<CONFIG:Release>:${LAYERS_LIBRARY_RELEASE}>
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::Network
)

# Install rules
install(TARGETS vortex-demo DESTINATION lib)
install(DIRECTORY include/Vortex DESTINATION include)

# Set output directory
set_target_properties(vortex-demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

if(WIN32)
    # Copy Layers DLL
    add_custom_command(TARGET vortex-demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Layers DLL to VortexDemo output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${LAYERS_DIR}/bin/Layersd.dll,${LAYERS_DIR}/bin/Layers.dll>
            $<TARGET_FILE_DIR:vortex-demo>
    )
    
    # Copy VortexCore DLL
    add_custom_command(TARGET vortex-demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying VortexCore DLL to VortexDemo output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${CMAKE_SOURCE_DIR}/bin/Debug/VortexCored.dll,${CMAKE_SOURCE_DIR}/bin/Release/VortexCore.dll>
            $<TARGET_FILE_DIR:vortex-demo>
    )
    
    # Copy VortexWidgets DLL
    add_custom_command(TARGET vortex-demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying VortexWidgets DLL to VortexDemo output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${CMAKE_SOURCE_DIR}/bin/Debug/VortexWidgetsd.dll,${CMAKE_SOURCE_DIR}/bin/Release/VortexWidgets.dll>
            $<TARGET_FILE_DIR:vortex-demo>
    )
endif()