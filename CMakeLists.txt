cmake_minimum_required(VERSION 3.0)
project(Tracking)

#To put all the executables in build directory
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

enable_language(CXX)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
include(MacroUtilities)

find_package(MYSQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
message(STATUS "mysql inc : ${MYSQL_INCLUDE_DIR}")
include_directories(inc)

add_library(Dqm SHARED src/Database.cpp)
target_link_libraries(Dqm ${MYSQL_LIBRARIES}) 

add_executable(TestMysql test/TestMysql.cpp)
target_link_libraries(TestMysql Dqm)

#hadd_executable(TestTime test/TestTime.cpp )

add_executable(Test_Cron_Hash_Copy test/Test_Cron_Hash_Copy.cpp)
target_link_libraries(Test_Cron_Hash_Copy Dqm)

add_executable(Test_Copy_From_Daq test/Test_Copy_From_Daq.cpp)
target_link_libraries(Test_Copy_From_Daq Dqm)

add_executable(Test_Integrity_Check test/Test_Integrity_Check.cpp)
target_link_libraries(Test_Integrity_Check Dqm)
