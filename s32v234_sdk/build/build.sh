#!/bin/sh

case $PWD in
  # Vybrid TWR board
  *"cmake-twrvf600-gnu-mqx") 
  cmake -DCMAKE_TOOLCHAIN_FILE=../../../tools/cmake/arm-none-eabi-gcc.cmake ../.
  echo ""
  echo -- Makefile created, call make to build target
  echo "" ;;

  # Xilinx ZC702 Evaluation board w/ GNU/Linux
  *"cmake-zc702-gnu-linux")
  echo "\n    ############ Building for ZC702-GNU-LINUX ############\n"
  cmake -DCMAKE_TOOLCHAIN_FILE=../../../build/cmake/toolchains/arm-none-linux-gnueabi-gcc.cmake -DCMAKE_BUILD_TYPE=Debug ../.
  echo ""
  echo -- Makefile created, call make to build target
  echo "" ;;

  # Xilinx ZC702 Evaluation board w/ GHS/Integrity
  *"cmake-zc702-ghs-integrity")
  echo "\n    ############ Building for ZC702-GHS-INTEGRITY ############\n"
  cmake -DCMAKE_TOOLCHAIN_FILE=../../../build/cmake/toolchains/arm-integrity-ghs.cmake -DCMAKE_BUILD_TYPE=Debug ../.
  echo ""
  echo -- Makefile created, call make to build target
  echo "" ;;

  *) echo -- No apropriate tool chain file available ;;

esac
