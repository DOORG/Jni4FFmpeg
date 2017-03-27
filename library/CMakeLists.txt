cmake_minimum_required(VERSION 3.4.1)


set(dist_DIR ${CMAKE_SOURCE_DIR}/../dist)




add_library(lib-ffmpeg SHARED IMPORTED)

set_target_properties(lib-ffmpeg PROPERTIES IMPORTED_LOCATION
    ${dist_DIR}/${ANDROID_ABI}/libffmpeg.so)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wno-error=format-security")

add_library(native-lib SHARED
            ${CMAKE_SOURCE_DIR}/src/main/cpp/native-lib.cpp
            ${CMAKE_SOURCE_DIR}/src/main/cpp/check_env.cpp
            ${CMAKE_SOURCE_DIR}/src/main/cpp/check_env.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/cmdutils.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/cmdutils.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_opt.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_filter.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/android-log.h

            ${CMAKE_SOURCE_DIR}/src/main/cpp/Errors.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_utils.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_utils.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/mediametadataretriever.cpp
            ${CMAKE_SOURCE_DIR}/src/main/cpp/mediametadataretriever.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/Mutex.h
            ${CMAKE_SOURCE_DIR}/src/main/cpp/wseemann_media_MediaMetadataRetriever.cpp
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_mediametadataretriever.c
            ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_mediametadataretriever.h


            )

target_include_directories(native-lib PRIVATE
                             ${CMAKE_SOURCE_DIR}/../source/ffmpeg)

target_link_libraries(native-lib
                      android
                      jnigraphics
                      lib-ffmpeg
                      m
                      z
                      dl
                      log)
