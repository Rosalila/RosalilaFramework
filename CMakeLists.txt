cmake_minimum_required(VERSION 3.5)
project(rosalila)
# set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

IF (APPLE)
  find_package(ZLIB REQUIRED)
  find_package(CURL REQUIRED)
  target_link_libraries(rosalila ${CURL_LIBRARIES} ZLIB::ZLIB)
ENDIF()

IF (UNIX AND NOT APPLE)
  add_definitions(-DROSALILA_DYNAMICLIB)
  add_library(rosalila SHARED ${SOURCES})
  
  add_definitions(-DGLEW_STATIC)
  target_link_libraries (rosalila GLEW GL SDL2 SDL2_mixer SDL2_image SDL2_ttf SDL2_net)
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
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/libcurl_a.lib  ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/zlib.lib )
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_link_libraries (rosalila ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2main.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2_image.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2_mixer.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2_ttf.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/SDL2test.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/steam_api.lib ${CMAKE_SOURCE_DIR}/windows_dependencies/lib/glew32.lib opengl32.lib)
  endif()
ENDIF()
