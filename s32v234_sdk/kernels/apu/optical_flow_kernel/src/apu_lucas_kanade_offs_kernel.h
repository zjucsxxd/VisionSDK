#ifndef APU_LUCAS_KANADE_OFFS_KERNEL_H
#define APU_LUCAS_KANADE_OFFS_KERNEL_H


#define LUCAS_KANADE_MISMATCH_KN					"apu_lucas_kanade_mismatch"
#define LUCAS_KANADE_ACCUM_KN						"apu_lucas_kanade_accum"
#define LUCAS_KANADE_OFFSET_KN						"apu_lucas_kanade_offset"
#define LUCAS_KANADE_OFFSET_X_KN					"apu_lucas_kanade_offset_x"
#define LUCAS_KANADE_OFFSET_Y_KN					"apu_lucas_kanade_offset_y"

#define LUCAS_KANADE_KERNEL_IMG_A					"INPUT_IMG_A"
#define LUCAS_KANADE_KERNEL_IMG_B					"INPUT_IMG_B"
#define LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_HIGH	"OUT_OFFS_G_X_VECT_HIGH"
#define LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_HIGH	"OUT_OFFS_G_Y_VECT_HIGH"
#define LUCAS_KANADE_KERNEL_OFFS_G_OUT_X_VECT_LOW	"OUT_OFFS_G_X_VECT_LOW"
#define LUCAS_KANADE_KERNEL_OFFS_G_OUT_Y_VECT_LOW	"OUT_OFFS_G_Y_VECT_LOW"


#define LUCAS_KANADE_KERNEL_OFFS_G_IN_X_VECT	"IN_OFFS_G_X_VECTOR"
#define LUCAS_KANADE_KERNEL_OFFS_G_IN_Y_VECT	"IN_OFFS_G_Y_VECTOR"
#define LUCAS_KANADE_KERNEL_OFFS_ETA_X_VECT		"OFFS_ETA_X_VECTOR"
#define LUCAS_KANADE_KERNEL_OFFS_ETA_Y_VECT		"OFFS_ETA_Y_VECTOR"

#define LUCAS_KANADE_KERNEL_DELTAK_IMG			"IN_DELTA_K_IMG"
#define LUCAS_KANADE_KERNEL_DELTAK_GRADX_IMG	"OUT_DELTAK_GRADX_IM"
#define LUCAS_KANADE_KERNEL_DELTAK_GRADY_IMG	"OUT_DELTAK_GRADY_IM"

#define LUCAS_KANADE_KERNEL_GRAD_X				"IN_GRAD_X"
#define LUCAS_KANADE_KERNEL_GRAD_Y				"IN_GRAD_Y"
#define LUCAS_KANADE_KERNEL_ACC_GRAD_X_SQR		"IN_ACC_GRAD_X_SQR"
#define LUCAS_KANADE_KERNEL_ACC_GRAD_Y_SQR		"IN_ACC_GRAD_Y_SQR"
#define LUCAS_KANADE_KERNEL_ACC_GRAD_XY			"IN_ACC_GRAD_XY"
#define LUCAS_KANADE_KERNEL_ACC_DET_G			"IN_ACC_DET_G"

#define LUCAS_KANADE_KERNEL_VALID_POINTS		"IN_VALID_POINTS"

#define LUCAS_KANADE_KERNEL_ETA_NORM			"OUT_ETA_NORM"


#ifdef APEX2_EMULATE

extern KERNEL_INFO _kernel_info_apu_lucas_kanade_offset;

void apu_lucas_kanade_offset(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/);


extern KERNEL_INFO _kernel_info_apu_lucas_kanade_offset_x;

void apu_lucas_kanade_offset_x(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGXVect_high, kernel_io_desc lOutOffsetGXVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/);

extern KERNEL_INFO _kernel_info_apu_lucas_kanade_offset_y;

void apu_lucas_kanade_offset_y(/*kernel_io_desc lInOffsetGXVect, kernel_io_desc lInOffsetGYVect,*/
	kernel_io_desc lInOffsetEtaXVect, kernel_io_desc lInOffsetEtaYVect,
	kernel_io_desc lOutOffsetGYVect_high, kernel_io_desc lOutOffsetGYVect_low,
	kernel_io_desc inGradXSqrImg, kernel_io_desc inGradYSqrImg,
	kernel_io_desc inGradXGradYImg/*, kernel_io_desc inDetGImg, */ /*kernel_io_desc lEtaNorm*/);


#endif

#endif
