def main():
    # x = int(input("What's x? "))
    # y = int(input("What's y? "))

    x = float(input("What's x? "))
    y = float(input("What's y? "))

    # int() or float() - must convert string to number so it doesn't concatenate input as strings (want to actually add them)
    # int = integer, another data type
    # float = floating point, i.e. allows decimals

    # round(number[, ndigits])
    # 1st object = number - positional parameter
    # generally [] in documentation = optional
    # [, ndigits] to specify digits to round to (by default, it rounds to nearest integer)

    z = round(x + y)

    print(z)
    #just round(x + y) = 1.2 + 3.4 = 5
    # ndigits = 1 → 1 decimal place
    # ndigits = 2 → 2 decimal places

    print(f"{z:,}") #prints , like 1,000 or 200,000

    # no limit in python on how high an int can go
    # there IS a limit in python on how high a floating point can go

    print(f"{z:.2f}") #specifies how many decimal places to print in f strings, not round()

    print("x squared is", square(x))

def square(n):
    return n * n
    # alternatives to n * n:cd cs50xs
    return n ** 2
    return pow(n, 2)

main()