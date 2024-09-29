cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(PluginReload)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(ELF PluginReload.elf)
set(SELF PluginReload.suprx)
set(LIB PluginReload_stub)
set(LIB_FILE "lib${LIB}.a")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -fshort-wchar -O3 -std=gnu99")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/PluginReload-stubs
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()

# Builds

add_executable("${ELF}"
  main.c
)

target_include_directories("${ELF}"
  PRIVATE "../include"
)

target_link_libraries("${ELF}"
  taihen_stub
  SceLibKernel_stub
  SceIofilemgr_stub
  SceSysmem_stub 
  SceRegistryMgr_stub
  ScePower_stub
  SceVshBridge_stub
  SceKernelModulemgr_stub
  SceKernelThreadMgr_stub
  SceCtrl_stub
)


vita_create_self("${SELF}"
  "${ELF}"
  CONFIG ${CMAKE_SOURCE_DIR}/PluginReload.yml
  UNSAFE
)

vita_create_stubs(stubs
  "${ELF}"
  PluginReload.yml
  USER
)

add_library("${LIB}" STATIC IMPORTED GLOBAL)

add_dependencies("${LIB}" stubs)

set_target_properties("${LIB}" PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/stubs/${LIB_FILE}"
)