#ifndef __MEMCPY_NEON__H__
#define __MEMCPY_NEON__H__

namespace neon
{
	void neon_memcpy(void* dst, void* src, long size);
	void neon_memcpy_1080to720(void* dst, void* src);
	void neon_memcpy_rotate_720to1080(void* dst, void* src);
	void neon_memcpy_720to1080(void* dst, void* src);
}

#endif