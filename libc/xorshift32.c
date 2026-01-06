#include <stdint.h>

// 全局状态变量 (在多核环境下需要加锁，见第四阶段)
static uint32_t prng_state = 1;

// 初始化种子 (Seed)
void prng_seed(uint32_t seed) {
    if (seed == 0) { // Xorshift不能为0
        prng_state = 0xDEADBEEF; 
    } else {
        prng_state = seed;
    }
}

// 获取随机数
uint32_t prng_next(void) {
    uint32_t x = prng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    prng_state = x;
    return x;
}

int32_t prng_next_mod(int32_t min, int32_t max) {
    if(min > max) {
        int32_t temp = min;
        min = max;
        max = temp;
    }

    uint32_t range = max - min + 1;
    return (int32_t)(prng_next() % range) + min;
}