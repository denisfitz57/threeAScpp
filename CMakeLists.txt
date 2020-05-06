cmake_minimum_required(VERSION 3.17)
project(ThreeAS)
set(OPENFRAMEWORKS_ROOT /Users/basset/Downloads/of_v0.11.0_osx_release)
set(OPENFRAMEWORKS_LIBS ${OPENFRAMEWORKS_ROOT}/libs)
add_executable(main
    src/main.cpp
    src/ofApp.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxCsv-0.2.1/src/ofxCsv.cpp
    ${OPENFRAMEWORKS_ROOT}/addons/ofxCsv-0.2.1/src/ofxCsvRow.cpp)
target_include_directories(main PRIVATE
    ${OPENFRAMEWORKS_ROOT}/addons/ofxCsv-0.2.1/src
    ${OPENFRAMEWORKS_LIBS}/glew/include
    ${OPENFRAMEWORKS_LIBS}/tess2/include
    ${OPENFRAMEWORKS_LIBS}/boost/include
    ${OPENFRAMEWORKS_LIBS}/utf8/include
    ${OPENFRAMEWORKS_LIBS}/glm/include
    ${OPENFRAMEWORKS_LIBS}/json/include
    ${OPENFRAMEWORKS_LIBS}/pugixml/include
    ${OPENFRAMEWORKS_LIBS}/fmodex/include
    ${OPENFRAMEWORKS_LIBS}/cairo/include/cairo
    ${OPENFRAMEWORKS_LIBS}/openFrameworks
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/utils
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/events
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/types
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/math
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/graphics
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/communication
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/gl
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/app
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/3d
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/sound
    ${OPENFRAMEWORKS_LIBS}/openFrameworks/video)
find_library(IO_KIT IOKit)
find_library(CORE_FOUNDATION CoreFoundation)
find_library(CORE_GRAPHICS CoreGraphics)
find_library(CORE_TEXT CoreText)
find_library(CORE_VIDEO CoreVideo)
find_library(APP_KIT AppKit)
find_library(SECURITY Security)
find_library(LDAP_LIB LDAP)
find_library(OPEN_GL OpenGL)
target_link_libraries(main
    ${OPENFRAMEWORKS_LIBS}/openFrameworksCompiled/lib/osx/openFrameworks.a
    ${OPENFRAMEWORKS_LIBS}/glfw/lib/osx/glfw3.a
    ${OPENFRAMEWORKS_LIBS}/glew/lib/osx/glew.a
    ${OPENFRAMEWORKS_LIBS}/uriparser/lib/osx/uriparser.a
    ${OPENFRAMEWORKS_LIBS}/tess2/lib/osx/tess2.a
    ${OPENFRAMEWORKS_LIBS}/cairo/lib/osx/cairo.a
    ${OPENFRAMEWORKS_LIBS}/cairo/lib/osx/pixman-1.a
    ${OPENFRAMEWORKS_LIBS}/curl/lib/osx/curl.a
    ${OPENFRAMEWORKS_LIBS}/openssl/lib/osx/ssl.a
    ${OPENFRAMEWORKS_LIBS}/freetype/lib/osx/freetype.a
    ${OPENFRAMEWORKS_LIBS}/FreeImage/lib/osx/freeimage.a
    ${OPENFRAMEWORKS_LIBS}/boost/lib/osx/boost_filesystem.a
    ${OPENFRAMEWORKS_LIBS}/boost/lib/osx/boost_system.a
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
