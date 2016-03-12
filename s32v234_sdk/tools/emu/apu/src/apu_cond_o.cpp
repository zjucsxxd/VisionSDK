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
* \file APU_cond.cpp
* \brief APU vector conditions implementation
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#include "apu_cond.hpp"

using namespace APEX2;

/****************************************************************************
* globals
****************************************************************************/

//global vector condition state
bool APEX2::gEnabledCUs[VSIZE];
VectorConditionController* VectorConditionController::mpInstance = NULL;

/****************************************************************************
* functions
****************************************************************************/

VectorConditionController::VectorConditionController(): mCurrentLevel(0)
{
	Init();
}


void VectorConditionController::Init() {
	PAUSE_CYCLE_COUNTING
		//for (int i = 0; i < VSIZE; ++i)

		for (int i = 0; i < _tileWidthInChunks; ++i)
		{
			gEnabledCUs[i] = true;
		}

	for (int i = _tileWidthInChunks; i < VSIZE; ++i) {
		gEnabledCUs[i] = false;
	}

	mCurrentLevel = 0;
	mConditionStack[0].condition = true;
	mConditionStack[0].wasFlipped = false;
	RESUME_CYCLE_COUNTING
}

//push/pop/flip implementation

void VectorConditionController::Push(const vbool& condition)
{
  ADD_VECTOR_CYCLES(vif)
  PAUSE_CYCLE_COUNTING
  assert(mCurrentLevel < VECTOR_CONDITION_STACK_SIZE);
  //increase the level
  ++mCurrentLevel;
  //reset flipping
  mConditionStack[mCurrentLevel].wasFlipped = false;
  for (int i = 0; i < VSIZE; ++i)
  {
    //can't use !vbool -> it depends on enabled CUs!
    bool newElement = condition.mElements[i] && gEnabledCUs[i];
    mConditionStack[mCurrentLevel].condition.mElements[i] = newElement;
    gEnabledCUs[i] = newElement;
  }
  RESUME_CYCLE_COUNTING
}

void VectorConditionController::Pop()
{
  PAUSE_CYCLE_COUNTING
  assert(mCurrentLevel >= 0);
  //decrease level
  --mCurrentLevel;
  for (int i = 0; i < VSIZE; ++i)
  {
    gEnabledCUs[i] = mConditionStack[mCurrentLevel].condition.mElements[i];
  }
  RESUME_CYCLE_COUNTING
}

void VectorConditionController::Flip()
{
  ADD_VECTOR_CYCLES(velse)
  PAUSE_CYCLE_COUNTING
  assert(mCurrentLevel > 0);
  assert(!mConditionStack[mCurrentLevel].wasFlipped);
  //flib the boolean values
  for (int i = 0; i < VSIZE; ++i)
  {
    //can't use !vbool -> it depends on enabled CUs!
    bool newElement = !gEnabledCUs[i] && mConditionStack[mCurrentLevel - 1].condition.mElements[i];
    //disable what should be disabled from previous level
    mConditionStack[mCurrentLevel].condition.mElements[i] = newElement;
    gEnabledCUs[i] = newElement;
  }
  //set the state to flipped
  mConditionStack[mCurrentLevel].wasFlipped = true;
  RESUME_CYCLE_COUNTING
}
