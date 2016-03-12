/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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
#include <global_types.h>
#include <oal.h>
#include <global_errors.h>

/*==============================================================================*/
/* Initialize interrupt service routines					*/
/*==============================================================================*/
LIB_RESULT OAL_SISRInit(void (*pSISREntry)(void), unsigned int StackSize, unsigned int priority, const char* pSisrName, OAL_SISR_ID* pSisrId)
{
  LIB_RESULT    rc = LIB_FAILURE;
  if (pSisrId)
  {
    *pSisrId = (OAL_SISR_ID)pSISREntry;
    rc = LIB_SUCCESS;
  }

  return (rc);
}

/*==============================================================================*/
/* Delete interrupt service routines						*/
/*==============================================================================*/
LIB_RESULT OAL_SISRDelete(OAL_SISR_ID SisrId)
{
  return (LIB_SUCCESS);
}

/*==============================================================================*/
/* Connect the ISR with some function						*/
/*==============================================================================*/
void OAL_SISRVecConnect(int VecNumber, void (*pLisrFunction)(int))
{
   // InterruptSetVector((INT_IRQ) VecNumber, pLisrFunction);
}

/*==============================================================================*/
/* Enable IRQs									*/
/*==============================================================================*/
void OAL_SISREnableIrq(unsigned int irq)
{
   // InterruptEnableIRQ((INT_IRQ)irq);
}

/*==============================================================================*/
/* Disable IRQs									*/
/*==============================================================================*/
void OAL_SISRDisableIrq(unsigned int irq)
{
   // InterruptDisableIRQ((INT_IRQ)irq);
}

/*==============================================================================*/
/* Activate SISR								*/
/*==============================================================================*/
void OAL_SISRActivate(OAL_SISR_ID sisr)
{
  void (*HisrFunc)(void);
  if (sisr)
  {
    HisrFunc = (void(*)(void))sisr;
    HisrFunc();
  }
}

/*==============================================================================*/
/* Interrupt lock								*/
/*==============================================================================*/
void OAL_InterruptLock(void)
{
   // disable_interrupts();
}

/*==============================================================================*/
/* Interrupt free								*/
/*==============================================================================*/
void OAL_InterruptFree(void)
{
   // reenable_interrupts();
}

