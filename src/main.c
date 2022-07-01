#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png_wrapper.h"
// #include "big_number.h"
#include <gmp.h>

const char base_92[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`";
const char base_10[] = "0123456789";
const char base_2[] = "01";


char *toBase(mpz_t number, const char* base)
{
    size_t size = mpz_sizeinbase(number, strlen(base));
    char *result = malloc(sizeof(char) * (size + 1));

    //https://github.com/pierremolinaro/omnibus-dev/blob/master/build/libpm/gmp/mpn-get_str.c
    //size_t mpn_get_str (unsigned char *str, int base, mp_ptr up, mp_size_t un)
    mpn_get_str((unsigned char*)result, strlen(base), number->_mp_d, number->_mp_size);

    // https://github.com/alisw/GMP/blob/master/mpz/get_str.c
    for (size_t i = 0; i < size; i++)
        result[i] = base[(int) result[i]];
    result[size] = 0;
    return result;
}

int main(void)
{
    // printf("Base %ld\n", strlen(base));

    // Image *image = ReadPNG("test.png");
    // printf("Image %ux%u\n", image->width, image->height);
    // DestroyImage(&image);
    // BigNumber *a = BigNumber_new(2, base_92);
    // BigNumber *b = BigNumber_new(256*256, base_10);

    // BigNumber_print(a);
    // BigNumber_print(b);

    // BigNumber *c = BigNumber_pow(a, 256*256, base_92);
    // //BigNumber *c = BigNumber_mul(a, b, base_10);
    // BigNumber_print(c);
    // BigNumber_free(&c);

    // BigNumber_free(&a);
    // BigNumber_free(&b);
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_set_str(a, "2", 10);
    mpz_pow_ui(b, a, 65536);

    char *result = toBase(b, base_92);
    printf("%s\n", result);
    free(result);

    mpz_clear(a);
    mpz_clear(b);

    return 0;
}
