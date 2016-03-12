#ifndef AVUTIL_AVCONFIG_H
#define AVUTIL_AVCONFIG_H
#if defined(__BIG_ENDIAN__)
#define AV_HAVE_BIGENDIAN 1
#else
#define AV_HAVE_BIGENDIAN 0
#endif
#if defined(__i386__)
#define AV_HAVE_FAST_UNALIGNED 1
#else
#define AV_HAVE_FAST_UNALIGNED 0
#endif
#endif /* AVUTIL_AVCONFIG_H */
