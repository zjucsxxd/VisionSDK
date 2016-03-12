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
* FDMA Registers
*
******************************************************************/




/* Instance FDMA */

#define FDMA_BASEADDRESS               0x40020000

/* Register definitions */

/* 0 */
#define FDMA_XFR_REC_LIST_PTR_OFF 0x00000000
#define FDMA_XFR_REC_LIST_PTR          (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_REC_LIST_PTR_OFF))
#define FDMA_X_XFR_REC_LIST_PTR(x)     (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_REC_LIST_PTR_OFF + ((x)*0x0)))

#define FDMA_XFR_REC_LIST_PTR_RESET_VALUE 0x00000000
#define FDMA_XFR_REC_LIST_PTR_VOLATILE 0x0
#define FDMA_XFR_REC_LIST_PTR_BITFIELD_MASK 0xFFFFFFFF
#define FDMA_XFR_REC_LIST_PTR_RWMASK   0xFFFFFFFF
#define FDMA_XFR_REC_LIST_PTR_ROMASK   0x00000000
#define FDMA_XFR_REC_LIST_PTR_WOMASK   0x00000000
#define FDMA_XFR_REC_LIST_PTR_UNUSED_MASK 0x00000000

/* 0 */
#define FDMA_CALC_CRC_VAL_OFF 0x0000001C
#define FDMA_CALC_CRC_VAL              (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_CALC_CRC_VAL_OFF))
#define FDMA_X_CALC_CRC_VAL(x)         (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_CALC_CRC_VAL_OFF + ((x)*0x0)))

#define FDMA_CALC_CRC_VAL_RESET_VALUE  0x00000000
#define FDMA_CALC_CRC_VAL_VOLATILE     0x0
#define FDMA_CALC_CRC_VAL_BITFIELD_MASK 0xFFFFFFFF
#define FDMA_CALC_CRC_VAL_RWMASK       0x00000000
#define FDMA_CALC_CRC_VAL_ROMASK       0xFFFFFFFF
#define FDMA_CALC_CRC_VAL_WOMASK       0x00000000
#define FDMA_CALC_CRC_VAL_UNUSED_MASK  0x00000000

/* 0 */
#define FDMA_XFR_REC_CNT_OFF 0x00000004
#define FDMA_XFR_REC_CNT               (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_REC_CNT_OFF))
#define FDMA_X_XFR_REC_CNT(x)          (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_REC_CNT_OFF + ((x)*0x0)))

#define FDMA_XFR_REC_CNT_RESET_VALUE   0x00000000
#define FDMA_XFR_REC_CNT_VOLATILE      0x0
#define FDMA_XFR_REC_CNT_BITFIELD_MASK 0x0000007F
#define FDMA_XFR_REC_CNT_RWMASK        0x0000007F
#define FDMA_XFR_REC_CNT_ROMASK        0x00000000
#define FDMA_XFR_REC_CNT_WOMASK        0x00000000
#define FDMA_XFR_REC_CNT_UNUSED_MASK   0xFFFFFF80

/* 0 */
#define FDMA_XFR_LINE_NUM_OFF 0x0000000C
#define FDMA_XFR_LINE_NUM              (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_LINE_NUM_OFF))
#define FDMA_X_XFR_LINE_NUM(x)         (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_LINE_NUM_OFF + ((x)*0x0)))

#define FDMA_XFR_LINE_NUM_RESET_VALUE  0x00000000
#define FDMA_XFR_LINE_NUM_VOLATILE     0x0
#define FDMA_XFR_LINE_NUM_BITFIELD_MASK 0xFFFFFFFF
#define FDMA_XFR_LINE_NUM_RWMASK       0xFFFFFFFF
#define FDMA_XFR_LINE_NUM_ROMASK       0x00000000
#define FDMA_XFR_LINE_NUM_WOMASK       0x00000000
#define FDMA_XFR_LINE_NUM_UNUSED_MASK  0x00000000

