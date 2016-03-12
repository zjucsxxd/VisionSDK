/******************************************************************************/
/*  FILE NAME: mem_map          Copyright (c) Freescale 2005                  */
/*                                                                            */
/*  Freescale Confidential Proprietary, NDA Required                          */
/*                                                                            */
/*  This document contains information on a new product. Specifications       */
/*  and information herein are subject to change without notice.              */
/*                                                                            */
/*  DESCRIPTION:  This file defines the registers and bit fields for the      */
/*                JDP Chipset.                                                */
/*                                                                            */
/*  REV         DATE                                                          */
/*  ---         ----                                                          */
/*  1118 Jan 2006 20:18:24                                                    */
/*                                                                            */
/*  COMMENTS                                                                  */
/*  --------                                                                  */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*  FREESCALE SEMICONDUCTOR SOFTWARE LICENSE AGREEMENT                        */
/*                                                                            */
/*  This is a legal agreement between you (either as an individual or as an   */
/*  authorized representative of your employer) and Freescale Semiconductor,  */
/*  Inc. ("Freescale"). It concerns your rights to use this file and any      */
/*  accompanying written materials (the "Software"). In consideration for     */
/*  Freescale allowing you to access the Software, you are agreeing to be     */
/*  bound by the terms of this Agreement. If you do not agree to all of the   */
/*  terms of this Agreement, do not download the Software. If you change your */
/*  mind later, stop using the Software and delete all copies of the Software */
/*  in your possession or control. Any copies of the Software that you have   */
/*  already distributed, where permitted, and do not destroy will continue to */
/*  be governed by this Agreement. Your prior use will also continue to be    */
/*  governed by this Agreement.                                               */
/*                                                                            */
/*  LICENSE GRANT.  Freescale grants to you, free of charge, the non-         */
/*  exclusive, non-transferable right (1) to use the Software, (2) to         */
/*  reproduce the Software, (3) to prepare derivative works of the Software,  */
/*  (4) to distribute the Software and derivative works thereof in source     */
/*  (human-readable) form and object (machine-readable) form, and (5) to      */
/*  sublicense to others the right to use the distributed Software. If you    */
/*  violate any of the terms or restrictions of this Agreement, Freescale may */
/*  immediately terminate this Agreement, and require that you stop using and */
/*  delete all copies of the Software in your possession or control.          */
/*                                                                            */
/*  COPYRIGHT.  The Software is licensed to you, not sold. Freescale owns the */
/*  Software, and United States copyright laws and international treaty       */
/*  provisions protect the Software. Therefore, you must treat the Software   */
/*  like any other copyrighted material (e.g. a book or musical recording).   */
/*  You may not use or copy the Software for any other purpose than what is   */
/*  described in this Agreement. Except as expressly provided herein,         */
/*  Freescale does not grant to you any express or implied rights under any   */
/*  Freescale or third-party patents, copyrights, trademarks, or trade        */
/*  secrets. Additionally, you must reproduce and apply any copyright or other*/
/*  proprietary rights notices included on or embedded in the Software to any */
/*  copies or derivative works made thereof, in whole or in part, if any.     */
/*                                                                            */
/*  SUPPORT.  Freescale is NOT obligated to provide any support, upgrades or  */
/*  new releases of the Software. If you wish, you may contact Freescale and  */
/*  report problems and provide suggestions regarding the Software. Freescale */
/*  has no obligation whatsoever to respond in any way to such a problem      */
/*  report or suggestion. Freescale may make changes to the Software at any   */
/*  time, without any obligation to notify or provide updated versions of the */
/*  Software to you.                                                          */
/*                                                                            */
/*  NO WARRANTY.  TO THE MAXIMUM EXTENT PERMITTED BY LAW, FREESCALE EXPRESSLY */
/*  DISCLAIMS ANY WARRANTY FOR THE SOFTWARE. THE SOFTWARE IS PROVIDED "AS IS",*/
/*  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,       */
/*  WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR*/
/*  A PARTICULAR PURPOSE, OR NON-INFRINGEMENT. YOU ASSUME THE ENTIRE RISK     */
/*  ARISING OUT OF THE USE OR PERFORMANCE OF THE SOFTWARE, OR ANY SYSTEMS YOU */
/*  DESIGN USING THE SOFTWARE (IF ANY). NOTHING IN THIS AGREEMENT MAY BE      */
/*  CONSTRUED AS A WARRANTY OR REPRESENTATION BY FREESCALE THAT THE SOFTWARE  */
/*  OR ANY DERIVATIVE WORK DEVELOPED WITH OR INCORPORATING THE SOFTWARE WILL  */
/*  BE FREE FROM INFRINGEMENT OF THE INTELLECTUAL PROPERTY RIGHTS OF THIRD    */
/*  PARTIES.                                                                  */
/*                                                                            */
/*  INDEMNITY.  You agree to fully defend and indemnify Freescale from any and*/
/*  all claims, liabilities, and costs (including reasonable attorney’s fees) */
/*  related to (1) your use (including your sublicensee’s use, if permitted)  */
/*  of the Software or (2) your violation of the terms and conditions of this */
/*  Agreement.                                                                */
/*                                                                            */
/*  LIMITATION OF LIABILITY.  IN NO EVENT WILL FREESCALE BE LIABLE, WHETHER IN*/
/*  CONTRACT, TORT, OR OTHERWISE, FOR ANY INCIDENTAL, SPECIAL, INDIRECT,      */
/*  CONSEQUENTIAL OR PUNITIVE DAMAGES, INCLUDING, BUT NOT LIMITED TO, DAMAGES */
/*  FOR ANY LOSS OF USE, LOSS OF TIME, INCONVENIENCE, COMMERCIAL LOSS, OR LOST*/
/*  PROFITS, SAVINGS, OR REVENUES TO THE FULL EXTENT SUCH MAY BE DISCLAIMED BY*/
/*  LAW.                                                                      */
/*                                                                            */
/*  COMPLIANCE WITH LAWS; EXPORT RESTRICTIONS.  You must use the Software in  */
/*  accordance with all applicable U.S. laws, regulations and statutes. You   */
/*  agree that neither you nor your licensees (if any) intend to or will,     */
/*  directly or indirectly, export or transmit the Software to any country in */
/*  violation of U.S. export restrictions.                                    */
/*                                                                            */
/*  GOVERNMENT USE.  Use of the Software and any corresponding documentation, */
/*  if any, is provided with RESTRICTED RIGHTS. Use, duplication or disclosure*/
/*  by the Government is subject to restrictions as set forth in subparagraph */
/*  (c)(1)(ii) of The Rights in Technical Data and Computer Software clause at*/
/*  DFARS 252.227-7013 or subparagraphs (c)(l) and (2) of the Commercial      */
/*  Computer Software--Restricted Rights at 48 CFR 52.227-19, as applicable.  */
/*  Manufacturer is Freescale Semiconductor, Inc., 6501 William Cannon Drive  */
/*  West, Austin, TX, 78735.                                                  */
/*                                                                            */
/*  HIGH RISK ACTIVITIES.  You acknowledge that the Software is not fault     */
/*  tolerant and is not designed, manufactured or intended by Freescale for   */
/*  incorporation into products intended for use or resale in on-line control */
/*  equipment in hazardous, dangerous to life or potentially life-threatening */
/*  environments requiring fail-safe performance, such as in the operation of */
/*  nuclear facilities, aircraft navigation or communication systems, air     */
/*  traffic control, direct life support machines or weapons systems, in which*/
/*  the failure of products could lead directly to death, personal injury or  */
/*  severe physical or environmental damage ("High Risk Activities"). You     */
/*  specifically represent and warrant that you will not use the Software or  */
/*  any derivative work of the Software for High Risk Activities.             */
/*                                                                            */
/*  CHOICE OF LAW; VENUE; LIMITATIONS.  You agree that the statutes and laws  */
/*  of the United States and the State of Texas, USA, without regard to       */
/*  conflicts of laws principles, will apply to all matters relating to this  */
/*  Agreement or the Software, and you agree that any litigation will be      */
/*  subject to the exclusive jurisdiction of the state or federal courts in   */
/*  Texas, USA. You agree that regardless of any statute or law to the        */
/*  contrary, any claim or cause of action arising out of or related to this  */
/*  Agreement or the Software must be filed within one (1) year after such    */
/*  claim or cause of action arose or be forever barred.                      */
/*                                                                            */
/*  PRODUCT LABELING.  You are not authorized to use any Freescale trademarks,*/
/*  brand names, or logos.                                                    */
/*                                                                            */
/*  ENTIRE AGREEMENT.  This Agreement constitutes the entire agreement between*/
/*  you and Freescale regarding the subject matter of this Agreement, and     */
/*  supersedes all prior communications, negotiations, understandings,        */
/*  agreements or representations, either written or oral, if any. This       */
/*  Agreement may only be amended in written form, executed by you and        */
/*  Freescale.                                                                */
/*                                                                            */
/*  SEVERABILITY.  If any provision of this Agreement is held for any reason  */
/*  to be invalid or unenforceable, then the remaining provisions of this     */
/*  Agreement will be unimpaired and, unless a modification or replacement of */
/*  the invalid or unenforceable provision is further held to deprive you or  */
/*  Freescale of a material benefit, in which case the Agreement will         */
/*  immediately terminate, the invalid or unenforceable provision will be     */
/*  replaced with a provision that is valid and enforceable and that comes    */
/*  closest to the intention underlying the invalid or unenforceable          */
/*  provision.                                                                */
/*                                                                            */
/*  NO WAIVER.  The waiver by Freescale of any breach of any provision of this*/
/*  Agreement will not operate or be construed as a waiver of any other or a  */
/*  subsequent breach of the same or a different provision.                   */
/*                                                                            */
/******************************************************************************/


