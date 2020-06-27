#指定cmake最小版本,nihao
cmake_minimum_required(VERSION 3.4.1)
project (Testpcm2mp3)
#源文件
set(SOURCES 
    src/ALSA_AUDIO_CAPTURE.c
    src/Lame_pcm2mp3.c
    src/testpcm2mp3.c
    )
include_directories(3rdparty/lame/include/lame/)

link_directories(3rdparty/lame/lib/)

#链接static alsa&lame库  
link_libraries(-lasound
)

link_libraries(libmp3lame.so)

add_executable(${PROJECT_NAME} ${SOURCES})

#头文件
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include 
    )
