#ifndef __asmport_h__
#define __asmport_h__   1

#ifdef __ghs__ /***** GHS ****************************************************/

#define ASM_PREFIX(x)   x

#define ASM_EQUATE(label,value)
#define ASM_EXTERN(label)       import ASM_PREFIX(label)
#define ASM_ALIGN(value)
#define ASM_PUBLIC(label)       EXPORT ASM_PREFIX(label)
#define ASM_CONST16(value)
#define ASM_CONST32(value)      .word value
#define ASM_LABEL(label)        label
#define ASM_LABEL_CONST32(label,value)

#define ASM_CODE_SECTION(name)  SECTION name : CODE
#define ASM_DATA_SECTION(name)  SECTION name : DATA
#define ASM_END

#define ASM_THUMB		THUMB

#else /***** GCC *************************************************************/

#define ASM_PREFIX(x)   x

#define ASM_EQUATE(label,value) .equ label, value
#define ASM_EXTERN(label)       .extern ASM_PREFIX(label)
#define ASM_ALIGN(value)        .balign value
#define ASM_PUBLIC(label)       .global ASM_PREFIX(label)
#define ASM_CONST16(value)      .short value
#define ASM_CONST32(value)      .long value
#define ASM_LABEL(label)        label:
#define ASM_LABEL_CONST32(label,value) label: .long value

#define ASM_CODE_SECTION(name)  .section name, "x"
#define ASM_DATA_SECTION(name)  .section name, "w"
#define ASM_END                 .end

#define ASM_COMP_SPECIFIC_DIRECTIVES .syntax unified

#define ASM_PUBLIC_BEGIN(name) .type name,%function
#define ASM_PUBLIC_FUNC(name)
#define ASM_PUBLIC_END(name)

#define ASM_THUMB		.thumb

#endif /* __ghs__ */

#endif /* __asmport_h__ */
