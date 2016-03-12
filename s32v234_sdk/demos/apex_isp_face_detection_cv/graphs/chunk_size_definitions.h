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
const int ACCUM_TILE_SIZE_X = 10; // otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 10;
#endif



#ifdef APEX2_EMULATE
extern const int VECT_TILE_SIZE_X;// need to be redefined, otherwise g++ linker complains
extern const int VECT_TILE_SIZE_Y;
#else
const int VECT_TILE_SIZE_X = 1;// need to be redefined, otherwise g++ linker complains
const int VECT_TILE_SIZE_Y = 1;
#endif

#endif