/*****************************************************************
*
* EVT_CTRL Registers
*
******************************************************************/




/* Instance EVT_CTRL */

#define EVT_CTRL_BASEADDRESS           0x40002000

/* Register definitions */

/* 0 */
#define EVT_CTRL_DONE_ENGN_TYPE_OFF 0x00000000
#define EVT_CTRL_DONE_ENGN_TYPE        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_DONE_ENGN_TYPE_OFF))
#define EVT_CTRL_X_DONE_ENGN_TYPE(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_DONE_ENGN_TYPE_OFF + ((x)*0x0)))

#define EVT_CTRL_DONE_ENGN_TYPE_RESET_VALUE 0x00000000
#define EVT_CTRL_DONE_ENGN_TYPE_VOLATILE 0x0
#define EVT_CTRL_DONE_ENGN_TYPE_BITFIELD_MASK 0x00000007
#define EVT_CTRL_DONE_ENGN_TYPE_RWMASK 0x00000000
#define EVT_CTRL_DONE_ENGN_TYPE_ROMASK 0x00000007
#define EVT_CTRL_DONE_ENGN_TYPE_WOMASK 0x00000000
#define EVT_CTRL_DONE_ENGN_TYPE_UNUSED_MASK 0xFFFFFFF8

/* 0 */
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_OFF 0x00000004
#define EVT_CTRL_IPUS_CNTR_MAX_VAL     (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_CNTR_MAX_VAL_OFF))
#define EVT_CTRL_X_IPUS_CNTR_MAX_VAL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_CNTR_MAX_VAL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_CNTR_MAX_VAL_RESET_VALUE 0x00000001
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_VOLATILE 0x0
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_BITFIELD_MASK 0x0000000F
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_RWMASK 0x0000000F
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_ROMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_WOMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_UNUSED_MASK 0xFFFFFFF0

/* 0 */
#define EVT_CTRL_IPUS_CNTR_CLREVT_OFF 0x0000000C
#define EVT_CTRL_IPUS_CNTR_CLREVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_CNTR_CLREVT_OFF))
#define EVT_CTRL_X_IPUS_CNTR_CLREVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_CNTR_CLREVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_CNTR_CLREVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_VOLATILE 0x0
#define EVT_CTRL_IPUS_CNTR_CLREVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_CNTR_CLREVT_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_CNTR_CLREVT_ROMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_WOMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_CNTR_NXTEVT_OFF 0x00000010
#define EVT_CTRL_IPUS_CNTR_NXTEVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_CNTR_NXTEVT_OFF))
#define EVT_CTRL_X_IPUS_CNTR_NXTEVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_CNTR_NXTEVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_CNTR_NXTEVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_CNTR_NXTEVT_VOLATILE 0x0
#define EVT_CTRL_IPUS_CNTR_NXTEVT_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUS_CNTR_NXTEVT_RWMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_NXTEVT_ROMASK 0x0000003F
#define EVT_CTRL_IPUS_CNTR_NXTEVT_WOMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_NXTEVT_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUS_CNTR_ALLEVT_OFF 0x00000014
#define EVT_CTRL_IPUS_CNTR_ALLEVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_CNTR_ALLEVT_OFF))
#define EVT_CTRL_X_IPUS_CNTR_ALLEVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_CNTR_ALLEVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_CNTR_ALLEVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_CNTR_ALLEVT_VOLATILE 0x0
#define EVT_CTRL_IPUS_CNTR_ALLEVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_CNTR_ALLEVT_RWMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_ALLEVT_ROMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_CNTR_ALLEVT_WOMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_ALLEVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_OFF 0x00000018
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_TRIG_ENC_OFF))
#define EVT_CTRL_X_IPUS_ENGN_TRIG_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_TRIG_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUS_ENGN_TRIG_OFF 0x0000001C
#define EVT_CTRL_IPUS_ENGN_TRIG        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_TRIG_OFF))
#define EVT_CTRL_X_IPUS_ENGN_TRIG(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_TRIG_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_TRIG_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_TRIG_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_TRIG_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_TRIG_ROMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_TRIG_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_OFF 0x00000020
#define EVT_CTRL_IPUS_ENGN_FREE_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_FREE_ENC_OFF))
#define EVT_CTRL_X_IPUS_ENGN_FREE_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_FREE_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_FREE_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUS_ENGN_FREE_OFF 0x00000024
#define EVT_CTRL_IPUS_ENGN_FREE        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_FREE_OFF))
#define EVT_CTRL_X_IPUS_ENGN_FREE(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_FREE_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_FREE_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_FREE_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_FREE_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_FREE_ROMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_FREE_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_ENGN_USBL_OFF 0x00000028
#define EVT_CTRL_IPUS_ENGN_USBL        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_USBL_OFF))
#define EVT_CTRL_X_IPUS_ENGN_USBL(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_USBL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_USBL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_USBL_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_USBL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_USBL_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_USBL_ROMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_USBL_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_USBL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_ENGN_FF1_OFF 0x0000002C
#define EVT_CTRL_IPUS_ENGN_FF1         (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_FF1_OFF))
#define EVT_CTRL_X_IPUS_ENGN_FF1(x)    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_FF1_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_FF1_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_FF1_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_FF1_BITFIELD_MASK 0x003F003F
#define EVT_CTRL_IPUS_ENGN_FF1_RWMASK  0x00000000
#define EVT_CTRL_IPUS_ENGN_FF1_ROMASK  0x003F003F
#define EVT_CTRL_IPUS_ENGN_FF1_WOMASK  0x00000000
#define EVT_CTRL_IPUS_ENGN_FF1_UNUSED_MASK 0xFFC0FFC0