/* 0 */
#define FDMA_LINE_INCR_OFF 0x00000010
#define FDMA_LINE_INCR                 (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_LINE_INCR_OFF))
#define FDMA_X_LINE_INCR(x)            (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_LINE_INCR_OFF + ((x)*0x0)))

#define FDMA_LINE_INCR_RESET_VALUE     0x00000000
#define FDMA_LINE_INCR_VOLATILE        0x0
#define FDMA_LINE_INCR_BITFIELD_MASK   0x00FF00FF
#define FDMA_LINE_INCR_RWMASK          0x00FF00FF
#define FDMA_LINE_INCR_ROMASK          0x00000000
#define FDMA_LINE_INCR_WOMASK          0x00000000
#define FDMA_LINE_INCR_UNUSED_MASK     0xFF00FF00

/* 0 */
#define FDMA_XFR_STAT_OFF 0x00000018
#define FDMA_XFR_STAT                  (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_STAT_OFF))
#define FDMA_X_XFR_STAT(x)             (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_STAT_OFF + ((x)*0x0)))

#define FDMA_XFR_STAT_RESET_VALUE      0x00000001
#define FDMA_XFR_STAT_VOLATILE         0x0
#define FDMA_XFR_STAT_BITFIELD_MASK    0xFF0101FF
#define FDMA_XFR_STAT_RWMASK           0x00000000
#define FDMA_XFR_STAT_ROMASK           0xFF0101FF
#define FDMA_XFR_STAT_WOMASK           0x00000000
#define FDMA_XFR_STAT_UNUSED_MASK      0x00FEFE00

/* 0 */
#define FDMA_CURR_SRAM_PTR_OFF 0x00000024
#define FDMA_CURR_SRAM_PTR             (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_CURR_SRAM_PTR_OFF))
#define FDMA_X_CURR_SRAM_PTR(x)        (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_CURR_SRAM_PTR_OFF + ((x)*0x0)))

#define FDMA_CURR_SRAM_PTR_RESET_VALUE 0x00000000
#define FDMA_CURR_SRAM_PTR_VOLATILE    0x0
#define FDMA_CURR_SRAM_PTR_BITFIELD_MASK 0xFFFFFFFF
#define FDMA_CURR_SRAM_PTR_RWMASK      0x00000000
#define FDMA_CURR_SRAM_PTR_ROMASK      0xFFFFFFFF
#define FDMA_CURR_SRAM_PTR_WOMASK      0x00000000
#define FDMA_CURR_SRAM_PTR_UNUSED_MASK 0x00000000

/* 0 */
#define FDMA_XFR_QUEUE_DEPTH_OFF 0x00000014
#define FDMA_XFR_QUEUE_DEPTH           (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_QUEUE_DEPTH_OFF))
#define FDMA_X_XFR_QUEUE_DEPTH(x)      (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_QUEUE_DEPTH_OFF + ((x)*0x0)))

#define FDMA_XFR_QUEUE_DEPTH_RESET_VALUE 0x00000010
#define FDMA_XFR_QUEUE_DEPTH_VOLATILE  0x0
#define FDMA_XFR_QUEUE_DEPTH_BITFIELD_MASK 0x0000001F
#define FDMA_XFR_QUEUE_DEPTH_RWMASK    0x0000001F
#define FDMA_XFR_QUEUE_DEPTH_ROMASK    0x00000000
#define FDMA_XFR_QUEUE_DEPTH_WOMASK    0x00000000
#define FDMA_XFR_QUEUE_DEPTH_UNUSED_MASK 0xFFFFFFE0

/* 0 */
#define FDMA_CURR_DDR_PTR_OFF 0x00000020
#define FDMA_CURR_DDR_PTR              (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_CURR_DDR_PTR_OFF))
#define FDMA_X_CURR_DDR_PTR(x)         (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_CURR_DDR_PTR_OFF + ((x)*0x0)))

