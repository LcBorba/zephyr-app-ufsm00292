cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(APP_gfschuster)

target_include_directories(app PRIVATE include)

target_sources(app PRIVATE
    src/main.c
    src/sensor_temp.c
    src/sensor_lux.c
    src/sensor_humidity.c
    src/data_center.c
)
