/* We need these for SunPro C/C++ */
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#if defined(__i386__)
static __inline unsigned long long rdtsc(void)
{
	unsigned long long int x;
	asm volatile ("rdtsc" : "=A" (x));
	return x;
}
#define CTR ecx
#elif defined(__x86_64__) || defined(__amd64__)
static __inline unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}
#define CTR rcx
#endif
static __inline uint64_t rdtscp(void) {
	uint32_t lo, hi;
	asm volatile ("rdtscp"
	    : /* outputs */ "=a" (lo), "=d" (hi)
	    : /* no inputs */
	    : /* clobbers */ "%CTR");
	return (uint64_t)lo | (((uint64_t)hi) << 32);
}
#endif
