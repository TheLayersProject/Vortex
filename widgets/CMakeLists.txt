# Enable AUTOMOC for this directory
set(CMAKE_AUTOMOC ON)

set(LAYERS_RC_DEB "${LAYERS_DIR}/bin/LayersResourceCompilerd")
set(LAYERS_RC_REL "${LAYERS_DIR}/bin/LayersResourceCompiler")

set(STYLES_LRC "${CMAKE_CURRENT_SOURCE_DIR}/styles/styles.lrc")
set(STYLES_CPP "${CMAKE_CURRENT_BINARY_DIR}/styles.cpp")

add_custom_command(
  OUTPUT ${STYLES_CPP}
  COMMAND $<$<CONFIG:Debug>:${LAYERS_RC_DEB}>$<$<CONFIG:Release>:${LAYERS_RC_REL}>
    ${STYLES_LRC}
    ${STYLES_CPP}
  DEPENDS ${STYLES_LRC}
  COMMENT "Generating ${STYLES_CPP} from ${STYLES_LRC}"
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
