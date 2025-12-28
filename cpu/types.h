#ifndef TYPES_H
#define TYPES_H

#include "stdint.h"
#include "stddef.h"


/*
typedef unsigned int	u32;
typedef		 int	s32;
typedef	unsigned short	u16;
typedef		 short	s16;
typedef	unsigned char	u8;
typedef		 char	s8;
*/

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif
