/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2015 Freescale Semiconductor;
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
* \file     seq_sa_kernel_api.h
* \brief    declarations for missing kernel API for standalone environment
* \author   Tomas Babinec
* \version  0.1
* \date     9.9.2015
* \note
****************************************************************************/

#ifndef SEQ_SA_KERNEL_API_H
#define SEQ_SA_KERNEL_API_H

  // to get micro seconds since reset   
  extern unsigned long get_uptime_microS(void); 

  // define missing kernel API features
  #define IRQ_HANDLED 0
  #define jiffies     (get_uptime_microS())
  #define EIO         (-SEQ_DRV_FAILURE)
  #define printk //printf
  #define ERESTARTSYS       1
  #define spinlock_t        uint32_t
  #define wait_queue_head_t uint32_t

  struct tasklet_struct
  {
    void (*func)(unsigned long);
    unsigned long data;
  } tasklet_struct_t;

  #define GFP_KERNEL 12345
  #define kmalloc(_size, _unused) (malloc(_size))
  #define kfree(_pointer)         (free(_pointer))

  #define DECLARE_TASKLET(_name, _func, _data)  \
  struct tasklet_struct _name = { _func, _data }

  #define tasklet_schedule(_pTasklet) ((_pTasklet)->func((_pTasklet)->data))

  #define ioremap(_addr, _size)     (_addr)
  #define iounmap(_addr)            
  #define spin_lock_init(_pLock)    (*_pLock  = 0)
  #define spin_lock(_pLock)         (*_pLock  = 0)
  #define spin_unlock(_pLock)       (*_pLock  = 0)
  #define spin_lock_irqsave(_pLock, _Flags) (*_pLock  = 0, _Flags = 0)
  #define spin_unlock_irqrestore(_pLock, _Flags) (*_pLock  = 0, _Flags = 0)
  #define init_waitqueue_head(_pWq) (*_pWq    = 0);
  #define wake_up(_pWq)
  #define wake_up_interruptible(_pWq)

  #define wait_event(_wq, _cond)      \
  ({                                  \
      while(!(_cond))                 \
      {                               \
        ;\
      }                               \
  }) // wait_event

  #define wait_event_interruptible(_wq, _cond)        \
  ({                                                  \
      int __ret = 0;                                  \
      wait_event(_wq,_cond);                          \
      __ret;                                          \
  }) // wait_event_interruptible

  #define wait_event_timeout(_wq, _cond, _timeout)    \
  ({                                                  \
      int __ret = 2;                                  \
      wait_event(_wq, _cond);                         \
      __ret;                                          \
  }) // wait_event_timeout

  #define copy_from_user(_dst, _src, _size)           \
  ({                                                  \
    int __ret = 0;                                    \
    memcpy(_dst, _src, _size);                        \
    __ret;                                            \
  })

  #define copy_to_user(_dst, _src, _size)             \
  ({                                                  \
    int __ret = 0;                                    \
    memcpy(_dst, _src, _size);                        \
    __ret;                                            \
  })
  
  typedef unsigned long	jiffy_t;

#endif // ifndef SEQ_SA_KERNEL_API_H