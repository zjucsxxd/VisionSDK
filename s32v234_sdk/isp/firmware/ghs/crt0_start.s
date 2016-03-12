;/*
; * File:	crt0_m0_0_start.s
; * Purpose:	Lowest level routines for CM0.
; *
; * Notes:	
; *
; */

;       AREA   Crt0, CODE, READONLY      ; name this block of code

  	;SECTION .noinit : CODE
	;.section .noinit
	EXPORT _reset
	import main
	import exception
	import __CM0_0_STACK_ADDRESS
	import __ghsbinfo_clear
	import __ghseinfo_clear

	THUMB
.section .vectable
  .word __CM0_0_STACK_ADDRESS	; #0 stack
  .word (_reset +1)		; #1 reset
  .word exception		; #2 NMI
  .word exception		; #3 hard fault
  .word __done			; #4
  .word __done			; #5
  .word __done			; #6
  .word __done			; #7
  .word __done			; #8
  .word __done			; #9
  .word __done			; #a
  .word __done			; #b
  .word __done			; #c
  .word __done			; #d
  .word __done			; #e
  .word __done			; #f

.section .text
_reset
	; *** disable interrupts ***
	movs	r0,	0x1
	msr	PRIMASK,r0
	
	ldr	r0,	=__CM0_0_STACK_ADDRESS	; set stack 
	mov	sp,	r0

	; *** clear ghs ***
	movs	r0,	0x0
	ldr	r1,	=__ghsbinfo_clear
	ldr	r2,	=__ghseinfo_clear
clearGHS
	strb	r0,	[r1]
	adds	r1,	r1,	#0x1
	cmp	r1,	r2
	blt	clearGHS

	; *** clear BSS ***
	movs	r0,	0x0
	ldr	r1,	=BSS_START
	ldr	r2,	=BSS_END
clearBSS
	strb	r0,	[r1]
	adds	r1,	r1,	#0x1
	cmp	r1,	r2
	blt	clearBSS
	
	; *** clear core regs ***
	movs	r0,	0x0
	mov	r1,	r0
	mov	r2,	r0
	mov	r3,	r0
	mov	r4,	r0
	mov	r5,	r0
	mov	r6,	r0
	mov	r7,	r0
	mov	r8,	r0
	mov	r9,	r0
	mov	r10,	r0
	mov	r11,	r0
	mov	r12,	r0

	movs	r0,	0x0	; parameter to main
	BL	main		; call the C code
	; *** shouldn't return ***
__done
	B	__done
