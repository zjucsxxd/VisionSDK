inline void neon_memcpy(char* dst, char* src, long size)
{
  long simd_pixels = size & ~15; 
  long simd_iterations = simd_pixels >> 4;
  
  char *dst_local = dst;
  char *src_local = src;
  if(simd_iterations)
  { 
    asm volatile( "1: \n\t"
		      "LD1 {V0.8H}, [%[src_local]], #16	\n\t"
			  "ST1 {V0.H}[0], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[1], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[2], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[3], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[4], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[5], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[6], [%[dst_local]], #2	\n\t"
			  "ST1 {V0.H}[7], [%[dst_local]], #2	\n\t"
			  "subs %[iterations],%[iterations],#1 \n\t"
		      "bne 1b \n\t"
		      : [src_local]"+r"(src_local), [dst_local] "+r"(dst_local), [iterations]"+r"(simd_iterations) 
		      : 
		      //: "memory", "d0" 
		   );
    }
}