#define FDMA_CURR_DDR_PTR_RESET_VALUE  0x00000000
#define FDMA_CURR_DDR_PTR_VOLATILE     0x0
#define FDMA_CURR_DDR_PTR_BITFIELD_MASK 0xFFFFFFFF
#define FDMA_CURR_DDR_PTR_RWMASK       0x00000000
#define FDMA_CURR_DDR_PTR_ROMASK       0xFFFFFFFF
#define FDMA_CURR_DDR_PTR_WOMASK       0x00000000
#define FDMA_CURR_DDR_PTR_UNUSED_MASK  0x00000000

/* 0 */
#define FDMA_XFR_REC_NUM_DONE_OFF 0x00000028
#define FDMA_XFR_REC_NUM_DONE          (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_REC_NUM_DONE_OFF))
#define FDMA_X_XFR_REC_NUM_DONE(x)     (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_REC_NUM_DONE_OFF + ((x)*0x0)))

#define FDMA_XFR_REC_NUM_DONE_RESET_VALUE 0x00000000
#define FDMA_XFR_REC_NUM_DONE_VOLATILE 0x0
#define FDMA_XFR_REC_NUM_DONE_BITFIELD_MASK 0x0000007F
#define FDMA_XFR_REC_NUM_DONE_RWMASK   0x00000000
#define FDMA_XFR_REC_NUM_DONE_ROMASK   0x0000007F
#define FDMA_XFR_REC_NUM_DONE_WOMASK   0x00000000
#define FDMA_XFR_REC_NUM_DONE_UNUSED_MASK 0xFFFFFF80

/* 0 */
#define FDMA_XFR_REC_NUM_OFF 0x00000008
#define FDMA_XFR_REC_NUM               (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_XFR_REC_NUM_OFF))
#define FDMA_X_XFR_REC_NUM(x)          (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_XFR_REC_NUM_OFF + ((x)*0x0)))

#define FDMA_XFR_REC_NUM_RESET_VALUE   0x00000000
#define FDMA_XFR_REC_NUM_VOLATILE      0x0
#define FDMA_XFR_REC_NUM_BITFIELD_MASK 0x0000007F
#define FDMA_XFR_REC_NUM_RWMASK        0x0000007F
#define FDMA_XFR_REC_NUM_ROMASK        0x00000000
#define FDMA_XFR_REC_NUM_WOMASK        0x00000000
#define FDMA_XFR_REC_NUM_UNUSED_MASK   0xFFFFFF80

/* 0 */
#define FDMA_SRAM_NEXT_LINE_OFF 0x00000030
#define FDMA_SRAM_NEXT_LINE            (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_SRAM_NEXT_LINE_OFF))
#define FDMA_X_SRAM_NEXT_LINE(x)       (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_SRAM_NEXT_LINE_OFF + ((x)*0x0)))

#define FDMA_SRAM_NEXT_LINE_RESET_VALUE 0x00000000
#define FDMA_SRAM_NEXT_LINE_VOLATILE   0x0
#define FDMA_SRAM_NEXT_LINE_BITFIELD_MASK 0x0000FFFF
#define FDMA_SRAM_NEXT_LINE_RWMASK     0x00000000
#define FDMA_SRAM_NEXT_LINE_ROMASK     0x0000FFFF
#define FDMA_SRAM_NEXT_LINE_WOMASK     0x00000000
#define FDMA_SRAM_NEXT_LINE_UNUSED_MASK 0xFFFF0000

/* 0 */
#define FDMA_ERR_XFR_REC_NUM_OFF 0x00000028
#define FDMA_ERR_XFR_REC_NUM           (*(vuint32_t *) (FDMA_BASEADDRESS+FDMA_ERR_XFR_REC_NUM_OFF))
#define FDMA_X_ERR_XFR_REC_NUM(x)      (*(vuint32_t *) (FDMA_BASEADDRESS  + FDMA_ERR_XFR_REC_NUM_OFF + ((x)*0x0)))

