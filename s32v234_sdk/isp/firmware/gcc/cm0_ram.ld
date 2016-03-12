ENTRY(_reset)

MEMORY {
  m0_0_intvec	: ORIGIN = 0x0,			LENGTH = 0xC0
  sram_RAM	: ORIGIN = 0x100,		LENGTH = 64K - 16K - 0x100 - 1K
  stack		: ORIGIN = 64K - 16K - 1K,	LENGTH = 1K
  graph		: ORIGIN = 64K - 16K,		LENGTH = 16K
}
   
SECTIONS
{
  .vectable	ORIGIN(m0_0_intvec) :
  {
    __CM0_0_VECTOR_TABLE = .; 
    KEEP(*(.vectable))
  }
  
  .init		ORIGIN(sram_RAM)		: { *(.init)	}
  .text		ALIGN(8)			: { *(.text*)	}
  .rodata	ALIGN(4)			: { *(.rodata*)	}
  .sdabase	ALIGN(16)			: { *(.sdabase*)}
  .sdata	ALIGN(4)			: { *(.sdata*)	}
  .sdata2	ALIGN(4)			: { *(.sdata2*)	}
  .sbss		ALIGN(4)			: { *(.sbss*)	}
  .data		ALIGN(4)			: { *(.data*)	}

  .bss ALIGN(16) :
  {
    __bss_start__ = .;
    *(.bss*)
    __bss_end__ = .;
  }
    
  .stack	ORIGIN(stack) :
  {
    __CM0_0_STACK_ADDRESS = .; 
  } > stack

  .graph	ORIGIN(graph) :
  {
    __graph_start = .; 
  } > graph

} /* SECTIONS */
