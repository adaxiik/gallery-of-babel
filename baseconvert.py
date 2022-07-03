#!/usr/bin/env python3

base = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+={}[]|:;\"'<>,.?~`"
#base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

class BaseConverter:
    def __init__(self, base):
        self.base = base

    def convert(self, inp):

        out = []
        while inp > 0:
            out.append(self.base[inp % len(self.base)])
            inp //= len(self.base)
        # reverse the list
        out.reverse()
        return ''.join(out)

b = BaseConverter(base)
print(b.convert(4096**64))