/* 0 */
#define EVT_CTRL_IPUS_ENGN_AVL_OFF 0x00000030
#define EVT_CTRL_IPUS_ENGN_AVL         (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_AVL_OFF))
#define EVT_CTRL_X_IPUS_ENGN_AVL(x)    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_AVL_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_AVL_RWMASK  0x00000000
#define EVT_CTRL_IPUS_ENGN_AVL_ROMASK  0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_AVL_WOMASK  0x00000000
#define EVT_CTRL_IPUS_ENGN_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_OFF 0x00000034
#define EVT_CTRL_IPUS_ENGN_BUF_AVL     (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_ENGN_BUF_AVL_OFF))
#define EVT_CTRL_X_IPUS_ENGN_BUF_AVL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_ENGN_BUF_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_ENGN_BUF_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_VOLATILE 0x0
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_RWMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_ROMASK 0xFFFFFFFF
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_WOMASK 0x00000000
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_OFF 0x0000003C
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC  (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_CNTR_CLREVT_ENC_OFF))
#define EVT_CTRL_X_IPUV_CNTR_CLREVT_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_CNTR_CLREVT_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUV_CNTR_CLREVT_OFF 0x00000040
#define EVT_CTRL_IPUV_CNTR_CLREVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_CNTR_CLREVT_OFF))
#define EVT_CTRL_X_IPUV_CNTR_CLREVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_CNTR_CLREVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_CNTR_CLREVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_VOLATILE 0x0
#define EVT_CTRL_IPUV_CNTR_CLREVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_CNTR_CLREVT_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_CNTR_CLREVT_ROMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_WOMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_CLREVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_CNTR_NXTEVT_OFF 0x00000044
#define EVT_CTRL_IPUV_CNTR_NXTEVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_CNTR_NXTEVT_OFF))
#define EVT_CTRL_X_IPUV_CNTR_NXTEVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_CNTR_NXTEVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_CNTR_NXTEVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_CNTR_NXTEVT_VOLATILE 0x0
#define EVT_CTRL_IPUV_CNTR_NXTEVT_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUV_CNTR_NXTEVT_RWMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_NXTEVT_ROMASK 0x0000003F
#define EVT_CTRL_IPUV_CNTR_NXTEVT_WOMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_NXTEVT_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUV_CNTR_ALLEVT_OFF 0x00000048
#define EVT_CTRL_IPUV_CNTR_ALLEVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_CNTR_ALLEVT_OFF))
#define EVT_CTRL_X_IPUV_CNTR_ALLEVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_CNTR_ALLEVT_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_CNTR_ALLEVT_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_CNTR_ALLEVT_VOLATILE 0x0
#define EVT_CTRL_IPUV_CNTR_ALLEVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_CNTR_ALLEVT_RWMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_ALLEVT_ROMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_CNTR_ALLEVT_WOMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_ALLEVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_OFF 0x0000004C
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_TRIG_ENC_OFF))
#define EVT_CTRL_X_IPUV_ENGN_TRIG_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_TRIG_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUV_ENGN_TRIG_OFF 0x00000050
#define EVT_CTRL_IPUV_ENGN_TRIG        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_TRIG_OFF))
#define EVT_CTRL_X_IPUV_ENGN_TRIG(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_TRIG_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_TRIG_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_TRIG_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_TRIG_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_TRIG_ROMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_TRIG_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_OFF 0x00000054
#define EVT_CTRL_IPUV_ENGN_FREE_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_FREE_ENC_OFF))
#define EVT_CTRL_X_IPUV_ENGN_FREE_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_FREE_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_FREE_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUV_ENGN_FREE_OFF 0x00000058
#define EVT_CTRL_IPUV_ENGN_FREE        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_FREE_OFF))
#define EVT_CTRL_X_IPUV_ENGN_FREE(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_FREE_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_FREE_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_FREE_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_FREE_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_FREE_ROMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_FREE_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_ENGN_USBL_OFF 0x0000005C
#define EVT_CTRL_IPUV_ENGN_USBL        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_USBL_OFF))
#define EVT_CTRL_X_IPUV_ENGN_USBL(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_USBL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_USBL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_USBL_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_USBL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_USBL_RWMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_USBL_ROMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_USBL_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_USBL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_ENGN_FF1_OFF 0x00000060
#define EVT_CTRL_IPUV_ENGN_FF1         (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_FF1_OFF))
#define EVT_CTRL_X_IPUV_ENGN_FF1(x)    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_FF1_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_FF1_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_FF1_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_FF1_BITFIELD_MASK 0x003F003F
#define EVT_CTRL_IPUV_ENGN_FF1_RWMASK  0x00000000
#define EVT_CTRL_IPUV_ENGN_FF1_ROMASK  0x003F003F
#define EVT_CTRL_IPUV_ENGN_FF1_WOMASK  0x00000000
#define EVT_CTRL_IPUV_ENGN_FF1_UNUSED_MASK 0xFFC0FFC0

/* 0 */
#define EVT_CTRL_IPUV_ENGN_AVL_OFF 0x00000064
#define EVT_CTRL_IPUV_ENGN_AVL         (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_AVL_OFF))
#define EVT_CTRL_X_IPUV_ENGN_AVL(x)    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_AVL_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_AVL_RWMASK  0x00000000
#define EVT_CTRL_IPUV_ENGN_AVL_ROMASK  0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_AVL_WOMASK  0x00000000
#define EVT_CTRL_IPUV_ENGN_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_OFF 0x00000068
#define EVT_CTRL_IPUV_ENGN_BUF_AVL     (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_ENGN_BUF_AVL_OFF))
#define EVT_CTRL_X_IPUV_ENGN_BUF_AVL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_ENGN_BUF_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_ENGN_BUF_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_VOLATILE 0x0
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_RWMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_ROMASK 0xFFFFFFFF
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_WOMASK 0x00000000
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OFF 0x0000006C
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC  (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OFF))
#define EVT_CTRL_X_OTHR_CNTR_CLREVT_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_VOLATILE 0x0
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_RWMASK 0x0000003F
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_ROMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_WOMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_OTHR_CNTR_CLREVT_OFF 0x00000070
#define EVT_CTRL_OTHR_CNTR_CLREVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_CNTR_CLREVT_OFF))
#define EVT_CTRL_X_OTHR_CNTR_CLREVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_CNTR_CLREVT_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_CNTR_CLREVT_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_VOLATILE 0x0
#define EVT_CTRL_OTHR_CNTR_CLREVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_CNTR_CLREVT_RWMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_CNTR_CLREVT_ROMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_WOMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_CLREVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_CNTR_ALLEVT_OFF 0x00000074
#define EVT_CTRL_OTHR_CNTR_ALLEVT      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_CNTR_ALLEVT_OFF))
#define EVT_CTRL_X_OTHR_CNTR_ALLEVT(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_CNTR_ALLEVT_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_CNTR_ALLEVT_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_CNTR_ALLEVT_VOLATILE 0x0
#define EVT_CTRL_OTHR_CNTR_ALLEVT_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_CNTR_ALLEVT_RWMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_ALLEVT_ROMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_CNTR_ALLEVT_WOMASK 0x00000000
#define EVT_CTRL_OTHR_CNTR_ALLEVT_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OFF 0x00000078
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_TRIG_ENC_OFF))
#define EVT_CTRL_X_OTHR_ENGN_TRIG_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_TRIG_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_RWMASK 0x0000003F
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_ROMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_OTHR_ENGN_TRIG_OFF 0x0000007C
#define EVT_CTRL_OTHR_ENGN_TRIG        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_TRIG_OFF))
#define EVT_CTRL_X_OTHR_ENGN_TRIG(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_TRIG_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_TRIG_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_TRIG_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_TRIG_RWMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_TRIG_ROMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_TRIG_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_FREE_OFF 0x00000084
#define EVT_CTRL_OTHR_ENGN_FREE        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_FREE_OFF))
#define EVT_CTRL_X_OTHR_ENGN_FREE(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_FREE_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_FREE_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_FREE_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_FREE_RWMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_FREE_ROMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_USBL_OFF 0x00000088
#define EVT_CTRL_OTHR_ENGN_USBL        (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_USBL_OFF))
#define EVT_CTRL_X_OTHR_ENGN_USBL(x)   (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_USBL_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_USBL_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_USBL_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_USBL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_USBL_RWMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_USBL_ROMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_USBL_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_USBL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_AVL_OFF 0x0000008C
#define EVT_CTRL_OTHR_ENGN_AVL         (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_AVL_OFF))
#define EVT_CTRL_X_OTHR_ENGN_AVL(x)    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_AVL_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_AVL_RWMASK  0x00000000
#define EVT_CTRL_OTHR_ENGN_AVL_ROMASK  0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_AVL_WOMASK  0x00000000
#define EVT_CTRL_OTHR_ENGN_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OFF 0x00000090
#define EVT_CTRL_OTHR_ENGN_BUF_AVL     (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_BUF_AVL_OFF))
#define EVT_CTRL_X_OTHR_ENGN_BUF_AVL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_BUF_AVL_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_BUF_AVL_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_BITFIELD_MASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_RWMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_ROMASK 0xFFFFFFFF
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_UNUSED_MASK 0x00000000

/* 0 */
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OFF 0x00000080
#define EVT_CTRL_OTHR_ENGN_FREE_ENC    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR_ENGN_FREE_ENC_OFF))
#define EVT_CTRL_X_OTHR_ENGN_FREE_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR_ENGN_FREE_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR_ENGN_FREE_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_VOLATILE 0x0
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_RWMASK 0x0000003F
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_ROMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_WOMASK 0x00000000
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_OFF 0x00000008
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC  (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUS_CNTR_CLREVT_ENC_OFF))
#define EVT_CTRL_X_IPUS_CNTR_CLREVT_ENC(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUS_CNTR_CLREVT_ENC_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_RESET_VALUE 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_VOLATILE 0x0
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_BITFIELD_MASK 0x0000003F
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_RWMASK 0x0000003F
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_ROMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_WOMASK 0x00000000
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_UNUSED_MASK 0xFFFFFFC0

/* 0 */
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_OFF 0x00000038
#define EVT_CTRL_IPUV_CNTR_MAX_VAL     (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_IPUV_CNTR_MAX_VAL_OFF))
#define EVT_CTRL_X_IPUV_CNTR_MAX_VAL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_IPUV_CNTR_MAX_VAL_OFF + ((x)*0x0)))

