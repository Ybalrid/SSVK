cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)

IF(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W4 /MD /Ot /Oi")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4 /MDd")
ENDIF()

project(SSVK)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB SSVK_SRC src/*.cpp)
file(GLOB SSVK_INCLUDE include/*.hpp)
file(GLOB SSVK_TESTCODE test/*.cpp)

if(UNIX)
    find_library(X11 REQUIRED)
endif()

add_definitions(-DDLLEXPORT)
add_library(SSVK SHARED ${SSVK_SRC} ${SSVK_INCLUDE})

target_link_libraries(SSVK X11 Xtst)

add_executable(SSVK_TEST ${SSVK_TESTCODE})
target_link_libraries(SSVK_TEST SSVK)

INSTALL(DIRECTORY include DESTINATION inlcude)
INSTALL(TARGETS SSVK DESTINATION lib)



