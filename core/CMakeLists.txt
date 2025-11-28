# Enable AUTOMOC for this directory
set(CMAKE_AUTOMOC ON)

# Set the source files for VortexCore
file(GLOB CORE_SOURCES "src/*.cpp")

# Set the header files for VortexCore (public and private)
file(GLOB CORE_PUBLIC_HEADERS "include/VortexCore/*.h")
file(GLOB CORE_PRIVATE_HEADERS "src/*.h")

# Set the resource files
set(ROBOTOFONT "fonts/Roboto/roboto_font.qrc")
set(IMAGES "images/images.qrc")
set(THEMES "themes/themes.qrc")

# Generate resource files
qt6_add_resources(ROBOTOFONT_RC ${ROBOTOFONT})
qt6_add_resources(IMAGES_RC ${IMAGES})
qt6_add_resources(THEMES_RC ${THEMES})

# Combine all headers for moc generation
# set(ALL_CORE_HEADERS
#     ${CORE_PUBLIC_HEADERS}
#     ${CORE_PRIVATE_HEADERS})

# Generate moc files for all headers with Q_OBJECT
# qt6_wrap_cpp(CORE_MOC_FILES ${ALL_CORE_HEADERS})

# Add the shared library target
add_library(VortexCore SHARED
    ${CORE_SOURCES}
    # ${CORE_MOC_FILES}
    ${CORE_PUBLIC_HEADERS}
    ${CORE_PRIVATE_HEADERS}
    ${ROBOTOFONT_RC}
    ${IMAGES_RC}
    ${THEMES_RC})

# Add the VORTEX_CORE_LIB definition when building the library
target_compile_definitions(VortexCore PRIVATE VORTEX_CORE_LIB)

# Include directories
target_include_directories(VortexCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${LAYERS_DIR}/include"
)

target_link_libraries(VortexCore PRIVATE
    $<$<CONFIG:Debug>:${LAYERS_LIBRARY_DEBUG}>
    $<$<CONFIG:Release>:${LAYERS_LIBRARY_RELEASE}>
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::Network
)

# Install rules
install(TARGETS VortexCore DESTINATION lib)
install(DIRECTORY include/Vortex DESTINATION include)

# Set the output directory for the built library
set_target_properties(VortexCore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"  # for .dll
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # for .lib
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # for .lib
    DEBUG_POSTFIX "d"
)
