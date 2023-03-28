# parity asks "odd or even?"

def main():
    x = int(input("Give me a number: "))
    if parity(x):
        print("Even")
    else:
        print("Odd")

def parity(n):
# this is good if it helps you and others understand your code,
# but not the most concise
    #if n % 2 == 0:
    #    return True #boolean is all you need for if/else
    #else:
    #    return False

#Pythonic describes ways of doing things, usually only available
#in python, that make ur code better designed
    #more concise:
    #return True if n % 2 == 0 else False

#not pythonic but even more concise:
    return n % 2 == 0

#if boolean expression itself (e.g. n % 2 == 0) has a true/false value/answer,
#why ask if or else? just return the value of boolean expression.

main()
# you can use string methods on your own functions
# if your function returns a string