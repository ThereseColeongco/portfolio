from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# this code makes a left-aligned pyramid.
for j in reversed(range(height)):
    k = height - j
    print(" " * j + "#" * k + "  " + "#" * k)

'''
for both pyramids:
start w/ 8, you want to subtract 7 for the hash
start w/ 7, you want to subtract 6 for the hash
and so on.
'''