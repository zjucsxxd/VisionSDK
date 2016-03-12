// --- Default link map for the INTEGRITY Kernel Address Space ---
//
// Information about the format and various sections of the linker directives
// files can be found in the "Linker Directives Files" section of
// the "Building INTEGRITY Applications" chapter of the INTEGRITY Development
// Guide, and in the "Linker Directives Files" section of the "File Structure"
// chapter of the INTEGRITY BSP User's Guide.
//
// Per-CPU linker directives files included here are located in the common
// library directory corresponding to the BSP. For more infromation refer to
// the "Common Library Directories" section of the INTEGRITY Development
// Guide.

DEFAULTS
{
	__INTEGRITY_DebugBufferSize	= 0x10000
	__INTEGRITY_DebugEntities	= 128
	__INTEGRITY_DebugEventLogSize	= 0x20000
	__INTEGRITY_HeapSize 		= 0x60000
	__INTEGRITY_StackSize 		= 0x4000
	__INTEGRITY_KernelStackSize	= 0x4000
	__INTEGRITY_FiqStackSize	= 0x1000
	__INTEGRITY_DownloadSize 	= 0x180000
	__INTEGRITY_MaxCoreSize 	= 0x200000
	__INTEGRITY_BootAreaSize 	= 0x800000
	__INTEGRITY_FlashBufSize	= 0x20000
}

MEMORY
{
	// ram_memory is the range of kernel RAM, stated in terms of kernel
	// addresses. This can be varied independently of the physical address
	// at which the kernel is loaded.
	ram_memory	:	ORIGIN = 0xc0000000, LENGTH = 256M
}

SECTIONS
{
	// The .ramlowerlimit section exists at the first kernel address at
	// which kernel RAM is mapped by the BSP.
	.ramlowerlimit					: > ram_memory
	.ramstart	PAD(0x100000)			:
	#include "ram_sections.ld"
	.probescratch0	align(0x4000) NOCLEAR		: { __probescratch0=.; .+=128; } > .
	.probescratch1	align(0x4000) NOCLEAR		: { __probescratch1=.; .+=128; } > .
	.armspecialbss					: > .
	.ramend	 	align(0x1000)			: > ram_memory
	// The .ramlimit section exists just past the last kernel address at
	// which kernel RAM can be mapped by the BSP. The amount of kernel RAM
	// is never more than the gap between .ramlowerlimit and .ramlimit.
	.ramlimit	MEMENDADDR(ram_memory)		:
}
