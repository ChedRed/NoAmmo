# Basic project requirements
cmake_minimum_required(VERSION 3.30)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_OSX_SYSROOT macosx)
endif()
project(NoAmmo)


# Set CMake variables
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Main executable

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_executable(NoAmmo MACOSX_BUNDLE main.cpp buildfiles/icon.icns)
    set_target_properties(NoAmmo PROPERTIES OUTPUT_NAME "No Ammo" MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/buildfiles/Info.plist)
else(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(NoAmmo WIN32 main.cpp buildfiles/wicon.rc)
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Set macos executable rpath and result path
    set_target_properties(NoAmmo PROPERTIES INSTALL_RPATH "@executable_path/../Resources" BUILD_WITH_INSTALL_RPATH TRUE)
    set_target_properties(NoAmmo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)


    # Link libraries and include directories
    target_link_libraries(NoAmmo PRIVATE ${CMAKE_SOURCE_DIR}/../Cached/libSDL3.0.dylib)
    target_link_libraries(NoAmmo PRIVATE ${CMAKE_SOURCE_DIR}/../Cached/libSDL3_ttf.0.0.0.dylib)
    # target_link_libraries(NoAmmo PRIVATE ${CMAKE_SOURCE_DIR}/../Cached/libgtk-4.1.dylib)
    target_include_directories(NoAmmo PRIVATE /usr/local/include)


    # Make directories for macos app
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/build/No Ammo.app/Contents/MacOS")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/build/No Ammo.app/Contents/Resources")


    # Add basic files to macos app
    file(COPY ${CMAKE_SOURCE_DIR}/buildfiles/info.plist DESTINATION "${CMAKE_SOURCE_DIR}/build/No Ammo.app/Contents")
    file(COPY ${CMAKE_SOURCE_DIR}/buildfiles/icon.icns DESTINATION "${CMAKE_SOURCE_DIR}/build/No Ammo.app/Contents/Resources")
    file(COPY ${CMAKE_SOURCE_DIR}/buildfiles/FreeSans.ttf DESTINATION "${CMAKE_SOURCE_DIR}/build/No Ammo.app/Contents/Resources")


    # Add resources to macos app
    file(COPY ${CMAKE_SOURCE_DIR}/../Cached/libSDL3.0.dylib DESTINATION "${CMAKE_SOURCE_DIR}/build/No Ammo.app/contents/Resources")
    configure_file(${CMAKE_SOURCE_DIR}/../Cached/libSDL3_ttf.0.0.0.dylib "${CMAKE_SOURCE_DIR}/build/No Ammo.app/contents/Resources/libSDL3_ttf.0.dylib" COPYONLY)


else(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Set windows result path
    set_target_properties(NoAmmo PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/NoAmmo")


    # Link libraries and include directories
    target_link_libraries(NoAmmo PRIVATE C:/usr/local/lib/SDL3.lib)
    target_link_libraries(NoAmmo PRIVATE C:/usr/local/lib/SDL3_ttf.lib)
    target_include_directories(NoAmmo PRIVATE C:/usr/local/include)


    # Add basic files to windows app
    file(COPY ${CMAKE_SOURCE_DIR}/buildfiles/FreeSans.ttf DESTINATION "${CMAKE_SOURCE_DIR}/build/NoAmmo")


    # Add resources to windows app
    file(COPY C:/usr/local/lib/SDL3.dll DESTINATION "${CMAKE_SOURCE_DIR}/build/NoAmmo")
    file(COPY C:/usr/local/lib/SDL3_ttf.dll DESTINATION "${CMAKE_SOURCE_DIR}/build/NoAmmo")
endif()
