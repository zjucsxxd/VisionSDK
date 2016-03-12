/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
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

  
/*!*********************************************************************************
*  @file graph_templates.h
*  @brief ACF graph macros for 2,3 Inputs and 1,2 Ouptuts
***********************************************************************************/
#ifndef GRAPH_TEMPLATES_H
#define GRAPH_TEMPLATES_H

#include "stringify_macros.h"

#ifndef INPUT_2
#define INPUT_2		"INPUT_2"
#endif

#define GR_IN_0		"INPUT_0" //"GR_In_0"
#define GR_IN_1		"INPUT_1" //"GR_In_1"
#define GR_IN_2		"INPUT_2" //"GR_In_2"
#define GR_ALPHA	"ALPHA"
#define GR_DELTA_X	"DELTA_X"
#define GR_OUT_0	"OUTPUT_0" //"GR_Out_0"
#define GR_OUT_1	"OUTPUT_1" //"GR_Out_1"
#define GR_F_SCALE	"F_SCALE" 
#define GR_F_COEFF	"F_COEFF" 
#define GR_F_ROW	"F_ROW" 
#define GR_F_COL	"F_COL" 

#define kernelInstName(kn)	XSTR(plainConcat(kn,_inst))
#define kernelName(kn)		XSTR(kn)

#define graphClassName(kn)	plainConcat(graph_,kn)
//#define GRAPH_CLASS_DECL(kn) class graphClassName(kn)


#define GRAPH_CLASS_DEF_1In_1Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddOutputPort(GR_OUT_0); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(KernelPort(knInst,OUTPUT_0), GraphPort(GR_OUT_0)); \
		}\
};


#define GRAPH_CLASS_DEF_2In_1Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddInputPort(GR_IN_1); \
		AddOutputPort(GR_OUT_0); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(GraphPort(GR_IN_1), KernelPort(knInst, INPUT_1)); \
		Connect(KernelPort(knInst,OUTPUT_0), GraphPort(GR_OUT_0)); \
	}\
};

#define GRAPH_CLASS_DEF_2In_1Alpha_1Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddInputPort(GR_IN_1); \
		AddInputPort(GR_ALPHA); \
		AddOutputPort(GR_OUT_0); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(GraphPort(GR_IN_1), KernelPort(knInst, INPUT_1)); \
		Connect(GraphPort(GR_ALPHA), KernelPort(knInst, GR_ALPHA));\
		Connect(KernelPort(knInst,OUTPUT_0), GraphPort(GR_OUT_0)); \
		}\
};


#define GRAPH_CLASS_DEF_3In_1Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddInputPort(GR_IN_1); \
		AddInputPort(GR_IN_2);  \
		AddOutputPort(GR_OUT_0); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(GraphPort(GR_IN_1), KernelPort(knInst, INPUT_1)); \
		Connect(GraphPort(GR_IN_2), KernelPort(knInst, INPUT_2)); \
		Connect(KernelPort(knInst,OUTPUT_0), GraphPort(GR_OUT_0)); \
      }\
};

#define GRAPH_CLASS_DEF_2In_2Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddInputPort(GR_IN_1); \
		AddInputPort(GR_OUT_0); \
		AddOutputPort(GR_OUT_1); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(GraphPort(GR_IN_1), KernelPort(knInst, INPUT_1)); \
		Connect(KernelPort(knInst, OUTPUT_0), GraphPort(GR_OUT_0)); \
		Connect(KernelPort(knInst, OUTPUT_1), GraphPort(GR_OUT_1)); \
		}\
};

#define GRAPH_CLASS_DEF_3In_2Out(kn) class plainConcat(graph_,kn): public ACF_Graph { \
	public:\
	  void Create() {\
	    XREGISTER_ACF_KERNEL(kn); \
		SetIdentifier(XSTR(graphClassName(kn))); \
		std::string knInst = kernelInstName(kn);\
		AddKernel(knInst, kernelName(kn));\
		AddInputPort(GR_IN_0); \
		AddInputPort(GR_IN_1); \
		AddInputPort(GR_IN_2); \
		AddInputPort(GR_OUT_0); \
		AddOutputPort(GR_OUT_1); \
		Connect(GraphPort(GR_IN_0), KernelPort(knInst, INPUT_0)); \
		Connect(GraphPort(GR_IN_1), KernelPort(knInst, INPUT_1)); \
		Connect(GraphPort(GR_IN_2), KernelPort(knInst, INPUT_2)); \
		Connect(KernelPort(knInst, OUTPUT_0), GraphPort(GR_OUT_0)); \
		Connect(KernelPort(knInst, OUTPUT_1), GraphPort(GR_OUT_1)); \
	}\
};

#endif