#define EVT_CTRL_IPUV_CNTR_MAX_VAL_RESET_VALUE 0x00000001
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_VOLATILE 0x0
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_BITFIELD_MASK 0x0000000F
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_RWMASK 0x0000000F
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_ROMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_WOMASK 0x00000000
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_UNUSED_MASK 0xFFFFFFF0

/* 0 */
#define EVT_CTRL_SW_EVT_TRIG_OFF 0x00000098
#define EVT_CTRL_SW_EVT_TRIG           (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_SW_EVT_TRIG_OFF))
#define EVT_CTRL_X_SW_EVT_TRIG(x)      (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_SW_EVT_TRIG_OFF + ((x)*0x0)))

#define EVT_CTRL_SW_EVT_TRIG_RESET_VALUE 0x00000000
#define EVT_CTRL_SW_EVT_TRIG_VOLATILE  0x0
#define EVT_CTRL_SW_EVT_TRIG_BITFIELD_MASK 0x000000FF
#define EVT_CTRL_SW_EVT_TRIG_RWMASK    0x000000FF
#define EVT_CTRL_SW_EVT_TRIG_ROMASK    0x00000000
#define EVT_CTRL_SW_EVT_TRIG_WOMASK    0x00000000
#define EVT_CTRL_SW_EVT_TRIG_UNUSED_MASK 0xFFFFFF00

/* 0 */
#define EVT_CTRL_SW_EVT_CLR_DONE_OFF 0x0000009C
#define EVT_CTRL_SW_EVT_CLR_DONE       (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_SW_EVT_CLR_DONE_OFF))
#define EVT_CTRL_X_SW_EVT_CLR_DONE(x)  (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_SW_EVT_CLR_DONE_OFF + ((x)*0x0)))

#define EVT_CTRL_SW_EVT_CLR_DONE_RESET_VALUE 0x00000000
#define EVT_CTRL_SW_EVT_CLR_DONE_VOLATILE 0x0
#define EVT_CTRL_SW_EVT_CLR_DONE_BITFIELD_MASK 0x000100FF
#define EVT_CTRL_SW_EVT_CLR_DONE_RWMASK 0x00000000
#define EVT_CTRL_SW_EVT_CLR_DONE_ROMASK 0x00010000
#define EVT_CTRL_SW_EVT_CLR_DONE_WOMASK 0x000000FF
#define EVT_CTRL_SW_EVT_CLR_DONE_UNUSED_MASK 0xFFFEFF00

/* 0 */
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OFF 0x00000094
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL    (*(vuint32_t *) (EVT_CTRL_BASEADDRESS+EVT_CTRL_OTHR0_CNTR_MAX_VAL_OFF))
#define EVT_CTRL_X_OTHR0_CNTR_MAX_VAL(x) (*(vuint32_t *) (EVT_CTRL_BASEADDRESS  + EVT_CTRL_OTHR0_CNTR_MAX_VAL_OFF + ((x)*0x0)))

#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_RESET_VALUE 0x00000001
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_VOLATILE 0x0
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_BITFIELD_MASK 0x0000001F
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_RWMASK 0x0000001F
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_ROMASK 0x00000000
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_WOMASK 0x00000000
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_UNUSED_MASK 0xFFFFFFE0


/* Field definitions for DONE_ENGN_TYPE */

#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUS_ENGN_VALUE(x) (((x)&0x00000001)<<0)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUS_ENGN_BIT (0)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUS_ENGN ((1) << (EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUS_ENGN_BIT))

#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUV_ENGN_VALUE(x) (((x)&0x00000001)<<1)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUV_ENGN_BIT (1)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUV_ENGN ((1) << (EVT_CTRL_DONE_ENGN_TYPE_DONE_IPUV_ENGN_BIT))

#define EVT_CTRL_DONE_ENGN_TYPE_DONE_OTHR_ENGN_VALUE(x) (((x)&0x00000001)<<2)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_OTHR_ENGN_BIT (2)
#define EVT_CTRL_DONE_ENGN_TYPE_DONE_OTHR_ENGN ((1) << (EVT_CTRL_DONE_ENGN_TYPE_DONE_OTHR_ENGN_BIT))



/* Field definitions for IPUS_CNTR_MAX_VAL */

#define EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_VALUE(x) (((x)&0x0000000F)<<0)
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_MSB (3)
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_LSB (0)
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_MASK (0x0000000F)
#define EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL ((EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_MASK) << (EVT_CTRL_IPUS_CNTR_MAX_VAL_IPUS_CNTR_MAX_VAL_LSB))



/* Field definitions for IPUS_CNTR_CLREVT */

#define EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_MSB (31)
#define EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_LSB (0)
#define EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT ((EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_MASK) << (EVT_CTRL_IPUS_CNTR_CLREVT_IPUS_CNTR_CLREVT_LSB))



/* Field definitions for IPUS_CNTR_NXTEVT */

#define EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_MSB (5)
#define EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_LSB (0)
#define EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_MASK (0x0000003F)
#define EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT ((EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_MASK) << (EVT_CTRL_IPUS_CNTR_NXTEVT_IPUS_CNTR_NXTEVT_LSB))



/* Field definitions for IPUS_CNTR_ALLEVT */

#define EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_MSB (31)
#define EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_LSB (0)
#define EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT ((EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_MASK) << (EVT_CTRL_IPUS_CNTR_ALLEVT_IPUS_CNTR_ALLEVT_LSB))



/* Field definitions for IPUS_ENGN_TRIG_ENC */

#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_MSB (5)
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_LSB (0)
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC ((EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_MASK) << (EVT_CTRL_IPUS_ENGN_TRIG_ENC_IPUS_ENGN_TRIG_ENC_LSB))



/* Field definitions for IPUS_ENGN_TRIG */

#define EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_MSB (31)
#define EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_LSB (0)
#define EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG ((EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_MASK) << (EVT_CTRL_IPUS_ENGN_TRIG_IPUS_ENGN_TRIG_LSB))



/* Field definitions for IPUS_ENGN_FREE_ENC */

#define EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_MSB (5)
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_LSB (0)
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC ((EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_MASK) << (EVT_CTRL_IPUS_ENGN_FREE_ENC_IPUS_ENGN_FREE_ENC_LSB))



/* Field definitions for IPUS_ENGN_FREE */

#define EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_MSB (31)
#define EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_LSB (0)
#define EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE ((EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_MASK) << (EVT_CTRL_IPUS_ENGN_FREE_IPUS_ENGN_FREE_LSB))



/* Field definitions for IPUS_ENGN_USBL */

#define EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_MSB (31)
#define EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_LSB (0)
#define EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL ((EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_MASK) << (EVT_CTRL_IPUS_ENGN_USBL_IPUS_ENGN_USBL_LSB))



/* Field definitions for IPUS_ENGN_FF1 */

#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_MSB (5)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_LSB (0)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_MASK (0x0000003F)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL ((EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_MASK) << (EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_AVL_LSB))

#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_VALUE(x) (((x)&0x0000003F)<<16)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_MSB (21)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_LSB (16)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_MASK (0x0000003F)
#define EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL ((EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_MASK) << (EVT_CTRL_IPUS_ENGN_FF1_IPUS_ENGN_FF1_BUF_AVL_LSB))



/* Field definitions for IPUS_ENGN_AVL */

#define EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_MSB (31)
#define EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_LSB (0)
#define EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL ((EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_MASK) << (EVT_CTRL_IPUS_ENGN_AVL_IPUS_ENGN_AVL_LSB))



/* Field definitions for IPUS_ENGN_BUF_AVL */

#define EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_MSB (31)
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_LSB (0)
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL ((EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_MASK) << (EVT_CTRL_IPUS_ENGN_BUF_AVL_IPUS_ENGN_BUF_AVL_LSB))



/* Field definitions for IPUV_CNTR_CLREVT_ENC */

#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_MSB (5)
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_LSB (0)
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC ((EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_MASK) << (EVT_CTRL_IPUV_CNTR_CLREVT_ENC_IPUV_CNTR_CLREVT_ENC_LSB))



/* Field definitions for IPUV_CNTR_CLREVT */

#define EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_MSB (31)
#define EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_LSB (0)
#define EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT ((EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_MASK) << (EVT_CTRL_IPUV_CNTR_CLREVT_IPUV_CNTR_CLREVT_LSB))



/* Field definitions for IPUV_CNTR_NXTEVT */

#define EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_MSB (5)
#define EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_LSB (0)
#define EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_MASK (0x0000003F)
#define EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT ((EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_MASK) << (EVT_CTRL_IPUV_CNTR_NXTEVT_IPUV_CNTR_NXTEVT_LSB))



/* Field definitions for IPUV_CNTR_ALLEVT */

