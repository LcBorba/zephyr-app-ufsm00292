# Install script for directory: C:/my-workspace/modules/lib/picolibc/newlib/libc/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/Jaque/Downloads/arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi/bin/arm-none-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/sys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/machine/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/ssp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/rpc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/arpa/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/alloca.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/argz.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/ar.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/assert.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/byteswap.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/cpio.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/ctype.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/devctl.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/dirent.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/endian.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/envlock.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/envz.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/errno.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/fastmath.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/fcntl.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/fenv.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/fnmatch.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/getopt.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/glob.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/grp.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/iconv.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/ieeefp.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/inttypes.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/langinfo.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/libgen.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/limits.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/locale.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/malloc.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/math.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/memory.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/ndbm.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/newlib.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/paths.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/picotls.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/pwd.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/regdef.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/regex.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/sched.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/search.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/setjmp.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/signal.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/spawn.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/stdint.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/stdnoreturn.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/stdlib.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/string.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/strings.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/tar.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/termios.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/time.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/uchar.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/unctrl.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/unistd.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/utime.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/utmp.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/wchar.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/wctype.h"
    "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/wordexp.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/my-workspace/modules/lib/picolibc/newlib/libc/include/complex.h")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/my-workspace/zephyr-app-ufsm00292/AppJaqueline/build/modules/picolibc/newlib/libc/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
