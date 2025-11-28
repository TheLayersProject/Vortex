# Enable AUTOMOC for this directory
set(CMAKE_AUTOMOC ON)

# Set the resource compiler path based on configuration
if (WIN32)
    set(RESOURCE_COMPILER_DEBUG "${LAYERS_DIR}/bin/Debug/LayersResourceCompilerd.exe")
    set(RESOURCE_COMPILER_RELEASE "${LAYERS_DIR}/bin/Release/LayersResourceCompiler.exe")
else()
    set(RESOURCE_COMPILER_DEBUG "${LAYERS_DIR}/bin/LayersResourceCompilerd")
    set(RESOURCE_COMPILER_RELEASE "${LAYERS_DIR}/bin/LayersResourceCompiler")
endif()

# Generate styles.cpp from styles.lrc using the Layers resource compiler
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    COMMAND $<$<CONFIG:Debug>:${RESOURCE_COMPILER_DEBUG}>$<$<CONFIG:Release>:${RESOURCE_COMPILER_RELEASE}>
        ${CMAKE_CURRENT_SOURCE_DIR}/styles/styles.lrc
        ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/styles/styles.lrc
    COMMENT "Generating styles.cpp from styles.lrc"
    VERBATIM
)

# Set the source files for VortexWidgets
file(GLOB WIDGETS_SOURCES "src/*.cpp")

# Set the header files for VortexWidgets (public and private)
file(GLOB WIDGETS_PUBLIC_HEADERS "include/VortexWidgets/*.h")
file(GLOB WIDGETS_PRIVATE_HEADERS "src/*.h")

# Combine all headers for moc generation
# set(ALL_WIDGETS_HEADERS
#     ${WIDGETS_PUBLIC_HEADERS}
#     ${WIDGETS_PRIVATE_HEADERS})

# Generate moc files for all headers with Q_OBJECT
# qt6_wrap_cpp(WIDGETS_MOC_FILES ${ALL_WIDGETS_HEADERS})

# Add the shared library target
add_library(VortexWidgets SHARED
    ${WIDGETS_SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    ${WIDGETS_PUBLIC_HEADERS}
    ${WIDGETS_PRIVATE_HEADERS}
    # ${WIDGETS_MOC_FILES}
    )

# Add the VORTEX_WIDGETS_LIB definition when building the library
target_compile_definitions(VortexWidgets PRIVATE VORTEX_WIDGETS_LIB)

# Include directories
target_include_directories(VortexWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${LAYERS_DIR}/include"
)

target_link_libraries(VortexWidgets PRIVATE
    VortexCore
    $<$<CONFIG:Debug>:${LAYERS_LIBRARY_DEBUG}>
    $<$<CONFIG:Release>:${LAYERS_LIBRARY_RELEASE}>
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::Network
)

# Install rules
install(TARGETS VortexWidgets DESTINATION lib)
install(DIRECTORY include/Vortex DESTINATION include)

# Set the output directory for the built library
set_target_properties(VortexWidgets PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"  # for .dll
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # for .lib
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # for .lib
    DEBUG_POSTFIX "d"
)
