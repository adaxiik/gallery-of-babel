#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>

BigNumber *BigNumber_new(uint32_t value, Base base)
{
    BigNumber *self = malloc(sizeof(BigNumber));
    uint32_t value_temp = value;
    uint32_t value_length = 0;
    while (value_temp > 0)
    {
        value_temp /= strlen(base);
        value_length++;
    }

    self->value = malloc(sizeof(char) * (value_length));
    self->length = value_length;

    value_temp = value;
    for (uint32_t i = 0; i < value_length; i++)
    {
        self->value[i] = base[value_temp % strlen(base)];
        value_temp /= strlen(base);
    }
    return self;
}

void BigNumber_free(BigNumber **self)
{
    free((*self)->value);
    free(*self);
    *self = NULL;
}

void BigNumber_print(BigNumber *self)
{
    for (uint32_t i = self->length; i > 0; i--)
        putchar(self->value[i - 1]);
    putchar('\n');
}

void BigNumber_extendLength(BigNumber *self, uint32_t length, Base base)
{
    if(self->length >= length)
        return;

    self->value = realloc(self->value, sizeof(char) * (length));
    for (uint32_t i = self->length; i < length; i++)
        self->value[i] = base[0];
    self->length = length;

}

BigNumber* BigNumber_add(BigNumber *self, BigNumber *other, Base base)
{
    BigNumber *result = BigNumber_new(0, base);
    uint32_t carry = 0;
    uint32_t i = 0;
    while (i < self->length || i < other->length)
    {
        uint32_t self_value = i < self->length ? BigNumber_BaseToDecimal(self->value[i], base) : 0;
        uint32_t other_value = i < other->length ? BigNumber_BaseToDecimal(other->value[i], base) : 0;
        uint32_t sum = self_value + other_value + carry;
        carry = sum / strlen(base);
        sum %= strlen(base);
        BigNumber_extendLength(result, i + 1, base);
        result->value[i] = base[sum];
        i++;
    }
    if (carry > 0)
    {
        BigNumber_extendLength(result, i + 1, base);
        result->value[i] = base[carry];
    }
    return result;
}