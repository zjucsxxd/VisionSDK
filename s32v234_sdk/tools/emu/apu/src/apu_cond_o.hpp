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
/**
* \file APU_cond.h
* \brief APU vector conditions
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#ifndef _APU_COND_H_
#define _APU_COND_H_

#include "apu_config.hpp"
#include "apu_vbool.hpp"
#include <cassert>

namespace APEX2
{
	extern int _tileWidthInChunks;
/****************************************************************************
* constants
****************************************************************************/

//7 in APU-C + 1 ACF
const int VECTOR_CONDITION_STACK_SIZE = 8;

/****************************************************************************
* types
****************************************************************************/

//singleton
class VectorConditionController
{
public:
  static VectorConditionController& Instance(){
	  if (mpInstance == NULL) {
		  mpInstance = new VectorConditionController();
	  }
	  return *mpInstance;
  };

  /***********************************************************************
  * Initializes the active CUs
  */
  void Init();

 /****************************************************************************
* Pushes condition into the stack.
****************************************************************************/

  void Push(const vbool& condition);

/****************************************************************************
* Pops the condition from the stack.
****************************************************************************/

  void Pop();

/****************************************************************************
* Flips the condition (else branch). Only can flip once!
****************************************************************************/

  void Flip();

private:

  static VectorConditionController *mpInstance;
  
  //current stack depth
  int mCurrentLevel;

  struct ConditionStackElement
  {
    //condition vector
    vbool condition;
	//was the condition flipped already? If so, it can't be flipped anymore.
    bool wasFlipped;
  };
  ConditionStackElement mConditionStack[VECTOR_CONDITION_STACK_SIZE];

  VectorConditionController();
  VectorConditionController(VectorConditionController const&){ }
  VectorConditionController& operator=(VectorConditionController const&){return *this;}
 
};

//syntax sugar macros for APU-C syntax

#define vif(C)  (VectorConditionController::Instance().Push(C));
#define velse   (VectorConditionController::Instance().Flip());
#define vendif  (VectorConditionController::Instance().Pop());

}

#endif // _APU_COND_H_
