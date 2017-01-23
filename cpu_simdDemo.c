/******************************************************************************
* cpu_simdDemo.c
* code come from x264
* usage: use to detect cpuid for x86
* 2016/12/13
*
*******************************************************************************/
#if defined(__i386__) || defined(__x86_64__) || defined(_MSC_VER)
#include "cpu_simd.h"

enum ARCHTYPE{
	ARCH_X86_NONE,
	ARCH_X86_GENERIC,
	ARCH_X86_SSSE3,
	ARCH_X86_SSE42,
	ARCH_X86_AVX2
};

void ihevcd_init_arch(void *pv_codec)
{
	codec_t *ps_codec = (codec_t *)pv_codec;
	int cpu_flags = ihevc_get_cpu_flags_x86();
	ARCHTYPE type = ARCH_X86_GENERIC;

	//printf("cpu_flags = %x\n", cpu_flags);

	if (!cpu_flags)
	{
		type = ARCH_X86_GENERIC;
	}

	else
	{
		if (HAVE_SSSE3(cpu_flags))
		{
			type = ARCH_X86_SSSE3;
		}

		if (HAVE_SSE42(cpu_flags))
		{
			type = ARCH_X86_SSE42;
		}

		if (HAVE_AVX2(cpu_flags))
		{
			type = ARCH_X86_AVX2;
		}

	}
}

#endif//defined(__i386__) || defined(__x86_64__)
