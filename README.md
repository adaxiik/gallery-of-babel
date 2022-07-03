# Gallery of Babel
Have you ever heard about Library of Babel ? 

`It's a short story by Argentine author and librarian Jorge Luis Borges (1899–1986), conceiving of a universe in the form of a vast library containing all possible 410-page books of a certain format and character set.`

` Though the vast majority of the books in this universe are pure gibberish, the library also must contain, somewhere, every coherent book ever written, or that might ever be written, and every possible permutation or slightly erroneous version of every one of those books. The narrator notes that the library must contain all useful information, including predictions of the future, biographies of any person, and translations of every book in all languages.`

[Wikipedia](https://en.wikipedia.org/wiki/Library_of_Babel)

..and I did something similar with the pictures.

The picture you drew when you were 5, your selfie, the test you're about to write... even the picture of your funeral... all the pictures are there... you just have to find them.

# So what's it actually doing?
It looks for the position of the image in all possible images, or it shows the image at a certain position

# Limitations
Even for black and white, 8x8 picture, there are 2^64 (18,446,744,073,709,551,616) of possible combinations.

.. that's a lot of combinations for such a small picture..

So I had to compromise, instead of using full rgb range (256^3), I'm only using 16^3 (16 colors for each channel, 4096 colors in total).

I also had to lower the resolution a lot, so with the default settings it only looks for 256x256 images (all images are scaled to 1:1 for simplicity).

This means that with the default settings, there are 4096^65536 possible images (don't worry.. that's around 3,2 * 10^236753 images.. for example, there are 'just' 10^82 atoms in observable universe).

# Usage
`./galleryofbabel -i <file> -o <file> [flags]`

for example:
`./galleryofbabel -i input.png -o output.txt`
or 
`./galleryofbabel -i input.txt -o output.png -v 1 -s 512 -b 10`
(way of 'conversion' is determined by input file extension)

# Examples
try 
`./galleryofbabel -i examples/example.txt -o output.png -v 1`
it should output 256x256 picture on that position


| flag | description |
| ---- | ----------- |
| -i | input file |
| -o | output file |
| -v | verbose mode, default: 0, {0,1}|
| -s | size of the image, default: 256, {2 to 8192}|
| -b | base of i/o number, default: 92, {2, 10, 92} |

note: to make the position shorter, it is converted to base 92.
``0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~` ``  

## Build 

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```
(or just `make` in root directory)

## Dependencies
- [libpng](http://www.libpng.org/pub/png/libpng.html)
- [gmp](https://gmplib.org/)