#define EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_MSB (31)
#define EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_LSB (0)
#define EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT ((EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_MASK) << (EVT_CTRL_IPUV_CNTR_ALLEVT_IPUV_CNTR_ALLEVT_LSB))



/* Field definitions for IPUV_ENGN_TRIG_ENC */

#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_MSB (5)
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_LSB (0)
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC ((EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_MASK) << (EVT_CTRL_IPUV_ENGN_TRIG_ENC_IPUV_ENGN_TRIG_ENC_LSB))



/* Field definitions for IPUV_ENGN_TRIG */

#define EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_MSB (31)
#define EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_LSB (0)
#define EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG ((EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_MASK) << (EVT_CTRL_IPUV_ENGN_TRIG_IPUV_ENGN_TRIG_LSB))



/* Field definitions for IPUV_ENGN_FREE_ENC */

#define EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_MSB (5)
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_LSB (0)
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC ((EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_MASK) << (EVT_CTRL_IPUV_ENGN_FREE_ENC_IPUV_ENGN_FREE_ENC_LSB))



/* Field definitions for IPUV_ENGN_FREE */

#define EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_MSB (31)
#define EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_LSB (0)
#define EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE ((EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_MASK) << (EVT_CTRL_IPUV_ENGN_FREE_IPUV_ENGN_FREE_LSB))



/* Field definitions for IPUV_ENGN_USBL */

#define EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_MSB (31)
#define EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_LSB (0)
#define EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL ((EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_MASK) << (EVT_CTRL_IPUV_ENGN_USBL_IPUV_ENGN_USBL_LSB))



/* Field definitions for IPUV_ENGN_FF1 */

#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_MSB (5)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_LSB (0)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_MASK (0x0000003F)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL ((EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_MASK) << (EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_AVL_LSB))

#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_VALUE(x) (((x)&0x0000003F)<<16)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_MSB (21)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_LSB (16)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_MASK (0x0000003F)
#define EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL ((EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_MASK) << (EVT_CTRL_IPUV_ENGN_FF1_IPUV_ENGN_FF1_BUF_AVL_LSB))



/* Field definitions for IPUV_ENGN_AVL */

#define EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_MSB (31)
#define EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_LSB (0)
#define EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL ((EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_MASK) << (EVT_CTRL_IPUV_ENGN_AVL_IPUV_ENGN_AVL_LSB))



/* Field definitions for IPUV_ENGN_BUF_AVL */

#define EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_MSB (31)
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_LSB (0)
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL ((EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_MASK) << (EVT_CTRL_IPUV_ENGN_BUF_AVL_IPUV_ENGN_BUF_AVL_LSB))



/* Field definitions for OTHR_CNTR_CLREVT_ENC */

#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_MSB (5)
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_LSB (0)
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_MASK (0x0000003F)
#define EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC ((EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_MASK) << (EVT_CTRL_OTHR_CNTR_CLREVT_ENC_OTHR_CNTR_CLREVT_ENC_LSB))



/* Field definitions for OTHR_CNTR_CLREVT */

#define EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_MSB (31)
#define EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_LSB (0)
#define EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT ((EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_MASK) << (EVT_CTRL_OTHR_CNTR_CLREVT_OTHR_CNTR_CLREVT_LSB))



/* Field definitions for OTHR_CNTR_ALLEVT */

#define EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_MSB (31)
#define EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_LSB (0)
#define EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT ((EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_MASK) << (EVT_CTRL_OTHR_CNTR_ALLEVT_OTHR_CNTR_ALLEVT_LSB))



/* Field definitions for OTHR_ENGN_TRIG_ENC */

#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_MSB (5)
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_LSB (0)
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_MASK (0x0000003F)
#define EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC ((EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_MASK) << (EVT_CTRL_OTHR_ENGN_TRIG_ENC_OTHR_ENGN_TRIG_ENC_LSB))



/* Field definitions for OTHR_ENGN_TRIG */

#define EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_MSB (31)
#define EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_LSB (0)
#define EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG ((EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_MASK) << (EVT_CTRL_OTHR_ENGN_TRIG_OTHR_ENGN_TRIG_LSB))



/* Field definitions for OTHR_ENGN_FREE */

#define EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_MSB (31)
#define EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_LSB (0)
#define EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE ((EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_MASK) << (EVT_CTRL_OTHR_ENGN_FREE_OTHR_ENGN_FREE_LSB))



/* Field definitions for OTHR_ENGN_USBL */

#define EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_MSB (31)
#define EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_LSB (0)
#define EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL ((EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_MASK) << (EVT_CTRL_OTHR_ENGN_USBL_OTHR_ENGN_USBL_LSB))



/* Field definitions for OTHR_ENGN_AVL */

#define EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_MSB (31)
#define EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_LSB (0)
#define EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL ((EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_MASK) << (EVT_CTRL_OTHR_ENGN_AVL_OTHR_ENGN_AVL_LSB))



/* Field definitions for OTHR_ENGN_BUF_AVL */

#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_MSB (31)
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_LSB (0)
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_MASK (0xFFFFFFFF)
#define EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL ((EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_MASK) << (EVT_CTRL_OTHR_ENGN_BUF_AVL_OTHR_ENGN_BUF_AVL_LSB))



/* Field definitions for OTHR_ENGN_FREE_ENC */

#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_MSB (5)
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_LSB (0)
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_MASK (0x0000003F)
#define EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC ((EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_MASK) << (EVT_CTRL_OTHR_ENGN_FREE_ENC_OTHR_ENGN_FREE_ENC_LSB))



/* Field definitions for IPUS_CNTR_CLREVT_ENC */

#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_VALUE(x) (((x)&0x0000003F)<<0)
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_MSB (5)
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_LSB (0)
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_MASK (0x0000003F)
#define EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC ((EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_MASK) << (EVT_CTRL_IPUS_CNTR_CLREVT_ENC_IPUS_CNTR_CLREVT_ENC_LSB))



/* Field definitions for IPUV_CNTR_MAX_VAL */

#define EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_VALUE(x) (((x)&0x0000000F)<<0)
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_MSB (3)
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_LSB (0)
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_MASK (0x0000000F)
#define EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL ((EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_MASK) << (EVT_CTRL_IPUV_CNTR_MAX_VAL_IPUV_CNTR_MAX_VAL_LSB))



/* Field definitions for SW_EVT_TRIG */

#define EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_VALUE(x) (((x)&0x000000FF)<<0)
#define EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_MSB (7)
#define EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_LSB (0)
#define EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_MASK (0x000000FF)
#define EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG ((EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_MASK) << (EVT_CTRL_SW_EVT_TRIG_SW_EVT_TRIG_LSB))



/* Field definitions for SW_EVT_CLR_DONE */

#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_VALUE(x) (((x)&0x000000FF)<<0)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_MSB (7)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_LSB (0)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_MASK (0x000000FF)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR ((EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_MASK) << (EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_CLR_LSB))

#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_DONE_VALUE(x) (((x)&0x00000001)<<16)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_DONE_BIT (16)
#define EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_DONE ((1) << (EVT_CTRL_SW_EVT_CLR_DONE_SW_EVT_DONE_BIT))



/* Field definitions for OTHR0_CNTR_MAX_VAL */

#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_VALUE(x) (((x)&0x0000001F)<<0)
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_MSB (4)
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_LSB (0)
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_MASK (0x0000001F)
#define EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL ((EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_MASK) << (EVT_CTRL_OTHR0_CNTR_MAX_VAL_OTHR0_CNTR_MAX_VAL_LSB))




/*****************************************************************
*
* CTRL_BLK Registers
*
******************************************************************/




/* Instance CTRL_BLK */

#define CTRL_BLK_BASEADDRESS           0x40001000

/* Register definitions */

/* 0 */
#define CTRL_BLK_CLKRST_OFF 0x00000000
#define CTRL_BLK_CLKRST                (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_CLKRST_OFF))
#define CTRL_BLK_X_CLKRST(x)           (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_CLKRST_OFF + ((x)*0x0)))

#define CTRL_BLK_CLKRST_RESET_VALUE    0x00020002
#define CTRL_BLK_CLKRST_VOLATILE       0x0
#define CTRL_BLK_CLKRST_BITFIELD_MASK  0x00030003
#define CTRL_BLK_CLKRST_RWMASK         0x00020003
#define CTRL_BLK_CLKRST_ROMASK         0x00010000
#define CTRL_BLK_CLKRST_WOMASK         0x00000000
#define CTRL_BLK_CLKRST_UNUSED_MASK    0xFFFCFFFC

