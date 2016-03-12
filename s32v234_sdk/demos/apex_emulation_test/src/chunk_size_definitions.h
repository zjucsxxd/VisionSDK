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

#ifndef CHUNK_SIZE_DEFINITIONS_H
#define CHUNK_SIZE_DEFINITIONS_H


#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
#else
const int ACCUM_TILE_SIZE_X = 8; // otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 8;
#endif



#ifdef APEX2_EMULATE
extern const int SAT_TILE_SIZE_X;
extern const int SAT_TILE_SIZE_Y;
#else
const int SAT_TILE_SIZE_X = 8; // otherwise g++ linker complains
const int SAT_TILE_SIZE_Y = 8;
#endif

#ifdef APEX2_EMULATE
extern const int VECT_TILE_WIDTH;// need to be redefined, otherwise g++ linker complains
extern const int VECT_TILE_HEIGHT;
#else
const int VECT_TILE_WIDTH = 8;// need to be redefined, otherwise g++ linker complains
const int VECT_TILE_HEIGHT = 2;
#endif


#ifdef APEX2_EMULATE
extern const int BOX_64_WIDTH ;
extern const int BOX_64_HEIGHT;
extern const int BOX_64_AREA;
extern const int BOX_SIZE;
extern const int BOX_AREA;

#else
extern const int BOX_64_WIDTH = ACCUM_TILE_SIZE_X;
extern const int BOX_64_HEIGHT = ACCUM_TILE_SIZE_Y;
extern const int BOX_64_AREA = BOX_64_WIDTH * BOX_64_HEIGHT;
#endif


#endif