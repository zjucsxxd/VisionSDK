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
* \file OAL_Extras.h
* \brief helpful functions not included in the original OAL
* \author Igor Aleksandrowicz
* \version
* \date 05-August-2013
****************************************************************************/

#ifndef OAL_EXTRAS_H_
#define OAL_EXTRAS_H_

/*****************************************************************************
* prototypes
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/** Gets semaphore by name.
*
* \param apSem pointer to semaphore handle (should not be initialized yet)
* \param apName name of the semaphore
*
* \return LIB_SUCCESS on success, LIB_FAILURE otherwise
*
* \note doesn't have to work for OAL_SEMAPHORE_MUTEX
*****************************************************************************/
LIB_RESULT OAL_SemaphoreGetByName(OAL_SEMAPHORE *apSem, const char *apName);

/****************************************************************************/
/** Sets ownerships of a semaphore.
 * Semaphore owner is responsible for semaphore unlink call.
 * Ownership has no effect on mutexes.
 *
 * \param aSem  semaphore handle
 * \param aOwner  set ownership (true/false)
 *
 * \return LIB_SUCCESS on success, LIB_FAILURE otherwise
 *
 * \note added to better suit gdi needs
 */
LIB_RESULT OAL_SemaphoreOwnershipSet(OAL_SEMAPHORE aSem, bool aOwner);

/****************************************************************************/
/** Creates interprocess mutex structure on the supplied address.
 *
 * \param apSem pointer to output semaphore handle (should not be initialized
 *              yet)
 * \param pName name of the semaphore
 * \param p address where the underlying mutex structure should be created
 *
 * \return LIB_SUCCESS on success, LIB_FAILURE otherwise
 */
LIB_RESULT OAL_SemaphoreCreateInterprocessMutexOnAddress
  (OAL_SEMAPHORE *apSem, const char *apName, void *ap);

/****************************************************************************/
/** Creates an OAL_SEMAPHORE from (already created) mutex address.
 *
 * \param apSem pointer to output semaphore handle (should not be initialized
 *              yet)
 * \param pName name of the semaphore
 * \param p address where the underlying mutex can be found
 *
 * \return LIB_SUCCESS on success, LIB_FAILURE otherwise
 */
LIB_RESULT
  OAL_SemaphoreGetFromMutexAddress(OAL_SEMAPHORE *apSem,
  const char *apName, void *ap);

extern const size_t SEMAPHORE_STRUCT_SIZE;

#ifdef __cplusplus
}
#endif

#endif /* OAL_EXTRAS_H_ */
