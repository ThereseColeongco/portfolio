def main():
    number = input("Card number: ")

    first_two = number[:2]

    if checksum(number) == True:
        if first_two in ['34', '37'] and len(number) == 15:
            print("AMEX")
        elif first_two in ['51', '52', '53', '54', '55'] and len(number) == 16:
            print("MASTERCARD")
        elif len(number) in [13, 16] and number[:1] == '4':
            print("VISA")
    else:
        print("INVALID")


def checksum(card):
    s = ""
    x = 0
    for i in range(len(card)):
        if i % 2 == 0:
            s += str(int(card[i]) * 2)
    x = sum([int(d) for d in s])

    for j in reversed(range(len(card))):
        if j % 2 != 0:
            x += int(card[j])
    if x % 10 == 0:
        return True


main()