Building of examples for Linux OS
=================================

1) Set following system variables:
----------------------------------
  - export ARCH=arm
     - Target architecture
  - export PATH=/path/to/your/CHESS/compiler/binaries:$PATH
     - Path to the target APEX compiler binaries
  - export PATH=/path/to/your/arm/cross/compiler/binaries:$PATH
     - Path to the compiler binaries
     
2) Build the application
-----------------------
  BUILD WITH APEX COMPILER
  ------------------------
  - run "make clean" for the first time (the included header files must be deleted)
  - run "make allsub" in the build-v234ce-gnu-sa-d directory
  
  BUILD WITHOUT APEX COMPILER
  ---------------------------
  - run "make APEX_PREBUILD=1 allsub" command
  - WARNING, after "make clean", the pre-build header files will de deleted along with all targets.
	In order to preserve the header files, please issue "make APEX_PREBUILD=1 clean"
