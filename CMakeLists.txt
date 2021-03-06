cmake_minimum_required(VERSION 3.5)
project(rosalila)
# set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

IF (APPLE)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")
  add_definitions(-DROSALILA_DYNAMICLIB)
  add_library(rosalila SHARED ${SOURCES})
  FIND_PACKAGE(SDL2 REQUIRED)
  FIND_PACKAGE(SDL2_IMAGE REQUIRED)
  FIND_PACKAGE(SDL2TTF REQUIRED)
  FIND_PACKAGE(SDL2Mixer REQUIRED)

  find_package(OpenGL REQUIRED)

  include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})
  
  add_definitions(-DGLEW_STATIC)
  target_link_libraries(rosalila ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY})
ENDIF()

IF (UNIX AND NOT APPLE)
  add_definitions(-DROSALILA_DYNAMICLIB)
  add_library(rosalila SHARED ${SOURCES})
  
  add_definitions(-DGLEW_STATIC)
  target_link_libraries (rosalila GL SDL2 SDL2_mixer SDL2_image SDL2_ttf)
ENDIF ()

IF (MINGW)
  target_link_libraries(rosalila
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libcurl.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libz.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libcrypto.dll.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libeay32.dll
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libssl.dll.a
    wldap32 ws2_32)
ENDIF()

IF (MSVC)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  add_definitions(-DROSALILA_STATICLIB)
  add_library(rosalila STATIC ${SOURCES})

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  include_directories(windows_dependencies/include)
  link_directories(${CMAKE_SOURCE_DIR}/windows_dependencies/lib)
  target_link_libraries(rosalila glew32.lib SDL2.lib SDL2_image.lib SDL2_mixer.lib SDL2_ttf.lib SDL2main.lib SDL2test.lib steam_api.lib )
ENDIF()
