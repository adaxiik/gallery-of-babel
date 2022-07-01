#pragma once
#include <stdint.h>
#include <string.h>
typedef struct
{
    char *value;
    uint32_t length;
} BigNumber;
typedef const char *Base;

BigNumber *BigNumber_new(uint32_t value, Base base);
void BigNumber_extendLength(BigNumber *self, uint32_t length, Base base);

void BigNumber_print(BigNumber *self);
void BigNumber_free(BigNumber **self);
BigNumber *BigNumber_add(BigNumber *self, BigNumber *other, Base base);
BigNumber *BigNumber_subtract(BigNumber *self, BigNumber *other, Base base);
BigNumber *BigNumber_multiply(BigNumber *self, BigNumber *other, Base base);
BigNumber *BigNumber_divide(BigNumber *self, BigNumber *other, Base base);

static inline uint32_t BigNumber_BaseToDecimal(char c, Base base)
{
    for (uint32_t i = 0; i < strlen(base); i++)
        if (base[i] == c)
            return i;

    return 0;
}