#define FDMA_ERR_XFR_REC_NUM_RESET_VALUE 0x00000000
#define FDMA_ERR_XFR_REC_NUM_VOLATILE  0x0
#define FDMA_ERR_XFR_REC_NUM_BITFIELD_MASK 0x0000007F
#define FDMA_ERR_XFR_REC_NUM_RWMASK    0x00000000
#define FDMA_ERR_XFR_REC_NUM_ROMASK    0x0000007F
#define FDMA_ERR_XFR_REC_NUM_WOMASK    0x00000000
#define FDMA_ERR_XFR_REC_NUM_UNUSED_MASK 0xFFFFFF80


/* Field definitions for XFR_REC_LIST_PTR */

#define FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_MSB (31)
#define FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_LSB (0)
#define FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_MASK (0xFFFFFFFF)
#define FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR ((FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_MASK) << (FDMA_XFR_REC_LIST_PTR_XFR_REC_LIST_PTR_LSB))



/* Field definitions for CALC_CRC_VAL */

#define FDMA_CALC_CRC_VAL_CALC_CRC_VAL_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define FDMA_CALC_CRC_VAL_CALC_CRC_VAL_MSB (31)
#define FDMA_CALC_CRC_VAL_CALC_CRC_VAL_LSB (0)
#define FDMA_CALC_CRC_VAL_CALC_CRC_VAL_MASK (0xFFFFFFFF)
#define FDMA_CALC_CRC_VAL_CALC_CRC_VAL ((FDMA_CALC_CRC_VAL_CALC_CRC_VAL_MASK) << (FDMA_CALC_CRC_VAL_CALC_CRC_VAL_LSB))



/* Field definitions for XFR_REC_CNT */

#define FDMA_XFR_REC_CNT_XFR_REC_CNT_VALUE(x) (((x)&0x0000007F)<<0)
#define FDMA_XFR_REC_CNT_XFR_REC_CNT_MSB (6)
#define FDMA_XFR_REC_CNT_XFR_REC_CNT_LSB (0)
#define FDMA_XFR_REC_CNT_XFR_REC_CNT_MASK (0x0000007F)
#define FDMA_XFR_REC_CNT_XFR_REC_CNT   ((FDMA_XFR_REC_CNT_XFR_REC_CNT_MASK) << (FDMA_XFR_REC_CNT_XFR_REC_CNT_LSB))



/* Field definitions for XFR_LINE_NUM */

#define FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_VALUE(x) (((x)&0x0000FFFF)<<0)
#define FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_MSB (15)
#define FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_LSB (0)
#define FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_MASK (0x0000FFFF)
#define FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM ((FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_MASK) << (FDMA_XFR_LINE_NUM_DDR_IMG_LINE_NUM_LSB))

#define FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_VALUE(x) (((x)&0x0000FFFF)<<16)
#define FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_MSB (31)
#define FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_LSB (16)
#define FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_MASK (0x0000FFFF)
#define FDMA_XFR_LINE_NUM_SRAM_LINE_NUM ((FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_MASK) << (FDMA_XFR_LINE_NUM_SRAM_LINE_NUM_LSB))



/* Field definitions for LINE_INCR */

#define FDMA_LINE_INCR_SRAM_LINE_INCR_VALUE(x) (((x)&0x000000FF)<<16)
#define FDMA_LINE_INCR_SRAM_LINE_INCR_MSB (23)
#define FDMA_LINE_INCR_SRAM_LINE_INCR_LSB (16)
#define FDMA_LINE_INCR_SRAM_LINE_INCR_MASK (0x000000FF)
#define FDMA_LINE_INCR_SRAM_LINE_INCR  ((FDMA_LINE_INCR_SRAM_LINE_INCR_MASK) << (FDMA_LINE_INCR_SRAM_LINE_INCR_LSB))

#define FDMA_LINE_INCR_DDR_LINE_INCR_VALUE(x) (((x)&0x000000FF)<<0)
#define FDMA_LINE_INCR_DDR_LINE_INCR_MSB (7)
#define FDMA_LINE_INCR_DDR_LINE_INCR_LSB (0)
#define FDMA_LINE_INCR_DDR_LINE_INCR_MASK (0x000000FF)
#define FDMA_LINE_INCR_DDR_LINE_INCR   ((FDMA_LINE_INCR_DDR_LINE_INCR_MASK) << (FDMA_LINE_INCR_DDR_LINE_INCR_LSB))



