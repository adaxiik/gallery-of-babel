#!/usr/bin/env python3

base = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`"

def convert(inp, target):
    print("Converting to base %d" % len(target))
    print("Input length: %d" % len(str(inp)))

    out = []
    while inp > 0:
        out.append(target[inp % len(target)])
        inp //= len(target)
    # reverse the list
    # out.reverse()
    print("Output length: %d" % len(out))
    return ''.join(out)


#convert(8**(256*256), base)
print(convert(8**(65*65), base))
