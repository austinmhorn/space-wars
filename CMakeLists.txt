cmake_minimum_required( VERSION 3.21 )

set( PROJECT_NAME "SpaceWars" )
project( ${PROJECT_NAME} LANGUAGES CXX )
set( TARGET ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Define the path of additional CMake modules
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/" )

find_package( SFML 2.5 COMPONENTS graphics window system network audio REQUIRED )

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

if( WIN32 )

elseif( APPLE )
    find_library( FOUNDATION_LIBRARY Foundation REQUIRED )
    find_library( COREGRAPHICS_LIBRARY CoreGraphics REQUIRED )

    target_link_libraries( ${TARGET} PUBLIC ${FOUNDATION_LIBRARY} ${COREGRAPHICS_LIBRARY} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    set( LIB_PATH "lib" )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
    find_package( X11 REQUIRED )
    target_link_libraries( ${TARGET} PUBLIC ${X11_LIBRARIES} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    
    if( LIB_SUFFIX )
        set( LIB_PATH "lib${LIB_SUFFIX}" )
    else()
        set( LIB_PATH "lib" )
    endif()
else()
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    set( LIB_PATH "lib" )    
endif()

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${TARGET}
        RUNTIME DESTINATION)