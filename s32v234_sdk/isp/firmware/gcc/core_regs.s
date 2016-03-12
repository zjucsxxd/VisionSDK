	.thumb

; ###################################################################
	.globl	getIPSR
getIPSR:
	.text
	.align	2

	mrs	r0, IPSR
	bx	lr

; ###################################################################
	.globl	getPRIMASK
getPRIMASK:
	.text
	.align	2

	mrs	r0, PRIMASK
	bx	lr

; ###################################################################
	.globl	getCONTROL
getCONTROL:
	.text
	.align	2

	mrs	r0, CONTROL
	bx	lr
