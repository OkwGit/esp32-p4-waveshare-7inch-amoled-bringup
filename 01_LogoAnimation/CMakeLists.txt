cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../ESP32-P4-WIFI6-Touch-LCD-7B-main/examples/ESP-IDF/08_lvgl_display_panel/components
    )

add_compile_options(-Wno-format)
project(logo_animation)