/* Field definitions for XFR_STAT */

#define FDMA_XFR_STAT_XFR_QUEUE_EMPTY_VALUE(x) (((x)&0x00000001)<<0)
#define FDMA_XFR_STAT_XFR_QUEUE_EMPTY_BIT (0)
#define FDMA_XFR_STAT_XFR_QUEUE_EMPTY  ((1) << (FDMA_XFR_STAT_XFR_QUEUE_EMPTY_BIT))

#define FDMA_XFR_STAT_XFR_CMD_QUEUE_FULL_VALUE(x) (((x)&0x00000001)<<1)
#define FDMA_XFR_STAT_XFR_CMD_QUEUE_FULL_BIT (1)
#define FDMA_XFR_STAT_XFR_CMD_QUEUE_FULL ((1) << (FDMA_XFR_STAT_XFR_CMD_QUEUE_FULL_BIT))

#define FDMA_XFR_STAT_CMD_CFG_ERR_VALUE(x) (((x)&0x00000001)<<3)
#define FDMA_XFR_STAT_CMD_CFG_ERR_BIT  (3)
#define FDMA_XFR_STAT_CMD_CFG_ERR      ((1) << (FDMA_XFR_STAT_CMD_CFG_ERR_BIT))

#define FDMA_XFR_STAT_XFR_STP_ERR_TR_VALUE(x) (((x)&0x00000001)<<4)
#define FDMA_XFR_STAT_XFR_STP_ERR_TR_BIT (4)
#define FDMA_XFR_STAT_XFR_STP_ERR_TR   ((1) << (FDMA_XFR_STAT_XFR_STP_ERR_TR_BIT))

#define FDMA_XFR_STAT_CRC_ERR_VALUE(x) (((x)&0x00000001)<<2)
#define FDMA_XFR_STAT_CRC_ERR_BIT      (2)
#define FDMA_XFR_STAT_CRC_ERR          ((1) << (FDMA_XFR_STAT_CRC_ERR_BIT))

#define FDMA_XFR_STAT_DONE_CNT_VALUE(x) (((x)&0x000000FF)<<24)
#define FDMA_XFR_STAT_DONE_CNT_MSB     (31)
#define FDMA_XFR_STAT_DONE_CNT_LSB     (24)
#define FDMA_XFR_STAT_DONE_CNT_MASK    (0x000000FF)
#define FDMA_XFR_STAT_DONE_CNT         ((FDMA_XFR_STAT_DONE_CNT_MASK) << (FDMA_XFR_STAT_DONE_CNT_LSB))

#define FDMA_XFR_STAT_XFR_DONE_VALUE(x) (((x)&0x00000001)<<16)
#define FDMA_XFR_STAT_XFR_DONE_BIT     (16)
#define FDMA_XFR_STAT_XFR_DONE         ((1) << (FDMA_XFR_STAT_XFR_DONE_BIT))

#define FDMA_XFR_STAT_XFR_STP_ERR_CT_VALUE(x) (((x)&0x00000001)<<5)
#define FDMA_XFR_STAT_XFR_STP_ERR_CT_BIT (5)
#define FDMA_XFR_STAT_XFR_STP_ERR_CT   ((1) << (FDMA_XFR_STAT_XFR_STP_ERR_CT_BIT))

#define FDMA_XFR_STAT_XFR_CFG_ERR_VALUE(x) (((x)&0x00000001)<<6)
#define FDMA_XFR_STAT_XFR_CFG_ERR_BIT  (6)
#define FDMA_XFR_STAT_XFR_CFG_ERR      ((1) << (FDMA_XFR_STAT_XFR_CFG_ERR_BIT))

