cmake_minimum_required( VERSION 3.21 )

set( PROJECT_NAME "SpaceWars" )
project( ${PROJECT_NAME} LANGUAGES CXX )
set( TARGET ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Define the path of additional CMake modules
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/" )

find_package( SFML 2.5 REQUIRED COMPONENTS graphics window system network audio )

# find_package( leafy REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )
# include_directories( ${LEAFY_INCLUDE_DIR} )

# Set source and include paths
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include/" )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src/" )

# Define the path of the executable output directory
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

# Recursively find files
file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE INLS "${INCLUDE_PATH}/*.inl" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp"  )

add_executable( ${TARGET} ${CPPS} ${INLS} ${HPPS} )

# Include header file directory to target
target_include_directories( ${TARGET} PUBLIC $<BUILD_INTERFACE:${INCLUDE_PATH}> $<INSTALL_INTERFACE:include/> )

target_link_libraries( ${TARGET} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network ) # ${LEAFY_LIBRARY}

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${TARGET}
        RUNTIME DESTINATION)