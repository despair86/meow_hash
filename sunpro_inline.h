/* We need these for SunPro C/C++ */
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#if defined(__i386__)
static __inline unsigned long long rdtsc(void)
{
	unsigned long long int x;
	asm volatile ("rdtsc" : "=A" (x));
	return x;
}
#elif defined(__x86_64__) || defined(__amd64__)
static __inline unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}
#endif
static __inline uint64_t rdtscp(void) {
	uint32_t lo, hi;
	asm volatile ("rdtscp"
	    : /* outputs */ "=a" (lo), "=d" (hi)
	    : /* no inputs */
#ifdef __i386__
	    : /* clobbers */ "%ecx");
#elif __amd64__ || __x86_64__
	    : /* clobbers */ "%rcx");
#endif
	return (uint64_t)lo | (((uint64_t)hi) << 32);
}
#endif