#define FDMA_XFR_STAT_XFR_ERR_DDR_VALUE(x) (((x)&0x00000001)<<7)
#define FDMA_XFR_STAT_XFR_ERR_DDR_BIT  (7)
#define FDMA_XFR_STAT_XFR_ERR_DDR      ((1) << (FDMA_XFR_STAT_XFR_ERR_DDR_BIT))

#define FDMA_XFR_STAT_XFR_ERR_SRAM_VALUE(x) (((x)&0x00000001)<<8)
#define FDMA_XFR_STAT_XFR_ERR_SRAM_BIT (8)
#define FDMA_XFR_STAT_XFR_ERR_SRAM     ((1) << (FDMA_XFR_STAT_XFR_ERR_SRAM_BIT))



/* Field definitions for CURR_SRAM_PTR */

#define FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_MSB (31)
#define FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_LSB (0)
#define FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_MASK (0xFFFFFFFF)
#define FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR ((FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_MASK) << (FDMA_CURR_SRAM_PTR_CURR_SRAM_PTR_LSB))



/* Field definitions for XFR_QUEUE_DEPTH */

#define FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_VALUE(x) (((x)&0x0000001F)<<0)
#define FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_MSB (4)
#define FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_LSB (0)
#define FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_MASK (0x0000001F)
#define FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH ((FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_MASK) << (FDMA_XFR_QUEUE_DEPTH_XFR_QUEUE_DEPTH_LSB))



/* Field definitions for CURR_DDR_PTR */

#define FDMA_CURR_DDR_PTR_CURR_DDR_PTR_VALUE(x) (((x)&0xFFFFFFFF)<<0)
#define FDMA_CURR_DDR_PTR_CURR_DDR_PTR_MSB (31)
#define FDMA_CURR_DDR_PTR_CURR_DDR_PTR_LSB (0)
#define FDMA_CURR_DDR_PTR_CURR_DDR_PTR_MASK (0xFFFFFFFF)
#define FDMA_CURR_DDR_PTR_CURR_DDR_PTR ((FDMA_CURR_DDR_PTR_CURR_DDR_PTR_MASK) << (FDMA_CURR_DDR_PTR_CURR_DDR_PTR_LSB))



/* Field definitions for XFR_REC_NUM_DONE */

#define FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_VALUE(x) (((x)&0x0000007F)<<0)
#define FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_MSB (6)
#define FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_LSB (0)
#define FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_MASK (0x0000007F)
#define FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE ((FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_MASK) << (FDMA_XFR_REC_NUM_DONE_XFR_REC_NUM_DONE_LSB))



/* Field definitions for XFR_REC_NUM */

#define FDMA_XFR_REC_NUM_XFR_REC_NUM_VALUE(x) (((x)&0x0000007F)<<0)
#define FDMA_XFR_REC_NUM_XFR_REC_NUM_MSB (6)
#define FDMA_XFR_REC_NUM_XFR_REC_NUM_LSB (0)
#define FDMA_XFR_REC_NUM_XFR_REC_NUM_MASK (0x0000007F)
#define FDMA_XFR_REC_NUM_XFR_REC_NUM   ((FDMA_XFR_REC_NUM_XFR_REC_NUM_MASK) << (FDMA_XFR_REC_NUM_XFR_REC_NUM_LSB))



/* Field definitions for SRAM_NEXT_LINE */

#define FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_VALUE(x) (((x)&0x0000FFFF)<<0)
#define FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_MSB (15)
#define FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_LSB (0)
#define FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_MASK (0x0000FFFF)
#define FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM ((FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_MASK) << (FDMA_SRAM_NEXT_LINE_SRAM_NEXT_LINE_NUM_LSB))



/* Field definitions for ERR_XFR_REC_NUM */

#define FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_VALUE(x) (((x)&0x0000007F)<<0)
#define FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_MSB (6)
#define FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_LSB (0)
#define FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_MASK (0x0000007F)
#define FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM ((FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_MASK) << (FDMA_ERR_XFR_REC_NUM_ERR_XFR_REC_NUM_LSB))




