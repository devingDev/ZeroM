cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(ZeroM)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
  ./
  "${CMAKE_CURRENT_SOURCE_DIR}/../common/"
  "${CMAKE_CURRENT_SOURCE_DIR}/sample/plugin/src/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../vita-rss-libdl/include/"
  
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()

# Builds


add_executable(user
  user.c
  hooks.c
  log.c
  testhooks.c
  patches.c
  renderer.c
  menu.c
  navigation.c
  mem.c
  hash.c
)

set(LIB PluginReload_stub_weak)
set(LIB_FILE "lib${LIB}.a")
add_library("${LIB}" STATIC IMPORTED GLOBAL)
add_dependencies("${LIB}" stubs)
set_target_properties("${LIB}" PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../PluginReload/build/stubs/${LIB_FILE}"
)


target_link_libraries(user
  #"${CMAKE_CURRENT_SOURCE_DIR}/../vita-rss-libdl/build/libdl.a"
  dl
  taihen_stub
  SceLibKernel_stub
  SceDisplay_stub
  SceSysmem_stub 
  SceIofilemgr_stub
  SceRegistryMgr_stub
  SceVshBridge_stub
  SceKernelThreadMgr_stub 
  SceKernelModulemgr_stub 
#  SceSblSsMgr_stub
  SceCtrl_stub
  k
  gcc
  ScePower_stub
  PluginReload_stub_weak
  
)

set_target_properties(user
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(ZeroM.suprx user
  UNSAFE
  CONFIG ${CMAKE_SOURCE_DIR}/user.yml
)
