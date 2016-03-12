/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* The normal alignment of `double16', in bytes. */
#define ALIGNOF_DOUBLE16 128

/* The normal alignment of `float16', in bytes. */
#define ALIGNOF_FLOAT16 64

/* Absolute path of build directory. */
#define BUILDDIR "/home/cxu/X/M_20121205/CFolder/MyWork/Eclipse/development_apex_cl/pocl-0.7"

/* "Build with ICD" */
/* #undef BUILD_ICD */

/*  Defined when CellSPU tools are found */
/* #undef BUILD_SPU */

/* clang executable. */
#define CLANG "/home/cxu/CWORK/OpenCL/release_32/bin_install/bin/clang"

/* CL compiler flags. */
#define CLFLAGS ""

/* "Use a custom buffer allocator" */
#define CUSTOM_BUFFER_ALLOCATOR /**/

/* "Export OpenCL symbols" */
#define DIRECT_LINKAGE /**/

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Defined if The OpenGL Extension Wrangler library is found */
/* #undef HAVE_GLEW */

/* Define to 1 if you have the <GL/gl.h> header file. */
#define HAVE_GL_GL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Defined to 1 if ocl-icd is found on system */
/* #undef HAVE_OCL_ICD */

/* Define to 1 if you have the <OpenGL/OpenGL.h> header file. */
#define HAVE_OPENGL_OPENGL_H /**/

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* The host triple. */
#define HOST "x86_64-unknown-linux-gnu"

/* Parameters to for host compilation. */
#define HOST_CLANG_FLAGS ""

/* The host CPU type. */
#define HOST_CPU "x86_64"

/* Parameter to compiler to generate loadable module. */
#define HOST_LD_FLAGS "-shared -lm"

/* Parameters to llc for code generation in the host. */
#define HOST_LLC_FLAGS "-relocation-model=pic"

/* Use the libkernel from lib/kernel/$KERNEL_DIR/ */
#define KERNEL_DIR "x86_64"

/* LLVM compiler executable. */
#define LLC "/home/cxu/CWORK/OpenCL/release_32/bin_install/bin/llc"

/* "Using LLVM 3.1" */
/* #undef LLVM_3_1 */

/* "Using LLVM 3.2" */
#define LLVM_3_2 /**/

/* LLVM linker binary */
#define LLVM_LD "pocl-llvm-ld"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "pocl"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "pocl-devel@lists.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "pocl"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "pocl 0.7"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "pocl"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.7"

/* The installation directory */
#define POCL_INSTALLATION_ROOT "/home/cxu/X/M_20121205/CFolder/MyWork/Eclipse/development_apex_cl/pocl-0.7/bin_install"

/* The installation directory */
#define POCL_INSTALLED_DATA "/home/cxu/X/M_20121205/CFolder/MyWork/Eclipse/development_apex_cl/pocl-0.7/bin_install/share/pocl"

/* The size of `double', as computed by sizeof. */
#define SIZEOF_DOUBLE 8

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* The size of `__fp16', as computed by sizeof. */
#define SIZEOF___FP16 2

/* Root for the project sources. */
#define SRCDIR "C:\\"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* The target triple. */
#define TARGET "x86_64-unknown-linux-gnu"

/* Parameters to for target compilation. */
#define TARGET_CLANG_FLAGS ""

/* Parameters to llc for code generation in the target. */
#define TARGET_LLC_FLAGS ""

/* Version number of package */
#define VERSION "0.7"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif
