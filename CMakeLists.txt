cmake_minimum_required(VERSION 3.17)
project(threeAS)

add_library(threeAS src/task.cpp src/Timer.cpp src/SteadyClock.cpp)
set_target_properties(threeAS PROPERTIES OUTPUT_NAME "threeAS")
target_include_directories(
  threeAS
  PUBLIC src
  PRIVATE src)

if(${WITH_TESTS})
  set(WITH_TESTS OFF)
  include(FetchContent)
  FetchContent_Declare(
    testcpplite
    GIT_REPOSITORY https://github.com/sbash64/testcpplite
    GIT_TAG v1.1.3)
  FetchContent_MakeAvailable(testcpplite)
  add_subdirectory(test)
endif()

set(OPENFRAMEWORKS_ROOT /Users/basset/Downloads/of_v0.11.0_osx_release)
set(OPENFRAMEWORKS_CSV_ROOT ${OPENFRAMEWORKS_ROOT}/addons/ofxCsv-0.2.1)
add_executable(
  main MACOSX_BUNDLE
  src/main.cpp src/ofApp.cpp ${OPENFRAMEWORKS_CSV_ROOT}/src/ofxCsv.cpp
  ${OPENFRAMEWORKS_CSV_ROOT}/src/ofxCsvRow.cpp)
set_target_properties(main PROPERTIES OUTPUT_NAME "threeAS")
set(OPENFRAMEWORKS_LIBS ${OPENFRAMEWORKS_ROOT}/libs)
set(OPENFRAMEWORKS_GLEW ${OPENFRAMEWORKS_LIBS}/glew)
set(OPENFRAMEWORKS_TESS2 ${OPENFRAMEWORKS_LIBS}/tess2)
set(OPENFRAMEWORKS_BOOST ${OPENFRAMEWORKS_LIBS}/boost)
set(OPENFRAMEWORKS_CAIRO ${OPENFRAMEWORKS_LIBS}/cairo)
set(OPENFRAMEWORKS_CORE ${OPENFRAMEWORKS_LIBS}/openFrameworks)
target_include_directories(
  main
  PRIVATE ${OPENFRAMEWORKS_CSV_ROOT}/src
          ${OPENFRAMEWORKS_LIBS}/glew/include
          ${OPENFRAMEWORKS_TESS2}/include
          ${OPENFRAMEWORKS_BOOST}/include
          ${OPENFRAMEWORKS_LIBS}/utf8/include
          ${OPENFRAMEWORKS_LIBS}/glm/include
          ${OPENFRAMEWORKS_LIBS}/json/include
          ${OPENFRAMEWORKS_LIBS}/pugixml/include
          ${OPENFRAMEWORKS_LIBS}/fmodex/include
          ${OPENFRAMEWORKS_CAIRO}/include/cairo
          ${OPENFRAMEWORKS_CORE}
          ${OPENFRAMEWORKS_CORE}/utils
          ${OPENFRAMEWORKS_CORE}/events
          ${OPENFRAMEWORKS_CORE}/types
          ${OPENFRAMEWORKS_CORE}/math
          ${OPENFRAMEWORKS_CORE}/graphics
          ${OPENFRAMEWORKS_CORE}/communication
          ${OPENFRAMEWORKS_CORE}/gl
          ${OPENFRAMEWORKS_CORE}/app
          ${OPENFRAMEWORKS_CORE}/3d
          ${OPENFRAMEWORKS_CORE}/sound
          ${OPENFRAMEWORKS_CORE}/video)
find_library(IO_KIT IOKit)
find_library(CORE_FOUNDATION CoreFoundation)
find_library(CORE_GRAPHICS CoreGraphics)
find_library(CORE_TEXT CoreText)
find_library(CORE_VIDEO CoreVideo)
find_library(APP_KIT AppKit)
find_library(SECURITY Security)
find_library(LDAP_LIB LDAP)
find_library(OPEN_GL OpenGL)
target_link_libraries(
  main
  threeAS
  ${OPENFRAMEWORKS_LIBS}/openFrameworksCompiled/lib/osx/openFrameworks.a
  ${OPENFRAMEWORKS_LIBS}/glfw/lib/osx/glfw3.a
  ${OPENFRAMEWORKS_LIBS}/glew/lib/osx/glew.a
  ${OPENFRAMEWORKS_LIBS}/uriparser/lib/osx/uriparser.a
  ${OPENFRAMEWORKS_TESS2}/lib/osx/tess2.a
  ${OPENFRAMEWORKS_CAIRO}/lib/osx/cairo.a
  ${OPENFRAMEWORKS_CAIRO}/lib/osx/pixman-1.a
  ${OPENFRAMEWORKS_LIBS}/curl/lib/osx/curl.a
  ${OPENFRAMEWORKS_LIBS}/openssl/lib/osx/ssl.a
  ${OPENFRAMEWORKS_LIBS}/freetype/lib/osx/freetype.a
  ${OPENFRAMEWORKS_LIBS}/FreeImage/lib/osx/freeimage.a
  ${OPENFRAMEWORKS_BOOST}/lib/osx/boost_filesystem.a
  ${OPENFRAMEWORKS_BOOST}/lib/osx/boost_system.a
  ${OPENFRAMEWORKS_LIBS}/fmodex/lib/osx/libfmodex.dylib
  ${IO_KIT}
  ${CORE_FOUNDATION}
  ${CORE_GRAPHICS}
  ${CORE_TEXT}
  ${CORE_VIDEO}
  ${APP_KIT}
  ${SECURITY}
  ${LDAP_LIB}
  ${OPEN_GL})

# https://stackoverflow.com/a/17988981
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
install(TARGETS main BUNDLE DESTINATION . COMPONENT Runtime)
install(
  CODE "
    include(BundleUtilities)
    fixup_bundle(
        \"${CMAKE_INSTALL_PREFIX}/threeAS.app\" \"\"
        \"${OPENFRAMEWORKS_LIBS}/fmodex/lib/osx\")
")
