#pragma once
#include <gmp.h>
#include "png_wrapper.h"


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
char *toBase(mpz_t number, const char *base);

void fromBase(mpz_t *result, char *number, const char *base);

void ImageToPosition(mpz_t *result, Image *image, bool verbose);

Image* ImageFromPosition(mpz_t number, bool verbose , int image_size);

void SaveToTXT(const char* filename, char* str);

char* LoadFromTXT(const char* filename);