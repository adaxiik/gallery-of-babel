#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <gmp.h>
#include "png_wrapper.h"
#include "gallery.h"

const char base_92[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`";
const char base_10[] = "0123456789";
const char base_2[] = "01";

typedef struct
{
    char *input_file;
    char *output_file;
    const char *base;
    int size;
    bool verbose;
} Arguments;

const char *GetExt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

void ToNumber(Arguments *args)
{
    Image *image = ReadPNG(args->input_file);
    if (args->verbose)
        printf("%s: %d x %d\n", args->input_file, image->width, image->height);

    mpz_t number;
    mpz_init(number);

    image = ScaleXY(image, (float)args->size / image->width, (float)args->size / image->height);
    ImageToPosition(&number, image, args->verbose);
    char *str = toBase(number, args->base);

    if (args->verbose)
        printf("Number length: %ld\n", strlen(str));

    SaveToTXT(args->output_file, str);

    free(str);
    mpz_clear(number);
    DestroyImage(&image);
}

void FromNumber(Arguments *args)
{
    if (args->verbose)
        printf("Reading number from file...\n");
    char *str = LoadFromTXT(args->input_file);
    mpz_t number;
    mpz_init(number);

    fromBase(&number, str, args->base);
    Image *image = ImageFromPosition(number, args->verbose, args->size);
    WritePNG(args->output_file, image);

    if (args->verbose)
        printf("File saved to %s\n", args->output_file);

    DestroyImage(&image);
    mpz_clear(number);
    free(str);
}

// ./galleryofbabel -i <file> -o <file> [-v (verbose, default: 0, {0,1})] [-s (size, default: 256)] [-b (base, default: 92, {2, 10, 92})]
void ParseArgs(int argc, char **argv)
{
    if (argc < 5)
        goto error;

    Arguments args = {.input_file = NULL, .output_file = NULL, .base = base_92, .size = 256, .verbose = false};

    for (int i = 1; i < argc - 1; i++)
    {
        for (size_t j = 0; j < strlen(argv[i]); j++)
            argv[i][j] = tolower(argv[i][j]);

        if (!strcmp(argv[i], "-i"))
            args.input_file = argv[i + 1];
        else if (!strcmp(argv[i], "-o"))
            args.output_file = argv[i + 1];
        else if (!strcmp(argv[i], "-v"))
        {
            args.verbose = atoi(argv[i + 1]);
        }
        else if (!strcmp(argv[i], "-s"))
        {
            args.size = atoi(argv[i + 1]);
            if (args.size < 2 || args.size > 8192)
                args.size = 256;
        }
        else if (!strcmp(argv[i], "-b"))
        {
            if (!strcmp(argv[i + 1], "2"))
                args.base = base_2;
            else if (!strcmp(argv[i + 1], "10"))
                args.base = base_10;
            else if (!strcmp(argv[i + 1], "92"))
                args.base = base_92;
            else
                goto error;
        }
    }
    if (!args.input_file || !args.output_file)
        goto error;

    if (args.verbose)
        printf("Input file: %s\nOutput file: %s\nSize: %d\n", args.input_file, args.output_file, args.size);

    if (!strcmp(GetExt(args.input_file), "png"))
        ToNumber(&args);
    else
        FromNumber(&args);

    return;
error:
    printf("Usage: %s -i <file> -o <file> [-v (verbose, default: 0, {0,1})] [-s (size, default: 256)] [-b (base, default: 92, {2, 10, 92})]\n", argv[0]);
    exit(1);
}

int main(int argc, char **argv)
{
    ParseArgs(argc, argv);
    return 0;
}