/* 0 */
#define CTRL_BLK_MSGCTRL_OFF 0x00000004
#define CTRL_BLK_MSGCTRL               (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_MSGCTRL_OFF))
#define CTRL_BLK_X_MSGCTRL(x)          (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_MSGCTRL_OFF + ((x)*0x0)))

#define CTRL_BLK_MSGCTRL_RESET_VALUE   0x00000000
#define CTRL_BLK_MSGCTRL_VOLATILE      0x0
#define CTRL_BLK_MSGCTRL_BITFIELD_MASK 0x00030003
#define CTRL_BLK_MSGCTRL_RWMASK        0x00000000
#define CTRL_BLK_MSGCTRL_ROMASK        0x00030003
#define CTRL_BLK_MSGCTRL_WOMASK        0x00000000
#define CTRL_BLK_MSGCTRL_UNUSED_MASK   0xFFFCFFFC

/* 0 */
#define CTRL_BLK_OUTMSG_ADDR_OFF 0x00000008
#define CTRL_BLK_OUTMSG_ADDR           (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_OUTMSG_ADDR_OFF))
#define CTRL_BLK_X_OUTMSG_ADDR(x)      (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_OUTMSG_ADDR_OFF + ((x)*0x0)))

#define CTRL_BLK_OUTMSG_ADDR_RESET_VALUE 0x00000000
#define CTRL_BLK_OUTMSG_ADDR_VOLATILE  0x0
#define CTRL_BLK_OUTMSG_ADDR_BITFIELD_MASK 0xFFFFFFFF
#define CTRL_BLK_OUTMSG_ADDR_RWMASK    0xFFFFFFFF
#define CTRL_BLK_OUTMSG_ADDR_ROMASK    0x00000000
#define CTRL_BLK_OUTMSG_ADDR_WOMASK    0x00000000
#define CTRL_BLK_OUTMSG_ADDR_UNUSED_MASK 0x00000000

/* 0 */
#define CTRL_BLK_OUTMSG_LEN_OFF 0x0000000C
#define CTRL_BLK_OUTMSG_LEN            (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_OUTMSG_LEN_OFF))
#define CTRL_BLK_X_OUTMSG_LEN(x)       (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_OUTMSG_LEN_OFF + ((x)*0x0)))

#define CTRL_BLK_OUTMSG_LEN_RESET_VALUE 0x00000000
#define CTRL_BLK_OUTMSG_LEN_VOLATILE   0x0
#define CTRL_BLK_OUTMSG_LEN_BITFIELD_MASK 0x00000FFF
#define CTRL_BLK_OUTMSG_LEN_RWMASK     0x00000FFF
#define CTRL_BLK_OUTMSG_LEN_ROMASK     0x00000000
#define CTRL_BLK_OUTMSG_LEN_WOMASK     0x00000000
#define CTRL_BLK_OUTMSG_LEN_UNUSED_MASK 0xFFFFF000

/* 0 */
#define CTRL_BLK_INMSG_ADDR_OFF 0x00000010
#define CTRL_BLK_INMSG_ADDR            (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_INMSG_ADDR_OFF))
#define CTRL_BLK_X_INMSG_ADDR(x)       (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_INMSG_ADDR_OFF + ((x)*0x0)))

#define CTRL_BLK_INMSG_ADDR_RESET_VALUE 0x00000000
#define CTRL_BLK_INMSG_ADDR_VOLATILE   0x0
#define CTRL_BLK_INMSG_ADDR_BITFIELD_MASK 0xFFFFFFFF
#define CTRL_BLK_INMSG_ADDR_RWMASK     0xFFFFFFFF
#define CTRL_BLK_INMSG_ADDR_ROMASK     0x00000000
#define CTRL_BLK_INMSG_ADDR_WOMASK     0x00000000
#define CTRL_BLK_INMSG_ADDR_UNUSED_MASK 0x00000000

/* 0 */
#define CTRL_BLK_INMSG_LEN_OFF 0x00000014
#define CTRL_BLK_INMSG_LEN             (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_INMSG_LEN_OFF))
#define CTRL_BLK_X_INMSG_LEN(x)        (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_INMSG_LEN_OFF + ((x)*0x0)))

#define CTRL_BLK_INMSG_LEN_RESET_VALUE 0x00000000
#define CTRL_BLK_INMSG_LEN_VOLATILE    0x0
#define CTRL_BLK_INMSG_LEN_BITFIELD_MASK 0x00000FFF
#define CTRL_BLK_INMSG_LEN_RWMASK      0x00000FFF
#define CTRL_BLK_INMSG_LEN_ROMASK      0x00000000
#define CTRL_BLK_INMSG_LEN_WOMASK      0x00000000
#define CTRL_BLK_INMSG_LEN_UNUSED_MASK 0xFFFFF000

/* 0 */
#define CTRL_BLK_ERRSTAT_OFF 0x00000018
#define CTRL_BLK_ERRSTAT               (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_ERRSTAT_OFF))
#define CTRL_BLK_X_ERRSTAT(x)          (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_ERRSTAT_OFF + ((x)*0x0)))

#define CTRL_BLK_ERRSTAT_RESET_VALUE   0x00000000
#define CTRL_BLK_ERRSTAT_VOLATILE      0x0
#define CTRL_BLK_ERRSTAT_BITFIELD_MASK 0x00000003
#define CTRL_BLK_ERRSTAT_RWMASK        0x00000000
#define CTRL_BLK_ERRSTAT_ROMASK        0x00000003
#define CTRL_BLK_ERRSTAT_WOMASK        0x00000000
#define CTRL_BLK_ERRSTAT_UNUSED_MASK   0xFFFFFFFC

/* 0 */
#define CTRL_BLK_HOST_IRQ_EN_OFF 0x00000020
#define CTRL_BLK_HOST_IRQ_EN           (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_HOST_IRQ_EN_OFF))
#define CTRL_BLK_X_HOST_IRQ_EN(x)      (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_HOST_IRQ_EN_OFF + ((x)*0x0)))

#define CTRL_BLK_HOST_IRQ_EN_RESET_VALUE 0x00000000
#define CTRL_BLK_HOST_IRQ_EN_VOLATILE  0x0
#define CTRL_BLK_HOST_IRQ_EN_BITFIELD_MASK 0x00FF007F
#define CTRL_BLK_HOST_IRQ_EN_RWMASK    0x00FF007F
#define CTRL_BLK_HOST_IRQ_EN_ROMASK    0x00000000
#define CTRL_BLK_HOST_IRQ_EN_WOMASK    0x00000000
#define CTRL_BLK_HOST_IRQ_EN_UNUSED_MASK 0xFF00FF80

/* 0 */
#define CTRL_BLK_SEQ_CORE_IRQ_EN_OFF 0x0000001C
#define CTRL_BLK_SEQ_CORE_IRQ_EN       (*(vuint32_t *) (CTRL_BLK_BASEADDRESS+CTRL_BLK_SEQ_CORE_IRQ_EN_OFF))
#define CTRL_BLK_X_SEQ_CORE_IRQ_EN(x)  (*(vuint32_t *) (CTRL_BLK_BASEADDRESS  + CTRL_BLK_SEQ_CORE_IRQ_EN_OFF + ((x)*0x0)))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_RESET_VALUE 0x00000000
#define CTRL_BLK_SEQ_CORE_IRQ_EN_VOLATILE 0x0
#define CTRL_BLK_SEQ_CORE_IRQ_EN_BITFIELD_MASK 0x000001FF
#define CTRL_BLK_SEQ_CORE_IRQ_EN_RWMASK 0x000001FF
#define CTRL_BLK_SEQ_CORE_IRQ_EN_ROMASK 0x00000000
#define CTRL_BLK_SEQ_CORE_IRQ_EN_WOMASK 0x00000000
#define CTRL_BLK_SEQ_CORE_IRQ_EN_UNUSED_MASK 0xFFFFFE00


/* Field definitions for CLKRST */

#define CTRL_BLK_CLKRST_SEQ_INT_RESET_VALUE(x) (((x)&0x00000001)<<0)
#define CTRL_BLK_CLKRST_SEQ_INT_RESET_BIT (0)
#define CTRL_BLK_CLKRST_SEQ_INT_RESET  ((1) << (CTRL_BLK_CLKRST_SEQ_INT_RESET_BIT))

#define CTRL_BLK_CLKRST_CM0p_RESET_VALUE(x) (((x)&0x00000001)<<1)
#define CTRL_BLK_CLKRST_CM0p_RESET_BIT (1)
#define CTRL_BLK_CLKRST_CM0p_RESET     ((1) << (CTRL_BLK_CLKRST_CM0p_RESET_BIT))

