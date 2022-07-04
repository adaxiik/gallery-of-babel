#pragma once
#include <gmp.h>
#include "png_wrapper.h"

typedef struct
{
    char *input_file;
    char *output_file;
    const char *base;
    int size;
    bool verbose;
} Arguments;

inline static const char *GetExt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

inline static uint32_t PixelPosition(Pixel p)
{
    // return p.red * 256 * 256 + p.green * 256 + p.blue;
    return (p.red / 16) * 16 * 16 + (p.green / 16) * 16 + (p.blue / 16);
}

inline static Pixel PixelFromPosition(uint32_t position)
{
    // Pixel p;
    // p.red = position / (256 * 256);
    // p.green = (position - p.red * 256 * 256) / 256;
    // p.blue = position - p.red * 256 * 256 - p.green * 256;
    // return p;
    Pixel p;
    p.red = (position / 16);
    p.green = (position - p.red * 16 * 16);
    p.blue = (position - p.red * 16 * 16 - p.green * 16) * 16;
    return p;
}

void FromNumber(Arguments *args);
void ToNumber(Arguments *args);