cmake_minimum_required(VERSION 3.23)

set(GENERAL_PROJECT_VERSION_MAJOR_MINOR_PATCH "0.0.1")

project(ActiveObject VERSION ${GENERAL_PROJECT_VERSION_MAJOR_MINOR_PATCH})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Erstelle eine Liste der Quell- und Header-Dateien
set(SOURCES
    ActiveObject.cpp
    ActiveObjectPool.cpp
)

set(HEADERS
include/ActiveObject.h
include/IMessage.h
include/Pool/ActiveObjectPool.h
)

# Erstelle eine statische Bibliothek
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Define options
option(AO_ENABLE_CUSTOM_INSTALL "Enable feature X" OFF)
option(AO_ENABLE_DEBUG_MODE "Enable debug mode" OFF)
set(AO_CUSTOM_INSTALL_PATH "/usr/local" CACHE PATH "Custom install path")

# Print the options
message(STATUS "Enable Custom install Path: ${AO_ENABLE_CUSTOM_INSTALL}")
message(STATUS "Enable Debug Mode: ${AO_ENABLE_DEBUG_MODE}")
message(STATUS "Custom Install Path: ${AO_CUSTOM_INSTALL_PATH}")

set(bin_dest "bin")
set(include_dest "include/${PROJECT_NAME}-${PROJECT_VERSION}")
set(lib_dest "lib/${PROJECT_NAME}-${PROJECT_VERSION}")
set(cmake_dest "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")

# Erstelle eine dynamische Bibliothek
#add_library(MyLibraryShared SHARED ${SOURCES} ${HEADERS})

# Specify the include directories
target_include_directories(ActiveObject PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${include_dest}>)


if(AO_ENABLE_CUSTOM_INSTALL)
  set(CMAKE_INSTALL_PREFIX ${AO_CUSTOM_INSTALL_PATH} CACHE PATH "Installation Directory" FORCE)
endif()

# Set the installation directories
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/${bin_dest}")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/${lib_dest}")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${include_dest}")
set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/${cmake_dest}")
set(INSTALL_SHARE_DIR "${CMAKE_INSTALL_PREFIX}/share")

# Output various CMake variables and custom paths
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "INSTALL_LIB_DIR: ${INSTALL_LIB_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE CURRENT BIN: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "INSTALL_INCLUDE_DIR: ${INSTALL_INCLUDE_DIR}")
message(STATUS "INSTALL_CMAKE_DIR: ${INSTALL_CMAKE_DIR}")

include(GNUInstallDirs)
# Installationsregeln
install(TARGETS ${PROJECT_NAME}
        DESTINATION ${INSTALL_LIB_DIR}
        EXPORT ${PROJECT_NAME}Targets)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Create a Config.cmake file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${INSTALL_CMAKE_DIR}
)

# Install the Config and ConfigVersion files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${INSTALL_CMAKE_DIR}
)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${INSTALL_CMAKE_DIR})

# Install header files
install(FILES include/ActiveObject.h include/IMessage.h DESTINATION ${INSTALL_INCLUDE_DIR})
install(FILES include/Pool/ActiveObjectPool.h DESTINATION ${INSTALL_INCLUDE_DIR}/Pool)

# For FetchContent compatibility
export(EXPORT ${PROJECT_NAME}Targets
       NAMESPACE ${PROJECT_NAME}::
       FILE ${PROJECT_NAME}Targets.cmake)