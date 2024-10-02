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



include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  ${CMAKE_SOURCE_DIR}/../common/include/
  ${CMAKE_SOURCE_DIR}/../GameMod/include/
  ${CMAKE_SOURCE_DIR}/../PluginReload/include/
  
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

  ../common/src/resourcelocation.c
)

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
  
)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VITASDK}/arm-vita-eabi/include/)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
  UNSAFE
  CONFIG ZeroM.yml
)
