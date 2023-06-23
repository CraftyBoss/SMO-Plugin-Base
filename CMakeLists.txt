cmake_minimum_required(VERSION 3.21)
project(subsdk CXX C ASM)

## Error if not using switch toolchain file
if (NOT SWITCH)
    message(FATAL_ERROR "Not targeting switch, make sure to specify -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake")
endif ()

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

if (LOGGER_IP)
    add_compile_definitions(LOGGER_IP="${LOGGER_IP}")
endif ()

## Plugin Name (Be sure to change this for your own plugin!)
set(TARGET_NAME my-cool-plugin)
## Plugin Folder name (mainly for FTP transfer, plugin loader figures this out on its own)
set(FOLDER_NAME MyCoolPlugin)

## Title Id
set(TITLE_ID 0100000000010000)
set(CONFIG_TITLE_ID 0x${TITLE_ID})
add_compile_definitions(NNSDK=1 PLUGIN_NAME="${TARGET_NAME}")

## Project sources
include_directories(${PROJECT_SOURCE_DIR}/libs)

include_directories(${PROJECT_SOURCE_DIR}/libs/exl)
include_directories(${PROJECT_SOURCE_DIR}/libs/imgui)
include_directories(${PROJECT_SOURCE_DIR}/libs/sead)

include_directories(${PROJECT_SOURCE_DIR}/libs/NintendoSDK)
include_directories(${PROJECT_SOURCE_DIR}/libs/NintendoSDK/nn)
include_directories(${PROJECT_SOURCE_DIR}/libs/NintendoSDK/nvn)
include_directories(${PROJECT_SOURCE_DIR}/libs/NintendoSDK/nvnTool)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/program)

file(GLOB_RECURSE SOURCES_ASM ${PROJECT_SOURCE_DIR}/src/*.s ${PROJECT_SOURCE_DIR}/libs/*.s  ${PROJECT_SOURCE_DIR}/libs/*.s)
file(GLOB_RECURSE SOURCES_H ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp   ${PROJECT_SOURCE_DIR}/libs/*.h ${PROJECT_SOURCE_DIR}/libs/*.hpp)
file(GLOB_RECURSE SOURCES_CXX ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/libs/*.cpp ${PROJECT_SOURCE_DIR}/libs/*.c)

file(GLOB_RECURSE LOCAL_LIBRARIES ${PROJECT_SOURCE_DIR}/libs/*.a)

## Include nx tools
include(${CMAKE_SOURCE_DIR}/cmake/SwitchTools.cmake)

## create nro executable
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
add_executable(${TARGET_NAME} ${SOURCES_ASM} ${SOURCES_C} ${SOURCES_H} ${SOURCES_CXX})
target_link_libraries(${TARGET_NAME} ${LOCAL_LIBRARIES})

## Prepare subsdk ld
set(SUBSDK_LD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.ld)
set(PLUGIN_MODULE_NAME ${TARGET_NAME})
execute_process(COMMAND uname OUTPUT_VARIABLE uname)
if (uname MATCHES "^MINGW")
    string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" SUBSDK_LD_PATH "${SUBSDK_LD_PATH}")
endif ()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.specs.template ${CMAKE_CURRENT_BINARY_DIR}/subsdk9.specs)

## Build nro
add_nro_target(${TARGET_NAME})
add_custom_target(subsdk9_meta DEPENDS ${TARGET_NAME}_nro)
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "-specs ${CMAKE_BINARY_DIR}/subsdk9.specs -g3 ${ARCH} -nostartfiles")

if (FTP_IP)
    ## Upload to target switch
    if (FTP_USERNAME AND FTP_PASSWORD) # login using a username and password
        add_custom_command(TARGET subsdk9_meta POST_BUILD COMMAND ncftpput -u ${FTP_USERNAME} -p ${FTP_PASSWORD} -P 5000 ${FTP_IP} /smo/PluginData/${FOLDER_NAME} ${CMAKE_BINARY_DIR}/${TARGET_NAME}.nro)
    endif ()
endif ()

#if (RYU_PATH)
#    add_custom_command(TARGET subsdk9_meta POST_BUILD COMMAND mkdir -p ${RYU_PATH}/mods/contents/${TITLE_ID}/mods/exefs/)
#    add_custom_command(TARGET subsdk9_meta POST_BUILD COMMAND cp ${CMAKE_BINARY_DIR}/main.npdm ${RYU_PATH}/mods/contents/${TITLE_ID}/mods/exefs/main.npdm)
#    add_custom_command(TARGET subsdk9_meta POST_BUILD COMMAND cp ${CMAKE_BINARY_DIR}/subsdk9 ${RYU_PATH}/mods/contents/${TITLE_ID}/mods/exefs/subsdk9)
#endif ()