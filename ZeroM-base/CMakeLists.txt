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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -w -O3 -std=gnu99 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")


add_subdirectory(PluginReload)


include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  ${CMAKE_SOURCE_DIR}/gamemod/include/
  ${CMAKE_SOURCE_DIR}/PluginReload/
  
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()

# Builds


add_executable(${PROJECT_NAME}
  src/user.c
  src/hooks.c
  src/log.c
  src/testhooks.c
  src/patches.c
  src/renderer.c
  src/menu.c
  src/navigation.c
  src/mem.c
  src/hash.c
  src/gamemodloader.c
  src/customitem.c
)

add_dependencies(${PROJECT_NAME} PluginReload)

#set(LIB PluginReload_stub_weak)
#set(LIB_FILE "lib${LIB}.a")
#add_library("${LIB}" STATIC IMPORTED GLOBAL)
#add_dependencies("${LIB}" stubs)
#set_target_properties(PluginReload PROPERTIES   IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/PluginReload/build/stubs/${LIB_FILE}" )

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VITASDK}/arm-vita-eabi/include/)

target_link_libraries(${PROJECT_NAME}
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

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VITASDK}/arm-vita-eabi/include/)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
  UNSAFE
  CONFIG ${CMAKE_SOURCE_DIR}/ZeroM.yml
)
