cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


project(ZeroM_Main)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -w -O3 -std=gnu99 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")



include_directories(
  ${CMAKE_SOURCE_DIR}/common/
  ${CMAKE_SOURCE_DIR}/ZeroM-base/include/
  ${CMAKE_SOURCE_DIR}/GameMod/include/
  ${CMAKE_SOURCE_DIR}/PluginReload/include/
  
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()


add_subdirectory(ZeroM-base)
execute_process(
  COMMAND sh build_step1.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/GameMod
  RESULT_VARIABLE result
)
add_subdirectory(GameMod)
add_subdirectory(PluginReload)

