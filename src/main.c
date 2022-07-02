#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png_wrapper.h"
// #include "big_number.h"
#include <gmp.h>

const char base_92[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`";
const char base_10[] = "0123456789";
const char base_2[] = "01";

#define IMAGE_SIZE 256.0
//#define PRINT_PROGRESS

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

inline static uint32_t PixelPosition(Pixel p)
{
    //return p.red * 256 * 256 + p.green * 256 + p.blue;
    return (p.red/16) *16*16 + (p.green/16) *16 + (p.blue/16);
}

inline static Pixel PixelFromPosition(uint32_t position)
{
    // Pixel p;
    // p.red = position / (256 * 256);
    // p.green = (position - p.red * 256 * 256) / 256;
    // p.blue = position - p.red * 256 * 256 - p.green * 256;
    // return p;
    Pixel p;
    p.red = (position / 16) ;
    p.green = (position - p.red * 16 * 16) ;
    p.blue = (position - p.red * 16 * 16 - p.green * 16)*16;
    return p;
}

void ImageToPosition(mpz_t *result, Image *image)
{
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(temp, 0);

    // for (uint32_t y = 0; y < image->height; y++)
    // {
    //     printf("%d/%d => %d%%\n", y, image->height, (int)(100 * y / image->height));
    //     for (uint32_t x = 0; x < image->width; x++)
    //     {
    //         mpz_mul_ui(temp, temp, 4096);
    //         mpz_add_ui(temp, temp, PixelPosition(image->pixels[y * image->width + x]));
    //     }
    // }

    for(uint32_t i = 0; i < image->width * image->height; i++)
    {
        #ifdef PRINT_PROGRESS
        if(i%(image->width * image->height / 100) == 0)
            printf("%d%%\n",(int)(100 * i / (image->width * image->height)));
        #endif
        mpz_mul_ui(temp, temp, 4096);
        mpz_add_ui(temp, temp, PixelPosition(image->pixels[i]));
    }


    mpz_set(*result, temp);
    mpz_clear(temp);
}

Image* ImageFromPosition(mpz_t number)
{
    Image *image = malloc(sizeof(Image));
    image->pixels = malloc(sizeof(Pixel) * IMAGE_SIZE * IMAGE_SIZE);
    image->width = IMAGE_SIZE;
    image->height = IMAGE_SIZE;
   
    // for (uint32_t y = 0; y < image->height; y++)
    // {
    //     printf("%d/%d => %d%%\n", y, image->height, (int)(100 * y / image->height));
    //     for (uint32_t x = 0; x < image->width; x++)
    //     {
    //         image->pixels[(image->height - y - 1) * image->width + (image->width - x - 1)] = PixelFromPosition(mpz_get_ui(number));
    //         mpz_div_ui(number, number, 4096);
    //     }
    // }
    for(uint32_t i = 0; i < image->width * image->height; i++)
    {
        #ifdef PRINT_PROGRESS
        if(i % (image->width * image->height / 100) == 0)
            printf("%d%%\n", (int)(100 * i / image->width / image->height));
        #endif
        
        image->pixels[(image->height - i / image->width - 1) * image->width + (image->width - i % image->width - 1)] = PixelFromPosition(mpz_get_ui(number));
        mpz_div_ui(number, number, 4096);   
    }
    return image;
}

void SaveToTXT(const char* filename, char* str)
{
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", str);
    fclose(file);
}

char* LoadFromTXT(const char* filename)
{
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(sizeof(char) * (size + 1));

    fread(content, 1, size, file);
    fclose(file);

    content[size] = '\0';
    return content;
}

int main(void)
{
    // printf("Base %ld\n", strlen(base));

    // mpz_t a, b;
    // mpz_init(a);
    // mpz_init(b);
    // mpz_set_str(a, "16777216", 10);
    // mpz_pow_ui(b, a, 512*512);

    // mpz_out_str(stdout, 10, b);

    // printf("\n===\n");
    // char *result = toBase(b, base_92);
    // printf("%ld\n", strlen(result));
    // mpz_t c;
    // mpz_init(c);
    // fromBase(&c, result, base_92);
    // mpz_out_str(stdout, 10, c);
    // printf("\n");

    // printf("%s\n", result);
    //  free(result);

    // mpz_clear(a);
    // mpz_clear(b);
    Image *image = ReadPNG("brm.png");

    printf("%dx%d\n", image->width, image->height);
    image = ScaleXY(image, IMAGE_SIZE / image->width, IMAGE_SIZE / image->height);
    printf("%dx%d\n", image->width, image->height);

    mpz_t position;
    mpz_init(position);
    ImageToPosition(&position, image);

    Image *image2 = ImageFromPosition(position);
    WritePNG("brm2.png", image2);

    DestroyImage(&image);
    DestroyImage(&image2);

    return 0;
}