#define CTRL_BLK_CLKRST_Reserved_VALUE(x) (((x)&0x00000001)<<16)
#define CTRL_BLK_CLKRST_Reserved_BIT   (16)
#define CTRL_BLK_CLKRST_Reserved       ((1) << (CTRL_BLK_CLKRST_Reserved_BIT))

#define CTRL_BLK_CLKRST_CM0p_CLK_EN_VALUE(x) (((x)&0x00000001)<<17)
#define CTRL_BLK_CLKRST_CM0p_CLK_EN_BIT (17)
#define CTRL_BLK_CLKRST_CM0p_CLK_EN    ((1) << (CTRL_BLK_CLKRST_CM0p_CLK_EN_BIT))



/* Field definitions for MSGCTRL */

#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_RDY_VALUE(x) (((x)&0x00000001)<<0)
#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_RDY_BIT (0)
#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_RDY ((1) << (CTRL_BLK_MSGCTRL_OUTBOUND_MSG_RDY_BIT))

#define CTRL_BLK_MSGCTRL_INBOUND_MSG_RDY_VALUE(x) (((x)&0x00000001)<<16)
#define CTRL_BLK_MSGCTRL_INBOUND_MSG_RDY_BIT (16)
#define CTRL_BLK_MSGCTRL_INBOUND_MSG_RDY ((1) << (CTRL_BLK_MSGCTRL_INBOUND_MSG_RDY_BIT))

#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_ACKED_VALUE(x) (((x)&0x00000001)<<1)
#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_ACKED_BIT (1)
#define CTRL_BLK_MSGCTRL_OUTBOUND_MSG_ACKED ((1) << (CTRL_BLK_MSGCTRL_OUTBOUND_MSG_ACKED_BIT))

#define CTRL_BLK_MSGCTRL_INBOUND_MSG_ACKED_VALUE(x) (((x)&0x00000001)<<17)
#define CTRL_BLK_MSGCTRL_INBOUND_MSG_ACKED_BIT (17)
#define CTRL_BLK_MSGCTRL_INBOUND_MSG_ACKED ((1) << (CTRL_BLK_MSGCTRL_INBOUND_MSG_ACKED_BIT))



/* Field definitions for OUTMSG_ADDR */

#define CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_MSB (31)
#define CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_LSB (0)
#define CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_MASK (0xFFFFFFFF)
#define CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR ((CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_MASK) << (CTRL_BLK_OUTMSG_ADDR_OUTBOUND_MSG_ADDR_LSB))



/* Field definitions for OUTMSG_LEN */

#define CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_VALUE(x) (((x)&0x00000FFF)<<0)
#define CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_MSB (11)
#define CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_LSB (0)
#define CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_MASK (0x00000FFF)
#define CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN ((CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_MASK) << (CTRL_BLK_OUTMSG_LEN_OUTBOUND_MSG_LEN_LSB))



/* Field definitions for INMSG_ADDR */

#define CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_MSB (31)
#define CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_LSB (0)
#define CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_MASK (0xFFFFFFFF)
#define CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR ((CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_MASK) << (CTRL_BLK_INMSG_ADDR_INBOUND_MSG_ADDR_LSB))



/* Field definitions for INMSG_LEN */

#define CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_VALUE(x) (((x)&0x00000FFF)<<0)
#define CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_MSB (11)
#define CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_LSB (0)
#define CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_MASK (0x00000FFF)
#define CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN ((CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_MASK) << (CTRL_BLK_INMSG_LEN_INBOUND_MSG_LEN_LSB))



/* Field definitions for ERRSTAT */

#define CTRL_BLK_ERRSTAT_OUTBOUND_MSG_CFG_ERR_VALUE(x) (((x)&0x00000001)<<0)
#define CTRL_BLK_ERRSTAT_OUTBOUND_MSG_CFG_ERR_BIT (0)
#define CTRL_BLK_ERRSTAT_OUTBOUND_MSG_CFG_ERR ((1) << (CTRL_BLK_ERRSTAT_OUTBOUND_MSG_CFG_ERR_BIT))

#define CTRL_BLK_ERRSTAT_INBOUND_MSG_CFG_ERR_VALUE(x) (((x)&0x00000001)<<1)
#define CTRL_BLK_ERRSTAT_INBOUND_MSG_CFG_ERR_BIT (1)
#define CTRL_BLK_ERRSTAT_INBOUND_MSG_CFG_ERR ((1) << (CTRL_BLK_ERRSTAT_INBOUND_MSG_CFG_ERR_BIT))



/* Field definitions for HOST_IRQ_EN */

#define CTRL_BLK_HOST_IRQ_EN_SEQ_INT_ERR_IRQ_EN_VALUE(x) (((x)&0x00000001)<<0)
#define CTRL_BLK_HOST_IRQ_EN_SEQ_INT_ERR_IRQ_EN_BIT (0)
#define CTRL_BLK_HOST_IRQ_EN_SEQ_INT_ERR_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_SEQ_INT_ERR_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_OUTMSG_RDY_IRQ_EN_VALUE(x) (((x)&0x00000001)<<2)
#define CTRL_BLK_HOST_IRQ_EN_OUTMSG_RDY_IRQ_EN_BIT (2)
#define CTRL_BLK_HOST_IRQ_EN_OUTMSG_RDY_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_OUTMSG_RDY_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<4)
#define CTRL_BLK_HOST_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_BIT (4)
#define CTRL_BLK_HOST_IRQ_EN_IPUS_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<5)
#define CTRL_BLK_HOST_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_BIT (5)
#define CTRL_BLK_HOST_IRQ_EN_IPUV_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<6)
#define CTRL_BLK_HOST_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_BIT (6)
#define CTRL_BLK_HOST_IRQ_EN_OTHR_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_VALUE(x) (((x)&0x000000FF)<<16)
#define CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_MSB (23)
#define CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_LSB (16)
#define CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_MASK (0x000000FF)
#define CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN ((CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_MASK) << (CTRL_BLK_HOST_IRQ_EN_SW_EVT_TRIG_EN_LSB))

#define CTRL_BLK_HOST_IRQ_EN_IDMA_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<1)
#define CTRL_BLK_HOST_IRQ_EN_IDMA_DONE_IRQ_EN_BIT (1)
#define CTRL_BLK_HOST_IRQ_EN_IDMA_DONE_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_IDMA_DONE_IRQ_EN_BIT))

#define CTRL_BLK_HOST_IRQ_EN_INMSG_ACK_IRQ_EN_VALUE(x) (((x)&0x00000001)<<3)
#define CTRL_BLK_HOST_IRQ_EN_INMSG_ACK_IRQ_EN_BIT (3)
#define CTRL_BLK_HOST_IRQ_EN_INMSG_ACK_IRQ_EN ((1) << (CTRL_BLK_HOST_IRQ_EN_INMSG_ACK_IRQ_EN_BIT))



/* Field definitions for SEQ_CORE_IRQ_EN */

#define CTRL_BLK_SEQ_CORE_IRQ_EN_SEQ_INT_ERR_IRQ_EN_VALUE(x) (((x)&0x00000001)<<0)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_SEQ_INT_ERR_IRQ_EN_BIT (0)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_SEQ_INT_ERR_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_SEQ_INT_ERR_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_INMSG_RDY_IRQ_EN_VALUE(x) (((x)&0x00000001)<<2)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_INMSG_RDY_IRQ_EN_BIT (2)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_INMSG_RDY_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_INMSG_RDY_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<4)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_BIT (4)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUS_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_IPUS_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<5)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_BIT (5)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IPUV_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_IPUV_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<6)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_BIT (6)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_OTHR_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_OTHR_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_IDMA_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<1)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IDMA_DONE_IRQ_EN_BIT (1)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_IDMA_DONE_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_IDMA_DONE_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_FDMA_ERR_IRQ_EN_VALUE(x) (((x)&0x00000001)<<8)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_FDMA_ERR_IRQ_EN_BIT (8)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_FDMA_ERR_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_FDMA_ERR_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_SW_EVT_DONE_IRQ_EN_VALUE(x) (((x)&0x00000001)<<7)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_SW_EVT_DONE_IRQ_EN_BIT (7)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_SW_EVT_DONE_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_SW_EVT_DONE_IRQ_EN_BIT))

#define CTRL_BLK_SEQ_CORE_IRQ_EN_OUTMSG_ACK_IRQ_EN_VALUE(x) (((x)&0x00000001)<<3)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_OUTMSG_ACK_IRQ_EN_BIT (3)
#define CTRL_BLK_SEQ_CORE_IRQ_EN_OUTMSG_ACK_IRQ_EN ((1) << (CTRL_BLK_SEQ_CORE_IRQ_EN_OUTMSG_ACK_IRQ_EN_BIT))




