/******************************************************************************
* ihevc_cpu.c
* usage: use to detect cpuid for x86
* code come from x264
* 2016/12/13
* 
******************************************************************************/
#ifndef _IHEVC_CPU_H_
#define _IHEVC_CPU_H_
#if defined(__i386__) || defined(__x86_64__) || defined(_MSC_VER)
#include <string.h>
#include <stdint.h>

#ifdef __x86_64__
#    define OPSIZE "q"
#    define REG_a "rax"
#    define REG_b "rbx"
#    define REG_c "rcx"
#    define REG_d "rdx"
#    define REG_D "rdi"
#    define REG_S "rsi"
#    define PTR_SIZE "8"
#else
#    define OPSIZE "l"
#    define REG_a "eax"
#    define REG_b "ebx"
#    define REG_c "ecx"
#    define REG_d "edx"
#    define REG_D "edi"
#    define REG_S "esi"
#    define PTR_SIZE "4"
#endif

#define IHEVC_CPU_FLAG_FORCE    0x80000000 /* force usage of selected flags (OR) */

/* lower 16 bits - CPU features */
#define IHEVC_CPU_FLAG_MMX          0x0001 ///< standard MMX
#define IHEVC_CPU_FLAG_MMXEXT       0x0002 ///< SSE integer functions or AMD MMX ext
#define IHEVC_CPU_FLAG_MMX2         0x0002 ///< SSE integer functions or AMD MMX ext
#define IHEVC_CPU_FLAG_3DNOW        0x0004 ///< AMD 3DNOW
#define IHEVC_CPU_FLAG_SSE          0x0008 ///< SSE functions
#define IHEVC_CPU_FLAG_SSE2         0x0010 ///< PIV SSE2 functions
#define IHEVC_CPU_FLAG_SSE2SLOW 0x40000000 ///< SSE2 supported, but usually not faster
///< than regular MMX/SSE (e.g. Core1)
#define IHEVC_CPU_FLAG_3DNOWEXT     0x0020 ///< AMD 3DNowExt
#define IHEVC_CPU_FLAG_SSE3         0x0040 ///< Prescott SSE3 functions
#define IHEVC_CPU_FLAG_SSE3SLOW 0x20000000 ///< SSE3 supported, but usually not faster
///< than regular MMX/SSE (e.g. Core1)
#define IHEVC_CPU_FLAG_SSSE3        0x0080 ///< Conroe SSSE3 functions
#define IHEVC_CPU_FLAG_ATOM     0x10000000 ///< Atom processor, some SSSE3 instructions are slower
#define IHEVC_CPU_FLAG_SSE4         0x0100 ///< Penryn SSE4.1 functions
#define IHEVC_CPU_FLAG_SSE42        0x0200 ///< Nehalem SSE4.2 functions
#define IHEVC_CPU_FLAG_AVX          0x4000 ///< AVX functions: requires OS support even if YMM registers aren't used
#define IHEVC_CPU_FLAG_AVXSLOW   0x8000000 ///< AVX supported, but slow when using YMM registers (e.g. Bulldozer)
#define IHEVC_CPU_FLAG_XOP          0x0400 ///< Bulldozer XOP functions
#define IHEVC_CPU_FLAG_FMA4         0x0800 ///< Bulldozer FMA4 functions
// #if LIBAVUTIL_VERSION_MAJOR <52
#define IHEVC_CPU_FLAG_CMOV      0x1001000 ///< supports cmov instruction
// #else
// #define AV_CPU_FLAG_CMOV         0x1000 ///< supports cmov instruction
// #endif
#define IHEVC_CPU_FLAG_AVX2         0x8000 ///< AVX2 functions: requires OS support even if YMM registers aren't used
#define IHEVC_CPU_FLAG_FMA3        0x10000 ///< Haswell FMA3 functions
#define IHEVC_CPU_FLAG_BMI1        0x20000 ///< Bit Manipulation Instruction Set 1
#define IHEVC_CPU_FLAG_BMI2        0x40000 ///< Bit Manipulation Instruction Set 2

#define IHEVC_CPU_FLAG_ALTIVEC      0x0001 ///< standard
#define IHEVC_CPU_FLAG_VSX          0x0002 ///< ISA 2.06
#define IHEVC_CPU_FLAG_POWER8       0x0004 ///< ISA 2.07

#define IHEVC_CPU_FLAG_ARMV5TE      (1 << 0)
#define IHEVC_CPU_FLAG_ARMV6        (1 << 1)
#define IHEVC_CPU_FLAG_ARMV6T2      (1 << 2)
#define IHEVC_CPU_FLAG_VFP          (1 << 3)
#define IHEVC_CPU_FLAG_VFPV3        (1 << 4)
#define IHEVC_CPU_FLAG_NEON         (1 << 5)
#define IHEVC_CPU_FLAG_ARMV8        (1 << 6)
#define IHEVC_CPU_FLAG_SETEND       (1 <<16)
                            
#define CPUEXT(flags, cpuext)       ((flags) & IHEVC_CPU_FLAG_ ## cpuext)

#define HAVE_AMD3DNOW(flags)    CPUEXT(flags, AMD3DNOW)
#define HAVE_AMD3DNOWEXT(flags) CPUEXT(flags, AMD3DNOWEXT)
#define HAVE_MMX(flags)         CPUEXT(flags, MMX)
#define HAVE_MMXEXT(flags)      CPUEXT(flags, MMXEXT)
#define HAVE_SSE(flags)         CPUEXT(flags, SSE)
#define HAVE_SSE2(flags)        CPUEXT(flags, SSE2)
#define HAVE_SSE2_FAST(flags)   CPUEXT(flags, SSE2)
#define HAVE_SSE2_SLOW(flags)   CPUEXT(flags, SSE2)
#define HAVE_SSE3(flags)        CPUEXT(flags, SSE3)
#define HAVE_SSE3_FAST(flags)   CPUEXT(flags, SSE3)
#define HAVE_SSE3_SLOW(flags)   CPUEXT(flags, SSE3)
#define HAVE_SSSE3(flags)       CPUEXT(flags, SSSE3)
#define HAVE_SSE4(flags)        CPUEXT(flags, SSE4)
#define HAVE_SSE42(flags)       CPUEXT(flags, SSE42)
#define HAVE_AVX(flags)         CPUEXT(flags, AVX)
#define HAVE_AVX_FAST(flags)    CPUEXT(flags, AVX)
#define HAVE_AVX_SLOW(flags)    CPUEXT(flags, AVX)
#define HAVE_XOP(flags)         CPUEXT(flags, XOP)
#define HAVE_FMA3(flags)        CPUEXT(flags, FMA3)
#define HAVE_FMA4(flags)        CPUEXT(flags, FMA4)
#define HAVE_AVX2(flags)        CPUEXT(flags, AVX2)

int ihevc_get_cpu_flags_x86(void);

#endif
#endif //_IHEVC_CPU_H_
