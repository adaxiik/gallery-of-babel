#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gallery.h"

char *toBase(mpz_t number, const char *base)
{
    size_t size = mpz_sizeinbase(number, strlen(base));
    char *result = malloc(sizeof(char) * (size + 1));

    // https://github.com/pierremolinaro/omnibus-dev/blob/master/build/libpm/gmp/mpn-get_str.c
    // size_t mpn_get_str (unsigned char *str, int base, mp_ptr up, mp_size_t un)
    mpn_get_str((unsigned char *)result, strlen(base), number->_mp_d, number->_mp_size);

    // https://github.com/alisw/GMP/blob/master/mpz/get_str.c
    for (size_t i = 0; i < size; i++)
        result[i] = base[(int)result[i]];
    result[size] = '\0';
    return result;
}

void fromBase(mpz_t *result, char *number, const char *base)
{
    size_t size = strlen(number);
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(temp, 0);
    for (size_t i = 0; i < size; i++)
    {
        int index = strchr(base, number[i]) - base;
        mpz_mul_ui(temp, temp, strlen(base));
        mpz_add_ui(temp, temp, index);
    }
    mpz_set(*result, temp);
    mpz_clear(temp);
}


void ImageToPosition(mpz_t *result, Image *image, bool verbose)
{
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(temp, 0);

    for(uint32_t i = 0; i < image->width * image->height; i++)
    {
        if(verbose && i%(image->width * image->height / 100) == 0)
            printf("%d%%\n",(int)(100 * i / (image->width * image->height)));

        mpz_mul_ui(temp, temp, 4096);
        mpz_add_ui(temp, temp, PixelPosition(image->pixels[i]));
    }


    mpz_set(*result, temp);
    mpz_clear(temp);
}

Image* ImageFromPosition(mpz_t number, bool verbose , int image_size)
{
    Image *image = malloc(sizeof(Image));
    image->pixels = malloc(sizeof(Pixel) * image_size * image_size);
    image->width = image->height = image_size;

    for(uint32_t i = 0; i < image_size* image_size; i++)
    {
        if(verbose && i % (image_size * image_size / 100) == 0)
            printf("%d%%\n", (int)(100 * i / image_size / image_size));

        image->pixels[(image_size - i / image_size - 1) * image_size + (image_size - i % image_size - 1)] = PixelFromPosition(mpz_get_ui(number));
        mpz_div_ui(number, number, 4096);   
    }
    return image;
}

void SaveToTXT(const char* filename, char* str)
{
    FILE *file = fopen(filename, "w");
    if(file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", str);
    fclose(file);
}

char* LoadFromTXT(const char* filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(sizeof(char) * (size + 1));

    fread(content, size, 1, file);

    fclose(file);
    content[size] = '\0';
    return content;
}