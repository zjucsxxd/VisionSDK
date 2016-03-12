
cmake_minimum_required (VERSION 2.6)

set (LibName "APU_Lib")

set(OWN_KERNEL_SRC "${CMAKE_CURRENT_LIST_DIR}/src")

file( GLOB srcFilesCPP "${OWN_KERNEL_SRC}/*.cpp")
file( GLOB srcFilesC "${OWN_KERNEL_SRC}/*.c")
file( GLOB headerFilesH "${OWN_KERNEL_SRC}/*.h")
file( GLOB headerFilesHPP "${OWN_KERNEL_SRC}/*.hpp")

set (srcFiles "")
list(APPEND srcFiles ${srcFilesCPP} ${srcFilesC})
set (headerFiles "")
list(APPEND headerFiles ${headerFilesHPP} ${headerFilesH})

#message("own kernel cat src files: " ${srcFiles})

LIST(APPEND GEN_DEPENDENCIES ${LibName})

#set(LibFound "")
#find_library(LibFound ${LibName} "${CMAKE_CURRENT_LIST_DIR}/${VS_PROJ_DIR}/Release" )
#message ("Lib ${LibName} found " ${LibFound})

#add_library(${LibName} STATIC IMPORTED)
add_library(${LibName} STATIC ${headerFiles} ${srcFiles})

source_group("Header Files" FILES ${headerFiles} )
source_group("Source Files" FILES ${srcFiles})
target_compile_definitions(${LibName} PUBLIC ACF_KERNEL_IMPLEMENTATION)

# Creates a folder "cmake/proj" and adds target 
# project (<LibName>.vcproj) under it
#set_property(TARGET ${LibName} PROPERTY FOLDER "${LIB_SOURCE_DIR}/build-deskwin32/mvc")
#set_property(TARGET ${LibName} PROPERTY IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/${VS_PROJ_DIR}/Debug")
#set_property(TARGET ${LibName} PROPERTY IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/${VS_PROJ_DIR}/Release")

# Adds logic to INSTALL.vcproj to copy sobelDemo.exe to destination directory
#install (TARGETS ${LibName} 
#		ARCHIVE DESTINATION ${LIB_SOURCE_DIR}/build-deskwin32/mvc)
