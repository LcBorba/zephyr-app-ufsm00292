#
# CMakeLists.txt para projeto sensor AT30TSE752A
# Semana 6 - Integração completa
#

# Versão mínima do CMake
cmake_minimum_required(VERSION 3.20.0)

# Encontrar Zephyr package
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Projeto
project(temp_sensor_app)

# Arquivo principal da aplicação
target_sources(app PRIVATE src/main.c)

# Incluir nosso driver de sensor
zephyr_library()
zephyr_library_sources_ifdef(CONFIG_SENSOR drivers/sensors/temperature_at30tse752a.c)