/*****************************************************************
*
* SEQ_INT_DMA Registers
*
******************************************************************/




/* Instance SEQ_INT_DMA */

#define SEQ_INT_DMA_BASEADDRESS        0x40004000

/* Register definitions */

/* 0 */
#define SEQ_INT_DMA_CTRL_STAT_OFF 0x0000000C
#define SEQ_INT_DMA_CTRL_STAT          (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS+SEQ_INT_DMA_CTRL_STAT_OFF))
#define SEQ_INT_DMA_X_CTRL_STAT(x)     (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS  + SEQ_INT_DMA_CTRL_STAT_OFF + ((x)*0x0)))

#define SEQ_INT_DMA_CTRL_STAT_RESET_VALUE 0x00000000
#define SEQ_INT_DMA_CTRL_STAT_VOLATILE 0x0
#define SEQ_INT_DMA_CTRL_STAT_BITFIELD_MASK 0x001F0001
#define SEQ_INT_DMA_CTRL_STAT_RWMASK   0x00000000
#define SEQ_INT_DMA_CTRL_STAT_ROMASK   0x001F0000
#define SEQ_INT_DMA_CTRL_STAT_WOMASK   0x00000001
#define SEQ_INT_DMA_CTRL_STAT_UNUSED_MASK 0xFFE0FFFE

/* 0 */
#define SEQ_INT_DMA_KRAM_ADDR_OFF 0x00000000
#define SEQ_INT_DMA_KRAM_ADDR          (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS+SEQ_INT_DMA_KRAM_ADDR_OFF))
#define SEQ_INT_DMA_X_KRAM_ADDR(x)     (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS  + SEQ_INT_DMA_KRAM_ADDR_OFF + ((x)*0x0)))

#define SEQ_INT_DMA_KRAM_ADDR_RESET_VALUE 0x00000000
#define SEQ_INT_DMA_KRAM_ADDR_VOLATILE 0x0
#define SEQ_INT_DMA_KRAM_ADDR_BITFIELD_MASK 0x00003FFF
#define SEQ_INT_DMA_KRAM_ADDR_RWMASK   0x00003FFF
#define SEQ_INT_DMA_KRAM_ADDR_ROMASK   0x00000000
#define SEQ_INT_DMA_KRAM_ADDR_WOMASK   0x00000000
#define SEQ_INT_DMA_KRAM_ADDR_UNUSED_MASK 0xFFFFC000

/* 0 */
#define SEQ_INT_DMA_TRANSFER_LEN_OFF 0x00000008
#define SEQ_INT_DMA_TRANSFER_LEN       (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS+SEQ_INT_DMA_TRANSFER_LEN_OFF))
#define SEQ_INT_DMA_X_TRANSFER_LEN(x)  (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS  + SEQ_INT_DMA_TRANSFER_LEN_OFF + ((x)*0x0)))

#define SEQ_INT_DMA_TRANSFER_LEN_RESET_VALUE 0x00000000
#define SEQ_INT_DMA_TRANSFER_LEN_VOLATILE 0x0
#define SEQ_INT_DMA_TRANSFER_LEN_BITFIELD_MASK 0xFFFFFFFF
#define SEQ_INT_DMA_TRANSFER_LEN_RWMASK 0xFFFFFFFF
#define SEQ_INT_DMA_TRANSFER_LEN_ROMASK 0x00000000
#define SEQ_INT_DMA_TRANSFER_LEN_WOMASK 0x00000000
#define SEQ_INT_DMA_TRANSFER_LEN_UNUSED_MASK 0x00000000

/* 0 */
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_OFF 0x00000004
#define SEQ_INT_DMA_TARGET_IPUx_ENGN   (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS+SEQ_INT_DMA_TARGET_IPUx_ENGN_OFF))
#define SEQ_INT_DMA_X_TARGET_IPUx_ENGN(x) (*(vuint32_t *) (SEQ_INT_DMA_BASEADDRESS  + SEQ_INT_DMA_TARGET_IPUx_ENGN_OFF + ((x)*0x0)))

#define SEQ_INT_DMA_TARGET_IPUx_ENGN_RESET_VALUE 0x00000000
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_VOLATILE 0x0
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_BITFIELD_MASK 0x003F003F
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_RWMASK 0x003F003F
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_ROMASK 0x00000000
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_WOMASK 0x00000000
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_UNUSED_MASK 0xFFC0FFC0


/* Field definitions for CTRL_STAT */

#define SEQ_INT_DMA_CTRL_STAT_START_VALUE(x) (((x)&0x00000001)<<0)
#define SEQ_INT_DMA_CTRL_STAT_START_BIT (0)
#define SEQ_INT_DMA_CTRL_STAT_START    ((1) << (SEQ_INT_DMA_CTRL_STAT_START_BIT))

#define SEQ_INT_DMA_CTRL_STAT_DMA_DONE_VALUE(x) (((x)&0x00000001)<<16)
#define SEQ_INT_DMA_CTRL_STAT_DMA_DONE_BIT (16)
#define SEQ_INT_DMA_CTRL_STAT_DMA_DONE ((1) << (SEQ_INT_DMA_CTRL_STAT_DMA_DONE_BIT))

#define SEQ_INT_DMA_CTRL_STAT_BUSY_VALUE(x) (((x)&0x00000001)<<17)
#define SEQ_INT_DMA_CTRL_STAT_BUSY_BIT (17)
#define SEQ_INT_DMA_CTRL_STAT_BUSY     ((1) << (SEQ_INT_DMA_CTRL_STAT_BUSY_BIT))

#define SEQ_INT_DMA_CTRL_STAT_DMA_CFG_ERR_VALUE(x) (((x)&0x00000001)<<18)
#define SEQ_INT_DMA_CTRL_STAT_DMA_CFG_ERR_BIT (18)
#define SEQ_INT_DMA_CTRL_STAT_DMA_CFG_ERR ((1) << (SEQ_INT_DMA_CTRL_STAT_DMA_CFG_ERR_BIT))

#define SEQ_INT_DMA_CTRL_STAT_BED_VALUE(x) (((x)&0x00000001)<<19)
#define SEQ_INT_DMA_CTRL_STAT_BED_BIT  (19)
#define SEQ_INT_DMA_CTRL_STAT_BED      ((1) << (SEQ_INT_DMA_CTRL_STAT_BED_BIT))

#define SEQ_INT_DMA_CTRL_STAT_BES_VALUE(x) (((x)&0x00000001)<<20)
#define SEQ_INT_DMA_CTRL_STAT_BES_BIT  (20)
#define SEQ_INT_DMA_CTRL_STAT_BES      ((1) << (SEQ_INT_DMA_CTRL_STAT_BES_BIT))



/* Field definitions for KRAM_ADDR */

#define SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_VALUE(x) (((x)&0x00003FFF)<<0)
#define SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_MSB (13)
#define SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_LSB (0)
#define SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_MASK (0x00003FFF)
#define SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR ((SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_MASK) << (SEQ_INT_DMA_KRAM_ADDR_KRAM_ADDR_LSB))



/* Field definitions for TRANSFER_LEN */

#define SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_VALUE(x) (((x)&0x00007FFF)<<0)
#define SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_MSB (14)
#define SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_LSB (0)
#define SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_MASK (0x00007FFF)
#define SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN ((SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_MASK) << (SEQ_INT_DMA_TRANSFER_LEN_TRANSFER_LEN_LSB))

#define SEQ_INT_DMA_TRANSFER_LEN_Reserved_VALUE(x) (((x)&0x0001FFFF)<<15)
#define SEQ_INT_DMA_TRANSFER_LEN_Reserved_MSB (31)
#define SEQ_INT_DMA_TRANSFER_LEN_Reserved_LSB (15)
#define SEQ_INT_DMA_TRANSFER_LEN_Reserved_MASK (0x0001FFFF)
#define SEQ_INT_DMA_TRANSFER_LEN_Reserved ((SEQ_INT_DMA_TRANSFER_LEN_Reserved_MASK) << (SEQ_INT_DMA_TRANSFER_LEN_Reserved_LSB))



/* Field definitions for TARGET_IPUx_ENGN */

#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_VALUE(x) (((x)&0x0000003F)<<0)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_MSB (5)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_LSB (0)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_MASK (0x0000003F)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN ((SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_MASK) << (SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUS_ENGN_LSB))

#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_VALUE(x) (((x)&0x0000003F)<<16)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_MSB (21)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_LSB (16)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_MASK (0x0000003F)
#define SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN ((SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_MASK) << (SEQ_INT_DMA_TARGET_IPUx_ENGN_TARGET_IPUV_ENGN_LSB))
