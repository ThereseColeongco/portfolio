def main():
    fraction = fuel()
    percentage = round(fraction * 100)

    if percentage <= 1:
        print("E")
    elif percentage >= 99:
        print("F")
    else:
        print(str(percentage) + "%")


def fuel():
    while True:
        try:
            x, y = input("Fraction: ").split("/")
            x = int(x)
            y = int(y)
            fuel = x / y
            if fuel <= 1:
                return fuel
        except (ValueError, ZeroDivisionError):
            pass

main()