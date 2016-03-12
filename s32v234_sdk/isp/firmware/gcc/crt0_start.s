/*
 * File:	crt0_m0_0_start.s
 * Purpose:	Lowest level routines for CM0.
 *
 * Notes:	
 *
 */

.globl _reset
.globl _vectable_base

.extern _comp_init
.extern main
.extern exception 
.extern _done
.extern __CM0_0_STACK_ADDRESS

.thumb

.section .text
_reset:
	/*** disable interrupts ***/
	movs	r0,	#0x1
	msr	PRIMASK,r0
	
	ldr	r0,	=__CM0_0_STACK_ADDRESS	/* set stack */
	mov	sp,	r0

	/*** clear core regs ***/
	movs	r0,	#0x0
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

	movs	r0,	#0x0	/* parameter to main */
	BL	_comp_init	/* call compiler init code */
	BL	main		/* call the C code */
	/*** shouldn't return ***/
	B	_done
