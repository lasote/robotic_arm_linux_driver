# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html
# Or check the examples below

SET(CMAKE_BUILD_TYPE, Debug)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_recipes/libusb_1.0-config.cmake)
include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
# Initializes block variables
INIT_BIICODE_BLOCK()

SET(BII_CREATE_LIB TRUE)

# Actually create targets: EXEcutables and libraries.
ADD_BIICODE_TARGETS()


MESSAGE("Found headers on: ${LIBUSB_1_INCLUDE_DIRS}")

target_include_directories(${BII_LIB_TARGET} PUBLIC ${LIBUSB_1_INCLUDE_DIRS})
target_link_libraries(${BII_LIB_TARGET} PUBLIC ${LIBUSB_1_LIBRARIES})

