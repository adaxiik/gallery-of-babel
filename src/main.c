#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png_wrapper.h"
#include "big_number.h"
const char base_92[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`";
const char base_10[] = "0123456789";
const char base_2[] = "01";
int main(void)
{
    //printf("Base %ld\n", strlen(base));

    // Image *image = ReadPNG("test.png");
    // printf("Image %ux%u\n", image->width, image->height);
    // DestroyImage(&image);
    BigNumber *a = BigNumber_new(2, base_10);
    BigNumber *b = BigNumber_new(256*256, base_10);

    BigNumber_print(a);
    BigNumber_print(b);

    BigNumber *c = BigNumber_pow(a, 10000, base_10);
    //BigNumber *c = BigNumber_mul(a, b, base_10);
    BigNumber_print(c);
    BigNumber_free(&c);
    
    BigNumber_free(&a);
    BigNumber_free(&b);
    return 0;
}
