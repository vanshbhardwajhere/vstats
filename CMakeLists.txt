cmake_minimum_required(VERSION 3.15)

# Project metadata
project(vstat VERSION 0.1.0 DESCRIPTION "Runtime complexity and loop tracker utility" LANGUAGES CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library target
add_library(vstat
    src/timer.cpp
    src/loop_tracker.cpp
    src/complexity_estimator.cpp
)

# Public headers
target_include_directories(vstat
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation (so library can be reused)
install(TARGETS vstat
    EXPORT vstatTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

# Export configuration
install(EXPORT vstatTargets
    FILE vstatTargets.cmake
    NAMESPACE vstat::
    DESTINATION lib/cmake/vstat
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/vstatConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(vstatConfig.cmake.in vstatConfig.cmake @ONLY)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/vstatConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/vstatConfigVersion.cmake"
    DESTINATION lib/cmake/vstat
)

# (Optional) Enable tests
# enable_testing()
# add_subdirectory(tests)
