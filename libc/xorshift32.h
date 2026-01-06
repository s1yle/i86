#ifndef XORSHIFT32_H
#define XORSHIFT32_H

void prng_seed(uint32_t seed);
uint32_t prng_next(void);
int32_t prng_next_mod(int32_t min, int32_t max);

#endif